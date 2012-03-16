package com.bedatadriven.egcs.runtime;

import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;

/*  This is TranslatedFile.java.  This is the run time support system for
class files compiled with the EGCS JVM port.  TranslatedFile is
responsible for setting up memory for the class file and supplying
library functions.  

 - Trent Waddington 9/9/1999.
 */


public abstract class CObject {

	/* set this to true to get grotesque amounts of debugging info */
	boolean debug = false;

	/* The sub class program must supply us with a list of filenames
       that contain the memory that it wants us to load */
	public abstract String[] datanames();

	/* The sub class program must tell us how big these files are */
	public abstract int[] datasizes();

	/* The sub class program must tell us what the start addresses of
       these chunks of memory are */
	public abstract int[] datastarts();

	/* The sub class program must tell us what name it wants placed in
       argv[0] */
	public abstract String name();
	
	private PrintStream out = System.out;


	/* The sub class program must have a main method that takes two 
       integers (argc, argv) */
	public abstract void _main(int i,int j);

	// memory methods, these methods are only used internally now, but 
	// were previously called by the sub class program.

	public void memstorebyte(int location,int value) {
		if (debug)
			System.out.println("memstorebyte to " + location + " with value " + value);
		memory[location]=value&255;
	}

	public int memrefbyte(int location) { 
		return memory[location];
	}

	public void memstore(int i,int v) {
		if (debug)
			System.out.println("memstore to " + i + " with value " + v);
		memstorebyte(i,(v>>24));
		memstorebyte(i+1,((v>>16)&0xff));
		memstorebyte(i+2,((v>>8)&0xff));
		memstorebyte(i+3,(v&0xff));
	}

	public int memref(int i) { 
		boolean odebug=debug;
		if (debug) 
			debug=false;
		int j = memrefbyte(i)<<24;
		j|=memrefbyte(i+1)<<16;
		j|=memrefbyte(i+2)<<8;
		j|=memrefbyte(i+3);
		debug=odebug;
		if (debug)
			System.out.println("memref to " + i + " giving value " + j);
		return j;			
	}	

	/* The array of memory.. used by the sub class program */
	public int[] memory;

	/* This method loads in the various chunks of memory and places 
       them in the memory array at the relevant positions */
	public void InitMemory() {
		String[] names = datanames();
		int[] sizes = datasizes();
		int[] starts = datastarts();
		byte[] bmemory;

		int largest=0,j=0;
		if (names.length>0) {
			for (int i=0; i<starts.length; i++) 
				if (starts[i]>largest) { largest=starts[i]; j=i; }
			bmemory = new byte[largest+sizes[j]];
		} else {
			bmemory = new byte[4096+65536];
		}


		for (int i=0; i<names.length; i++) {
			try {
				FileInputStream f = new FileInputStream(names[i]);
				f.read(bmemory,starts[i],sizes[i]);
				f.close();
				if (debug) 
					System.out.println("loaded " + sizes[i] + " bytes from " + names[i] + " to address " + starts[i]);
			} catch (FileNotFoundException e) {
				//	System.err.println("cannot find " + names[i]);
			} catch (IOException e) {
				System.err.println("failed to read from " + names[i]);
			}
		}		

		try {
			String globalData = getClass().getSimpleName() + ".global";
			InputStream in = getClass().getResourceAsStream(globalData);
			if(in == null) {
				throw new RuntimeException("Could not find '" + globalData + "' on the classpath");
			}
			DataInputStream din = new DataInputStream(in);			
			int globalSize = din.readInt();
			din.readFully(bmemory,4096, globalSize);
			din.close();
			if (debug) {
				System.out.println("loaded " + globalSize + " bytes from global to address 4096");
			}
		} catch (IOException e) {
			System.err.println("failed to read from global");
		}
		memory = new int[bmemory.length];
		for (int i=0; i<bmemory.length; i++)
			memory[i]=bmemory[i]>=0?bmemory[i]:256+bmemory[i];

	}


