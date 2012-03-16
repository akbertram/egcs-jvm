#  GNU Objective C Runtime Makefile
#  Copyright (C) 1993, 1995, 1996, 1997 Free Software Foundation, Inc.
#
#  This file is part of GNU CC.
#
#  GNU CC is free software; you can redistribute it and/or modify it under the
#  terms of the GNU General Public License as published by the Free Software
#  Foundation; either version 2, or (at your option) any later version.
#
#  GNU CC is distributed in the hope that it will be useful, but WITHOUT ANY
#  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
#  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
#  details.
#
#  You should have received a copy of the GNU General Public License along with
#  GNU CC; see the file COPYING.  If not, write to the Free Software
#  Foundation, 59 Temple Place - Suite 330,
#  Boston, MA 02111-1307, USA.

#  This makefile is run by the parent dir's makefile.
#  thisdir1=`pwd`; \
#  srcdir1=`cd $(srcdir); pwd`; \
#  cd objc; \
#  $(MAKE) $(MAKEFLAGS) -f $$srcdir1/objc/Makefile libobjc.a \
#    srcdir=$$srcdir1 tooldir=$(tooldir) AR="$(AR)" AR_FLAGS="$(AR_FLAGS)" \
#    GCC_FOR_TARGET="$$thisdir1/xgcc -B$$thisdir1/" \
#    GCC_CFLAGS="$(GCC_CFLAGS)" incinstalldir=$$thisdir1/include
#    OBJC_THREAD_FILE="$(OBJC_THREAD_FILE)"
#  Two targets are used by ../Makefile: `all' and `mostlyclean'.

SHELL=/bin/sh

.SUFFIXES: .m

OPTIMIZE= -O

srcdir = .
VPATH = $(srcdir)

AR = ar
AR_FLAGS = rc

# Define this as & to perform parallel make on a Sequent.
# Note that this has some bugs, and it seems currently necessary 
# to compile all the gen* files first by hand to avoid erroneous results.
P =

# Definition of `all' is here so that new rules inserted by sed
# do not specify the default target.
all: all.indirect

# sed inserts variable overrides after the following line.
####target overrides
#
# t-jvm
#
# The Makefile fragment to include when compiling gcc et al for JVM
#
#
# The makefile macros etc. are included in the order found in the
# section "Target Fragment" in the gcc info-files or the paper copy of
# "Using and Porting GNU CC"
#
# Don't run fixproto
STMP_FIXPROTO =

# CROSS_LIBGCC1 is not defined, to make sure we use our own routines.
#
CROSS_LIBGCC1=

# Do not test the nonexistent/empty libgcc1
LIBGCC1_TEST=

#
# Since we need to pass 64-bit entities BY VALUE, we have to bypass
# the normal calling scheme when we make the internal functions in
# libgcc2.a 
#
# Also, there is no DF-mode.  Just hope the word 'DF' is only used as
# in mode(DF) in libgcc2 (seems reasonable)
#
LIBGCC2_CFLAGS = -mlibfunc -g -DDF=SF -Dinhibit_libc

#
# When compiling libgcc2 into an archive, it would be handy to have an
# archive-program.  Exclude the guess about where to find it, and call
# it by its name.  There is no ranlib here (it may be lost).
#
AR_FOR_TARGET=ar-jvm
RANLIB_TEST_FOR_TARGET=false

#
# We dont want the gcc-supplied headers.
#
USER_H = $(LANG_EXTRA_HEADERS)

#
# End of documented makefile fragment.  Over to hacking.
#

# This is where we want the C++ header files.  Experience shows that they are
# compiler-version-specific, also, as other include-files are here, they should be
# here as well (and not in $(libdir)/g++-include)
gxx_include_dir=$(libsubdir)/g++-include

# These two known to work.  Others attached by configure.  Use at own risk.
#
LANGUAGES=c c++

#
# Like install-cross, but without common-headers which are just a
# pain. 
#
INSTALL_TARGET= install-jvm-common install-man install-cross-tools \
 install-libgcc # install-jvm-misc

#
# We create a directory called jvm_c_support, and have to depend on a
# few files in there.
#
# Not any more
# VPATH+=:jvm_c_support

#
# install-jvm-common is like install-common, except it doesnt install
# any stupid scripts called 'c++' and 'g++' in /usr/local/bin.
#  Will also never overwrite /usr/local/bin/gcc.
#
install-jvm-common: native install-dir gcc-cross g++-cross specs
	for file in $(COMPILERS); do \
	  if [ -f $$file ] ; then \
	    rm -f $(libsubdir)/$$file; \
	    $(INSTALL_PROGRAM) $$file $(libsubdir)/$$file; \
	  else \
            true; \
	  fi; \
	done
	for file in $(EXTRA_PASSES) $(EXTRA_PARTS) $(EXTRA_PROGRAMS) ..; do \
	  if [ x"$$file" != x.. ]; then \
	    rm -f $(libsubdir)/$$file; \
	    $(INSTALL_PROGRAM) $$file $(libsubdir)/$$file; \
	  else \
	    true; \
	  fi; \
	done
	-rm -f $(libsubdir)/specs
	$(INSTALL_DATA) specs $(libsubdir)/specs
#
# Install the gcc driver program as gcc-<first word in target>
# Install the g++ driver program as g++-<first word in target>
#  The canonical cross-compiler name has changed for some reason, but we keep
# the "old" name.
#
	-if [ -f gcc-cross ] ; then \
	  target_name=`echo $(target) | sed 's/-.*//'`; \
	  rm -f $(bindir)/gcc-$$target_name; \
	  rm -f $(bindir)/$$target_name-gcc; \
	  $(INSTALL_PROGRAM) gcc-cross $(bindir)/gcc-$$target_name; \
	  $(HARDLINK) $(bindir)/gcc-$$target_name $(bindir)/$$target_name-gcc; \
	fi
	if [ -f g++-cross ] ; then \
	  target_name=`echo $(target) | sed 's/-.*//'`; \
	  rm -f $(bindir)/g++-$$target_name; \
	  rm -f $(bindir)/$$target_name-g++; \
	  $(INSTALL_PROGRAM) g++-cross $(bindir)/g++-$$target_name; \
	  $(HARDLINK) $(bindir)/g++-$$target_name $(bindir)/$$target_name-g++; \
	fi
	-rm -f $(libsubdir)/cpp
	$(INSTALL_PROGRAM) cpp $(libsubdir)/cpp
#
# End of jvm makefile fragment 
#
####host overrides
####cross overrides
####build overrides
#

OBJC_H = hash.h objc-list.h sarray.h objc.h objc-api.h \
  NXConstStr.h Object.h Protocol.h encoding.h typedstream.h thr.h

# Now figure out from those variables how to compile and link.
all.indirect: Makefile compiler objc-runtime

compiler:
	cd ..; $(MAKE) cc1obj$(exeext)

objc-runtime:
	cd ..; $(MAKE) libobjc.a

# copy objc headers to installation include directory
copy-headers: 
	-rm -fr $(incinstalldir)/objc
	-mkdir $(incinstalldir)/objc
	for file in $(OBJC_H); do \
	  realfile=$(srcdir)/$${file}; \
	  cp $${realfile} $(incinstalldir)/objc; \
	  chmod a+r $(incinstalldir)/objc/$${file}; \
	done

Makefile: $(srcdir)/Makefile.in $(srcdir)/../configure
	cd ..; $(SHELL) config.status

mostlyclean:
	-rm -f *.o libobjc.a xforward fflags
clean: mostlyclean
distclean: mostlyclean
extraclean: mostlyclean

# For Sun VPATH.

