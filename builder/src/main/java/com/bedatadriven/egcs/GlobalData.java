package com.bedatadriven.egcs;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.StringReader;
import java.util.List;

import com.google.common.annotations.VisibleForTesting;
import com.google.common.base.Charsets;
import com.google.common.collect.Lists;
import com.google.common.io.CharStreams;

public class GlobalData {
	
	public class Symbol {
		private String name;
		private byte[] data;
		
		public String getName() {
			return name;
		}
		
	}
	
	private List<Symbol> symbols = Lists.newArrayList();
	
	public GlobalData() {
		
	}
	
	public GlobalData(List<CompilationFragment> fragments) throws IOException {
		for(CompilationFragment fragment : fragments) {
			addOutput(fragment.getData());
		}
	}
	
	public void addOutput(String data) throws IOException {
		List<String> lines = CharStreams.readLines(new StringReader(data));
		Symbol lastSymbol = null; 
		for(String line : lines) {
			if(line.trim().startsWith(".")) {
				if(lastSymbol == null) {
					throw new EgcsException();
				}
				lastSymbol.data = toBytes(line.trim());
			} else {
				lastSymbol = parseSymbol(line);
				symbols.add(lastSymbol);
			}
		}
	}
	
	public List<Symbol> getSymbols() {
		return symbols;
	}

	private Symbol parseSymbol(String line) {
		int colon = line.indexOf(':');
		Symbol symbol = new Symbol();
		symbol.name = line.substring(0, colon);
		return symbol;
	}

	private byte[] toBytes(String line) {
		int space = line.indexOf(' ');
		if(space == -1) {
			throw new EgcsException("Cannot parse assembly output '" + line + "'");
		}
		String instruction = line.substring(0, space);
		if(instruction.equals(".ascii")) {
			return parseAsciiConstant(line);
		} else {
			throw new EgcsException("unimplemented assembly instruction '" + instruction + "'");
		}
	}

	//http://tigcc.ticalc.org/doc/gnuasm.html#SEC31
	@VisibleForTesting
	static byte[] parseAsciiConstant(String line) {
		String constant = line.substring(".ascii".length()).trim();
		if(constant.charAt(0) != '"' || constant.charAt(constant.length()-1) != '"') {
			throw new EgcsException("Malformed .ascii constant: '" + constant + "', expected constant to be enclosed in double quotes");
		}
		constant = constant.substring(1, constant.length()-1);
		StringBuilder sb = new StringBuilder();
		for(int i=0;i!=constant.length();++i) {
			char c = constant.charAt(i);
			if(c == '\\') {
				if(i+1 >= constant.length()) {
					throw new EgcsException("Malformed .ascii constant: " + line);
				}
				char next = constant.charAt(++i);
				if(next == 'b') {
					sb.append('\b');
				} else if(next == 'f') {
					sb.append('\f');
				} else if(next == 'n') {
					sb.append('\n');
				} else if(next == 'r') {
					sb.append('\r');
				} else if(next == 't') {
					sb.append('\t');
				} else if(Character.isDigit(next)) {
					StringBuilder number = new StringBuilder();
					number.append(next);
					
					while(i+1 < constant.length() && Character.isDigit(constant.charAt(i+1))) {
						number.append(constant.charAt(++i));
					}
					sb.appendCodePoint(Integer.parseInt(number.toString(), 8));
				} else if(next == 'x') {
					throw new UnsupportedOperationException();
				} else if(next == '"') {
					sb.append('"');
				} else if(next == '\\') {
					sb.append('\\');
				} else {
					throw new EgcsException("Unrecognized escape: \\" + next);
				}
			} else {
				sb.append(c);
			}
		}
		return sb.toString().getBytes(Charsets.US_ASCII);
	}

	public int totalSize() {
		int size = 0;
		for(Symbol symbol : symbols) {
			size += symbol.data.length;
		}
		return size;
	}
	
	public String substituteSymbolReferences(String source) {
		int offset = 0;
		for(Symbol symbol : symbols) {
			source = source.replace("symref" + symbol.name + "end",
					"sipush " + Integer.toString(4096 + offset));
			offset += symbol.data.length;
		}
		return source;
	}

	public void writeTo(File globalFile) throws IOException {
		DataOutputStream os = new DataOutputStream(new FileOutputStream(globalFile));
		os.writeInt(totalSize());
		for(Symbol symbol : symbols) {
			os.write(symbol.data);
		}
		os.close();
	}
}