	/* The sub class program receives execution from the JVM in its
       main(String[] args) method.  It then creates a single instance
       of itself and calls this method to setup the environment */
	public void Realmain(String[] args) {		
		if (debug) 
			System.out.println("Loading data files...");
		InitMemory();
		if (debug) 
			System.out.println("Setting up argv and argc...");
		int[] argoffs = new int[args.length+1];
		argoffs[0]=0;
		for (int i=0; i<name().getBytes().length; i++)
			memory[i]=name().getBytes()[i];
		if (debug)
			System.out.println("added string '" + name() + "' to stack at 0");
		int loc = name().length();
		memory[loc++]=0;
		for (int i=0; i<args.length; i++) {
			argoffs[i+1]=loc;
			for (int j=0; j<args[i].getBytes().length; j++)
				memory[j+loc]=args[i].getBytes()[j];
			if (debug)
				System.out.println("added string '" + args[i] + "' to stack at " + loc);
			loc+=args[i].length();
			memory[loc++]=0;			
		}
		int argv = loc;
		for (int i=0; i<argoffs.length; i++) {
			memstore(loc,argoffs[i]);
			loc+=4;
		}
		if (debug) 
			System.out.println("args taking up " + loc + " bytes at bottom of stack");		
		if (debug)
			System.out.println("Starting translated file.");		
		_main(args.length+1,argv);
		if (debug)
			System.out.println("Translated file terminated.");
	}
	
	public void setStandardOut(PrintStream out) {
		this.out = out;
	}

	// c library functions (wrappers to the java equivilent or simple implementations)
	// This is by no means complete, but it is enough to do simple
	// test programs

	public int _setlocale(int i, int j) {
		if (debug) 
			System.out.println("setlocale called with " + i + ", " + j + " : \"" + ((j==0)?"(null)":buildString(j)) + "\"");
		return 0;
	}

	public int _textdomain(int i) {
		if (debug)
			System.out.println("textdomain called with " + i + " : \"" + ((i==0)?"(null)":buildString(i)) + "\"");
		return i;
	}

	public int _gettext(int i) {
		if (debug) 
			System.out.println("gettext called with " + i + " : \"" + ((i==0)?"(null)":buildString(i)) + "\"");
		return i;
	}

	public int _exit(int i) {
		System.exit(i);
		return 0;
	}

	public int strlen(int str) {
		if (debug) 
			System.out.println("we have a strlen with " + str);
		int c = 0;
		while (memory[str++]!=0) c++;
		return c;
	}

	public int _strlen(int str) {
		return strlen(str);
	}

	public int strcpy(int str1, int str2) {
		if (debug) 
			System.out.println("we have a strcpy with " + str1 + " and " + str2);
		int c=str1;
		while (memory[str2]!=0) memory[str1++]=memory[str2++];
		return c;
	}

	public int _strcpy(int str1, int str2) {
		return strcpy(str1,str2);
	}	

	public int puts(int str) {
		if (debug)
			System.out.println("puts with " + str);
		System.out.println(buildString(str));
		return 0;		
	}	

	public int _puts(int str) {
		return puts(str);
	}

	public int memcpy(int dest, int src, int num) {
		for (int i=0; i<num; i++)
			memstorebyte(dest+i,memory[src+i]);
		return dest;
	}

	public int _memcpy(int dest, int src, int num) {
		if (debug)
			System.out.println("_memcpy from " + src + " to " + dest + " for " + num);
		for (int i=0; i<num; i++)
			memstorebyte(dest+i,memory[src+i]);
		return dest;
	}

	public String buildString(int str) {
		String s;
		byte[] b = new byte[strlen(str)];
		for (int i=0; i<b.length; i++)
			b[i]=(byte)memory[str+i];
		s = new String(b);
		if (debug)
			System.out.println("built string: " + s);
		return s;
	}

