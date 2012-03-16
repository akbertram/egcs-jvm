package com.bedatadriven.egcs;

import java.io.IOException;
import java.nio.charset.Charset;

import org.junit.Test;

import com.google.common.base.Charsets;
import com.google.common.io.Resources;

import static org.junit.Assert.*;
import static org.hamcrest.CoreMatchers.*;


public class GlobalDataTest {

	
	@Test
	public void parseAscii() {
		byte[] bytes = GlobalData.parseAsciiConstant(".ascii \"blah %s\\12\\0\"");
		assertThat(new String(bytes), equalTo("blah %s\n\0"));
		assertThat(bytes.length, equalTo(9));
	}
	
	@Test
	public void parseData() throws IOException {
		GlobalData globalData = new GlobalData();
		globalData.addOutput(Resources.toString(getClass().getResource("global.s"), Charsets.US_ASCII));
		
		assertThat(globalData.getSymbols().size(), equalTo(2));
		assertThat(globalData.getSymbols().get(0).getName(), equalTo("File1LC0"));
		assertThat(globalData.getSymbols().get(1).getName(), equalTo("File2LC0"));
	}
}
