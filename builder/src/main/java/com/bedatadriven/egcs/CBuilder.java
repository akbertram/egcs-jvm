package com.bedatadriven.egcs;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.util.List;

import com.google.common.base.Charsets;
import com.google.common.base.Joiner;
import com.google.common.collect.Lists;
import com.google.common.io.ByteStreams;
import com.google.common.io.Files;
import com.google.common.io.Resources;

public class CBuilder {
		
	private static final Charset SOURCE_CHARSET = Charsets.UTF_8;
		
	private String cc1Path = "cc1";
	private String gccPath = "gcc";
	
	private String className;
	private File sourceDir;
	private File outDir;
		
	public void setSourceDir(File file) {
		this.sourceDir = file;
	}
	
	/**
	 * 
	 * @param path the path to the egcs-jvm cc1 binary
	 */
	public void setCC1Path(String path) {
		this.cc1Path = path;
	}
	
	/**
	 * 
	 * @param path the path to the normal gcc binary; used for preprocessing
	 * the C source files
	 */
	public void setGccPath(String path) {
		this.gccPath = path;
	}
	
	/**
	 * @param className the fully qualified name of the class to build. 
	 * For example, "HelloWorld" or "com/mycompany/MyClass"
	 */
	public void setClassName(String className) {
		this.className = className;
	}
	
	private String getSimpleClassName() {
		if(className == null) {
			throw new NullPointerException("className has not been set");
		}
		int slash = className.indexOf('/');
		if(slash == -1) {
			return className;
		} else {
			return className.substring(slash+1);
		}
	}
	
	private String getPackage() {
		if(className == null) {
			throw new NullPointerException("className has not been set");
		}
		int slash = className.indexOf('/');
		if(slash == -1) {
			return "";
		} else {
			return className.substring(0, slash);
		}
	}
	
	private File getOutDir() {
		return outDir == null ? sourceDir : outDir;
	}

	private File getPackageDir() {
		return new File(getOutDir() + File.separator + 
			className.replace('/', File.separatorChar));
	}
	
	/**
	 * Compiles the sources into a single JVM classfile
	 */
	public void build()  {
		
		List<File> sources = findSources();
		List<CompilationFragment> fragments = Lists.newArrayList();
		
		try {
			for(File srcFile : sources) {
				File intermediate = preprocess(srcFile);
				fragments.add(compileToJasmin(intermediate));
			}
			
			GlobalData globalData = new GlobalData(fragments);
			
			File globalFile = new File(sourceDir, getSimpleClassName() + ".global");
			globalData.writeTo(globalFile);
			
			File classSource = new File(sourceDir, "prog.j");
			Files.write(	
					link(fragments, globalData),
					classSource,
					SOURCE_CHARSET);
			
			jasmin.Main.main(new String[] { "-d", 
					getOutDir().getAbsolutePath(), 
					classSource.getAbsolutePath() 
					});
			
			
		} catch(EgcsException e) {
			throw e;
		} catch(Exception e) {
			throw new EgcsException("Compilation failed", e);
		}
	}

	private String link(List<CompilationFragment> fragments,
			GlobalData globalData) throws IOException {
		String template = loadTemplate();
		
		StringBuilder classSource = new StringBuilder(template);
		for(CompilationFragment fragment : fragments) {
			classSource.append( globalData.substituteSymbolReferences( fragment.getBody() ));
		}
		String source = classSource.toString();
		source = source.replace("Prog", className);
		return source;
	}
	
	private String loadTemplate() throws IOException {
		return Resources.toString(getClass().getResource("template.j"), SOURCE_CHARSET);
	}

	private List<File> findSources() {
		List<File> sourceFiles = Lists.newArrayList();
		for(File file : sourceDir.listFiles()) {
			if(file.getName().endsWith(".c")) {
				sourceFiles.add(file);
			}
		}
		return sourceFiles;
	}
	
	/**
	 * Preprocesses a C source file using normal gcc
	 * 
	 * @param sourceFile the C source file
	 * @return the File containing the intermediate output
	 * @throws InterruptedException 
	 * @throws IOException 
	 */
	File preprocess(File sourceFile) throws InterruptedException, IOException {
		File intermediate = replaceExtension(sourceFile, "i");
		exec(gccPath, "-E", "-DVERSION=\"java\"", sourceFile.getName(), "-o", intermediate.getName());

		return intermediate;
	}
	
	/**
	 * Compiles a C source to byte code
	 * 
	 * @param sourceFile the preprocessed C source file
	 * @return the File containing jasmin assembler file
	 * @throws InterruptedException 
	 * @throws IOException 
	 */
	CompilationFragment compileToJasmin(File sourceFile) throws InterruptedException, IOException {
		
		File globals = new File(sourceFile.getParentFile(), "global.s");
		File jasmin = replaceExtension(sourceFile, "j");

		if(globals.exists()) {
			globals.delete();
		}
				
		exec(cc1Path, 
				"-O8", "-fno-function-cse", sourceFile.getName(), 
				"-o", jasmin.getName());
		
		CompilationFragment fragment = new CompilationFragment();
		fragment.body = Files.toString(jasmin, SOURCE_CHARSET);
	
		if(globals.exists()) {
			fragment.globalData = Files.toString(globals, SOURCE_CHARSET);
		}
		
		return fragment;
	}

	private void exec(String command, String... arguments) {
		int exitCode;
		
		String commandLine = Joiner.on(" ").join(Lists.asList(command, arguments));

		try {		
			Process process = new ProcessBuilder()
			.directory(sourceDir)
			.command(Lists.asList(command, arguments))
			.redirectErrorStream(true)
			.start();
			
			CollectorThread collectorThread = new CollectorThread(process.getInputStream());
			collectorThread.start();
					

			exitCode = process.waitFor();
			if(exitCode != 0) {
				throw new EgcsException("Execution of '" + commandLine + " failed, code " + exitCode + 
						", output:\n " + collectorThread.toString());
			}
		
		} catch (InterruptedException e) {
			throw new EgcsException("Execution of '" + commandLine + " interrupted", e );
		} catch (Exception e) {
			throw new EgcsException("Exception thrown while executing of '" + commandLine, e );
		}

	}
	
	private File replaceExtension(File file, String extension) {
		File parent = file.getParentFile();
		String name = file.getName();
		int dot = name.lastIndexOf('.');
		return new File(parent, name.substring(0, dot+1) + extension);
	}
	
	private class CollectorThread extends Thread {
		private ByteArrayOutputStream boas = new ByteArrayOutputStream();
		private InputStream processOutput;
		
		public CollectorThread(InputStream processOutput) {
			super();
			this.processOutput = processOutput;
		}

		@Override
		public void run() {
			try {
				ByteStreams.copy(processOutput, boas);
			} catch (IOException e) {
			}
		}
		
		public String toString() {
			return new String(boas.toByteArray(), SOURCE_CHARSET);
		}
	}
}