	public int _printf(String fmt, int arg1, int arg2) {
		int[] args = new int[2];
		args[0]=arg1; args[1]=arg2;
		return printf(fmt,args);	
	}

	public int _printf(String fmt, int arg1, int arg2, int arg3) {
		int[] args = new int[3];
		args[0]=arg1; args[1]=arg2; args[2]=arg3;
		return printf(fmt,args);	
	}

	public int _printf(int format) {
		int[] args = new int[0];
		return printf(buildString(format),args);
	}

	public int _printf(int format, int arg1) {
		int[] args = new int[1];
		args[0]=arg1;
		return printf(buildString(format),args);
	}

	public int _printf(int format, int arg1, int arg2) {
		int[] args = new int[2];
		args[0]=arg1; args[1]=arg2;
		return printf(buildString(format),args);
	}

	public int _printf(int format, int arg1, int arg2, int arg3) {
		int[] args = new int[3];
		args[0]=arg1; args[1]=arg2; args[2]=arg3;
		return printf(buildString(format),args);
	}

	public int _printf(int format, int arg1, int arg2, int arg3, int arg4) {
		int[] args = new int[4];
		args[0]=arg1; args[1]=arg2; args[2]=arg3; args[3]=arg4;
		return printf(buildString(format),args);
	}

	static String[] hexchars = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f" };

	public int printf(String fmt, int[] args) {
		if (debug) 
			System.out.println("Printf called with fmt string: " + fmt);
		int arg = 0;
		for (int i=0; i<fmt.length(); i++) {
			if (fmt.charAt(i)=='%') {
				switch(fmt.charAt(i+1)) {
				case 'd':
				case 'i':
					out.print(args[arg++]);
					break;
				case 'x':
					out.print(hexchars[(args[arg]>>28)&0x0f]);
					out.print(hexchars[(args[arg]>>24)&0x0f]);
					out.print(hexchars[(args[arg]>>20)&0x0f]);
					out.print(hexchars[(args[arg]>>16)&0x0f]);
					out.print(hexchars[(args[arg]>>12)&0x0f]);
					out.print(hexchars[(args[arg]>>8)&0x0f]);
					out.print(hexchars[(args[arg]>>4)&0x0f]);
					out.print(hexchars[args[arg++]&0x0f]);
					break;
				case 'c':
					out.print((char)args[arg++]);
					break;
				case 's':
					out.print(buildString(args[arg++]));
					break;
				case '%': out.print("%");
				}
				i++;
			} else out.print(""+fmt.charAt(i));			
		}
		return arg;
	}

	public int _scanf(int format, int arg1, int arg2, int arg3) {
		int[] args = new int[3];
		args[0]=arg1; args[1]=arg2; args[2]=arg3;
		return scanf(buildString(format),args);
	}

	public int _scanf(int format, int arg1, int arg2) {
		int[] args = new int[2];
		args[0]=arg1; args[1]=arg2; 
		return scanf(buildString(format),args);
	}

	public int _scanf(int format, int arg1) {
		int[] args = new int[1];
		args[0]=arg1;  
		return scanf(buildString(format),args);
	}

	public int scanf(String fmt, int[] args) {
		int arg = 0;
		try {
			for (int i=0; i<fmt.length(); i++) {
				if (fmt.charAt(i)=='%') {
					switch(fmt.charAt(i+1)) {
					case 'd':
					case 'i': {
						int ch;
						do 
							ch = System.in.read();
						while (ch<'0' || ch>'9');
						int v = 0;
						do { 
							v *= 10;
							v+=ch-'0';
							ch = System.in.read();
						} while (ch>='0' && ch<='9');
						memstore(args[arg],v);				
						arg++;
					}
					break;
					case 'c':
						memstorebyte(args[arg],System.in.read());
						arg++;	
						break;
					case 's': 
						System.out.println("eep.. I'm just panicing on a %s in a scanf");
						System.exit(0);
						break;
					}
					i++;				
				} 
			}		
		} catch (IOException e) {
		}
		return 0;
	}

}
