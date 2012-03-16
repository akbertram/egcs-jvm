package com.bedatadriven.egcs;

public class EgcsException extends RuntimeException {

	public EgcsException() {
		super();
	}

	public EgcsException(String arg0, Throwable arg1) {
		super(arg0, arg1);
	}

	public EgcsException(String arg0) {
		super(arg0);
	}

	public EgcsException(Throwable arg0) {
		super(arg0);
	}

}
