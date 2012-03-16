package com.bedatadriven.egcs;

import java.io.File;
import java.lang.reflect.InvocationTargetException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;

import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;

public class CBuilderTest {

	private CBuilder compiler;
	
	@Before
	public void setUp() {
		this.compiler = new CBuilder();
		compiler.setCC1Path("/home/alexander/dev/egcs-jvm/egcs-1.1.2/gcc/cc1");
	}

	@Test
	public void helloWorld() throws Exception {
		File sourceDir = new File("src/test/c/helloworld");
		compiler.setSourceDir(sourceDir);
		compiler.setClassName("HelloWorld");
		compiler.build();
		
		runMain(sourceDir, "HelloWorld");

	}
	
	@Test
	public void multiFile() throws Exception {
		File sourceDir = new File("src/test/c/multifile");
		compiler.setSourceDir(sourceDir);
		compiler.setClassName("Multifile");
		compiler.build();
		
		runMain(sourceDir, "Multifile");
	}
	
	@Test
	public void myarray() throws Exception {
		File sourceDir = new File("src/test/c/myarray");
		compiler.setSourceDir(sourceDir);
		compiler.setClassName("MyArray");
		compiler.build();
		
		runMain(sourceDir, "MyArray");
	}

	@Test
	@Ignore("compiler fails :-(")
	public void floatingPoint() throws Exception {
		File sourceDir = new File("src/test/c/fp");
		compiler.setSourceDir(sourceDir);
		compiler.setClassName("FloatingPoint");
		compiler.build();
		
		runMain(sourceDir, "FloatingPoint");
	}
	

	private void runMain(File sourceDir, String className) throws MalformedURLException,
			ClassNotFoundException, IllegalAccessException,
			InvocationTargetException, NoSuchMethodException {
		URL[] urls = new URL[] { sourceDir.toURL() };
	    ClassLoader cl = new URLClassLoader(urls);
	    Class cls = cl.loadClass(className);
	    cls.getMethod("main", String[].class)
	    	.invoke(null, new Object[] { new String[0] });
	}
	
}
