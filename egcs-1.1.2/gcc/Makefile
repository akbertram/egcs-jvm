# Makefile for GNU C compiler.
#   Copyright (C) 1987, 88, 90-97, 1998 Free Software Foundation, Inc.

#This file is part of GNU CC.

#GNU CC is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2, or (at your option)
#any later version.

#GNU CC is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with GNU CC; see the file COPYING.  If not, write to
#the Free Software Foundation, 59 Temple Place - Suite 330,
#Boston MA 02111-1307, USA.

# The targets for external use include:
# all, doc, proto, install, install-cross, install-cross-rest,
# uninstall, TAGS, mostlyclean, clean, distclean, maintainer-clean,
# stage1, stage2, stage3, stage4.

# Suppress smart makes who think they know how to automake Yacc files
.y.c:

# Directory where sources are, from where we are.
srcdir = .


# Variables that exist for you to override.
# See below for how to change them for certain systems.

# List of language subdirectories.
# This is overridden by configure.
SUBDIRS = cp f objc

# Selection of languages to be made.
# This is overridden by configure.
LANGUAGES = c proto gcov$(exeext)  c++ f77 objc

# Selection of languages to be made during stage1 build.
# This is overridden by configure.
BOOT_LANGUAGES = c 

ALLOCA =
ALLOCA_FLAGS =
ALLOCA_FINISH = true

# Various ways of specifying flags for compilations:  
# CFLAGS is for the user to override to, e.g., do a bootstrap with -O2.
# BOOT_CFLAGS is the value of CFLAGS to pass
# to the stage2 and stage3 compilations
# WARN_CFLAGS are the warning flags to pass to stage2 and stage3.  It is
# separate from BOOT_CFLAGS because people tend to override optimization
# flags and we'd like them to still have warnings turned on.  They are free
# to explicitly turn warnings off if they wish.
# XCFLAGS is used for most compilations but not when using the GCC just built.
# TCFLAGS is used for compilations with the GCC just built.
XCFLAGS =
TCFLAGS =
CFLAGS = -g
BOOT_CFLAGS = -O2 $(CFLAGS)
WARN_CFLAGS = 
# These exists to be overridden by the x-* and t-* files, respectively.
X_CFLAGS =
T_CFLAGS =

X_CPPFLAGS =
T_CPPFLAGS =

CC = gcc
# srcdir might be a relative pathname which won't be valid in a subdirectory,
# so we must use objdir/srcdir instead to make it safe.  objdir is always
# a full pathname.
BISON = `if [ -f $(objdir)/../bison/bison ] ; then case $(srcdir) in \
	/*) echo $(objdir)/../bison/bison -L $(srcdir)/../bison/ ;; \
	*) echo $(objdir)/../bison/bison -L $(objdir)/$(srcdir)/../bison/ ;; \
	esac else echo bison ; fi`
BISONFLAGS =
LEX = `if [ -f $(objdir)/../flex/flex ] ; then echo $(objdir)/../flex/flex ; else echo flex ; fi`
LEXFLAGS =
AR = ar
AR_FLAGS = rc
LN = ln -s
DLLTOOL = dlltool
SHELL = /bin/sh
# on sysV, define this as cp.
INSTALL = /usr/bin/install -c
# Some systems may be missing symbolic links, regular links, or both.
# Allow configure to check this and use "ln -s", "ln", or "cp" as appropriate.
LN=ln
LN_S=ln -s
# These permit overriding just for certain files.
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
MAKEINFO = makeinfo
MAKEINFOFLAGS =
TEXI2DVI = texi2dvi
# For GNUmake: let us decide what gets passed to recursive makes.
MAKEOVERRIDES =


# Define this as & to perform parallel make on a Sequent.
# Note that this has some bugs, and it seems currently necessary 
# to compile all the gen* files first by hand to avoid erroneous results.
P =

# How to invoke ranlib.
RANLIB = ranlib
# Test to use to see whether ranlib exists on the system.
RANLIB_TEST = [ -f /usr/bin/ranlib -o -f /bin/ranlib ]

# Compiler to use for compiling libgcc1.a.
# OLDCC should not be the GNU C compiler,
# since that would compile typical libgcc1.a functions such as mulsi3
# into infinite recursions.
OLDCC = cc

# CFLAGS for use with OLDCC, for compiling libgcc1.a.
# NOTE: -O does not work on some Unix systems!
CCLIBFLAGS = -O

# Version of ar to use when compiling libgcc1.a.
OLDAR = ar
OLDAR_FLAGS = qc

# Target to use when installing include directory.  Either
# install-headers-tar or install-headers-cpio.
INSTALL_HEADERS_DIR = install-headers-tar

# Header files that are made available under the same name
# to programs compiled with GCC.
USER_H = $(srcdir)/ginclude/stdarg.h $(srcdir)/ginclude/stddef.h \
    $(srcdir)/ginclude/varargs.h $(srcdir)/ginclude/va-alpha.h \
    $(srcdir)/ginclude/va-h8300.h $(srcdir)/ginclude/va-i860.h \
    $(srcdir)/ginclude/va-i960.h $(srcdir)/ginclude/va-mips.h \
    $(srcdir)/ginclude/va-m88k.h $(srcdir)/ginclude/va-mn10200.h \
    $(srcdir)/ginclude/va-mn10300.h $(srcdir)/ginclude/va-pa.h \
    $(srcdir)/ginclude/va-pyr.h $(srcdir)/ginclude/va-sparc.h \
    $(srcdir)/ginclude/va-clipper.h $(srcdir)/ginclude/va-spur.h \
    $(srcdir)/ginclude/va-m32r.h $(srcdir)/ginclude/va-sh.h \
    $(srcdir)/ginclude/va-v850.h $(srcdir)/ginclude/va-arc.h \
    $(srcdir)/ginclude/iso646.h $(srcdir)/ginclude/va-ppc.h \
    $(EXTRA_HEADERS) $(LANG_EXTRA_HEADERS) \
    $(srcdir)/ginclude/proto.h $(srcdir)/ginclude/stdbool.h

# Target to use whe installing assert.h.  Some systems may
# want to set this empty.
INSTALL_ASSERT_H = install-assert-h

# The GCC to use for compiling libgcc2.a, enquire, and libgcc1-test.
# Usually the one we just built.
# Don't use this as a dependency--use $(GCC_PASSES) or $(GCC_PARTS).
GCC_FOR_TARGET = ./xgcc -B./

# This is used instead of ALL_CFLAGS when compiling with GCC_FOR_TARGET.
# It omits XCFLAGS, and specifies -B./.
# It also specifies -I./include to find, e.g., stddef.h.
GCC_CFLAGS=$(INTERNAL_CFLAGS) $(X_CFLAGS) $(T_CFLAGS) $(CFLAGS) -I./include $(TCFLAGS)

# Sed command to transform gcc to installed name.  Overwritten by configure.
program_transform_name = s,x,x,
program_transform_cross_name = s,^,$(target_alias)-,

build_canonical = jvm-unknown-none
host_canonical = jvm-unknown-none

# Tools to use when building a cross-compiler.
# These are used because `configure' appends `cross-make'
# to the makefile when making a cross-compiler.

# Use the tools from the build tree, if they are available.

# objdir is set by configure.
objdir = /home/alexander/dev/egcs-jvm/egcs-1.1.2/gcc

AR_FOR_TARGET = ` \
  if [ -f $(objdir)/../binutils/ar ] ; then \
    echo $(objdir)/../binutils/ar ; \
  else \
    if [ "$(host_canonical)" = "$(target)" ] ; then \
      echo ar; \
    else \
       t='$(program_transform_name)'; echo ar | sed -e $$t ; \
    fi; \
  fi`
AR_FOR_TARGET_FLAGS = rc
RANLIB_FOR_TARGET = ` \
  if [ -f $(objdir)/../binutils/ranlib ] ; then \
    echo $(objdir)/../binutils/ranlib ; \
  else \
    if [ "$(host_canonical)" = "$(target)" ] ; then \
      echo ranlib; \
    else \
       t='$(program_transform_name)'; echo ranlib | sed -e $$t ; \
    fi; \
  fi`
RANLIB_TEST_FOR_TARGET = \
  [ -f $(RANLIB_FOR_TARGET) ] \
  || ( [ "$(host_canonical)" = "$(target)" ] \
       && [ -f /usr/bin/ranlib -o -f /bin/ranlib ] )

# We always act like a cross-compiler, even when we're
# compiling native.  This is because we want to use our own tools if
# we can.  We don't just set RANLIB to a complicated expression,
# because the top level Makefile.in might override RANLIB_FOR_TARGET.
# These are from the FSF file "cross-make".
AR = $(AR_FOR_TARGET)
AR_FLAGS = $(AR_FOR_TARGET_FLAGS)
OLDAR = $(AR_FOR_TARGET)
OLDAR_FLAGS = $(AR_FOR_TARGET_FLAGS)
RANLIB = $(RANLIB_FOR_TARGET)
RANLIB_TEST = $(RANLIB_TEST_FOR_TARGET)
  
# Dir to search for system headers.  Overridden by cross-make.
SYSTEM_HEADER_DIR = /usr/include

# Control whether to run fixproto.
STMP_FIXPROTO = stmp-fixproto

# Test to see whether <limits.h> exists in the system header files.
LIMITS_H_TEST = [ -f $(SYSTEM_HEADER_DIR)/limits.h ]

# There may be a premade insn-attrtab.c for this machine.
# (You could rebuild it with genattrtab as usual, but it takes a long time.)
# PREMADE_ATTRTAB is the file name of the file to use.
# PREMADE_ATTRTAB_MD is the md file it corresponds to.
PREMADE_ATTRTAB_MD = Makefile  # Guaranteed not to cmp equal to md.
PREMADE_ATTRTAB = 

target=jvm-unknown-none
target_alias=jvm
xmake_file=
tmake_file= ./config/jvm/t-jvm
out_file=$(srcdir)/config/jvm/jvm.c
out_object_file=jvm.o
md_file=$(srcdir)/config/jvm/jvm.md
tm_file= $(srcdir)/config/jvm/jvm.h
build_xm_file= auto-host.h $(srcdir)/config/jvm/xm-jvm.h
host_xm_file= auto-host.h $(srcdir)/config/jvm/xm-jvm.h
lang_specs_files= ./cp/lang-specs.h ./f/lang-specs.h
lang_options_files= ./cp/lang-options.h ./f/lang-options.h
GCC_THREAD_FILE=single
GTHREAD_FLAGS=
# Be prepared for gcc2 merges.
gcc_version=egcs-2.91.66
gcc_version_trigger=./version.c
version=$(gcc_version)
mainversion=`sed -e 's/.*\"\([0-9]*\.[0-9]*\).*/\1/' < $(srcdir)/version.c`

# Common prefix for installation directories.
# NOTE: This directory must exist when you start installation.
prefix = /usr/local
# Directory in which to put localized header files. On the systems with
# gcc as the native cc, `local_prefix' may not be `prefix' which is
# `/usr'.
# NOTE: local_prefix *should not* default from prefix.
local_prefix = /usr/local
# Directory in which to put host dependent programs and libraries
exec_prefix = ${prefix}
# Directory in which to put the executable for the command `gcc'
bindir = ${exec_prefix}/bin
# Directory in which to put the directories used by the compiler.
libdir = ${exec_prefix}/lib
# Directory in which the compiler finds executables, libraries, etc.
libsubdir = $(libdir)/gcc-lib/$(target_alias)/$(version)
# Directory in which the compiler finds g++ includes.
gxx_include_dir= ${prefix}/include/g++
# Directory in which the old g++ header files may be found.
# The reason we use $(libdir)/g++-include rather than using libsubdir
# is for compatibility with older versions of libg++.
old_gxx_include_dir= $(libdir)/g++-include
# Directory to search for site-specific includes.
includedir = $(local_prefix)/include
# assertdir is overridden in cross-make.
# (But this currently agrees with what is in cross-make.)
assertdir = $(tooldir)/include
# where the info files go
infodir = ${prefix}/share/info
# Where cpp should go besides $prefix/bin if necessary
cpp_install_dir = 
# Extension (if any) to put in installed man-page filename.
manext = .1
objext = .o
exeext = 
build_exeext = 

# Directory in which to put man pages.
mandir = ${prefix}/share/man/man1
# Directory in which to find other cross-compilation tools and headers.
# Used in install-cross.
tooldir = $(exec_prefix)/$(target_alias)
# Dir for temp files.
tmpdir = /tmp

# Additional system libraries to link with.
CLIB=

# Change this to a null string if obstacks are installed in the
# system library.
OBSTACK=obstack.o

# Configure will set these if you need vfprintf and possibly _doprnt support.
VFPRINTF=
DOPRINT=

# Specify the rule for actually making libgcc.a,
LIBGCC = libgcc.a
# and the rule for installing it.
INSTALL_LIBGCC = install-libgcc

# Specify the rule for actually making libgcc1.a.
# The value may be empty; that means to do absolutely nothing
# with or for libgcc1.a.
LIBGCC1 = libgcc1.a

# Specify the rule for making libgcc1.a for a cross-compiler.
# The default rule assumes that libgcc1.a is supplied by the user.
CROSS_LIBGCC1 = libgcc1.cross

# Specify the rule for actually making libgcc2.a.
LIBGCC2 = libgcc2.a

# Options to use when compiling libgcc2.a.
# -g1 causes output of debug info only for file-scope entities.
# we use this here because that should be enough, and also
# so that -g1 will be tested.
#
LIBGCC2_DEBUG_CFLAGS = -g1
LIBGCC2_CFLAGS = -O2 $(LIBGCC2_INCLUDES) $(GCC_CFLAGS) $(TARGET_LIBGCC2_CFLAGS) $(LIBGCC2_DEBUG_CFLAGS) $(GTHREAD_FLAGS) -DIN_LIBGCC2 -D__GCC_FLOAT_NOT_NEEDED  

# Additional options to use when compiling libgcc2.a.
# Some targets override this to -Iinclude
LIBGCC2_INCLUDES =

# Additional target-dependent options for compiling libgcc2.a.
TARGET_LIBGCC2_CFLAGS = 

# Things which must be built before building libgcc2.a.
# Some targets override this to stmp-int-hdrs
LIBGCC2_DEPS =

# libgcc1-test target (must also be overridable for a target)
LIBGCC1_TEST = libgcc1-test

# List of extra executables that should be compiled for this target machine
# that are used for compiling from source code to object code.
# The rules for compiling them should be in the t-* file for the machine.
EXTRA_PASSES =

# Like EXTRA_PASSES, but these are used when linking.
EXTRA_PROGRAMS = 

# List of extra object files that should be compiled for this target machine.
# The rules for compiling them should be in the t-* file for the machine.
EXTRA_PARTS = 

# List of extra object files that should be compiled and linked with
# compiler proper (cc1, cc1obj, cc1plus).
EXTRA_OBJS =  

# List of extra object files that should be compiled and linked with
# the gcc driver.
EXTRA_GCC_OBJS =

# List of additional header files to install.
# Often this is edited directly by `configure'.
EXTRA_HEADERS =

# Set this to `collect2' to enable use of collect2.
USE_COLLECT2 = 
MAYBE_USE_COLLECT2 = 
# It is convenient for configure to add the assignment at the beginning,
# so don't override it here.
USE_COLLECT2 = collect2$(exeext)

# List of extra C and assembler files to add to libgcc1.a.
# Assembler files should have names ending in `.asm'.
LIB1FUNCS_EXTRA = 

# List of extra C and assembler files to add to libgcc2.a.
# Assembler files should have names ending in `.asm'.
LIB2FUNCS_EXTRA = 

# Handle cpp installation.
INSTALL_CPP=
UNINSTALL_CPP=

# Default float.h source to use for cross-compiler.
# This is overridden by configure.
CROSS_FLOAT_H=$(srcdir)/config/float-i64.h

# We do not try to build float.h anymore.  Let configure select the
# appropriate pre-built float.h file for the target.
FLOAT_H=$(srcdir)/config/float-i64.h

# Program to convert libraries.
LIBCONVERT = 

# Control whether header files are installed.
INSTALL_HEADERS=install-headers

# Options for tar when copying trees.  So HPUX can override it.
TAROUTOPTS = xpBf

# Select which version of fixincludes to use (I.E. regular versus SVR4)
# This value is overridden directly by configure.
FIXINCLUDES = fixincludes

# Additional directories of header files to run fixincludes on.
# These should be directories searched automatically by default
# just as /usr/include is.
# *Do not* use this for directories that happen to contain 
# header files, but are not searched automatically by default.
# On most systems, this is empty.
OTHER_FIXINCLUDES_DIRS=

# A list of all the language-specific executables.
# This is overridden by configure.
COMPILERS = cc1$(exeext)  cc1plus$(exeext) f771$(exeext) cc1obj$(exeext)

# List of things which should already be built whenever we try to use xgcc
# to compile anything (without linking).
GCC_PASSES=xgcc$(exeext) cc1$(exeext) cpp$(exeext) $(EXTRA_PASSES)

# List of things which should already be built whenever we try to use xgcc
# to link anything.
GCC_PARTS=$(GCC_PASSES) $(LIBGCC) $(EXTRA_PROGRAMS) $(USE_COLLECT2) $(EXTRA_PARTS)

# Directory to link to, when using the target `maketest'.
DIR = ../gcc

# Guaranteed to not exist when not passing md through cpp.
# This value is overridden directly by configure.
MD_FILE = md-cpp-not-used

# Flags to use when cross-building GCC.
# Prefix to apply to names of object files when using them
# to run on the machine we are compiling on.
HOST_PREFIX=
# Prefix to apply to names of object files when compiling them
# to run on the machine we are compiling on.
# The default for this variable is chosen to keep these rules 
# out of the way of the other rules for compiling the same source files.
HOST_PREFIX_1=loser-
HOST_CC=$(CC)
HOST_CFLAGS=$(ALL_CFLAGS)
HOST_CLIB=$(CLIB)
HOST_LDFLAGS=$(LDFLAGS)
HOST_CPPFLAGS=$(ALL_CPPFLAGS)
HOST_ALLOCA=$(ALLOCA)
HOST_MALLOC=$(MALLOC)
HOST_OBSTACK=$(OBSTACK)
HOST_VFPRINTF=$(VFPRINTF)
HOST_DOPRINT=$(DOPRINT)

# Actual name to use when installing a native compiler.
GCC_INSTALL_NAME = `t='$(program_transform_name)'; echo gcc | sed -e $$t`
PROTOIZE_INSTALL_NAME = `t='$(program_transform_name)'; echo protoize | sed -e $$t`
UNPROTOIZE_INSTALL_NAME = `t='$(program_transform_name)'; echo unprotoize | sed -e $$t`

# Actual name to use when installing a cross-compiler.
GCC_CROSS_NAME = `t='$(program_transform_cross_name)'; echo gcc | sed -e $$t`
PROTOIZE_CROSS_NAME = `t='$(program_transform_cross_name)'; echo protoize | sed -e $$t`
UNPROTOIZE_CROSS_NAME = `t='$(program_transform_cross_name)'; echo unprotoize | sed -e $$t`

# Choose the real default target.
ALL=all.internal

# Choose the real install target.
INSTALL_TARGET=install-normal

# Setup the testing framework, if you have one
EXPECT = `if [ -f $${rootme}/../expect/expect ] ; then \
            echo $${rootme}/../expect/expect ; \
          else echo expect ; fi`

RUNTEST = `if [ -f $${srcdir}/../dejagnu/runtest ] ; then \
	       echo $${srcdir}/../dejagnu/runtest ; \
	    else echo runtest; fi`
RUNTESTFLAGS =

# Extra symbols for fixproto to define when parsing headers.
FIXPROTO_DEFINES = 

# Extra flags to use when compiling crt{begin,end}.o.
CRTSTUFF_T_CFLAGS = 

# Extra flags to use when compiling [m]crt0.o.
CRT0STUFF_T_CFLAGS = 

# "t" or nothing, for building multilibbed versions of, say, crtbegin.o.
T =

# End of variables for you to override.

# Definition of `all' is here so that new rules inserted by sed
# do not specify the default target.
# The real definition is under `all.internal' (for native compilers)
# or `all.cross' (for cross compilers).
all: all.indirect

# This tells GNU Make version 3 not to put all variables in the environment.
.NOEXPORT:

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
# Now figure out from those variables how to compile and link.

all.indirect: $(ALL)

# IN_GCC tells obstack.h that we are using gcc's <stddef.h> file.
# ??? IN_GCC should be obsolete now.
INTERNAL_CFLAGS = $(CROSS) -DIN_GCC 

# This is the variable actually used when we compile.
ALL_CFLAGS = $(INTERNAL_CFLAGS) $(X_CFLAGS) $(T_CFLAGS) $(CFLAGS) $(XCFLAGS) \
	-DHAVE_CONFIG_H $(SCHED_CFLAGS)

# Likewise.
ALL_CPPFLAGS = $(CPPFLAGS) $(X_CPPFLAGS) $(T_CPPFLAGS)

# Even if ALLOCA is set, don't use it if compiling with GCC.
USE_ALLOCA= ${ALLOCA}
USE_HOST_ALLOCA= ` case "${HOST_ALLOCA}" in ?*) echo ${HOST_PREFIX}${HOST_ALLOCA} ;; esac `
USE_HOST_MALLOC= ` case "${HOST_MALLOC}" in ?*) echo ${HOST_PREFIX}${HOST_MALLOC} ;; esac `
USE_HOST_OBSTACK= ` case "${HOST_OBSTACK}" in ?*) echo ${HOST_PREFIX}${HOST_OBSTACK} ;; esac `
USE_HOST_VFPRINTF= ` case "${HOST_VFPRINTF}" in ?*) echo ${HOST_PREFIX}${HOST_VFPRINTF} ;; esac `
USE_HOST_DOPRINT= ` case "${HOST_DOPRINT}" in ?*) echo ${HOST_PREFIX}${HOST_DOPRINT} ;; esac `

# Dependency on obstack, alloca, malloc or whatever library facilities
# are not installed in the system libraries.
# We don't use USE_ALLOCA because backquote expansion doesn't work in deps.
LIBDEPS= $(OBSTACK) $(ALLOCA) $(MALLOC) $(VFPRINTF) $(DOPRINT)

# Likewise, for use in the tools that must run on this machine
# even if we are cross-building GCC.
# We don't use USE_ALLOCA because backquote expansion doesn't work in deps.
HOST_LIBDEPS= $(HOST_PREFIX)$(HOST_OBSTACK) $(HOST_PREFIX)$(HOST_ALLOCA) $(HOST_PREFIX)$(HOST_MALLOC) $(HOST_PREFIX)$(HOST_VFPRINTF) $(HOST_PREFIX)$(HOST_DOPRINT)

# How to link with both our special library facilities
# and the system's installed libraries.
LIBS = $(OBSTACK) $(USE_ALLOCA) $(MALLOC) $(VFPRINTF) $(DOPRINT) $(CLIB)

# Likewise, for use in the tools that must run on this machine
# even if we are cross-building GCC.
HOST_LIBS = $(USE_HOST_OBSTACK) $(USE_HOST_ALLOCA) $(USE_HOST_MALLOC)  \
	    $(USE_HOST_VFPRINTF) $(USE_HOST_DOPRINT) $(HOST_CLIB)

HOST_RTL = $(HOST_PREFIX)rtl.o $(HOST_PREFIX)bitmap.o
HOST_RTLANAL = $(HOST_PREFIX)rtlanal.o
HOST_PRINT = $(HOST_PREFIX)print-rtl.o

# Specify the directories to be searched for header files.
# Both . and srcdir are used, in that order,
# so that tm.h and config.h will be found in the compilation
# subdirectory rather than in the source directory.
INCLUDES = -I. -I$(srcdir) -I$(srcdir)/config

# Always use -I$(srcdir)/config when compiling.
.c.o:
	$(CC) -c $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) $<

# This tells GNU make version 3 not to export all the variables
# defined in this file into the environment.
.NOEXPORT:
#
# Support for additional languages (other than c and objc).
# ??? objc can be supported this way too (leave for later).

# These next lines are overridden by configure.
LANG_MAKEFILES =  ./cp/Make-lang.in ./cp/Makefile.in ./f/Make-lang.in ./f/Makefile.in ./objc/Make-lang.in ./objc/Makefile.in
LANG_STAGESTUFF =  g++$(exeext) g++-cross$(exeext) cc1plus$(exeext) g77$(exeext) g77-cross$(exeext) f771$(exeext) 
LANG_DIFF_EXCLUDES =  -x parse.c -x parse.h -x f/BUGS -x f/NEWS -x f/INSTALL -x f/intdoc.texi -x objc-parse.c -x objc-parse.y 
LANG_LIB2FUNCS =  cplib2.txt  
LANG_EXTRA_HEADERS =  $(CXX_EXTRA_HEADERS)  

# Flags to pass to recursive makes.
# CC is set by configure.  Hosts without symlinks need special handling
# because we need CC="stage1/xgcc -Bstage1/" to work in the language
# subdirectories.
# ??? The choices here will need some experimenting with.
FLAGS_TO_PASS = \
	"AR_FLAGS=$(AR_FOR_TARGET_FLAGS)" \
	"AR_FOR_TARGET=$(AR_FOR_TARGET)" \
	"BISON=$(BISON)" \
	"BISONFLAGS=$(BISONFLAGS)" \
	"CC=$(CC)" \
	"CFLAGS=$(CFLAGS)" \
	"CLIB=$(CLIB)" \
	"GCC_FOR_TARGET=$(GCC_FOR_TARGET)" \
	"LDFLAGS=$(LDFLAGS)" \
	"LEX=$(LEX)" \
	"LEXFLAGS=$(LEXFLAGS)" \
	"LN=$(LN)" \
	"LN_S=$(LN_S)" \
	"MAKEINFO=$(MAKEINFO)" \
	"MAKEINFOFLAGS=$(MAKEINFOFLAGS)" \
	"RANLIB_FOR_TARGET=$(RANLIB_FOR_TARGET)" \
	"RANLIB_TEST_FOR_TARGET=$(RANLIB_TEST_FOR_TARGET)" \
	"SHELL=$(SHELL)" \
	"STAGE_PREFIX=$(STAGE_PREFIX)" \
	"exeext=$(exeext)" \
	"build_exeext=$(build_exeext)" \
	"objext=$(objext)" \
	"exec_prefix=$(exec_prefix)" \
	"prefix=$(prefix)" \
	"local_prefix=$(local_prefix)" \
	"gxx_include_dir=$(gxx_include_dir)" \
	"tooldir=$(tooldir)" \
	"bindir=$(bindir)" \
	"libsubdir=$(libsubdir)"
#
# Lists of files for various purposes.

# Language-specific object files for C and Objective C.
C_AND_OBJC_OBJS = c-lex.o c-pragma.o c-decl.o c-typeck.o c-convert.o \
  c-aux-info.o c-common.o c-iterate.o 

# Language-specific object files for C.
C_OBJS = c-parse.o c-lang.o $(C_AND_OBJC_OBJS)

SCHED_PREFIX = 
SCHED_CFLAGS = 

# Language-independent object files.
OBJS = toplev.o version.o tree.o print-tree.o stor-layout.o fold-const.o \
 function.o stmt.o except.o expr.o calls.o expmed.o explow.o optabs.o \
 varasm.o rtl.o print-rtl.o rtlanal.o emit-rtl.o genrtl.o real.o regmove.o \
 dbxout.o sdbout.o dwarfout.o dwarf2out.o xcoffout.o bitmap.o alias.o \
 integrate.o jump.o cse.o loop.o unroll.o flow.o stupid.o combine.o varray.o \
 regclass.o local-alloc.o global.o reload.o reload1.o caller-save.o gcse.o \
 insn-peep.o reorg.o $(SCHED_PREFIX)sched.o final.o recog.o reg-stack.o \
 insn-opinit.o insn-recog.o insn-extract.o insn-output.o insn-emit.o \
 profile.o insn-attrtab.o $(out_object_file) getpwd.o $(EXTRA_OBJS) convert.o \
 dyn-string.o

# GEN files are listed separately, so they can be built before doing parallel
#  makes for cc1 or cc1plus.  Otherwise sequent parallel make attempts to load
#  them before rtl.o is compiled.
GEN= genemit genoutput genrecog genextract genflags gencodes genconfig \
 genpeep gengenrtl gencheck

CCCP=cccp

# Files to be copied away after each stage in building.
STAGESTUFF = *$(objext) insn-flags.h insn-config.h insn-codes.h \
 insn-output.c insn-recog.c insn-emit.c insn-extract.c insn-peep.c \
 insn-attr.h insn-attrtab.c insn-opinit.c genrtl.c genrtl.h tree-check.h \
 s-flags s-config s-codes s-mlib s-under\
 s-output s-recog s-emit s-extract s-peep s-check \
 s-attr s-attrtab s-opinit s-crt s-crtS s-crt0 \
 genemit$(build_exeext) genoutput$(build_exeext) genrecog$(build_exeext) \
 genextract$(build_exeext) genflags$(build_exeext) gencodes$(build_exeext) \
 genconfig$(build_exeext) genpeep$(build_exeext) genattrtab$(build_exeext) \
 genattr$(build_exeext) genopinit$(build_exeext) gengenrtl$(build_exeext) \
 gencheck$(build_exeext) \
 xgcc$(exeext) cc1$(exeext) cpp$(exeext) $(EXTRA_PASSES) \
 $(EXTRA_PARTS) $(EXTRA_PROGRAMS) gcc-cross$(exeext) \
 $(CCCP)$(exeext) cc1obj$(exeext) enquire$(exeext) \
 protoize$(exeext) unprotoize$(exeext) \
 specs collect2$(exeext) $(USE_COLLECT2) underscore.c \
 gcov$(exeext) *.bp \
 *.greg *.lreg *.combine *.flow *.cse *.jump *.rtl *.tree *.loop \
 *.dbr *.jump2 *.sched *.cse2 *.sched2 *.stack *.gcse \
 *.[si] \
 $(LANG_STAGESTUFF)

# Members of libgcc1.a.
LIB1FUNCS = _mulsi3 _udivsi3 _divsi3 _umodsi3 _modsi3 \
   _lshrsi3 _ashrsi3 _ashlsi3 \
   _divdf3 _muldf3 _negdf2 _adddf3 _subdf3 \
   _fixdfsi _fixsfsi _floatsidf _floatsisf _truncdfsf2 _extendsfdf2 \
   _addsf3 _negsf2 _subsf3 _mulsf3 _divsf3 \
   _eqdf2 _nedf2 _gtdf2 _gedf2 _ltdf2 _ledf2 \
   _eqsf2 _nesf2 _gtsf2 _gesf2 _ltsf2 _lesf2

# Library members defined in libgcc2.c.
LIB2FUNCS = _muldi3 _divdi3 _moddi3 _udivdi3 _umoddi3 _negdi2 \
     _lshrdi3 _ashldi3 _ashrdi3 _ffsdi2 \
    _udiv_w_sdiv _udivmoddi4 _cmpdi2 _ucmpdi2 _floatdidf _floatdisf \
    _fixunsdfsi _fixunssfsi _fixunsdfdi _fixdfdi _fixunssfdi _fixsfdi \
    _fixxfdi _fixunsxfdi _floatdixf _fixunsxfsi \
    _fixtfdi _fixunstfdi _floatditf \
    __gcc_bcmp _varargs __dummy _eprintf \
    _bb _shtab _clear_cache _trampoline __main _exit \
    _ctors _pure

LIB2FUNCS_EH = _eh

FPBIT_FUNCS = _pack_sf _unpack_sf _addsub_sf _mul_sf _div_sf \
    _fpcmp_parts_sf _compare_sf _eq_sf _ne_sf _gt_sf _ge_sf \
    _lt_sf _le_sf _si_to_sf _sf_to_si _negate_sf _make_sf \
    _sf_to_df

DPBIT_FUNCS = _pack_df _unpack_df _addsub_df _mul_df _div_df \
    _fpcmp_parts_df _compare_df _eq_df _ne_df _gt_df _ge_df \
    _lt_df _le_df _si_to_df _df_to_si _negate_df _make_df \
    _df_to_sf

# The files that "belong" in CONFIG_H are deliberately omitted
# because having them there would not be useful in actual practice.
# All they would do is cause complete recompilation every time
# one of the machine description files is edited.
# That may or may not be what one wants to do.
# If it is, rm *.o is an easy way to do it.
# CONFIG_H = $(host_xm_file) $(tm_file)
CONFIG_H =
RTL_BASE_H = rtl.h rtl.def gansidecl.h machmode.h machmode.def
RTL_H = $(RTL_BASE_H) genrtl.h
TREE_H = tree.h real.h tree.def gansidecl.h machmode.h machmode.def tree-check.h
BASIC_BLOCK_H = basic-block.h bitmap.h
DEMANGLE_H = demangle.h gansidecl.h
RECOG_H = recog.h gansidecl.h
EXPR_H = expr.h insn-codes.h
REGS_H = regs.h varray.h machmode.h machmode.def gansidecl.h
#
# Language makefile fragments.

# The following targets define the interface between us and the languages.
#
# all.build, all.cross, start.encap, rest.encap,
# info, dvi,
# install-normal, install-common, install-info, install-man,
# uninstall, distdir,
# mostlyclean, clean, distclean, extraclean, maintainer-clean,
# stage1, stage2, stage3, stage4
#
# Each language is linked in with a series of hooks (since we can't use `::'
# targets).  The name of each hooked is "lang.${target_name}" (eg: lang.info).
# Configure computes and adds these here.

####language hooks
lang.all.build:  c++.all.build f77.all.build objc.all.build
lang.all.cross:  c++.all.cross f77.all.cross objc.all.cross
lang.start.encap:  c++.start.encap f77.start.encap objc.start.encap
lang.rest.encap:  c++.rest.encap f77.rest.encap objc.rest.encap
lang.info:  c++.info f77.info objc.info
lang.dvi:  c++.dvi f77.dvi objc.dvi
lang.install-normal:  c++.install-normal f77.install-normal objc.install-normal
lang.install-common:  c++.install-common f77.install-common objc.install-common
lang.install-info:  c++.install-info f77.install-info objc.install-info
lang.install-man:  c++.install-man f77.install-man objc.install-man
lang.uninstall:  c++.uninstall f77.uninstall objc.uninstall
lang.distdir:  c++.distdir f77.distdir objc.distdir
lang.mostlyclean:  c++.mostlyclean f77.mostlyclean objc.mostlyclean
lang.clean:  c++.clean f77.clean objc.clean
lang.distclean:  c++.distclean f77.distclean objc.distclean
lang.extraclean:  c++.extraclean f77.extraclean objc.extraclean
lang.maintainer-clean:  c++.maintainer-clean f77.maintainer-clean objc.maintainer-clean
lang.stage1:  c++.stage1 f77.stage1 objc.stage1
lang.stage2:  c++.stage2 f77.stage2 objc.stage2
lang.stage3:  c++.stage3 f77.stage3 objc.stage3
lang.stage4:  c++.stage4 f77.stage4 objc.stage4

# sed inserts language fragments after the following line.
####language fragments
# Top level makefile fragment for GNU C++.
#   Copyright (C) 1994, 1995, 1997 Free Software Foundation, Inc.

#This file is part of GNU CC.

#GNU CC is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2, or (at your option)
#any later version.

#GNU CC is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with GNU CC; see the file COPYING.  If not, write to
#the Free Software Foundation, 59 Temple Place - Suite 330,
#Boston, MA 02111-1307, USA.

# This file provides the language dependent support in the main Makefile.
# Each language makefile fragment must provide the following targets:
#
# foo.all.build, foo.all.cross, foo.start.encap, foo.rest.encap,
# foo.info, foo.dvi,
# foo.install-normal, foo.install-common, foo.install-info, foo.install-man,
# foo.uninstall, foo.distdir,
# foo.mostlyclean, foo.clean, foo.distclean, foo.extraclean,
# foo.maintainer-clean, foo.stage1, foo.stage2, foo.stage3, foo.stage4
#
# where `foo' is the name of the language.
#
# It should also provide rules for:
#
# - making any compiler driver (eg: g++)
# - the compiler proper (eg: cc1plus)
# - define the names for selecting the language in LANGUAGES.
#
# Extra flags to pass to recursive makes.
CXX_FLAGS_TO_PASS = \
	"CXX_FOR_BUILD=$(CXX_FOR_BUILD)" \
	"CXXFLAGS=$(CXXFLAGS)" \
	"CXX_FOR_TARGET=$(CXX_FOR_TARGET)"

# Actual names to use when installing a native compiler.
CXX_INSTALL_NAME = `t='$(program_transform_name)'; echo c++ | sed $$t`
GXX_INSTALL_NAME = `t='$(program_transform_name)'; echo g++ | sed $$t`
DEMANGLER_INSTALL_NAME = `t='$(program_transform_name)'; echo c++filt | sed $$t`

# Actual names to use when installing a cross-compiler.
CXX_CROSS_NAME = `t='$(program_transform_cross_name)'; echo c++ | sed $$t`
GXX_CROSS_NAME = `t='$(program_transform_cross_name)'; echo g++ | sed $$t`
DEMANGLER_CROSS_NAME = `t='$(program_transform_cross_name)'; echo c++filt | sed $$t`

# The name to use for the demangler program.
DEMANGLER_PROG = c++filt$(exeext)

# Extra headers to install.
CXX_EXTRA_HEADERS = $(srcdir)/cp/inc/typeinfo $(srcdir)/cp/inc/exception \
	$(srcdir)/cp/inc/new $(srcdir)/cp/inc/new.h

# Extra code to include in libgcc2.
CXX_LIB2FUNCS = tinfo.o tinfo2.o new.o opnew.o opnewnt.o opvnew.o opvnewnt.o \
	opdel.o opdelnt.o opvdel.o opvdelnt.o exception.o
CXX_LIB2SRCS = $(srcdir)/cp/new.cc $(srcdir)/cp/new1.cc $(srcdir)/cp/new2.cc \
	$(srcdir)/cp/exception.cc $(srcdir)/cp/tinfo.cc \
	$(srcdir)/cp/tinfo2.cc $(srcdir)/cp/tinfo.h
#
# Define the names for selecting c++ in LANGUAGES.
# Note that it would be nice to move the dependency on g++
# into the C++ rule, but that needs a little bit of work
# to do the right thing within all.cross.
C++ c++: cc1plus$(exeext)

# Tell GNU make to ignore these if they exist.
.PHONY: C++ c++

g++.c: $(srcdir)/gcc.c
	-rm -f $@
	$(LN_S) $(srcdir)/gcc.c $@

g++spec.o: $(srcdir)/cp/g++spec.c
	$(CC) -c $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) $(srcdir)/cp/g++spec.c

# N.B.: This is a copy of the gcc.o rule, with -DLANG_SPECIFIC_DRIVER added.
# It'd be nice if we could find an easier way to do this---rather than have
# to track changes to the toplevel gcc Makefile as well.
# We depend on g++.c last, to make it obvious where it came from.
g++.o: $(CONFIG_H) multilib.h config.status $(lang_specs_files) g++.c \
       system.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) \
	$(DRIVER_DEFINES) \
	-DLANG_SPECIFIC_DRIVER \
  -c g++.c

# Create the compiler driver for g++.
g++$(exeext): g++.o g++spec.o version.o choose-temp.o pexecute.o prefix.o mkstemp.o $(LIBDEPS) $(EXTRA_GCC_OBJS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $@ g++.o g++spec.o prefix.o \
	  version.o choose-temp.o pexecute.o mkstemp.o $(EXTRA_GCC_OBJS) $(LIBS)

# Create a version of the g++ driver which calls the cross-compiler.
g++-cross$(exeext): g++$(exeext)
	-rm -f g++-cross$(exeext)
	cp g++$(exeext) g++-cross$(exeext)

cxxmain.o: cplus-dem.c demangle.h
	rm -f cxxmain.c
	$(LN_S) $(srcdir)/cplus-dem.c cxxmain.c
	$(CC) -c -DMAIN $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) \
	  -DVERSION=\"$(version)\" cxxmain.c

$(DEMANGLER_PROG): cxxmain.o underscore.o getopt.o getopt1.o $(LIBDEPS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) $(LIBS) -o $@ \
	  cxxmain.o underscore.o getopt.o getopt1.o

CXX_SRCS = $(srcdir)/cp/call.c $(srcdir)/cp/decl2.c \
 $(srcdir)/cp/except.c $(srcdir)/cp/input.c $(srcdir)/cp/pt.c \
 $(srcdir)/cp/spew.c $(srcdir)/cp/xref.c $(srcdir)/cp/class.c \
 $(srcdir)/cp/expr.c $(srcdir)/cp/lex.c \
 $(srcdir)/cp/ptree.c $(srcdir)/cp/tree.c $(srcdir)/cp/cvt.c \
 $(srcdir)/cp/errfn.c $(srcdir)/cp/rtti.c $(srcdir)/cp/method.c \
 $(srcdir)/cp/search.c $(srcdir)/cp/typeck.c $(srcdir)/cp/decl.c \
 $(srcdir)/cp/error.c $(srcdir)/cp/friend.c $(srcdir)/cp/init.c \
 $(srcdir)/cp/parse.y $(srcdir)/cp/sig.c $(srcdir)/cp/typeck2.c \
 $(srcdir)/cp/repo.c $(srcdir)/cp/semantics.c

cc1plus$(exeext): $(P) $(CXX_SRCS) $(LIBDEPS) stamp-objlist c-common.o c-pragma.o \
	$(srcdir)/cp/cp-tree.h $(srcdir)/cp/cp-tree.def
	cd cp; $(MAKE) $(FLAGS_TO_PASS) $(CXX_FLAGS_TO_PASS) ../cc1plus$(exeext)
#
# Build hooks:

c++.all.build: g++$(exeext)
c++.all.cross: g++-cross$(exeext) $(DEMANGLER_PROG)
c++.start.encap: g++$(exeext)
c++.rest.encap: $(DEMANGLER_PROG)

c++.info:
c++.dvi:

# C++ language-support library pieces for libgcc.
tinfo.o: cc1plus$(exeext) $(srcdir)/cp/tinfo.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c $(srcdir)/cp/tinfo.cc
tinfo2.o: cc1plus$(exeext) $(srcdir)/cp/tinfo2.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c $(srcdir)/cp/tinfo2.cc
exception.o: cc1plus$(exeext) $(srcdir)/cp/exception.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c -fexceptions $(srcdir)/cp/exception.cc
new.o: cc1plus$(exeext) $(srcdir)/cp/new.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c $(srcdir)/cp/new.cc
opnew.o: cc1plus$(exeext) $(srcdir)/cp/new1.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c $(srcdir)/cp/new1.cc -DL_op_new -o opnew.o
opnewnt.o: cc1plus$(exeext) $(srcdir)/cp/new1.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c $(srcdir)/cp/new1.cc -DL_op_newnt -o opnewnt.o
opvnew.o: cc1plus$(exeext) $(srcdir)/cp/new2.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c $(srcdir)/cp/new2.cc -DL_op_vnew -o opvnew.o
opvnewnt.o: cc1plus$(exeext) $(srcdir)/cp/new2.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c $(srcdir)/cp/new2.cc -DL_op_vnewnt -o opvnewnt.o
opdel.o: cc1plus$(exeext) $(srcdir)/cp/new2.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c $(srcdir)/cp/new2.cc -DL_op_delete -o opdel.o
opdelnt.o: cc1plus$(exeext) $(srcdir)/cp/new2.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c $(srcdir)/cp/new2.cc -DL_op_delnt -o opdelnt.o
opvdel.o: cc1plus$(exeext) $(srcdir)/cp/new2.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c $(srcdir)/cp/new2.cc -DL_op_vdel -o opvdel.o
opvdelnt.o: cc1plus$(exeext) $(srcdir)/cp/new2.cc
	$(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) \
	  -c $(srcdir)/cp/new2.cc -DL_op_vdelnt -o opvdelnt.o

# We want to update cplib2.txt if any of the source files change...
cplib2.txt: $(CXX_LIB2SRCS) $(CXX_EXTRA_HEADERS) cplib2.ready
	case " $(LANGUAGES) " in \
	*" "[cC]"++ "*) \
	  echo $(CXX_LIB2FUNCS) > cplib2.new;; \
	*) \
	  echo "" > cplib2.new;; \
	esac
	mv -f cplib2.new cplib2.txt 

# Or if it would be different.
cplib2.ready: $(GCC_PASSES) $(LANGUAGES) $(LIBGCC2_DEPS) stmp-int-hdrs
	@if [ -r cplib2.txt ]; then \
	  case " $(LANGUAGES) " in \
	  *" "[cC]"++ "*) \
	    echo $(CXX_LIB2FUNCS) > cplib2.new;; \
	  *) \
	    echo "" > cplib2.new;; \
	  esac; \
	  if cmp -s cplib2.new cplib2.txt; then true; else \
	    touch cplib2.ready; \
	  fi; \
	  rm -f cplib2.new; \
	else true ; \
	fi
	@if [ -f cplib2.ready ]; then true; else \
	  touch cplib2.ready; \
	fi
#
# Install hooks:
# cc1plus is installed elsewhere as part of $(COMPILERS).

# Nothing to do here.
c++.install-normal:

# Install the driver program as $(target)-g++
# and also as either g++ (if native) or $(tooldir)/bin/g++.
c++.install-common:
	-if [ -f cc1plus$(exeext) ] ; then \
	  if [ -f g++-cross$(exeext) ] ; then \
	    rm -f $(bindir)/$(GXX_CROSS_NAME)$(exeext); \
	    $(INSTALL_PROGRAM) g++-cross$(exeext) $(bindir)/$(GXX_CROSS_NAME)$(exeext); \
	    chmod a+x $(bindir)/$(GXX_CROSS_NAME)$(exeext); \
	    rm -f $(bindir)/$(CXX_CROSS_NAME)$(exeext); \
	    $(LN) $(bindir)/$(GXX_CROSS_NAME)$(exeext) $(bindir)/$(CXX_CROSS_NAME)$(exeext); \
	  else \
	    rm -f $(bindir)/$(GXX_INSTALL_NAME)$(exeext); \
	    $(INSTALL_PROGRAM) g++$(exeext) $(bindir)/$(GXX_INSTALL_NAME)$(exeext); \
	    chmod a+x $(bindir)/$(GXX_INSTALL_NAME)$(exeext); \
	    rm -f $(bindir)/$(CXX_INSTALL_NAME)$(exeext); \
	    $(LN) $(bindir)/$(GXX_INSTALL_NAME)$(exeext) $(bindir)/$(CXX_INSTALL_NAME)$(exeext); \
	  fi ; \
	  if [ x$(DEMANGLER_PROG) != x ] && [ -x "$(DEMANGLER_PROG)" ]; then \
	    if [ -f g++-cross$(exeext) ] ; then \
	      rm -f $(bindir)/$(DEMANGLER_CROSS_NAME)$(exeext); \
	      $(INSTALL_PROGRAM) $(DEMANGLER_PROG) $(bindir)/$(DEMANGLER_CROSS_NAME)$(exeext); \
	      chmod a+x $(bindir)/$(DEMANGLER_CROSS_NAME)$(exeext); \
	    else \
	      rm -f $(bindir)/$(DEMANGLER_INSTALL_NAME)$(exeext); \
	      $(INSTALL_PROGRAM) $(DEMANGLER_PROG) $(bindir)/$(DEMANGLER_INSTALL_NAME)$(exeext); \
	      chmod a+x $(bindir)/$(DEMANGLER_INSTALL_NAME)$(exeext); \
	    fi ; \
	  fi ; \
	fi

c++.install-info:

c++.install-man: $(srcdir)/cp/g++.1
	-if [ -f cc1plus$(exeext) ] ; then \
	  if [ -f g++-cross$(exeext) ] ; then \
	    rm -f $(mandir)/$(GXX_CROSS_NAME)$(manext); \
	    $(INSTALL_DATA) $(srcdir)/cp/g++.1 $(mandir)/$(GXX_CROSS_NAME)$(manext); \
	    chmod a-x $(mandir)/$(GXX_CROSS_NAME)$(manext); \
	  else \
	    rm -f $(mandir)/$(GXX_INSTALL_NAME)$(manext); \
	    $(INSTALL_DATA) $(srcdir)/cp/g++.1 $(mandir)/$(GXX_INSTALL_NAME)$(manext); \
	    chmod a-x $(mandir)/$(GXX_INSTALL_NAME)$(manext); \
	  fi; \
	else true; fi

c++.uninstall:
	-rm -rf $(bindir)/$(CXX_INSTALL_NAME)$(exeext)
	-rm -rf $(bindir)/$(CXX_CROSS_NAME)$(exeext)
	-rm -rf $(bindir)/$(GXX_INSTALL_NAME)$(exeext)
	-rm -rf $(bindir)/$(GXX_CROSS_NAME)$(exeext)
	-rm -rf $(bindir)/$(DEMANGLER_INSTALL_NAME)$(exeext)
	-rm -rf $(bindir)/$(DEMANGLER_CROSS_NAME)$(exeext)
	-rm -rf $(mandir)/$(GXX_INSTALL_NAME)$(manext)
	-rm -rf $(mandir)/$(GXX_CROSS_NAME)$(manext)
#
# Clean hooks:
# A lot of the ancillary files are deleted by the main makefile.
# We just have to delete files specific to us.

c++.mostlyclean:
	-rm -f cp/*$(objext) $(DEMANGLER_PROG)
c++.clean:
	-rm -f cplib2.txt cplib2.ready
c++.distclean:
	-rm -f cp/config.status cp/Makefile
	-rm -f cp/parse.output
	-rm -f g++.c
c++.extraclean:
c++.maintainer-clean:
	-rm -f cp/parse.c cp/parse.h
#
# Stage hooks:
# The main makefile has already created stage?/cp.

c++.stage1: stage1-start
	-mv cp/*$(objext) stage1/cp
c++.stage2: stage2-start
	-mv cp/*$(objext) stage2/cp
c++.stage3: stage3-start
	-mv cp/*$(objext) stage3/cp
c++.stage4: stage4-start
	-mv cp/*$(objext) stage4/cp
#
# Maintenance hooks:

# This target creates the files that can be rebuilt, but go in the
# distribution anyway.  It then copies the files to the distdir directory.
c++.distdir:
	mkdir tmp/cp
	mkdir tmp/cp/inc
	cd cp ; $(MAKE) $(FLAGS_TO_PASS) $(CXX_FLAGS_TO_PASS) parse.c hash.h
	cd cp; \
	for file in *[0-9a-zA-Z+]; do \
	  $(LN) $$file ../tmp/cp; \
	done
	cd cp/inc; \
	for file in *[0-9a-zA-Z+]; do \
	  ln $$file ../../tmp/cp/inc >/dev/null 2>&1 \
	   || cp $$file ../../tmp/cp/inc; \
	done
# Top level makefile fragment for GNU Fortran.           -*-makefile-*-
#   Copyright (C) 1995-1998 Free Software Foundation, Inc.

#This file is part of GNU Fortran.

#GNU Fortran is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2, or (at your option)
#any later version.

#GNU Fortran is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with GNU Fortran; see the file COPYING.  If not, write to
#the Free Software Foundation, 59 Temple Place - Suite 330,
#Boston, MA 02111-1307, USA.

# This file provides the language dependent support in the main Makefile.
# Each language makefile fragment must provide the following targets:
#
# foo.all.build, foo.all.cross, foo.start.encap, foo.rest.encap,
# foo.info, foo.dvi,
# foo.install-normal, foo.install-common, foo.install-info, foo.install-man,
# foo.uninstall, foo.distdir,
# foo.mostlyclean, foo.clean, foo.distclean, foo.extraclean,
# foo.maintainer-clean, foo.stage1, foo.stage2, foo.stage3, foo.stage4
#
# where `foo' is the name of the language.
#
# It should also provide rules for:
#
# - making any compiler driver (eg: g++)
# - the compiler proper (eg: cc1plus)
# - define the names for selecting the language in LANGUAGES.
#
# $(srcdir) must be set to the gcc/ source directory (not gcc/f/).
#
# Actual name to use when installing a native compiler.
G77_INSTALL_NAME = `t='$(program_transform_name)'; echo g77 | sed $$t`

# Actual name to use when installing a cross-compiler.
G77_CROSS_NAME = `t='$(program_transform_cross_name)'; echo g77 | sed $$t`
#
# Define the names for selecting f77 in LANGUAGES.
# Note that it would be nice to move the dependency on g77
# into the F77 rule, but that needs a little bit of work
# to do the right thing within all.cross.
F77 f77: f771$(exeext)

# Tell GNU make to ignore these if they exist.
.PHONY: F77 f77 f77.all.build f77.all.cross \
  f77.start.encap f77.rest.encap f77.info f77.dvi \
  f77.install-normal \
  f77.install-common f77.install-info f77.install-man \
  f77.uninstall f77.mostlyclean f77.clean f77.distclean \
  f77.extraclean f77.maintainer-clean f77.distdir f77.rebuilt \
  f77.stage1 f77.stage2 f77.stage3 f77.stage4

g77.c: $(srcdir)/gcc.c
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
	if [ -f lang-f77 ]; then \
	  rm -f g77.c; \
	  $(LN_S) $(srcdir)/gcc.c g77.c; \
	else true; fi

g77spec.o: $(srcdir)/f/g77spec.c $(srcdir)/f/version.h
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
	if [ -f lang-f77 ]; then \
	  $(CC) -c $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) $(srcdir)/f/g77spec.c; \
	else true; fi

g77version.o: $(srcdir)/f/version.c
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
	if [ -f lang-f77 ]; then \
	  $(CC) -c $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -o g77version.o \
	    $(srcdir)/f/version.c; \
	else true; fi

# N.B.: This is a copy of the gcc.o rule, with -DLANG_SPECIFIC_DRIVER added.
# It'd be nice if we could find an easier way to do this---rather than have
# to track changes to the toplevel gcc Makefile as well.
# We depend on g77.c last, to make it obvious where it came from.
g77.o: $(CONFIG_H) multilib.h config.status $(lang_specs_files) g77.c
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
	if [ -f lang-f77 ]; then \
	  $(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) $(DRIVER_DEFINES) \
	   -DLANG_SPECIFIC_DRIVER -c g77.c; \
	else true; fi

# Create the compiler driver for g77.
g77$(exeext): g77.o g77spec.o g77version.o version.o choose-temp.o pexecute.o prefix.o mkstemp.o \
  $(LIBDEPS) $(EXTRA_GCC_OBJS)
	if [ -f lang-f77 ]; then \
	  $(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $@ g77.o g77spec.o g77version.o \
	   version.o choose-temp.o pexecute.o prefix.o mkstemp.o $(EXTRA_GCC_OBJS) $(LIBS); \
	else true; fi

# Create a version of the g77 driver which calls the cross-compiler.
g77-cross$(exeext): g77$(exeext)
	if [ -f lang-f77 ]; then \
	  rm -f g77-cross$(exeext); \
	  cp g77$(exeext) g77-cross$(exeext); \
	else true; fi

F77_SRCS = \
 $(srcdir)/f/assert.j \
 $(srcdir)/f/bad.c \
 $(srcdir)/f/bad.def \
 $(srcdir)/f/bad.h \
 $(srcdir)/f/bit.c \
 $(srcdir)/f/bit.h \
 $(srcdir)/f/bld-op.def \
 $(srcdir)/f/bld.c \
 $(srcdir)/f/bld.h \
 $(srcdir)/f/com-rt.def \
 $(srcdir)/f/com.c \
 $(srcdir)/f/com.h \
 $(srcdir)/f/config.j \
 $(srcdir)/f/convert.j \
 $(srcdir)/f/data.c \
 $(srcdir)/f/data.h \
 $(srcdir)/f/equiv.c \
 $(srcdir)/f/equiv.h \
 $(srcdir)/f/expr.c \
 $(srcdir)/f/expr.h \
 $(srcdir)/f/fini.c \
 $(srcdir)/f/flags.j \
 $(srcdir)/f/glimits.j \
 $(srcdir)/f/global.c \
 $(srcdir)/f/global.h \
 $(srcdir)/f/hconfig.j \
 $(srcdir)/f/implic.c \
 $(srcdir)/f/implic.h \
 $(srcdir)/f/input.j \
 $(srcdir)/f/info-b.def \
 $(srcdir)/f/info-k.def \
 $(srcdir)/f/info-w.def \
 $(srcdir)/f/info.c \
 $(srcdir)/f/info.h \
 $(srcdir)/f/intrin.c \
 $(srcdir)/f/intrin.def \
 $(srcdir)/f/intrin.h \
 $(srcdir)/f/lab.c \
 $(srcdir)/f/lab.h \
 $(srcdir)/f/lex.c \
 $(srcdir)/f/lex.h \
 $(srcdir)/f/malloc.c \
 $(srcdir)/f/malloc.h \
 $(srcdir)/f/name.c \
 $(srcdir)/f/name.h \
 $(srcdir)/f/output.j \
 $(srcdir)/f/parse.c \
 $(srcdir)/f/proj.c \
 $(srcdir)/f/proj.h \
 $(srcdir)/f/rtl.j \
 $(srcdir)/f/src.c \
 $(srcdir)/f/src.h \
 $(srcdir)/f/st.c \
 $(srcdir)/f/st.h \
 $(srcdir)/f/sta.c \
 $(srcdir)/f/sta.h \
 $(srcdir)/f/stb.c \
 $(srcdir)/f/stb.h \
 $(srcdir)/f/stc.c \
 $(srcdir)/f/stc.h \
 $(srcdir)/f/std.c \
 $(srcdir)/f/std.h \
 $(srcdir)/f/ste.c \
 $(srcdir)/f/ste.h \
 $(srcdir)/f/storag.c \
 $(srcdir)/f/storag.h \
 $(srcdir)/f/stp.c \
 $(srcdir)/f/stp.h \
 $(srcdir)/f/str-1t.fin \
 $(srcdir)/f/str-2t.fin \
 $(srcdir)/f/str-fo.fin \
 $(srcdir)/f/str-io.fin \
 $(srcdir)/f/str-nq.fin \
 $(srcdir)/f/str-op.fin \
 $(srcdir)/f/str-ot.fin \
 $(srcdir)/f/str.c \
 $(srcdir)/f/str.h \
 $(srcdir)/f/sts.c \
 $(srcdir)/f/sts.h \
 $(srcdir)/f/stt.c \
 $(srcdir)/f/stt.h \
 $(srcdir)/f/stu.c \
 $(srcdir)/f/stu.h \
 $(srcdir)/f/stv.c \
 $(srcdir)/f/stv.h \
 $(srcdir)/f/stw.c \
 $(srcdir)/f/stw.h \
 $(srcdir)/f/symbol.c \
 $(srcdir)/f/symbol.def \
 $(srcdir)/f/symbol.h \
 $(srcdir)/f/system.j \
 $(srcdir)/f/target.c \
 $(srcdir)/f/target.h \
 $(srcdir)/f/tconfig.j \
 $(srcdir)/f/tm.j \
 $(srcdir)/f/top.c \
 $(srcdir)/f/top.h \
 $(srcdir)/f/toplev.j \
 $(srcdir)/f/tree.j \
 $(srcdir)/f/type.c \
 $(srcdir)/f/type.h \
 $(srcdir)/f/version.c \
 $(srcdir)/f/version.h \
 $(srcdir)/f/where.c \
 $(srcdir)/f/where.h

f771$(exeext): $(P) $(F77_SRCS) $(LIBDEPS) stamp-objlist
	touch lang-f77
	cd f; $(MAKE) $(FLAGS_TO_PASS) \
	  HOST_CC="$(HOST_CC)" HOST_CFLAGS="$(HOST_CFLAGS)" HOST_CPPFLAGS="$(HOST_CPPFLAGS)" \
	  ../f771$(exeext)

#
# Build hooks:

f77.all.build: g77$(exeext)
f77.all.cross: g77-cross$(exeext)
f77.start.encap: g77$(exeext)
f77.rest.encap:

f77.info: f/g77.info
f77.dvi: f/g77.dvi

# g77 documentation.
f/g77.info: $(srcdir)/f/g77.texi $(srcdir)/f/bugs.texi \
	    $(srcdir)/f/g77install.texi $(srcdir)/f/news.texi \
	    $(srcdir)/f/intdoc.texi
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
	if [ -f lang-f77 ]; then \
	  rm -f $(srcdir)/f/g77.info-*; \
	  $(MAKEINFO) -I$(srcdir)/f -o f/g77.info $(srcdir)/f/g77.texi; \
	else true; fi

f/g77.dvi: $(srcdir)/f/g77.texi $(srcdir)/f/bugs.texi \
	    $(srcdir)/f/g77install.texi $(srcdir)/f/news.texi \
	    $(srcdir)/f/intdoc.texi
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
# `tex2dvi' was used below, but the Texinfo 3.12 one won't work properly
# with the include files from $(srcdir).  This use of TEXINPUTS may not
# be universally valid.  `$(TEX)' should be used if it gets defined in
# gcc/Makefile.in.
	if [ -f lang-f77 ]; then \
	  TEXINPUTS=$(srcdir)/f:$$TEXINPUTS tex $(srcdir)/f/g77.texi; \
	  texindex g77.??; \
	  TEXINPUTS=$(srcdir)/f:$$TEXINPUTS tex $(srcdir)/f/g77.texi; \
	  mv g77.dvi f; \
	else true; fi

# This dance is all about producing accurate documentation for g77's
# intrinsics with minimum fuss.  f/ansify appends "\n\" to C strings
# so ANSI C compilers can compile f/intdoc.h -- gcc can compile f/intdoc.in
# directly, if f/intdoc.c #include'd that, but we don't want to force
# people to install gcc just to build the documentation.  We use the
# C format for f/intdoc.in in the first place to allow a fairly "free",
# but widely known format for documentation -- basically anyone who knows
# how to write texinfo source and enclose it in C constants can handle
# it, and f/ansify allows them to not even end lines with "\n\".  So,
# essentially, the C preprocessor and compiler are used to enter the
# document snippets into a data base via name lookup, rather than duplicating
# that kind of code here.  And we use f/intdoc.c instead of straight
# texinfo in the first place so that as much information as possible
# contained in f/intrin.def can be inserted directly and reliably into
# the documentation.  That's better than replicating it, because it
# reduces the likelihood of discrepancies between the docs and the compiler
# itself, which uses f/intrin.def; in fact, many bugs in f/intrin.def have
# been found only upon reading the documentation that was automatically
# produced from it.
$(srcdir)/f/intdoc.texi: f/intdoc.c f/intdoc.in f/ansify.c f/intrin.def f/intrin.h
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
	if [ -f lang-f77 ]; then \
	  $(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) $(INCLUDES) \
	   `echo $(srcdir)/f/ansify.c | sed 's,^\./,,'` -o f/ansify; \
	  f/ansify < $(srcdir)/f/intdoc.in > f/intdoc.h0 $(srcdir)/f/intdoc.in; \
	  $(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) $(INCLUDES) -I./f \
	   `echo $(srcdir)/f/intdoc.c | sed 's,^\./,,'` -o f/intdoc; \
	  f/intdoc > $(srcdir)/f/intdoc.texi; \
	  rm f/intdoc f/ansify f/intdoc.h0; \
	else true; fi

$(srcdir)/f/BUGS: f/bugs0.texi f/bugs.texi
	cd $(srcdir)/f; $(MAKEINFO) -D BUGSONLY --no-header --no-split \
	  --no-validate -o BUGS bugs0.texi

$(srcdir)/f/INSTALL: f/install0.texi f/g77install.texi
	cd $(srcdir)/f; $(MAKEINFO) -D INSTALLONLY --no-header --no-split \
	  --no-validate -o INSTALL install0.texi

$(srcdir)/f/NEWS: f/news0.texi f/news.texi
	cd $(srcdir)/f; $(MAKEINFO) -D NEWSONLY --no-header --no-split \
	  --no-validate -o NEWS news0.texi

f77.rebuilt: f/g77.info $(srcdir)/f/BUGS $(srcdir)/f/INSTALL \
  $(srcdir)/f/NEWS 

#
# Install hooks:
# f771 is installed elsewhere as part of $(COMPILERS).

f77.install-normal:

# Install the driver program as $(target)-g77
# and also as either g77 (if native) or $(tooldir)/bin/g77.
f77.install-common:
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
	-if [ -f lang-f77 -a -f f771$(exeext) ] ; then \
	  if [ -f g77-cross$(exeext) ] ; then \
	    rm -f $(bindir)/$(G77_CROSS_NAME)$(exeext); \
	    $(INSTALL_PROGRAM) g77-cross$(exeext) $(bindir)/$(G77_CROSS_NAME)$(exeext); \
	    chmod a+x $(bindir)/$(G77_CROSS_NAME)$(exeext); \
	  else \
	    rm -f $(bindir)/$(G77_INSTALL_NAME)$(exeext); \
	    $(INSTALL_PROGRAM) g77$(exeext) $(bindir)/$(G77_INSTALL_NAME)$(exeext); \
	    chmod a+x $(bindir)/$(G77_INSTALL_NAME)$(exeext); \
	  fi ; \
	else true; fi
	@if [ -f f77-install-ok -o -f $(srcdir)/f77-install-ok ]; then \
	  echo ''; \
	  echo 'Warning: egcs no longer installs an f77 command.'; \
	  echo '         You must do so yourself.  For more information,'; \
	  echo '         read "Distributing Binaries" in the egcs g77 docs.'; \
	  echo '         (To turn off this warning, delete the file'; \
	  echo '         f77-install-ok in the source or build directory.)'; \
	  echo ''; \
	else true; fi

# $(INSTALL_DATA) might be a relative pathname, so we can't cd into srcdir
# to do the install.  The sed rule was copied from stmp-int-hdrs.
f77.install-info: f77.info
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
	if [ -f lang-f77 -a -f f/g77.info ] ; then \
	  rm -f $(infodir)/g77.info*; \
	  for f in f/g77.info*; do \
	      realfile=`echo $$f | sed -e 's|.*/\([^/]*\)$$|\1|'`; \
	      $(INSTALL_DATA) $$f $(infodir)/$$realfile; \
	  done; \
	  chmod a-x $(infodir)/g77.info*; \
	fi
	@if [ -f lang-f77 -a -f $(srcdir)/f/g77.info ] ; then \
	  if $(SHELL) -c 'install-info --version | sed 1q | fgrep -s -v -i debian' >/dev/null 2>&1; then \
	    echo " install-info --info-dir=$(infodir) $(infodir)/g77.info"; \
	    install-info --info-dir=$(infodir) $(infodir)/g77.info || : ; \
	  else : ; fi; \
	else : ; fi

f77.install-man: $(srcdir)/f/g77.1
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
	-if [ -f lang-f77 -a -f f771$(exeext) ] ; then \
	  if [ -f g77-cross$(exeext) ] ; then \
	    rm -f $(mandir)/$(G77_CROSS_NAME)$(manext); \
	    $(INSTALL_DATA) $(srcdir)/f/g77.1 $(mandir)/$(G77_CROSS_NAME)$(manext); \
	    chmod a-x $(mandir)/$(G77_CROSS_NAME)$(manext); \
	  else \
	    rm -f $(mandir)/$(G77_INSTALL_NAME)$(manext); \
	    $(INSTALL_DATA) $(srcdir)/f/g77.1 $(mandir)/$(G77_INSTALL_NAME)$(manext); \
	    chmod a-x $(mandir)/$(G77_INSTALL_NAME)$(manext); \
	  fi; \
	else true; fi

f77.uninstall:
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
	@if [ -f lang-f77 ] ; then \
	  if $(SHELL) -c 'install-info --version | sed 1q | fgrep -s -v -i debian' >/dev/null 2>&1; then \
	    echo " install-info --delete --info-dir=$(infodir) $(infodir)/g77.info"; \
	    install-info --delete --info-dir=$(infodir) $(infodir)/g77.info || : ; \
	  else : ; fi; \
	else : ; fi
	-if [ -f lang-f77 ]; then \
	  rm -rf $(bindir)/$(G77_INSTALL_NAME)$(exeext); \
	  rm -rf $(bindir)/$(G77_CROSS_NAME)$(exeext); \
	  rm -rf $(mandir)/$(G77_INSTALL_NAME)$(manext); \
	  rm -rf $(mandir)/$(G77_CROSS_NAME)$(manext); \
	  rm -rf $(infodir)/g77.info*; \
	fi
#
# Clean hooks:
# A lot of the ancillary files are deleted by the main makefile.
# We just have to delete files specific to us.

f77.mostlyclean:
	-rm -f f/*$(objext)
	-rm -f f/fini f/stamp-str f/str-*.h f/str-*.j
	-rm -f f/intdoc f/ansify f/intdoc.h0
	-rm -f g77.aux g77.cps g77.ky g77.toc g77.vr g77.fn g77.kys \
	       g77.pg g77.tp g77.vrs g77.cp g77.fns g77.log g77.pgs g77.tps 
f77.clean:
	-rm -f g77.c g77.o g77spec.o g77version.o
f77.distclean:
	-rm -f lang-f77 f/Makefile
f77.extraclean:
f77.maintainer-clean:
	-rm -f f/g77.info* f/g77.*aux f/TAGS f/BUGS f/INSTALL f/NEWS f/intdoc.texi
#
# Stage hooks:
# The main makefile has already created stage?/f.

G77STAGESTUFF = f/*$(objext) f/fini f/stamp-str f/str-*.h f/str-*.j \
  lang-f77 g77.c g77.o g77spec.o g77version.o

f77.stage1: stage1-start
	-if [ -f lang-f77 ]; then \
	  mv -f $(G77STAGESTUFF) stage1/f; \
	fi
f77.stage2: stage2-start
	-if [ -f lang-f77 ]; then \
	  mv -f $(G77STAGESTUFF) stage2/f; \
	fi
f77.stage3: stage3-start
	-if [ -f lang-f77 ]; then \
	  mv -f $(G77STAGESTUFF) stage3/f; \
	fi
f77.stage4: stage4-start
	-if [ -f lang-f77 ]; then \
	  mv -f $(G77STAGESTUFF) stage4/f; \
	fi
#
# Maintenance hooks:

# This target creates the files that can be rebuilt, but go in the
# distribution anyway.  It then copies the files to the distdir directory.
f77.distdir: f77.rebuilt
	case "$(LANGUAGES)" in \
	  *[fF]77*) touch lang-f77;; \
	  *) rm -f lang-f77;; \
	esac
	-if [ -f lang-f77 ]; then \
	  mkdir tmp/f; \
	  cd f; \
	  for file in *[0-9a-zA-Z+]; do \
	    $(LN_S) $$file ../tmp/f; \
	  done; \
	fi
# Top level makefile fragment for GNU Objective-C
#   Copyright (C) 1997, 1998 Free Software Foundation, Inc.

#This file is part of GNU CC.

#GNU CC is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2, or (at your option)
#any later version.

#GNU CC is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with GNU CC; see the file COPYING.  If not, write to
#the Free Software Foundation, 59 Temple Place - Suite 330,
#Boston, MA 02111-1307, USA.

# This file provides the language dependent support in the main Makefile.
# Each language makefile fragment must provide the following targets:
#
# foo.all.build, foo.all.cross, foo.start.encap, foo.rest.encap,
# foo.info, foo.dvi,
# foo.install-normal, foo.install-common, foo.install-info, foo.install-man,
# foo.uninstall, foo.distdir,
# foo.mostlyclean, foo.clean, foo.distclean, foo.extraclean,
# foo.maintainer-clean, foo.stage1, foo.stage2, foo.stage3, foo.stage4
#
# where `foo' is the name of the language.
#
# It should also provide rules for:
#
# - making any compiler driver (eg: g++)
# - the compiler proper (eg: cc1plus)
# - define the names for selecting the language in LANGUAGES.
#
# Extra flags to pass to recursive makes.
OBJC_FLAGS_TO_PASS = \
	"OBJC_FOR_BUILD=$(OBJC_FOR_BUILD)" \
	"OBJCFLAGS=$(OBJCFLAGS)" \
	"OBJC_FOR_TARGET=$(OBJC_FOR_TARGET)" \

# Actual names to use when installing a native compiler.
#OBJC_INSTALL_NAME = `t='$(program_transform_name)'; echo c++ | sed $$t`

# Actual names to use when installing a cross-compiler.
#OBJC_CROSS_NAME = `t='$(program_transform_cross_name)'; echo c++ | sed $$t`

#
# Define the names for selecting Objective-C in LANGUAGES.
OBJC objc: cc1obj$(exeext) objc-runtime
OBJECTIVE-C objective-c: cc1obj$(exeext) objc-runtime

# Tell GNU make to ignore these if they exist.
.PHONY: objective-c objc ObjC

# The Objective C thread file
OBJC_THREAD_FILE=thr-$(GCC_THREAD_FILE)

# Language-specific object files for Objective C.
OBJC_OBJS = objc-parse.o objc-act.o $(C_AND_OBJC_OBJS)

cc1obj$(exeext): $(P) $(OBJC_OBJS) $(OBJS) $(LIBDEPS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $@ $(OBJC_OBJS) $(OBJS) \
		$(LIBS)

# Objective C language specific files.

objc-parse.o : $(srcdir)/objc/objc-parse.c \
   $(CONFIG_H) $(TREE_H) $(srcdir)/toplev.h \
   $(srcdir)/c-lex.h $(srcdir)/c-tree.h $(srcdir)/input.h \
   $(srcdir)/flags.h $(srcdir)/output.h $(srcdir)/objc/objc-act.h system.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -I$(srcdir)/objc \
	-c $(srcdir)/objc/objc-parse.c

$(srcdir)/objc/objc-parse.c : $(srcdir)/objc/objc-parse.y
	cd $(srcdir)/objc; \
	$(BISON) $(BISONFLAGS) objc-parse.y -o objc-parse.c

$(srcdir)/objc/objc-parse.y: $(srcdir)/c-parse.in
	echo '/*WARNING: This file is automatically generated!*/' >tmp-objc-prs.y
	sed -e "/^ifc$$/,/^end ifc$$/d" \
	  -e "/^ifobjc$$/d" -e "/^end ifobjc$$/d" \
	  $(srcdir)/c-parse.in >>tmp-objc-prs.y
	$(srcdir)/move-if-change tmp-objc-prs.y $(srcdir)/objc/objc-parse.y

objc-act.o : $(srcdir)/objc/objc-act.c \
   $(CONFIG_H) $(TREE_H) $(RTL_H) system.h \
   $(srcdir)/c-tree.h $(srcdir)/c-lex.h $(srcdir)/toplev.h \
   $(srcdir)/flags.h $(srcdir)/objc/objc-act.h $(srcdir)/input.h \
   $(srcdir)/function.h $(srcdir)/output.h $(srcdir)/c-parse.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -I$(srcdir)/objc \
	-c $(srcdir)/objc/objc-act.c

objc-runtime: objc-headers libobjc.a

# copy objc header files into build directory
objc-headers: stmp-fixinc
	if [ -d include ]; then true; else mkdir include; fi
	cd objc; \
	if [ -f Makefile ]; then \
	  $(MAKE) copy-headers \
	  tooldir=$(tooldir) \
	  AR="$(AR)" AR_FLAGS="$(AR_FLAGS)" \
	  GCC_FOR_TARGET="../xgcc -B../" \
	  GCC_CFLAGS="$(GCC_CFLAGS)" incinstalldir=../include; \
	fi
	touch objc-headers

# Objective C runtime library specific files.

OBJC_O = objc/hash.o objc/sarray.o \
	objc/class.o objc/sendmsg.o \
	objc/init.o objc/archive.o \
	objc/encoding.o objc/selector.o \
	objc/objects.o objc/misc.o \
	objc/NXConstStr.o objc/Object.o \
	objc/Protocol.o objc/nil_method.o \
	objc/thr.o objc/linking.o \
	objc/$(OBJC_THREAD_FILE).o

objc/hash.o: $(srcdir)/objc/hash.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/hash.c -o $@
objc/sarray.o: $(srcdir)/objc/sarray.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/sarray.c -o $@
objc/class.o: $(srcdir)/objc/class.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/class.c -o $@
objc/sendmsg.o: $(srcdir)/objc/sendmsg.c $(GCC_PASSES) objc/runtime-info.h
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) -Iobjc \
	-c $(srcdir)/objc/sendmsg.c -o $@
objc/init.o: $(srcdir)/objc/init.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/init.c -o $@
objc/archive.o: $(srcdir)/objc/archive.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/archive.c -o $@
objc/encoding.o: $(srcdir)/objc/encoding.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/encoding.c -o $@
objc/selector.o: $(srcdir)/objc/selector.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/selector.c -o $@
objc/objects.o: $(srcdir)/objc/objects.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/objects.c -o $@
objc/misc.o: $(srcdir)/objc/misc.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/misc.c -o $@
objc/NXConstStr.o: $(srcdir)/objc/NXConstStr.m $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-fgnu-runtime -c $(srcdir)/objc/NXConstStr.m -o $@
objc/Object.o: $(srcdir)/objc/Object.m $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-fgnu-runtime -c $(srcdir)/objc/Object.m -o $@
objc/Protocol.o: $(srcdir)/objc/Protocol.m $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-fgnu-runtime -c $(srcdir)/objc/Protocol.m -o $@
objc/thr.o: $(srcdir)/objc/thr.h $(srcdir)/objc/thr.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/thr.c -o $@
objc/$(OBJC_THREAD_FILE).o: $(srcdir)/objc/$(OBJC_THREAD_FILE).c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/$(OBJC_THREAD_FILE).c -o $@
objc/nil_method.o: $(srcdir)/objc/nil_method.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/nil_method.c -o $@
objc/linking.o: $(srcdir)/objc/linking.m $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-fgnu-runtime -c $(srcdir)/objc/linking.m -o $@

objc/libobjc_entry.o: $(srcdir)/objc/libobjc_entry.c $(GCC_PASSES)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) \
	-c $(srcdir)/objc/libobjc_entry.c -o $@

$(OBJC_O): $(GCC_PASSES) cc1obj$(exeext)

# Build the Objective C runtime library.
libobjc.a: cc1obj$(exeext) specs stmp-int-hdrs libgcc2.ready \
 $(USE_COLLECT2) $(EXTRA_PARTS) objc/runtime-info.h $(OBJC_O)
	-rm -f libobjc.a
	$(AR) $(AR_FLAGS) libobjc.a $(OBJC_O)
	-if $(RANLIB_TEST) ; then $(RANLIB) libobjc.a; else true; fi

libobjc_s.a: libobjc.a
	mv libobjc.a libobjc_s.a

# Create a relocatable DLL
libobjc.dll: libobjc_s.a objc/libobjc_entry.o
	$(GCC_FOR_TARGET) -mdll -Wl,--base-file -Wl,libobjc.base \
		-o libobjc.dll libobjc_s.a \
		objc/libobjc_entry.o -lkernel32
	$(DLLTOOL) --dllname libobjc.dll --def $(srcdir)/objc/libobjc.def \
		--base-file libobjc.base --output-exp libobjc.exp
	$(GCC_FOR_TARGET) -mdll -Wl,--base-file libobjc.base libobjc.exp \
		-o libobjc.dll libobjc_s.a \
		objc/libobjc_entry.o -lkernel32
	$(DLLTOOL) --dllname libobjc.dll --def $(srcdir)/objc/libobjc.def \
		--base-file libobjc.base --output-exp libobjc.exp
	$(GCC_FOR_TARGET) libobjc.exp -mdll \
		-o libobjc.dll libobjc_s.a \
		objc/libobjc_entry.o -lkernel32
	$(DLLTOOL) --dllname libobjc.dll --def $(srcdir)/objc/libobjc.def \
		--output-lib libobjc.a

# Platform generated information needed by ObjC runtime
objc/runtime-info.h: cc1obj$(exeext)
	echo "" > tmp-runtime
	echo "/* This file is automatically generated */" >$@
	./cc1obj -print-objc-runtime-info tmp-runtime >>$@
	rm -f tmp-runtime
#
# Build hooks:

objc.all.build:
objc.all.cross:
objc.start.encap:
objc.rest.encap:

objc.info:
objc.dvi:

#
# Install hooks:
# cc1obj is installed elsewhere as part of $(COMPILERS).

objc.install-normal: installdirs
	-if [ -f libobjc.a ] ; then \
	  rm -f $(libsubdir)/libobjc.a; \
	  $(INSTALL_DATA) libobjc.a $(libsubdir)/libobjc.a; \
	  if $(RANLIB_TEST) ; then \
	    (cd $(libsubdir); $(RANLIB) libobjc.a); else true; fi; \
	  chmod a-x $(libsubdir)/libobjc.a; \
	else true; fi
	-if [ -f libobjc_s.a ] ; then \
	  rm -f $(libsubdir)/libobjc_s.a; \
	  $(INSTALL_DATA) libobjc_s.a $(libsubdir)/libobjc_s.a; \
	  if $(RANLIB_TEST) ; then \
	    (cd $(libsubdir); $(RANLIB) libobjc_s.a); else true; fi; \
	  chmod a-x $(libsubdir)/libobjc_s.a; \
	else true; fi
	-if [ -f libobjc.dll ] ; then \
	  rm -f $(bindir)/libobjc.dll; \
	  $(INSTALL_DATA) libobjc.dll $(bindir)/libobjc.dll; \
	else true; fi

objc.install-common:

objc.install-info:

objc.install-man:

objc.uninstall:
#
# Clean hooks:
# A lot of the ancillary files are deleted by the main makefile.
# We just have to delete files specific to us.
objc.mostlyclean:
	-rm -f tmp-objc-prs.y
	-rm -f objc/*$(objext) objc/xforward objc/fflags
	-rm -f objc/runtime-info.h
	-rm -f libobjc.a libobjc_s.a libobjc.dll
	-rm -f libobjc.base libobjc.exp
objc.clean: objc.mostlyclean
	-rm -rf objc-headers
objc.distclean:
	-rm -f objc/Makefile objc/Make-host objc/Make-target
	-rm -f objc/config.status objc/config.cache
	-rm -f objc-parse.output
objc.extraclean:
objc.maintainer-clean:
	-rm -f objc/objc-parse.y
	-rm -f objc/objc-parse.c objc/objc-parse.output

#
# Stage hooks:

objc.stage1: stage1-start
	-mv objc/*$(objext) stage1/objc
	-mv cc1obj$(exeext) stage1
	-mv libobjc.a stage1
objc.stage2: stage2-start
	-mv objc/*$(objext) stage2/objc
	-mv cc1obj$(exeext) stage2
	-mv libobjc.a stage2
objc.stage3: stage3-start
	-mv objc/*$(objext) stage3/objc
	-mv cc1obj$(exeext) stage3
	-mv libobjc.a stage3
objc.stage4: stage4-start
	-mv objc/*$(objext) stage4/objc
	-mv cc1obj$(exeext) stage4
	-mv libobjc.a stage4

#
# Maintenance hooks:

# This target creates the files that can be rebuilt, but go in the
# distribution anyway.  It then copies the files to the distdir directory.
# ??? Note that this should be fixed once the Makefile is fixed to do
# the build in the inner directory.
objc.distdir: $(srcdir)/objc/objc-parse.c
	mkdir tmp/objc
#	cd objc ; $(MAKE) $(FLAGS_TO_PASS) objc-parse.c
	cd objc; \
	for file in *[0-9a-zA-Z+]; do \
	  ln $$file ../tmp/objc >/dev/null 2>&1 || cp $$file ../tmp/objc; \
	done

# End of language makefile fragments.
#
# The only suffixes we want for implicit rules are .c and .o, so clear
# the list and add them.  This speeds up GNU Make, and allows -r to work.
.SUFFIXES:
.SUFFIXES: .c .o

Makefile: $(srcdir)/Makefile.in config.status $(srcdir)/version.c \
   $(xmake_file) $(tmake_file) $(LANG_MAKEFILES)
	$(SHELL) $(srcdir)/configure.frag $(srcdir) "$(SUBDIRS)" \
		"$(xmake_file)" "$(tmake_file)"
	cp config.status config.run
	$(SHELL) config.run
	rm -f config.run

$(srcdir)/configure: $(srcdir)/configure.in
	cd $(srcdir); autoconf

# cstamp-h.in controls rebuilding of config.in.
# It is named cstamp-h.in and not stamp-h.in so the mostlyclean rule doesn't
# delete it.  A stamp file is needed as autoheader won't update the file if
# nothing has changed.
# It remains in the source directory and is part of the distribution.
# This follows what is done in shellutils, fileutils, etc.
# "echo timestamp" is used instead of touch to be consistent with other
# packages that use autoconf (??? perhaps also to avoid problems with patch?).
# ??? Newer versions have a maintainer mode that may be useful here.
$(srcdir)/config.in: $(srcdir)/cstamp-h.in
$(srcdir)/cstamp-h.in: $(srcdir)/configure.in $(srcdir)/acconfig.h
	cd $(srcdir) && autoheader
	@rm -f $(srcdir)/cstamp-h.in
	echo timestamp > $(srcdir)/cstamp-h.in
auto-host.h: cstamp-h ; @true
cstamp-h: config.in config.status
	CONFIG_HEADERS=auto-host.h:config.in $(SHELL) config.status

# Really, really stupid make features, such as SUN's KEEP_STATE, may force
# a target to build even if it is up-to-date.  So we must verify that
# config.status does not exist before failing.
config.status: configure version.c
	@if [ ! -f config.status ] ; then \
	  echo You must configure gcc.  Look at the INSTALL file for details.; \
	  false; \
	else \
	  $(SHELL) config.status --recheck; \
	fi

all.internal: start.encap rest.encap
# This is what to compile if making a cross-compiler.
# Note that we can compile enquire using the cross-compiler just built,
# although we can't run it on this machine.
all.cross: native gcc-cross specs stmp-headers $(STMP_FIXPROTO) $(LIBGCC) \
	$(LIBGCC1_TEST) $(EXTRA_PARTS) lang.all.cross
# This is what to compile if making gcc with a cross-compiler.
all.build: native xgcc$(exeext) $(EXTRA_PARTS) lang.all.build
# This is what must be made before installing GCC and converting libraries.
start.encap: native xgcc$(exeext) specs $(LIBGCC1) xlimits.h lang.start.encap
# These can't be made until after GCC can run.
rest.encap: stmp-headers $(STMP_FIXPROTO) $(LIBGCC) $(EXTRA_PARTS) lang.rest.encap
# This is what is made with the host's compiler
# whether making a cross compiler or not.
native: config.status auto-host.h cpp$(exeext) $(LANGUAGES) \
	$(EXTRA_PASSES) $(EXTRA_PROGRAMS) $(USE_COLLECT2)

# Define the names for selecting languages in LANGUAGES.
C c: cc1$(exeext)
PROTO: proto

# Tell GNU make these are phony targets.
.PHONY: C c PROTO proto

# On the target machine, finish building a cross compiler.
# This does the things that can't be done on the host machine.
rest.cross: $(LIBGCC) gfloat.h specs

# Verify that it works to compile and link libgcc1-test.
# If it does, then there are sufficient replacements for libgcc1.a.
libgcc1-test: libgcc1-test.o native $(GCC_PARTS)
	@echo "Testing libgcc1.  Ignore linker warning messages."
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) libgcc1-test.o -o libgcc1-test \
	  -nostartfiles -nostdlib `$(GCC_FOR_TARGET) --print-libgcc-file-name`
libgcc1-test.o: libgcc1-test.c native xgcc$(exeext)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(ALL_CPPFLAGS) -c $(srcdir)/libgcc1-test.c

# Recompile all the language-independent object files.
# This is used only if the user explicitly asks for it.
compilations: ${OBJS}

# Create a list of the language-independent object files so the language
# subdirectories needn't mention their names explicitly.
stamp-objlist: $(OBJS) 
	echo " $(OBJS)" | sed -e 's, \([a-z0-9]\), ../\1,g' -e 's/\.o/$(objext)/g' >stamp-objlist

# We call this executable `xgcc' rather than `gcc'
# to avoid confusion if the current directory is in the path
# and CC is `gcc'.  It is renamed to `gcc' when it is installed.
xgcc$(exeext): gcc.o version.o choose-temp.o pexecute.o prefix.o version.o \
   mkstemp.o $(LIBDEPS) $(EXTRA_GCC_OBJS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $@ gcc.o prefix.o version.o \
	  choose-temp.o pexecute.o mkstemp.o $(EXTRA_GCC_OBJS) $(LIBS)

# Dump a specs file to make -B./ read these specs over installed ones.
specs: xgcc$(exeext)
	$(GCC_FOR_TARGET) -dumpspecs > tmp-specs
	mv tmp-specs specs

# We do want to create an executable named `xgcc', so we can use it to
# compile libgcc2.a.
# Also create gcc-cross, so that install-common will install properly.
gcc-cross: xgcc$(exeext)
	cp xgcc$(exeext) gcc-cross$(exeext)

cc1$(exeext): $(P) $(C_OBJS) $(OBJS) $(LIBDEPS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $@ $(C_OBJS) $(OBJS) $(LIBS)

# Copy float.h from its source.
gfloat.h: $(FLOAT_H)
	-rm -f gfloat.h
	cp $(FLOAT_H) gfloat.h

# Build the version of limits.h that we will install.
xlimits.h: glimits.h limitx.h limity.h
	if $(LIMITS_H_TEST) ; then \
	  cat $(srcdir)/limitx.h $(srcdir)/glimits.h $(srcdir)/limity.h > tmp-xlimits.h; \
	else \
	  cat $(srcdir)/glimits.h > tmp-xlimits.h; \
	fi
	mv tmp-xlimits.h xlimits.h
#
# Build libgcc.a.
# This is done in two parts because some functions, in libgcc1.c,
# must be compiled with something other than GCC,
# while the rest, in libgcc2.c, must be compiled with xgcc.
# That means we can't do libgcc2.c until after xgcc, cc1, etc.

# Use this as value of LIBGCC1 to cause conversion to GNU library format.
# LIBCONVERT should put its output in libgcc1.conv.
libgcc1.conv: libgcc1.a
	$(LIBCONVERT) libgcc1.a libgcc1.conv

# Use this as value of LIBGCC1 to inhibit use of libgcc1.c entirely.
# Make an empty file instead.
libgcc1.null: $(GCC_PASSES)
	echo "void __foo () {}" > dummy.c
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) -c dummy.c
	$(OLDAR) $(OLDAR_FLAGS) libgcc1.null dummy$(objext)
	rm -f dummy$(objext) dummy.c

# This is $(LIBGCC1) for a cross-compiler.
# We have no automatic way of building libgcc1.a, 
# so it's up to the installer to find a way to do that.
# This rule deliberately does not depend on libgcc1.a
# so that it will fail if the installer hasn't provided it.
libgcc1.cross:
	mv libgcc1.a libgcc1.cross || (echo You must find a way to make libgcc1.a; false)

# Compile the library of arithmetic subroutines with the native compiler.
# Don't compile it with GCC!
# (That would cause most arithmetic functions to call themselves.)
#
# NOTE: If you modify these rules substantially, please be sure to
# check at least config/i386/t-sco5 and possibly other makefile
# fragments.
libgcc1.a: libgcc1.c $(CONFIG_H) $(LIB1FUNCS_EXTRA) config.status
	-rm -f tmplibgcc1.a
# Actually build it in tmplibgcc1.a, then rename at end,
# so that libgcc1.a itself remains nonexistent if compilation is aborted.
# -e causes any failing command to make this rule fail.
# -e doesn't work in certain shells, so we test $$? as well.
# lynx has a broken ar, it always complains when the initial library is
# empty, thus this command works only if we don't do -e
# There is a trailing backslash (\) deleted from the following line.
#	set -e;
	for name in $(LIB1FUNCS); \
	do \
	  echo $${name}; \
	  rm -f $${name}$(objext); \
	  $(OLDCC) -DIN_LIBGCC1 $(CCLIBFLAGS) $(INCLUDES) -c -DL$${name} $(srcdir)/libgcc1.c; \
	  if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	  mv libgcc1$(objext) $${name}$(objext); \
	  $(OLDAR) $(OLDAR_FLAGS) tmplibgcc1.a $${name}$(objext); \
	  rm -f $${name}$(objext); \
	done
# Some shells crash when a loop has no items.
# So make sure there is always at least one--`..'.
# Then ignore it.
# We don't use -e here because there are if statements
# that should not make the command give up when the if condition is false.
# Instead, we test for failure after each command where it matters.
	for file in .. $(LIB1FUNCS_EXTRA); \
	do \
	  if [ x$${file} != x.. ]; then \
	    name=`echo $${file} | sed -e 's/[.][cS]$$//' -e 's/[.]asm$$//'`; \
	    echo $${name}; \
	    if [ $${name}.asm = $${file} ]; then \
	      cp $${file} $${name}.s || exit 1; file=$${name}.s; \
	    else true; fi; \
	    $(OLDCC) -DIN_LIBGCC1 $(CCLIBFLAGS) $(INCLUDES) -c $${file}; \
	    if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	    $(OLDAR) $(OLDAR_FLAGS) tmplibgcc1.a $${name}$(objext); \
	    if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	    rm -f $${name}.s $${name}$(objext); \
	  else true; \
	  fi; \
	done
	-if $(RANLIB_TEST) ; then $(RANLIB) tmplibgcc1.a; else true; fi
	mv tmplibgcc1.a libgcc1.a

# Build libgcc1.a from assembler source.  LIB1ASMFUNCS is the list of
# functions.  LIB1ASMSRC is the name of the source file in the config
# subdirectory.
libgcc1-asm.a: libgcc2.ready config.status $(srcdir)/config/$(LIB1ASMSRC)
	-rm -f tmplibgcc1.a libgcc1.S
	cp $(srcdir)/config/$(LIB1ASMSRC) libgcc1.S
# Actually build it in tmplibgcc1.a, then rename at end,
# so that libgcc1-asm.a itself remains nonexistent if compilation is aborted.
# -e causes any failing command to make this rule fail.
# -e doesn't work in certain shells, so we test $$? as well.
# lynx has a broken ar, it always complains when the initial library is
# empty, thus this command works only if we don't do -e
# There is a trailing backslash (\) deleted from the following line.
#	set -e;
	for name in $(LIB1ASMFUNCS); \
	do \
	  echo $${name}; \
	  $(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) -c -DL$${name} libgcc1.S; \
	  if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	  mv libgcc1$(objext) $${name}$(objext); \
	  $(AR) $(AR_FLAGS) tmplibgcc1.a $${name}$(objext); \
	  rm -f $${name}$(objext); \
	done
	-rm -f libgcc1.S
	mv tmplibgcc1.a libgcc1-asm.a

# Generate assembly versions of the functions required for libgcc1.
# You'll still need to massage the code by hand (possibly hacking
# underscores and local labels) but this will get you started.
libgcc1.S: libgcc1.c $(CONFIG_H) config.status
	-rm -f libgcc1.S
	touch libgcc1.S
	for name in $(LIB1FUNCS); \
	do \
	  echo $${name}; \
	  $(OLDCC) -DIN_LIBGCC1 $(CCLIBFLAGS) $(INCLUDES) -S -DL$${name} $(srcdir)/libgcc1.c; \
	  if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	  echo '#ifdef ' L$${name} >> libgcc1.S; \
	  cat  libgcc1.s >> libgcc1.S; \
	  echo '#endif /*' L$${name} '*/' >> libgcc1.S; \
	  echo "" >> libgcc1.S; \
	done

# Compiling libgcc2.a requires making sure that cc1, etc. have been compiled.
# But recompiling cc1 should not force recompilation of libgcc2.a.
# If you want to force recompilation, delete libgcc2.a.
libgcc2.ready: $(GCC_PASSES) $(LIBGCC2_DEPS) stmp-int-hdrs $(STMP_FIXPROTO)
	-if [ -f libgcc2.ready ] ; then \
		true; \
	else \
		touch libgcc2.ready; \
	fi

LIB2ADD = $(srcdir)/frame.c $(LIB2FUNCS_EXTRA) $(LANG_LIB2FUNCS)
libgcc2.a: libgcc2.c libgcc2.ready $(CONFIG_H) $(FPBIT) $(DPBIT) $(LIB2ADD) \
   machmode.h longlong.h frame.h gansidecl.h gbl-ctors.h config.status
# Actually build it in tmplibgcc2.a, then rename at end,
# so that libgcc2.a itself remains nonexistent if compilation is aborted.
	-rm -f tmplibgcc2.a
# -e causes any failing command to make this rule fail.
# -e doesn't work in certain shells, so we test $$? as well.
# lynx has a broken ar, it always complains when the initial library is
# empty, thus this command works only if we don't do -e
# There is a trailing backslash (\) deleted from the following line.
#	set -e;
	for name in $(LIB2FUNCS); \
	do \
	  echo $${name}; \
	  $(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) -c -DL$${name} \
	      $(srcdir)/libgcc2.c -o $${name}$(objext); \
	  if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	  $(AR) $(AR_FLAGS) tmplibgcc2.a $${name}$(objext); \
	  rm -f $${name}$(objext); \
	done
	for name in $(LIB2FUNCS_EH); \
	do \
	  echo $${name}; \
	  $(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) -fexceptions $(INCLUDES) -c \
	      -DL$${name} $(srcdir)/libgcc2.c -o $${name}$(objext); \
	  if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	  $(AR) $(AR_FLAGS) tmplibgcc2.a $${name}$(objext); \
	  rm -f $${name}$(objext); \
	done
	if [ x$(FPBIT) != x ]; then \
	  for name in $(FPBIT_FUNCS); \
	  do \
	    echo $${name}; \
	    $(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) -c -DL$${name} \
	        -DFINE_GRAINED_LIBRARIES $(FPBIT) -o $${name}$(objext); \
	    if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	    $(AR) $(AR_FLAGS) tmplibgcc2.a $${name}$(objext); \
	    rm -f $${name}$(objext); \
	  done; \
	else true; fi;
	if [ x$(DPBIT) != x ]; then \
	  for name in $(DPBIT_FUNCS); \
	  do \
	    echo $${name}; \
	    $(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) -c -DL$${name} \
	        -DFINE_GRAINED_LIBRARIES $(DPBIT) -o $${name}$(objext); \
	    if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	    $(AR) $(AR_FLAGS) tmplibgcc2.a $${name}$(objext); \
	    rm -f $${name}$(objext); \
	  done; \
	else true; fi;
# Some shells crash when a loop has no items.
# So make sure there is always at least one--`..'.
# Then ignore it.
# We don't use -e here because there are if statements
# that should not make the command give up when the if condition is false.
# Instead, we test for failure after each command where it matters.
	for file in $(LIB2ADD); do \
	  name=`echo $${file} | sed -e 's/[.][cSo]$$//' -e 's/[.]asm$$//' -e 's/[.]txt$$//'`; \
	  oname=` echo $${name} | sed -e 's,.*/,,'`; \
	  if [ $${name}.txt = $${file} ]; then \
	    for f in .. `cat $${file}`; do if [ x$${f} != x.. ]; then \
	      $(MAKE) GCC_FOR_TARGET="$(GCC_FOR_TARGET)" \
		AR="$(AR)" AR_FLAGS="$(AR_FLAGS)" CC="$(CC)" \
		CFLAGS="$(CFLAGS)" HOST_PREFIX="$(HOST_PREFIX)" \
		HOST_PREFIX_1="$(HOST_PREFIX_1)" \
		LANGUAGES="$(LANGUAGES)" \
		LIBGCC2_CFLAGS="$(LIBGCC2_CFLAGS)" $${f}; \
	      if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	      $(AR) $(AR_FLAGS) tmplibgcc2.a $${f}; \
	      rm -f $${f}; \
	    else true; \
	    fi; done; \
	  else \
	    echo $${name}; \
	    if [ $${name}.asm = $${file} ]; then \
	      cp $${file} $${name}.s || exit 1; file=$${name}.s; \
	    else true; fi; \
	    $(GCC_FOR_TARGET) $(LIBGCC2_CFLAGS) $(INCLUDES) -c $${file}; \
	    if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	    $(AR) $(AR_FLAGS) tmplibgcc2.a $${oname}$(objext); \
	    rm -f $${name}.s $${oname}$(objext); \
	  fi; \
	done
	mv tmplibgcc2.a libgcc2.a
# These lines were deleted from above the mv command
# because ranlibing libgcc.a itself should suffice.
#	-if [ x${HPUX_GAS} = x ] ; then \
#	  if $(RANLIB_TEST) ; then $(RANLIB) tmplibgcc2.a; else true; fi; \
#	else true; fi

# Combine the various libraries into a single library, libgcc.a.
libgcc.a: $(LIBGCC1) $(LIBGCC2)
	-rm -rf tmplibgcc.a libgcc.a tmpcopy
	mkdir tmpcopy
	-if [ x$(LIBGCC1) != x ];			\
	then (cd tmpcopy; $(AR) x ../$(LIBGCC1));	\
	else true;					\
	fi
# Some versions of ar (specifically the one in RISC/os 5.x), create an
# unwritable table of contents file, and then print an error message when
# the second ar command tries to overwrite this file.  To avoid the error
# message from ar, we make sure all files are writable.
	-(cd tmpcopy; chmod +w * > /dev/null 2>&1)
	(cd tmpcopy; $(AR) x ../$(LIBGCC2))
	(cd tmpcopy; $(AR) $(AR_FLAGS) ../tmplibgcc.a *$(objext))
	rm -rf tmpcopy
	-if $(RANLIB_TEST) ; then $(RANLIB) tmplibgcc.a; else true; fi
# Actually build it in tmplibgcc.a, then rename at end,
# so that libgcc.a itself remains nonexistent if compilation is aborted.
	mv tmplibgcc.a libgcc.a

# Use the genmultilib shell script to generate the information the gcc
# driver program needs to select the library directory based on the
# switches.
multilib.h: s-mlib; @true
s-mlib: $(srcdir)/genmultilib Makefile
	$(SHELL) $(srcdir)/genmultilib \
	  "$(MULTILIB_OPTIONS)" \
	  "$(MULTILIB_DIRNAMES)" \
	  "$(MULTILIB_MATCHES)" \
	  "$(MULTILIB_EXCEPTIONS)" \
	  "$(MULTILIB_EXTRA_OPTS)" > tmp-mlib.h
	$(srcdir)/move-if-change tmp-mlib.h multilib.h
	touch s-mlib

# Build multiple copies of libgcc.a, one for each target switch.
stmp-multilib: $(LIBGCC1) libgcc2.c libgcc2.ready $(CONFIG_H) \
   frame.h gansidecl.h \
   $(LIB2ADD) machmode.h longlong.h gbl-ctors.h config.status
	for i in `$(GCC_FOR_TARGET) --print-multi-lib`; do \
	  dir=`echo $$i | sed -e 's/;.*$$//'`; \
	  flags=`echo $$i | sed -e 's/^[^;]*;//' -e 's/@/ -/g'`; \
	  $(MAKE) GCC_FOR_TARGET="$(GCC_FOR_TARGET)" \
	    AR="$(AR)" AR_FLAGS="$(AR_FLAGS)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
	    RANLIB="$(RANLIB)" RANLIB_TEST="$(RANLIB_TEST)" \
	    LANGUAGES="$(LANGUAGES)" \
	    HOST_PREFIX="$(HOST_PREFIX)" HOST_PREFIX_1="$(HOST_PREFIX_1)" \
	    LIBGCC2_CFLAGS="$(LIBGCC2_CFLAGS) $${flags}" \
	    MULTILIB_CFLAGS="$${flags}" \
	    LIBGCC1="$(LIBGCC1)" LIBGCC2="$(LIBGCC2)" \
	    dir="$${dir}" stmp-multilib-sub; \
	  if [ $$? -eq 0 ] ; then true; else exit 1; fi; \
	done
	touch stmp-multilib

# Subroutine of stmp-multilib so make -n works.
stmp-multilib-sub:
	rm -f $(LIBGCC2)
	if [ -d $(dir) ]; then \
	  cd $(dir); \
	  rm -f libgcc.a $(EXTRA_MULTILIB_PARTS); \
	else true; \
	fi
	$(MAKE) GCC_FOR_TARGET="$(GCC_FOR_TARGET)" \
	  AR="$(AR)" AR_FLAGS="$(AR_FLAGS)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
	  HOST_PREFIX="$(HOST_PREFIX)" HOST_PREFIX_1="$(HOST_PREFIX_1)" \
	  LANGUAGES="$(LANGUAGES)" \
	  LIBGCC2_CFLAGS="$(LIBGCC2_CFLAGS)" $(LIBGCC2)
	if [ x$(LIBGCC1) != xlibgcc1-asm.a ]; \
	then true; \
	else rm -f $(LIBGCC1); \
	fi
	if [ x$(LIBGCC1) != xlibgcc1-asm.a ]; \
	then true; \
	else \
	  $(MAKE) GCC_FOR_TARGET="$(GCC_FOR_TARGET)" \
	    AR="$(AR)" AR_FLAGS="$(AR_FLAGS)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
	    HOST_PREFIX="$(HOST_PREFIX)" HOST_PREFIX_1="$(HOST_PREFIX_1)" \
	    LANGUAGES="$(LANGUAGES)" \
	    LIBGCC2_CFLAGS="$(LIBGCC2_CFLAGS)" $(LIBGCC1); \
	fi
	rm -rf tmplibgcc.a tmpcopy
	mkdir tmpcopy
	if [ x$(LIBGCC1) != x ]; \
	then (cd tmpcopy; $(AR) x ../$(LIBGCC1)); \
	else true; \
	fi
	(cd tmpcopy; $(AR) x ../$(LIBGCC2))
	(cd tmpcopy; $(AR) $(AR_FLAGS) ../tmplibgcc.a *$(objext))
	rm -rf libgcc2.a tmpcopy
	if $(RANLIB_TEST) ; then $(RANLIB) tmplibgcc.a; else true; fi
	if [ -d $(dir) ]; then true; else mkdir $(dir); fi
	mv tmplibgcc.a $(dir)/libgcc.a
	for f in .. $(EXTRA_MULTILIB_PARTS); do if [ x$${f} != x.. ]; then \
	  $(MAKE) GCC_FOR_TARGET="$(GCC_FOR_TARGET)" \
	    AR="$(AR)" AR_FLAGS="$(AR_FLAGS)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
	    HOST_PREFIX="$(HOST_PREFIX)" HOST_PREFIX_1="$(HOST_PREFIX_1)" \
	    LANGUAGES="$(LANGUAGES)" \
	    MULTILIB_CFLAGS="$(MULTILIB_CFLAGS)" T="t" t$${f}; \
	  mv t$${f} $(dir)/$${f}; \
	else true; \
	fi; done

# Compile two additional files that are linked with every program
# linked using GCC on systems using COFF or ELF, for the sake of C++
# constructors.
$(T)crtbegin.o: crtstuff.c $(GCC_PASSES) $(CONFIG_H) \
  defaults.h frame.h gbl-ctors.h
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) $(MULTILIB_CFLAGS) -g0 \
	  -finhibit-size-directive -fno-inline-functions -fno-exceptions $(CRTSTUFF_T_CFLAGS) \
	  -c $(srcdir)/crtstuff.c -DCRT_BEGIN -o $(T)crtbegin$(objext)

$(T)crtend.o: crtstuff.c $(GCC_PASSES) $(CONFIG_H) \
  defaults.h frame.h gbl-ctors.h
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) $(MULTILIB_CFLAGS) -g0 \
	  -finhibit-size-directive -fno-inline-functions -fno-exceptions $(CRTSTUFF_T_CFLAGS) \
	  -c $(srcdir)/crtstuff.c -DCRT_END -o $(T)crtend$(objext)

# On some systems we also want to install versions of these files
# compiled using PIC for use in shared libraries.
crtbeginS.o crtendS.o: s-crtS ; @true

s-crtS: crtstuff.c $(GCC_PASSES) $(CONFIG_H) \
  defaults.h frame.h gbl-ctors.h
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) $(CRTSTUFF_T_CFLAGS_S) \
	  -DCRT_BEGIN -DCRTSTUFFS_O -finhibit-size-directive -fno-inline-functions \
	  -fno-exceptions -g0 -c $(srcdir)/crtstuff.c 
	mv crtstuff$(objext) crtbeginS$(objext)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(INCLUDES) $(CRTSTUFF_T_CFLAGS_S) \
	  -DCRT_END -DCRTSTUFFS_O -finhibit-size-directive -fno-inline-functions \
	  -fno-exceptions -g0 -c $(srcdir)/crtstuff.c -o crtendS$(objext)
	touch s-crtS

# Compile the start modules crt0.o and mcrt0.o that are linked with every program
crt0.o: s-crt0 ; @true
mcrt0.o: s-crt0; @true

s-crt0:	$(CRT0_S) $(MCRT0_S) $(GCC_PASSES) $(CONFIG_H)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(CRT0STUFF_T_CFLAGS) \
	  -o crt0.o -c $(CRT0_S)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(CRT0STUFF_T_CFLAGS) \
	  -o mcrt0.o -c $(MCRT0_S)
	touch s-crt0
#
# Compiling object files from source files.

# Note that dependencies on obstack.h are not written
# because that file is not part of GCC.

# C language specific files.

c-parse.o : $(srcdir)/c-parse.c $(CONFIG_H) $(TREE_H) c-lex.h \
    $(srcdir)/c-parse.h c-tree.h input.h flags.h system.h toplev.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -c $(srcdir)/c-parse.c
$(srcdir)/c-parse.h: $(srcdir)/c-parse.c
$(srcdir)/c-parse.c: $(srcdir)/c-parse.y
	cd $(srcdir); $(BISON) $(BISONFLAGS) -d c-parse.y -o c-parse.c
$(srcdir)/c-parse.y: c-parse.in
	echo '/*WARNING: This file is automatically generated!*/' >tmp-c-parse.y
	sed -e "/^ifobjc$$/,/^end ifobjc$$/d" \
	  -e "/^ifc$$/d" -e "/^end ifc$$/d" \
	  $(srcdir)/c-parse.in >>tmp-c-parse.y
	$(srcdir)/move-if-change tmp-c-parse.y $(srcdir)/c-parse.y

$(srcdir)/c-gperf.h: c-parse.gperf
	gperf -p -j1 -i 1 -g -o -t -G -N is_reserved_word -k1,3,$$ \
	   $(srcdir)/c-parse.gperf >tmp-gperf.h
	 $(srcdir)/move-if-change tmp-gperf.h $(srcdir)/c-gperf.h

c-decl.o : c-decl.c $(CONFIG_H) system.h $(TREE_H) c-tree.h c-lex.h flags.h \
    output.h toplev.h
c-typeck.o : c-typeck.c $(CONFIG_H) system.h $(TREE_H) c-tree.h flags.h \
    output.h $(EXPR_H) $(RTL_H) toplev.h
c-lang.o : c-lang.c $(CONFIG_H) system.h $(TREE_H) c-tree.h c-lex.h toplev.h \
    output.h
c-lex.o : c-lex.c $(CONFIG_H) system.h $(TREE_H) $(RTL_H) c-lex.h c-tree.h \
    $(srcdir)/c-parse.h input.h flags.h $(srcdir)/c-gperf.h c-pragma.h \
    toplev.h output.h
c-aux-info.o : c-aux-info.c  $(CONFIG_H) system.h $(TREE_H) c-tree.h flags.h
c-convert.o : c-convert.c $(CONFIG_H) system.h $(TREE_H) flags.h toplev.h
c-pragma.o: c-pragma.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) except.h \
    function.h defaults.h c-pragma.h toplev.h
c-iterate.o: c-iterate.c $(CONFIG_H) system.h $(TREE_H) $(RTL_H) c-tree.h \
    flags.h toplev.h $(EXPR_H)

collect2$(exeext): collect2.o tlink.o hash.o cplus-dem.o underscore.o \
	version.o choose-temp.o mkstemp.o $(LIBDEPS)
# Don't try modifying collect2 (aka ld) in place--it might be linking this.
	-rm -f collect2$(exeext)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $@ collect2.o tlink.o hash.o \
	  cplus-dem.o underscore.o version.o choose-temp.o mkstemp.o $(LIBS)

collect2.o : collect2.c $(CONFIG_H) system.h gansidecl.h gstab.h obstack.h \
	$(DEMANGLE_H)
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES)  \
	-DTARGET_MACHINE=\"$(target_alias)\" $(MAYBE_USE_COLLECT2) \
	-c `echo $(srcdir)/collect2.c | sed 's,^\./,,'`

tlink.o: tlink.c $(DEMANGLE_H) hash.h $(CONFIG_H) system.h toplev.h
hash.o: hash.c hash.h system.h toplev.h
cplus-dem.o: cplus-dem.c $(DEMANGLE_H)

underscore.c: s-under ; @true

s-under: $(GCC_PASSES)
	echo "int xxy_us_dummy;" >tmp-dum.c
	$(GCC_FOR_TARGET) -S tmp-dum.c
	echo '/*WARNING: This file is automatically generated!*/' >tmp-under.c
	if grep _xxy_us_dummy tmp-dum.s > /dev/null ; then \
	  echo "int prepends_underscore = 1;" >>tmp-under.c; \
	else \
	  echo "int prepends_underscore = 0;" >>tmp-under.c; \
	fi
	$(srcdir)/move-if-change tmp-under.c underscore.c
	-rm -f tmp-dum.c tmp-dum.s
	touch s-under

# A file used by all variants of C.

c-common.o : c-common.c $(CONFIG_H) system.h $(TREE_H) c-tree.h c-lex.h \
	flags.h toplev.h output.h

# Language-independent files.

DRIVER_DEFINES = \
  -DSTANDARD_STARTFILE_PREFIX=\"$(libdir)/\" \
  -DSTANDARD_EXEC_PREFIX=\"$(libdir)/gcc-lib/\" \
  -DDEFAULT_TARGET_VERSION=\"$(version)\" \
  -DDEFAULT_TARGET_MACHINE=\"$(target_alias)\" \
  -DTOOLDIR_BASE_PREFIX=\"$(exec_prefix)/\"
gcc.o: gcc.c $(CONFIG_H) system.h gansidecl.h multilib.h Makefile \
	$(lang_specs_files)
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) \
  $(DRIVER_DEFINES) \
  -c `echo $(srcdir)/gcc.c | sed 's,^\./,,'`

tree-check.h: s-check ; @true
s-check : gencheck $(srcdir)/move-if-change
	./gencheck > tmp-check.h
	$(srcdir)/move-if-change tmp-check.h tree-check.h
	touch s-check

gencheck : gencheck.o tree.def $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 gencheck.o $(HOST_LIBS)

gencheck.o : gencheck.c hconfig.h system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/gencheck.c

dumpvers: dumpvers.c

version.o: version.c
obstack.o: obstack.c $(CONFIG_H)
choose-temp.o: choose-temp.c $(CONFIG_H) gansidecl.h system.h
mkstemp.o: mkstemp.c $(CONFIG_H) gansidecl.h system.h
pexecute.o: pexecute.c $(CONFIG_H) system.h gansidecl.h
prefix.o: prefix.c $(CONFIG_H) system.h gansidecl.h Makefile
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) \
	-DPREFIX=\"$(prefix)\" \
	  -c `echo $(srcdir)/prefix.c | sed 's,^\./,,'`

convert.o: convert.c $(CONFIG_H) $(TREE_H) flags.h convert.h toplev.h

tree.o : tree.c $(CONFIG_H) system.h $(TREE_H) flags.h function.h toplev.h except.h
print-tree.o : print-tree.c $(CONFIG_H) system.h $(TREE_H)
stor-layout.o : stor-layout.c $(CONFIG_H) system.h $(TREE_H) flags.h \
   function.h $(EXPR_H) $(RTL_H) toplev.h except.h
fold-const.o : fold-const.c $(CONFIG_H) system.h $(TREE_H) flags.h toplev.h
toplev.o : toplev.c $(CONFIG_H) system.h $(TREE_H) $(RTL_H) \
   flags.h input.h insn-attr.h xcoffout.h defaults.h output.h \
   insn-codes.h insn-config.h $(RECOG_H) Makefile toplev.h dwarfout.h \
   dwarf2out.h sdbout.h dbxout.h \
   $(lang_options_files)
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) $(MAYBE_USE_COLLECT2) \
	  -DTARGET_NAME=\"$(target_alias)\" \
	  -c `echo $(srcdir)/toplev.c | sed 's,^\./,,'`

rtl.o : rtl.c $(CONFIG_H) system.h $(RTL_H) bitmap.h

print-rtl.o : print-rtl.c $(CONFIG_H) system.h $(RTL_H) bitmap.h
rtlanal.o : rtlanal.c $(CONFIG_H) system.h $(RTL_H)

varasm.o : varasm.c $(CONFIG_H) system.h $(TREE_H) $(RTL_H) flags.h \
   function.h defaults.h $(EXPR_H) hard-reg-set.h $(REGS_H) \
   xcoffout.h output.h c-pragma.h toplev.h except.h dbxout.h sdbout.h
function.o : function.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) flags.h \
   function.h insn-flags.h insn-codes.h $(EXPR_H) $(REGS_H) hard-reg-set.h \
   insn-config.h $(RECOG_H) output.h toplev.h except.h
stmt.o : stmt.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) flags.h function.h  \
   insn-flags.h insn-config.h insn-codes.h hard-reg-set.h $(EXPR_H) except.h \
   loop.h $(RECOG_H) toplev.h output.h
except.o : except.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) flags.h \
   function.h insn-flags.h $(EXPR_H) $(REGS_H) hard-reg-set.h \
   insn-config.h $(RECOG_H) output.h except.h toplev.h
expr.o : expr.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) flags.h function.h \
   $(REGS_H) insn-flags.h insn-codes.h $(EXPR_H) insn-config.h $(RECOG_H) output.h \
   typeclass.h hard-reg-set.h toplev.h hard-reg-set.h except.h
calls.o : calls.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) flags.h $(EXPR_H) \
   insn-flags.h $(REGS_H) toplev.h output.h
expmed.o : expmed.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) flags.h  \
   insn-flags.h insn-config.h insn-codes.h $(EXPR_H) $(RECOG_H) real.h
explow.o : explow.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) flags.h \
   hard-reg-set.h insn-config.h $(EXPR_H) $(RECOG_H) insn-flags.h insn-codes.h
optabs.o : optabs.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) flags.h  \
   insn-flags.h insn-config.h insn-codes.h $(EXPR_H) $(RECOG_H) reload.h
dbxout.o : dbxout.c $(CONFIG_H) system.h $(TREE_H) $(RTL_H) flags.h $(REGS_H) \
   insn-config.h reload.h gstab.h xcoffout.h defaults.h output.h dbxout.h \
   toplev.h
sdbout.o : sdbout.c $(CONFIG_H) system.h $(TREE_H) $(RTL_H) flags.h except.h \
   function.h $(EXPR_H) output.h hard-reg-set.h $(REGS_H) defaults.h real.h \
   insn-config.h obstack.h xcoffout.h c-pragma.h sdbout.h toplev.h
dwarfout.o : dwarfout.c $(CONFIG_H) system.h $(TREE_H) $(RTL_H) dwarf.h \
   flags.h insn-config.h reload.h output.h defaults.h toplev.h dwarfout.h
dwarf2out.o : dwarf2out.c $(CONFIG_H) system.h $(TREE_H) $(RTL_H) dwarf2.h \
   flags.h insn-config.h reload.h output.h defaults.h \
   hard-reg-set.h $(REGS_H) $(EXPR_H) toplev.h dwarf2out.h dyn-string.h
xcoffout.o : xcoffout.c $(CONFIG_H) system.h $(TREE_H) $(RTL_H) xcoffout.h \
   flags.h toplev.h output.h dbxout.h
emit-rtl.o : emit-rtl.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) flags.h \
   except.h function.h $(REGS_H) insn-config.h $(RECOG_H) real.h \
   $(EXPR_H) obstack.h hard-reg-set.h bitmap.h
real.o : real.c $(CONFIG_H) system.h $(TREE_H) toplev.h
getpwd.o : getpwd.c $(CONFIG_H) system.h

integrate.o : integrate.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) flags.h \
   integrate.h insn-flags.h insn-config.h $(EXPR_H) real.h $(REGS_H) \
   function.h output.h $(RECOG_H) except.h toplev.h

jump.o : jump.c $(CONFIG_H) system.h $(RTL_H) flags.h hard-reg-set.h $(REGS_H) \
   insn-config.h insn-flags.h $(RECOG_H) $(EXPR_H) real.h except.h \
   toplev.h insn-attr.h
stupid.o : stupid.c $(CONFIG_H) system.h $(RTL_H) $(REGS_H) hard-reg-set.h \
   flags.h toplev.h

cse.o : cse.c $(CONFIG_H) system.h $(RTL_H) $(REGS_H) hard-reg-set.h flags.h \
   real.h insn-config.h $(RECOG_H) $(EXPR_H) toplev.h output.h
gcse.o : gcse.c $(CONFIG_H) system.h $(RTL_H) $(REGS_H) hard-reg-set.h flags.h \
   real.h insn-config.h $(RECOG_H) $(EXPR_H) $(BASIC_BLOCK_H) output.h
profile.o : profile.c $(CONFIG_H) system.h $(RTL_H) flags.h insn-flags.h \
   gcov-io.h $(TREE_H) output.h $(REGS_H) toplev.h
loop.o : loop.c $(CONFIG_H) system.h $(RTL_H) flags.h loop.h insn-config.h \
   insn-flags.h $(REGS_H) hard-reg-set.h $(RECOG_H) $(EXPR_H) real.h \
   toplev.h
unroll.o : unroll.c $(CONFIG_H) system.h $(RTL_H) insn-config.h \
   integrate.h $(REGS_H) $(RECOG_H) flags.h $(EXPR_H) loop.h toplev.h
flow.o : flow.c $(CONFIG_H) system.h $(RTL_H) flags.h insn-config.h \
   $(BASIC_BLOCK_H) $(REGS_H) hard-reg-set.h output.h toplev.h
combine.o : combine.c $(CONFIG_H) system.h $(RTL_H) flags.h  \
   insn-config.h insn-flags.h insn-codes.h insn-attr.h $(REGS_H) $(EXPR_H) \
   $(BASIC_BLOCK_H) $(RECOG_H) real.h hard-reg-set.h toplev.h
regclass.o : regclass.c $(CONFIG_H) system.h $(RTL_H) hard-reg-set.h flags.h \
   $(BASIC_BLOCK_H) $(REGS_H) insn-config.h $(RECOG_H) reload.h real.h toplev.h \
   output.h
local-alloc.o : local-alloc.c $(CONFIG_H) system.h $(RTL_H) flags.h \
   $(BASIC_BLOCK_H) $(REGS_H) hard-reg-set.h insn-config.h $(RECOG_H) output.h \
   insn-attr.h toplev.h
bitmap.o : bitmap.c $(CONFIG_H) system.h $(RTL_H) flags.h $(BASIC_BLOCK_H) \
   $(REGS_H)
global.o : global.c $(CONFIG_H) system.h $(RTL_H) flags.h  \
   $(BASIC_BLOCK_H) $(REGS_H) hard-reg-set.h insn-config.h output.h toplev.h
varray.o : varray.c $(CONFIG_H) system.h varray.h $(RTL_H) $(TREE_H) bitmap.h

reload.o : reload.c $(CONFIG_H) system.h $(RTL_H) flags.h output.h $(EXPR_H) \
   reload.h $(RECOG_H) hard-reg-set.h insn-config.h insn-codes.h $(REGS_H) \
   real.h toplev.h
reload1.o : reload1.c $(CONFIG_H) system.h $(RTL_H) real.h flags.h $(EXPR_H) \
   reload.h $(REGS_H) hard-reg-set.h insn-config.h insn-flags.h insn-codes.h \
   $(BASIC_BLOCK_H) $(RECOG_H) output.h toplev.h
caller-save.o : caller-save.c $(CONFIG_H) system.h $(RTL_H) flags.h \
   $(REGS_H) hard-reg-set.h insn-config.h $(BASIC_BLOCK_H) \
   $(RECOG_H) reload.h $(EXPR_H) toplev.h
reorg.o : reorg.c $(CONFIG_H) system.h $(RTL_H) conditions.h hard-reg-set.h \
   $(BASIC_BLOCK_H) $(REGS_H) insn-config.h insn-attr.h \
   insn-flags.h $(RECOG_H) flags.h output.h $(EXPR_H)
alias.o : alias.c $(CONFIG_H) system.h $(RTL_H) flags.h hard-reg-set.h \
   $(REGS_H) toplev.h $(EXPR_H)
regmove.o : regmove.c $(CONFIG_H) system.h $(RTL_H) insn-config.h \
   $(RECOG_H) output.h reload.h $(REGS_H) hard-reg-set.h flags.h \
   $(EXPR_H) insn-flags.h $(BASIC_BLOCK_H) toplev.h
$(SCHED_PREFIX)sched.o : $(SCHED_PREFIX)sched.c $(CONFIG_H) system.h $(RTL_H) \
   $(BASIC_BLOCK_H) $(REGS_H) hard-reg-set.h flags.h insn-config.h insn-attr.h \
   toplev.h
final.o : final.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) flags.h $(REGS_H) \
   $(RECOG_H) conditions.h insn-config.h insn-attr.h except.h real.h output.h \
   hard-reg-set.h insn-flags.h insn-codes.h gstab.h xcoffout.h defaults.h \
   toplev.h reload.h dwarfout.h dwarf2out.h sdbout.h dbxout.h
recog.o : recog.c $(CONFIG_H) system.h $(RTL_H)  \
   $(REGS_H) $(RECOG_H) hard-reg-set.h flags.h insn-config.h insn-attr.h \
   insn-flags.h insn-codes.h real.h
reg-stack.o : reg-stack.c $(CONFIG_H) system.h $(RTL_H) $(TREE_H) \
   $(REGS_H) hard-reg-set.h flags.h insn-config.h insn-flags.h toplev.h
dyn-string.o: dyn-string.c dyn-string.h $(CONFIG_H) system.h gansidecl.h

$(out_object_file): $(out_file) $(CONFIG_H) $(TREE_H) \
   $(RTL_H) $(REGS_H) hard-reg-set.h real.h insn-config.h conditions.h \
   insn-flags.h output.h insn-attr.h insn-codes.h system.h toplev.h
	$(CC) -c $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) $(out_file)

# Build auxiliary files that support ecoff format.
mips-tfile: mips-tfile.o version.o $(LIBDEPS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ mips-tfile.o version.o $(LIBS)

mips-tfile.o : mips-tfile.c $(CONFIG_H) $(RTL_H) system.h machmode.h

mips-tdump: mips-tdump.o version.o $(LIBDEPS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ mips-tdump.o version.o $(LIBS)

mips-tdump.o : mips-tdump.c $(CONFIG_H) $(RTL_H) system.h

# Build file to support OSF/rose half-pic format.
halfpic.o: halfpic.c $(CONFIG_H) $(RTL_H) $(TREE_H) system.h

# Normally this target is not used; but it is used if you
# define ALLOCA=alloca.o.  In that case, you must get a suitable alloca.c
# from the GNU Emacs distribution.
alloca.o:	alloca.c
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) $(ALLOCA_FLAGS) \
	  -c `echo $(srcdir)/alloca.c | sed 's,^\./,,'`
	$(ALLOCA_FINISH)
#
# Generate header and source files from the machine description, 
# and compile them.

.PRECIOUS: insn-config.h insn-flags.h insn-codes.h \
  insn-emit.c insn-recog.c insn-extract.c insn-output.c insn-peep.c \
  insn-attr.h insn-attrtab.c

# The following pair of rules has this effect:
# genconfig is run only if the md has changed since genconfig was last run;
# but the file insn-config.h is touched only when its contents actually change.

# Each of the other insn-* files is handled by a similar pair of rules.

# This causes an anomaly in the results of make -n
# because insn-* is older than s-*
# and thus make -n thinks that insn-* will be updated
# and force recompilation of things that depend on it.
# We use move-if-change precisely to avoid such recompilation.
# But there is no way to teach make -n that it will be avoided.

# Each of the insn-*.[ch] rules has a semicolon at the end,
# for otherwise the system Make on SunOS 4.1 never tries
# to recompile insn-*.o.  To avoid problems and extra noise from
# versions of make which don't like empty commands (nothing after the
# trailing `;'), we call true for each.

insn-config.h: s-config ; @true
s-config : $(md_file) genconfig $(srcdir)/move-if-change
	./genconfig $(md_file) > tmp-config.h
	$(srcdir)/move-if-change tmp-config.h insn-config.h
	touch s-config

insn-flags.h: s-flags ; @true
s-flags : $(md_file) genflags $(srcdir)/move-if-change
	./genflags $(md_file) > tmp-flags.h
	$(srcdir)/move-if-change tmp-flags.h insn-flags.h
	touch s-flags

insn-codes.h: s-codes ; @true
s-codes : $(md_file) gencodes $(srcdir)/move-if-change
	./gencodes $(md_file) > tmp-codes.h
	$(srcdir)/move-if-change tmp-codes.h insn-codes.h
	touch s-codes

insn-emit.o : insn-emit.c $(CONFIG_H) $(RTL_H) $(EXPR_H) real.h output.h \
  insn-config.h insn-flags.h insn-codes.h system.h reload.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -c insn-emit.c

insn-emit.c: s-emit ; @true
s-emit : $(md_file) genemit $(srcdir)/move-if-change
	./genemit $(md_file) > tmp-emit.c
	$(srcdir)/move-if-change tmp-emit.c insn-emit.c
	touch s-emit

insn-recog.o : insn-recog.c $(CONFIG_H) $(RTL_H) insn-config.h $(RECOG_H) \
  real.h output.h flags.h system.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -c insn-recog.c

insn-recog.c: s-recog ; @true
s-recog : $(md_file) genrecog $(srcdir)/move-if-change
	./genrecog $(md_file) > tmp-recog.c
	$(srcdir)/move-if-change tmp-recog.c insn-recog.c
	touch s-recog

insn-opinit.o : insn-opinit.c $(CONFIG_H) $(RTL_H) insn-codes.h insn-flags.h \
  insn-config.h flags.h $(RECOG_H) $(EXPR_H) reload.h system.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -c insn-opinit.c

insn-opinit.c: s-opinit ; @true
s-opinit : $(md_file) genopinit $(srcdir)/move-if-change
	./genopinit $(md_file) > tmp-opinit.c
	$(srcdir)/move-if-change tmp-opinit.c insn-opinit.c
	touch s-opinit

insn-extract.o : insn-extract.c $(CONFIG_H) $(RTL_H) system.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -c insn-extract.c

insn-extract.c: s-extract ; @true
s-extract : $(md_file) genextract $(srcdir)/move-if-change
	./genextract $(md_file) > tmp-extract.c
	$(srcdir)/move-if-change tmp-extract.c insn-extract.c
	touch s-extract

insn-peep.o : insn-peep.c $(CONFIG_H) $(RTL_H) $(REGS_H) output.h real.h system.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -c insn-peep.c

insn-peep.c: s-peep ; @true
s-peep : $(md_file) genpeep $(srcdir)/move-if-change
	./genpeep $(md_file) > tmp-peep.c
	$(srcdir)/move-if-change tmp-peep.c insn-peep.c
	touch s-peep

insn-attrtab.o : insn-attrtab.c $(CONFIG_H) $(RTL_H) $(REGS_H) real.h output.h \
     insn-attr.h insn-config.h system.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -c insn-attrtab.c

insn-attr.h: s-attr ; @true
s-attr : $(md_file) genattr $(srcdir)/move-if-change
	./genattr $(md_file) > tmp-attr.h
	$(srcdir)/move-if-change tmp-attr.h insn-attr.h
	touch s-attr

insn-attrtab.c: s-attrtab ; @true
s-attrtab : $(md_file) genattrtab $(srcdir)/move-if-change
	if cmp -s $(PREMADE_ATTRTAB_MD) $(md_file);	\
	then					\
	  echo Using $(PREMADE_ATTRTAB);	\
	  cp $(PREMADE_ATTRTAB) tmp-attrtab.c;	\
	else					\
	  ./genattrtab $(md_file) > tmp-attrtab.c;	\
	fi
	$(srcdir)/move-if-change tmp-attrtab.c insn-attrtab.c
	touch s-attrtab

insn-output.o : insn-output.c $(CONFIG_H) $(RTL_H) $(REGS_H) real.h conditions.h \
    hard-reg-set.h insn-config.h insn-flags.h insn-attr.h output.h $(RECOG_H) \
    insn-codes.h system.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -c insn-output.c

insn-output.c: s-output ; @true
s-output : $(md_file) genoutput $(srcdir)/move-if-change
	./genoutput $(md_file) > tmp-output.c
	$(srcdir)/move-if-change tmp-output.c insn-output.c
	touch s-output

genrtl.o : genrtl.c $(CONFIG_H) $(RTL_H) system.h
genrtl.c genrtl.h : s-genrtl
	@true	# force gnu make to recheck modification times.

s-genrtl: gengenrtl $(srcdir)/move-if-change $(RTL_BASE_H)
	./gengenrtl tmp-genrtl.h tmp-genrtl.c
	$(srcdir)/move-if-change tmp-genrtl.h genrtl.h
	$(srcdir)/move-if-change tmp-genrtl.c genrtl.c
	touch s-genrtl

#
# Compile the programs that generate insn-* from the machine description.
# They are compiled with $(HOST_CC), and associated libraries,
# since they need to run on this machine
# even if GCC is being compiled to run on some other machine.

# $(CONFIG_H) is omitted from the deps of the gen*.o
# because these programs don't really depend on anything 
# about the target machine.  They do depend on config.h itself,
# since that describes the host machine.

# Pass the md file through cpp if the target requests it.
$(MD_FILE): $(MD_DEPS)
	rm -f $@
	$(MD_CPP) $(MD_CPPFLAGS) $(md_file) | sed 's/^# /; /g' > tmp-$@
	mv tmp-$@ $@

genconfig : genconfig.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	  genconfig.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBS)

genconfig.o : genconfig.c $(RTL_H) $(build_xm_file) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/genconfig.c

genflags : genflags.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 genflags.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBS)

genflags.o : genflags.c $(RTL_H) $(build_xm_file) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/genflags.c

gencodes : gencodes.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 gencodes.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBS)

gencodes.o : gencodes.c $(RTL_H) $(build_xm_file) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/gencodes.c

genemit : genemit.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 genemit.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBS)

genemit.o : genemit.c $(RTL_H) $(build_xm_file) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/genemit.c

genopinit : genopinit.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 genopinit.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBS)

genopinit.o : genopinit.c $(RTL_H) $(build_xm_file) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/genopinit.c

genrecog : genrecog.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 genrecog.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBS)

genrecog.o : genrecog.c $(RTL_H) $(build_xm_file) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/genrecog.c

genextract : genextract.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 genextract.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBS)

genextract.o : genextract.c $(RTL_H) $(build_xm_file) system.h insn-config.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/genextract.c

genpeep : genpeep.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 genpeep.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBS)

genpeep.o : genpeep.c $(RTL_H) $(build_xm_file) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/genpeep.c

genattr : genattr.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 genattr.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBS)

genattr.o : genattr.c $(RTL_H) $(build_xm_file) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/genattr.c

genattrtab : genattrtab.o $(HOST_RTL) $(HOST_PRINT) $(HOST_RTLANAL) $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 genattrtab.o $(HOST_RTL) $(HOST_PRINT) $(HOST_RTLANAL) $(HOST_LIBS)

genattrtab.o : genattrtab.c $(RTL_H)  $(build_xm_file) system.h insn-config.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/genattrtab.c

genoutput : genoutput.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 genoutput.o $(HOST_RTL) $(HOST_PRINT) $(HOST_LIBS)

genoutput.o : genoutput.c $(RTL_H) $(build_xm_file) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/genoutput.c

gengenrtl : gengenrtl.o $(HOST_LIBDEPS)
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	 gengenrtl.o $(HOST_LIBS)

gengenrtl.o : gengenrtl.c $(RTL_BASE_H) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/gengenrtl.c

#
# Compile the libraries to be used by gen*.
# If we are not cross-building, gen* use the same .o's that cc1 will use,
# and HOST_PREFIX_1 is `foobar', just to ensure these rules don't conflict
# with the rules for rtl.o, alloca.o, etc.
$(HOST_PREFIX_1)rtl.o: $(srcdir)/rtl.c $(CONFIG_H) system.h $(RTL_H) bitmap.h
	rm -f $(HOST_PREFIX)rtl.c
	sed -e 's/config[.]h/hconfig.h/' $(srcdir)/rtl.c > $(HOST_PREFIX)rtl.c
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(HOST_PREFIX)rtl.c

$(HOST_PREFIX_1)print-rtl.o: $(srcdir)/print-rtl.c $(CONFIG_H) $(RTL_H)
	rm -f $(HOST_PREFIX)print-rtl.c
	sed -e 's/config[.]h/hconfig.h/' $(srcdir)/print-rtl.c > $(HOST_PREFIX)print-rtl.c
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(HOST_PREFIX)print-rtl.c

$(HOST_PREFIX_1)bitmap.o: $(srcdir)/bitmap.c $(CONFIG_H) system.h $(RTL_H) \
  flags.h $(BASIC_BLOCK_H) $(REGS_H)
	rm -f $(HOST_PREFIX)bitmap.c
	sed -e 's/config[.]h/hconfig.h/' $(srcdir)/bitmap.c > $(HOST_PREFIX)bitmap.c
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(HOST_PREFIX)bitmap.c

$(HOST_PREFIX_1)rtlanal.o: $(srcdir)/rtlanal.c $(CONFIG_H) $(RTL_H)
	rm -f $(HOST_PREFIX)rtlanal.c
	sed -e 's/config[.]h/hconfig.h/' $(srcdir)/rtlanal.c > $(HOST_PREFIX)rtlanal.c
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(HOST_PREFIX)rtlanal.c

$(HOST_PREFIX_1)alloca.o: alloca.c
	rm -f $(HOST_PREFIX)alloca.c
	cp $(srcdir)/alloca.c $(HOST_PREFIX)alloca.c
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(HOST_PREFIX)alloca.c

$(HOST_PREFIX_1)obstack.o: obstack.c
	rm -f $(HOST_PREFIX)obstack.c
	sed -e 's/config[.]h/hconfig.h/' $(srcdir)/obstack.c > $(HOST_PREFIX)obstack.c
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(HOST_PREFIX)obstack.c

$(HOST_PREFIX_1)vfprintf.o: vfprintf.c
	rm -f $(HOST_PREFIX)vfprintf.c
	sed -e 's/config[.]h/hconfig.h/' $(srcdir)/vfprintf.c > $(HOST_PREFIX)vfprintf.c
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(HOST_PREFIX)vfprintf.c

$(HOST_PREFIX_1)doprint.o: doprint.c
	rm -f $(HOST_PREFIX)doprint.c
	sed -e 's/config[.]h/hconfig.h/' $(srcdir)/doprint.c > $(HOST_PREFIX)doprint.c
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(HOST_PREFIX)doprint.c

$(HOST_PREFIX_1)malloc.o: malloc.c
	rm -f $(HOST_PREFIX)malloc.c
	sed -e 's/config[.]h/hconfig.h/' $(srcdir)/malloc.c > $(HOST_PREFIX)malloc.c
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(HOST_PREFIX)malloc.c

# This satisfies the dependency that we get if you cross-compile a compiler
# that does not need to compile alloca, malloc or whatever.
$(HOST_PREFIX_1): 
	touch $(HOST_PREFIX_1)

#
# Remake cpp and protoize.

# Making the preprocessor
cpp$(exeext): $(CCCP)$(exeext)
	-rm -f cpp$(exeext)
	$(LN) $(CCCP)$(exeext) cpp$(exeext)
cccp$(exeext): cccp.o cexp.o version.o prefix.o $(LIBDEPS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $@ cccp.o cexp.o prefix.o \
	  version.o $(LIBS)
cexp.o: $(srcdir)/cexp.c $(CONFIG_H) system.h gansidecl.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) -c $(srcdir)/cexp.c
$(srcdir)/cexp.c: $(srcdir)/cexp.y
	cd $(srcdir); $(BISON) -o cexp.c cexp.y

cccp.o: cccp.c $(CONFIG_H) pcp.h version.c config.status system.h gansidecl.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) \
	  -DGCC_INCLUDE_DIR=\"$(libsubdir)/include\" \
	  -DGPLUSPLUS_INCLUDE_DIR=\"$(gxx_include_dir)\" \
	  -DOLD_GPLUSPLUS_INCLUDE_DIR=\"$(old_gxx_include_dir)\" \
	  -DLOCAL_INCLUDE_DIR=\"$(includedir)\" \
	  -DCROSS_INCLUDE_DIR=\"$(tooldir)/sys-include\" \
	  -DTOOL_INCLUDE_DIR=\"$(tooldir)/include\" \
	  -c `echo $(srcdir)/cccp.c | sed 's,^\./,,'`

cppmain$(exeext): cppmain.o cpplib.o cpphash.o cppalloc.o cpperror.o cppexp.o \
  prefix.o version.o $(LIBDEPS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $@ cppmain.o cpplib.o cpphash.o \
	  cppalloc.o cpperror.o cppexp.o prefix.o version.o $(LIBS)

cppmain.o: cppmain.c $(CONFIG_H) cpplib.h system.h gansidecl.h

cpplib.o: cpplib.c $(CONFIG_H) cpplib.h cpphash.h config.status system.h \
	gansidecl.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) \
	  -DGCC_INCLUDE_DIR=\"$(libsubdir)/include\" \
	  -DGPLUSPLUS_INCLUDE_DIR=\"$(gxx_include_dir)\" \
	  -DOLD_GPLUSPLUS_INCLUDE_DIR=\"$(old_gxx_include_dir)\" \
	  -DLOCAL_INCLUDE_DIR=\"$(includedir)\" \
	  -DCROSS_INCLUDE_DIR=\"$(tooldir)/sys-include\" \
	  -DTOOL_INCLUDE_DIR=\"$(tooldir)/include\" \
	  -c `echo $(srcdir)/cpplib.c | sed 's,^\./,,'`

cpperror.o: cpperror.c $(CONFIG_H) cpplib.h system.h gansidecl.h

cppexp.o: cppexp.c $(CONFIG_H) cpplib.h system.h gansidecl.h

cpphash.o: cpphash.c cpplib.h cpphash.h $(CONFIG_H) system.h gansidecl.h

cppalloc.o: cppalloc.c $(CONFIG_H) cpplib.h system.h gansidecl.h

# Note for the stamp targets, we run the program `true' instead of
# having an empty command (nothing following the semicolon).

proto: config.status protoize$(exeext) unprotoize$(exeext) SYSCALLS.c.X

protoize$(exeext): protoize.o getopt.o getopt1.o getpwd.o version.o \
    pexecute.o choose-temp.o mkstemp.o $(LIBDEPS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $@ \
	  protoize.o getopt.o getopt1.o getpwd.o version.o \
	  pexecute.o choose-temp.o mkstemp.o $(LIBS)

unprotoize$(exeext): unprotoize.o getopt.o getopt1.o getpwd.o version.o \
    pexecute.o choose-temp.o mkstemp.o $(LIBDEPS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $@ \
	  unprotoize.o getopt.o getopt1.o getpwd.o version.o \
	  pexecute.o choose-temp.o mkstemp.o $(LIBS)

protoize.o: protoize.c getopt.h $(CONFIG_H) system.h
	$(CC) -c $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) \
          -DGCC_INCLUDE_DIR=\"$(libsubdir)/include\" \
	  -DGPLUSPLUS_INCLUDE_DIR=\"$(gxx_include_dir)\" \
          -DCROSS_INCLUDE_DIR=\"$(tooldir)/sys-include\" \
	  -DTOOL_INCLUDE_DIR=\"$(tooldir)/include\" \
	  -DLOCAL_INCLUDE_DIR=\"$(includedir)\" \
	  -DSTD_PROTO_DIR=\"$(libsubdir)\" \
	  $(srcdir)/protoize.c

unprotoize.o: unprotoize.c protoize.c getopt.h $(CONFIG_H) system.h
	$(CC) -c $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) \
          -DGCC_INCLUDE_DIR=\"$(libsubdir)/include\" \
	  -DGPLUSPLUS_INCLUDE_DIR=\"$(gxx_include_dir)\" \
          -DCROSS_INCLUDE_DIR=\"$(tooldir)/sys-include\" \
	  -DTOOL_INCLUDE_DIR=\"$(tooldir)/include\" \
	  -DLOCAL_INCLUDE_DIR=\"$(includedir)\" \
	  -DSTD_PROTO_DIR=\"$(libsubdir)\" \
	  $(srcdir)/unprotoize.c

getopt.o: getopt.c getopt.h
	$(CC) -c $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) $(srcdir)/getopt.c
getopt1.o: getopt1.c getopt.h
	$(CC) -c $(ALL_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) $(srcdir)/getopt1.c

# This info describes the target machine, so compile with GCC just built.
SYSCALLS.c.X: $(srcdir)/sys-types.h $(srcdir)/sys-protos.h $(GCC_PASSES) \
   stmp-int-hdrs
	-rm -f SYSCALLS.c tmp-SYSCALLS.s
	cat $(srcdir)/sys-types.h $(srcdir)/sys-protos.h > SYSCALLS.c
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(ALL_CPPFLAGS) $(INCLUDES) \
	  -aux-info $@ -S -o tmp-SYSCALLS.s SYSCALLS.c
	-rm -f SYSCALLS.c tmp-SYSCALLS.s


test-protoize-simple: ./protoize ./unprotoize $(GCC_PASSES)
	-rm -f tmp-proto.[cso]
	cp $(srcdir)/protoize.c tmp-proto.c
	chmod u+w tmp-proto.c
	./protoize -N -B ./ -x getopt.h -c "-B./ -Wall -Wwrite-strings \
	  $(CFLAGS) $(INCLUDES) \
	  -DGCC_INCLUDE_DIR=0 \
	  -DGPLUSPLUS_INCLUDE_DIR=0 \
	  -DCROSS_INCLUDE_DIR=0 \
	  -DTOOL_INCLUDE_DIR=0 \
	  -DSTD_PROTO_DIR=0" tmp-proto.c
	@echo '**********' Expect 400 lines of differences.
	-diff $(srcdir)/protoize.c tmp-proto.c > tmp-proto.diff
	-wc -l tmp-proto.diff
	./unprotoize -N -x getopt.h -c "-B./ -Wall -Wwrite-strings \
	  $(CFLAGS) $(INCLUDES) \
	  -DGCC_INCLUDE_DIR=0 \
	  -DGPLUSPLUS_INCLUDE_DIR=0 \
	  -DCROSS_INCLUDE_DIR=0 \
	  -DTOOL_INCLUDE_DIR=0 \
	  -DSTD_PROTO_DIR=0" tmp-proto.c
	@echo Expect zero differences.
	diff $(srcdir)/protoize.c tmp-proto.c | cat
	-rm -f tmp-proto.[cs] tmp-proto$(objext)

gcov.o: gcov.c gcov-io.h system.h

# Only one of 'gcov' or 'gcov.exe' is actually built, depending
# upon whether $(exeext) is empty or not.
gcov$(exeext): gcov.o $(LIBDEPS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) gcov.o $(LIBS) -o $@
#
# Build the include directory.  The stamp files are stmp-* rather than
# s-* so that mostlyclean does not force the include directory to
# be rebuilt.

# Build the include directory including float.h (which no longer depends upon
# enquire).
stmp-int-hdrs: stmp-fixinc $(USER_H) xlimits.h gfloat.h
# Copy in the headers provided with gcc.
# The sed command gets just the last file name component;
# this is necessary because VPATH could add a dirname.
# Using basename would be simpler, but some systems don't have it.
# The touch command is here to workaround an AIX/Linux NFS bug.
	for file in .. $(USER_H); do \
	  if [ X$$file != X.. ]; then \
	    realfile=`echo $$file | sed -e 's|.*/\([^/]*\)$$|\1|'`; \
	    touch include/$$realfile; \
	    rm -f include/$$realfile; \
	    cp $$file include; \
	    chmod a+r include/$$realfile; \
	  fi; \
	done
	rm -f include/limits.h
	cp xlimits.h include/limits.h
	chmod a+r include/limits.h
	rm -f include/float.h
	if [ -s gfloat.h ]; then \
	  cp gfloat.h include/float.h && \
	  chmod a+r include/float.h; \
	else :; fi
# Install the README
	rm -f include/README
	cp $(srcdir)/README-fixinc include/README
	chmod a+r include/README
	touch $@

# Now that gfloat.h no longer depends upon enquire, this is actually a no-op.
stmp-headers:
	touch $@

fixinc.sh :
	DEST=`cd $(srcdir) ; pwd`/$@ CC=$(CC) MAKE=$(MAKE) CFLAGS="$(CFLAGS)" \
	export DEST CC MAKE CFLAGS ; \
	echo DEST=$$DEST CC=$$CC MAKE=$$MAKE CFLAGS=$$CFLAGS ; \
	cd ../contrib/fixinc ;  \
	$(SHELL) mkfixinc.sh $(target) $$DEST

# Build fixed copies of system files.
stmp-fixinc: $(FIXINCLUDES) gsyslimits.h
	rm -rf include
	mkdir include
	if [ x$(FIXINCLUDES) != xMakefile.in ]; \
	then \
	  for dir in $(SYSTEM_HEADER_DIR) $(OTHER_FIXINCLUDES_DIRS); do \
	    if [ -d $$dir ]; \
	    then \
	      $(SHELL) $(srcdir)/$(FIXINCLUDES) include $$dir; \
	    else true; fi; \
	  done; \
	  if [ x$(INSTALL_ASSERT_H) != x ] ; \
	  then \
	    rm -f include/assert.h; \
	    cp $(srcdir)/assert.h include/assert.h; \
	    chmod a+r include/assert.h; \
	  fi \
	else true; \
	fi
	rm -f include/syslimits.h
	if [ -f include/limits.h ]; then \
	  mv include/limits.h include/syslimits.h; \
	else \
	  cp $(srcdir)/gsyslimits.h include/syslimits.h; \
	fi
	chmod a+r include/syslimits.h
	touch stmp-fixinc

# Files related to the fixproto script.

deduced.h: $(GCC_PASSES) $(srcdir)/scan-types.sh stmp-int-hdrs
	if [ -d $(SYSTEM_HEADER_DIR) ]; \
	then \
	  CC="$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(ALL_CPPFLAGS) -I. -I$(srcdir) -Iinclude -I${SYSTEM_HEADER_DIR}"; \
	  export CC; \
	  $(SHELL) $(srcdir)/scan-types.sh "$(srcdir)" >tmp-deduced.h; \
	  mv tmp-deduced.h deduced.h; \
	else \
	  touch deduced.h; \
	fi

gen-protos: gen-protos.o scan.o cppalloc.o $(HOST_LIBDEPS)
	${HOST_CC} $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ \
	  gen-protos.o scan.o cppalloc.o $(HOST_LIBS)

gen-protos.o: gen-protos.c scan.h $(build_xm_file) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/gen-protos.c

scan.o: scan.c scan.h $(build_xm_file) system.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/scan.c

xsys-protos.h: $(GCC_PASSES) $(srcdir)/sys-protos.h deduced.h gen-protos Makefile
	cat deduced.h $(srcdir)/sys-protos.h > tmp-fixtmp.c
	mv tmp-fixtmp.c fixtmp.c
	$(GCC_FOR_TARGET) fixtmp.c -w -U__SIZE_TYPE__ -U__PTRDIFF_TYPE__ -U__WCHAR_TYPE__ -E \
	  | sed -e 's/	/ /g' -e 's/ *(/ (/g' -e 's/ [ ]*/ /g' -e 's/( )/()/' \
	  | ./gen-protos >xsys-protos.hT
	mv xsys-protos.hT xsys-protos.h
	rm -rf fixtmp.c

fix-header: fix-header.o scan-decls.o scan.o xsys-protos.h $(HOST_LIBDEPS) \
   cpplib.o cpphash.o cppalloc.o cppexp.o prefix.o version.o
	$(HOST_CC) $(HOST_CFLAGS) $(HOST_LDFLAGS) -o $@ fix-header.o \
	   scan-decls.o scan.o cpplib.o cpphash.o cppalloc.o prefix.o \
	   version.o cppexp.o $(HOST_LIBS)

fix-header.o: fix-header.c obstack.h scan.h xsys-protos.h $(build_xm_file) \
	system.h cpplib.h cpphash.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/fix-header.c

scan-decls.o: scan-decls.c scan.h cpplib.h $(build_xm_file) system.h gansidecl.h
	$(HOST_CC) -c $(HOST_CFLAGS) $(HOST_CPPFLAGS) $(INCLUDES) $(srcdir)/scan-decls.c

# stmp-fixproto depends on this, not on fix-header directly.
# The idea is to make sure fix-header gets built,
# but not rerun fixproto after each stage
# just because fix-header's mtime has changed.
fixhdr.ready: fix-header
	-if [ -f fixhdr.ready ] ; then \
		true; \
	else \
		touch fixhdr.ready; \
	fi

# stmp-headers is to make sure fixincludes has already finished.
# The if statement is so that we don't run fixproto a second time
# if it has already been run on the files in `include'.
stmp-fixproto: fixhdr.ready fixproto stmp-headers
	@echo "Various warnings and error messages from fixproto are normal"
	-if [ -d include ] ; then true; else mkdir include; fi
	-if [ -f include/fixed ] ; then true; \
	else \
	  : This line works around a 'make' bug in BSDI 1.1.; \
	  FIXPROTO_DEFINES="$(FIXPROTO_DEFINES)"; export FIXPROTO_DEFINES; \
	  if [ -d $(SYSTEM_HEADER_DIR) ] ; then \
	    $(SHELL) ${srcdir}/fixproto include include $(SYSTEM_HEADER_DIR); \
	  else true; fi; \
	  touch include/fixed; \
	fi
	touch stmp-fixproto
#
# Remake the info files.

doc: info
info: cpp.info gcc.info lang.info

cpp.info: $(srcdir)/cpp.texi
	$(MAKEINFO) $(MAKEINFOFLAGS) -I$(srcdir) -o cpp.info $(srcdir)/cpp.texi

gcc.info: $(srcdir)/gcc.texi $(srcdir)/extend.texi $(srcdir)/install.texi \
	  $(srcdir)/invoke.texi $(srcdir)/md.texi $(srcdir)/rtl.texi \
	  $(srcdir)/tm.texi $(srcdir)/gcov.texi
	$(MAKEINFO) $(MAKEINFOFLAGS) -I$(srcdir) -o gcc.info $(srcdir)/gcc.texi

dvi: gcc.dvi cpp.dvi lang.dvi

# This works with GNU Make's default rule.
gcc.dvi: $(srcdir)/gcc.texi $(srcdir)/extend.texi $(srcdir)/install.texi \
	 $(srcdir)/invoke.texi $(srcdir)/md.texi $(srcdir)/rtl.texi \
	 $(srcdir)/tm.texi $(srcdir)/gcov.texi
	TEXINPUTS=${texidir}:$(srcdir):$$TEXINPUTS tex gcc.texi
	texindex gcc.??
	TEXINPUTS=${texidir}:$(srcdir):$$TEXINPUTS tex gcc.texi

cpp.dvi: $(srcdir)/cpp.texi
	TEXINPUTS=${texidir}:$(srcdir):$$TEXINPUTS tex cpp.texi
	texindex cpp.??
	TEXINPUTS=${texidir}:$(srcdir):$$TEXINPUTS tex cpp.texi


INSTALL: $(srcdir)/install1.texi $(srcdir)/install.texi
	cd $(srcdir); $(MAKEINFO) -D INSTALLONLY --no-header \
		--no-split -o INSTALL install1.texi 
#
# Deletion of files made during compilation.
# There are four levels of this:
#   `mostlyclean', `clean', `distclean' and `maintainer-clean'.
# `mostlyclean' is useful while working on a particular type of machine.
# It deletes most, but not all, of the files made by compilation.
# It does not delete libgcc.a or its parts, so it won't have to be recompiled.
# `clean' deletes everything made by running `make all'.
# `distclean' also deletes the files made by config.
# `maintainer-clean' also deletes everything that could be regenerated
# automatically, except for `configure'.
# We remove as much from the language subdirectories as we can
# (less duplicated code).


mostlyclean: lang.mostlyclean
	-rm -f $(STAGESTUFF)
# Delete the temporary source copies for cross compilation.
	-rm -f $(HOST_PREFIX_1)rtl.c $(HOST_PREFIX_1)rtlanal.c
	-rm -f $(HOST_PREFIX_1)alloca.c $(HOST_PREFIX_1)malloc.c
	-rm -f $(HOST_PREFIX_1)obstack.c 
# Delete the temp files made in the course of building libgcc.a.
	-rm -f tmplibgcc* tmpcopy xlimits.h libgcc1-test
	for name in $(LIB1FUNCS); do rm -f $${name}.c; done
# Delete other built files.
	-rm -f t-float.h-cross xsys-protos.hT fp-bit.c dp-bit.c
# Delete the stamp and temporary files.
	-rm -f s-* tmp-* stamp-* stmp-*
	-rm -f */stamp-* */tmp-*
# Delete debugging dump files.
	-rm -f *.greg *.lreg *.combine *.flow *.cse *.jump *.rtl *.tree *.loop
	-rm -f *.dbr *.jump2 *.sched *.cse2 *.sched2 *.stack *.addressof
	-rm -f *.regmove *.mach *.bp *.gcse
	-rm -f */*.greg */*.lreg */*.combine */*.flow */*.cse */*.jump */*.rtl
	-rm -f */*.tree */*.loop */*.dbr */*.jump2 */*.sched */*.cse2
	-rm -f */*.sched2 */*.stack */*.regmove */*.gcse
# Delete some files made during installation.
	-rm -f specs gfloat.h float.h-* enquire SYSCALLS.c.X SYSCALLS.c
	-rm -f collect collect2 mips-tfile mips-tdump alloca.s
# Delete files generated for fixproto
	-rm -rf fix-header xsys-protos.h deduced.h tmp-deduced.h \
	  gen-protos fixproto.list fixtmp.* fixhdr.ready
# Delete unwanted output files from TeX.
	-rm -f *.toc *.log *.vr *.fn *.cp *.tp *.ky *.pg
	-rm -f */*.toc */*.log */*.vr */*.fn */*.cp */*.tp */*.ky */*.pg
# Delete sorted indices we don't actually use.
	-rm -f gcc.vrs gcc.kys gcc.tps gcc.pgs gcc.fns
# Delete core dumps.
	-rm -f core */core
	-rm -f *.bp */*.bp

# Delete all files made by compilation
# that don't exist in the distribution.
clean: mostlyclean lang.clean
# It may not be quite desirable to delete unprotoize.c here,
# but the spec for `make clean' requires it.
# Using unprotoize.c is not quite right in the first place, 
# but what better way is there?
	-rm -f libgcc.a libgcc1.a libgcc1-asm.a libgcc2.a libgcc2.ready
	-rm -f libgcc1.null
	-rm -f *.dvi
	-rm -f */*.dvi
	-if [ -f md.pre-cpp ]; then \
	  rm -f md ; \
	fi
# Delete the include directory.
	-rm -rf include
# Delete files used by the "multilib" facility (including libgcc subdirs).
	-rm -f multilib.h tmpmultilib*
	-if [ "x$(MULTILIB_DIRNAMES)" != x ] ; then \
	  rm -rf $(MULTILIB_DIRNAMES); \
	else if [ "x$(MULTILIB_OPTIONS)" != x ] ; then \
	  rm -rf `echo $(MULTILIB_OPTIONS) | sed -e 's/\// /g'`; \
	fi ; fi
	-rm -fr stage1 stage2 stage3 stage4

# Delete all files that users would normally create
# while building and installing GCC.
distclean: clean lang.distclean
	-rm -f tm.h config.h auto-host.h auto-build.h tconfig.h hconfig.h
	-rm -f md cstamp-h
	-rm -f config.status config.run config.cache config.bak
	-rm -f Make-lang Make-hooks Make-host Make-target
	-rm -f Makefile specs.h options.h *.oaux
	-rm -f gthr-default.h
	-rm -f */stage1 */stage2 */stage3 */stage4 */include
	-rm -f c-parse.output
	-rm -f *.asm
	-rm -f float.h
	-rm -f site.exp site.bak testsuite/site.exp testsuite/site.bak
	-rm -f testsuite/{gcc,g++}.{log,sum}

# Delete anything likely to be found in the source directory
# that shouldn't be in the distribution.
extraclean: distclean lang.extraclean
	-rm -rf =* ./"#"* *~* config/=* config/"#"* config/*~*
	-rm -f patch* *.orig *.rej config/patch* config/*.orig config/*.rej
	-rm -f config/*/=* config/*/"#"* config/*/*~*
	-rm -f config/*/*.orig config/*/*.rej
	-rm -f *.dvi *.ps *.oaux *.d *.[zZ] *.gz
	-rm -f *.tar *.xtar *diff *.diff.* *.tar.* *.xtar.* *diffs
	-rm -f *lose config/*lose config/*/*lose
	-rm -f *.s *.s[0-9] *.i config/ChangeLog
	-rm -f */=* */"#"* */*~*
	-rm -f */patch* */*.orig */*.rej
	-rm -f */*.dvi */*.oaux */*.d */*.[zZ] */*.gz
	-rm -f */*.tar */*.xtar */*diff */*.diff.* */*.tar.* */*.xtar.* */*diffs
	-rm -f */*lose */*.s */*.s[0-9] */*.i

# Get rid of every file that's generated from some other file, except for `configure'.
# Most of these files ARE PRESENT in the GCC distribution.
maintainer-clean:
	@echo 'This command is intended for maintainers to use; it'
	@echo 'deletes files that may need special tools to rebuild.'
	$(MAKE) distclean lang.maintainer-clean
	-rm -f c-parse.y c-gperf.h
	-rm -f c-parse.c c-parse.h c-parse.output
	-rm -f cexp.c cexp.output TAGS 
	-rm -f cpp.info* cpp.??s cpp.*aux
	-rm -f gcc.info* gcc.??s gcc.*aux
#
# Entry points `install' and `uninstall'.
# Also use `install-collect2' to install collect2 when the config files don't.

# The semicolon is to prevent the install.sh -> install default rule
# from doing anything.  Having it run true helps avoid problems and
# noise from versions of make which don't like to have null commands.
install: $(INSTALL_TARGET) ; @true

# Copy the compiler files into directories where they will be run.
# Install the driver last so that the window when things are
# broken is small.
install-normal: install-common $(INSTALL_HEADERS) $(INSTALL_LIBGCC) \
    $(INSTALL_CPP) install-man install-info lang.install-normal \
    install-driver

# Do nothing while making gcc with a cross-compiler. The person who
# makes gcc for the target machine has to know how to put a complete
# gcc together by hand.
install-build: force
	@echo You have to install gcc on your target machine by hand.

# Run this on the target machine
# to finish installation of cross compiler.
install-cross-rest: install-float-h-cross

# Handle cpp installation.
install-cpp: cpp.sh
	-rm -f $(bindir)/cpp
	$(INSTALL_PROGRAM) -m 755 cpp.sh $(bindir)/cpp
	if [ x$(cpp_install_dir) != x ]; then \
	  rm -f $(cpp_install_dir)/cpp; \
	  $(INSTALL_PROGRAM) -m 755 cpp.sh $(cpp_install_dir)/cpp; \
	else true; fi

cpp.sh: $(srcdir)/cpp.in Makefile
	sed -e 's%@GCC@%'$(GCC_INSTALL_NAME)'%' $(srcdir)/cpp.in > xcpp.T
	mv -f xcpp.T cpp.sh

uninstall-cpp:
	-rm -f $(bindir)/cpp
	-if [ x$(cpp_install_dir) != x ]; then \
	  rm -f $(cpp_install_dir)/cpp; \
	else true; fi

# Install float.h for cross compiler.
# Run this on the target machine!
install-float-h-cross: installdirs
#	if [ -f enquire ] ; then true; else false; fi
# Note: don't use -.  We should fail right away if enquire was not made.
	./enquire -f > $(tmpdir)/float.h
	-rm -f $(libsubdir)/include/float.h
	$(INSTALL_DATA) $(tmpdir)/float.h $(libsubdir)/include/float.h
	-rm -f $(tmpdir)/float.h
	chmod a-x $(libsubdir)/include/float.h

# Create the installation directories.
installdirs:
	-if [ -d $(prefix) ] ; then true ; else mkdir $(prefix) ; chmod a+rx $(prefix) ; fi
	-if [ -d $(exec_prefix) ] ; then true ; else mkdir $(exec_prefix) ; chmod a+rx $(exec_prefix) ; fi
	-if [ -d $(libdir) ] ; then true ; else mkdir $(libdir) ; chmod a+rx $(libdir) ; fi
	-if [ -d $(libdir)/gcc-lib ] ; then true ; else mkdir $(libdir)/gcc-lib ; chmod a+rx $(libdir)/gcc-lib ; fi
# This dir isn't currently searched by cpp.
#	-if [ -d $(libdir)/gcc-lib/include ] ; then true ; else mkdir $(libdir)/gcc-lib/include ; chmod a+rx $(libdir)/gcc-lib/include ; fi
	-fdir= ; for dir in `echo $(libsubdir) | tr '/' ' '`; do \
	  fdir=$${fdir}/$${dir}; \
	  if [ -d $${fdir} ] ; then true ; else mkdir $${fdir}; chmod a+rx $${fdir}; fi ; \
	done
	-if [ -d $(bindir) ] ; then true ; else mkdir $(bindir) ; chmod a+rx $(bindir) ; fi
	-if [ -d $(includedir) ] ; then true ; else mkdir $(includedir) ; chmod a+rx $(includedir) ; fi
	-if [ -d $(tooldir) ] ; then true ; else mkdir $(tooldir) ; chmod a+rx $(tooldir) ; fi
	-if [ -d $(assertdir) ] ; then true ; else mkdir $(assertdir) ; chmod a+rx $(assertdir) ; fi
	-if [ -d $(infodir) ] ; then true ; else mkdir $(infodir) ; chmod a+rx $(infodir) ; fi
# We don't use mkdir -p to create the parents of mandir,
# because some systems don't support it.
# Instead, we use this technique to create the immediate parent of mandir.
	-parent=`echo $(mandir)|sed -e 's@/[^/]*$$@@'`; \
	if [ -d $$parent ] ; then true ; else mkdir $$parent ; chmod a+rx $$parent ; fi
	-if [ -d $(mandir) ] ; then true ; else mkdir $(mandir) ; chmod a+rx $(mandir) ; fi

# Install the compiler executables built during cross compilation.
install-common: native installdirs $(EXTRA_PARTS) lang.install-common
	for file in $(COMPILERS); do \
	  if [ -f $$file ] ; then \
	    rm -f $(libsubdir)/$$file; \
	    $(INSTALL_PROGRAM) $$file $(libsubdir)/$$file; \
	  else true; \
	  fi; \
	done
	for file in $(EXTRA_PASSES) $(EXTRA_PROGRAMS) $(USE_COLLECT2) ..; do \
	  if [ x"$$file" != x.. ]; then \
	    rm -f $(libsubdir)/$$file; \
	    $(INSTALL_PROGRAM) $$file $(libsubdir)/$$file; \
	  else true; fi; \
	done
	for file in $(EXTRA_PARTS) ..; do \
	  if [ x"$$file" != x.. ]; then \
	    rm -f $(libsubdir)/$$file; \
	    $(INSTALL_DATA) $$file $(libsubdir)/$$file; \
	    chmod a-x $(libsubdir)/$$file; \
	  else true; fi; \
	done
# Don't mess with specs if it doesn't exist yet.
	-if [ -f specs ] ; then \
	  rm -f $(libsubdir)/specs; \
	  $(INSTALL_DATA) specs $(libsubdir)/specs; \
	  chmod a-x $(libsubdir)/specs; \
	fi
# Install protoize if it was compiled.
	-if [ -f protoize$(exeext) ]; \
	then \
	    if [ -f gcc-cross$(exeext) ] ; then \
		rm -f $(bindir)/$(PROTOIZE_CROSS_NAME)$(exeext); \
		$(INSTALL_PROGRAM) protoize$(exeext) $(bindir)/$(PROTOIZE_CROSS_NAME)$(exeext); \
		rm -f $(bindir)/$(UNPROTOIZE_CROSS_NAME)$(exeext); \
		$(INSTALL_PROGRAM) unprotoize$(exeext) $(bindir)/$(UNPROTOIZE_CROSS_NAME)$(exeext); \
	    else \
		rm -f $(bindir)/$(PROTOIZE_INSTALL_NAME)$(exeext); \
		$(INSTALL_PROGRAM) protoize$(exeext) $(bindir)/$(PROTOIZE_INSTALL_NAME)$(exeext); \
		rm -f $(bindir)/$(UNPROTOIZE_INSTALL_NAME)$(exeext); \
		$(INSTALL_PROGRAM) unprotoize$(exeext) $(bindir)/$(UNPROTOIZE_INSTALL_NAME)$(exeext); \
	    fi ; \
	    rm -f $(libsubdir)/SYSCALLS.c.X; \
	    $(INSTALL_DATA) SYSCALLS.c.X $(libsubdir)/SYSCALLS.c.X; \
	    chmod a-x $(libsubdir)/SYSCALLS.c.X; \
	fi
	-rm -f $(libsubdir)/cpp$(exeext)
	$(INSTALL_PROGRAM) cpp$(exeext) $(libsubdir)/cpp$(exeext)
# Install gcov if it was compiled.
	-if [ -f gcov$(exeext) ]; \
	then \
	    rm -f $(bindir)/gcov$(exeext); \
	    $(INSTALL_PROGRAM) gcov$(exeext) $(bindir)/gcov$(exeext); \
	    chmod a+x $(bindir)/gcov$(exeext); \
	fi

# Install the driver program as $(target_alias)-gcc
# and also as either gcc (if native) or $(tooldir)/bin/gcc.
install-driver: xgcc$(exeext)
	-if [ -f gcc-cross$(exeext) ] ; then \
	  rm -f $(bindir)/$(GCC_CROSS_NAME)$(exeext); \
	  $(INSTALL_PROGRAM) gcc-cross$(exeext) $(bindir)/$(GCC_CROSS_NAME)$(exeext); \
	  if [ -d $(tooldir)/bin/. ] ; then \
	    rm -f $(tooldir)/bin/gcc$(exeext); \
	    $(INSTALL_PROGRAM) gcc-cross$(exeext) $(tooldir)/bin/gcc$(exeext); \
	  else true; fi; \
	else \
	  rm -f $(bindir)/$(GCC_INSTALL_NAME)$(exeext); \
	  $(INSTALL_PROGRAM) xgcc$(exeext) $(bindir)/$(GCC_INSTALL_NAME)$(exeext); \
	  rm -f $(bindir)/$(target_alias)-gcc-1$(exeext); \
	  $(LN) $(bindir)/$(GCC_INSTALL_NAME)$(exeext) $(bindir)/$(target_alias)-gcc-1$(exeext); \
	  mv $(bindir)/$(target_alias)-gcc-1$(exeext) $(bindir)/$(target_alias)-gcc$(exeext); \
	fi

# Install the info files.
# $(INSTALL_DATA) might be a relative pathname, so we can't cd into srcdir
# to do the install.
install-info: doc installdirs lang.install-info
	-rm -f $(infodir)/cpp.info* $(infodir)/gcc.info*
	for f in cpp.info* gcc.info*; do \
	    $(INSTALL_DATA) $$f $(infodir)/$$f; \
	done
	-if $(SHELL) -c 'install-info --version' >/dev/null 2>&1; then \
	  if [ -f $(infodir)/dir ] ; then \
	    for f in cpp.info gcc.info; do \
		install-info --dir-file=$(infodir)/dir $(infodir)/$$f; \
	    done; \
	  else true; fi; \
	else true; fi;
	-chmod a-x $(infodir)/cpp.info* $(infodir)/gcc.info*

# Install the man pages.
install-man: installdirs $(srcdir)/gcc.1 $(srcdir)/cccp.1 lang.install-man
	-if [ -f gcc-cross$(exeext) ] ; then \
	  rm -f $(mandir)/$(GCC_CROSS_NAME)$(manext); \
	  $(INSTALL_DATA) $(srcdir)/gcc.1 $(mandir)/$(GCC_CROSS_NAME)$(manext); \
	  chmod a-x $(mandir)/$(GCC_CROSS_NAME)$(manext); \
	else \
	  rm -f $(mandir)/$(GCC_INSTALL_NAME)$(manext); \
	  $(INSTALL_DATA) $(srcdir)/gcc.1 $(mandir)/$(GCC_INSTALL_NAME)$(manext); \
	  chmod a-x $(mandir)/$(GCC_INSTALL_NAME)$(manext); \
	fi
	-rm -f $(mandir)/cccp$(manext)
	-$(INSTALL_DATA) $(srcdir)/cccp.1 $(mandir)/cccp$(manext)
	-chmod a-x $(mandir)/cccp$(manext)

# Install the library.
install-libgcc: libgcc.a installdirs
	-if [ -f libgcc.a ] ; then \
	  rm -f $(libsubdir)/libgcc.a; \
	  $(INSTALL_DATA) libgcc.a $(libsubdir)/libgcc.a; \
	  if $(RANLIB_TEST) ; then \
	    (cd $(libsubdir); $(RANLIB) libgcc.a); else true; fi; \
	  chmod a-x $(libsubdir)/libgcc.a; \
	else true; fi

# Install multiple versions of libgcc.a.
install-multilib: stmp-multilib installdirs
	for i in `$(GCC_FOR_TARGET) --print-multi-lib`; do \
	  dir=`echo $$i | sed -e 's/;.*$$//'`; \
	  if [ -d $(libsubdir)/$${dir} ]; then true; else mkdir $(libsubdir)/$${dir}; fi; \
	  for f in libgcc.a $(EXTRA_MULTILIB_PARTS); do \
	    rm -f $(libsubdir)/$${dir}/$${f}; \
	    $(INSTALL_DATA) $${dir}/$${f} $(libsubdir)/$${dir}/$${f}; \
	  done; \
	  if $(RANLIB_TEST); then \
	    (cd $(libsubdir)/$${dir}; $(RANLIB) libgcc.a); else true; fi; \
	  chmod a-x $(libsubdir)/$${dir}/libgcc.a; \
	done

# Install all the header files built in the include subdirectory.
install-headers: install-include-dir $(INSTALL_HEADERS_DIR) $(INSTALL_ASSERT_H)
# Fix symlinks to absolute paths in the installed include directory to
# point to the installed directory, not the build directory.
# Don't need to use LN_S here since we really do need ln -s and no substitutes.
	-files=`cd $(libsubdir)/include; find . -type l -print 2>/dev/null`; \
	if [ $$? -eq 0 ]; then \
	  dir=`cd include; pwd`; \
	  for i in $$files; do \
	    dest=`ls -ld $(libsubdir)/include/$$i | sed -n 's/.*-> //p'`; \
	    if expr "$$dest" : "$$dir.*" > /dev/null; then \
	      rm -f $(libsubdir)/include/$$i; \
	      ln -s `echo $$i | sed "s|/[^/]*|/..|g" | sed 's|/..$$||'``echo "$$dest" | sed "s|$$dir||"` $(libsubdir)/include/$$i; \
	    fi; \
	  done; \
	fi

# Create or recreate the gcc private include file directory.
install-include-dir: installdirs
	-rm -rf $(libsubdir)/include
	mkdir $(libsubdir)/include
	-chmod a+rx $(libsubdir)/include

# Install the include directory using tar.
install-headers-tar: stmp-headers $(STMP_FIXPROTO) install-include-dir
	(cd include; \
	 tar -cf - .; exit 0) | (cd $(libsubdir)/include; tar $(TAROUTOPTS) - )
# /bin/sh on some systems returns the status of the first tar,
# and that can lose with GNU tar which always writes a full block.
# So use `exit 0' to ignore its exit status.

# Install the include directory using cpio.
install-headers-cpio: stmp-headers $(STMP_FIXPROTO) install-include-dir
	(cd include; find . -print) | (cd include; cpio -pdum $(libsubdir)/include)

# Put assert.h where it won't override GNU libc's assert.h.
# It goes in a dir that is searched after GNU libc's headers;
# thus, the following conditionals are no longer needed.
# But it's not worth deleting them now.
## Don't replace the assert.h already there if it is not from GCC.
## This code would be simpler if it tested for -f ... && ! grep ...
## but supposedly the ! operator is missing in sh on some systems.
install-assert-h: assert.h installdirs
	if [ -f $(assertdir)/assert.h ]; \
	then \
	  if grep "__eprintf" $(assertdir)/assert.h >/dev/null; \
	    then \
	    rm -f $(assertdir)/assert.h; \
	    $(INSTALL_DATA) $(srcdir)/assert.h $(assertdir)/assert.h; \
	    chmod a-x $(assertdir)/assert.h; \
	  else true; \
	  fi; \
	else \
	  rm -f $(assertdir)/assert.h; \
	  $(INSTALL_DATA) $(srcdir)/assert.h $(assertdir)/assert.h; \
	  chmod a-x $(assertdir)/assert.h; \
	fi

# Use this target to install the program `collect2' under the name `collect2'.
install-collect2: collect2 installdirs
	$(INSTALL_PROGRAM) collect2$(exeext) $(libsubdir)/collect2$(exeext)
# Install the driver program as $(libsubdir)/gcc for collect2.
	$(INSTALL_PROGRAM) xgcc$(exeext) $(libsubdir)/gcc$(exeext)

# Cancel installation by deleting the installed files.
uninstall: lang.uninstall $(UNINSTALL_CPP)
	-rm -rf $(libsubdir)
	-rm -rf $(bindir)/$(GCC_INSTALL_NAME)$(exeext)
	-rm -rf $(bindir)/$(GCC_CROSS_NAME)$(exeext)
	-rm -rf $(bindir)/protoize$(exeext)
	-rm -rf $(bindir)/unprotoize$(exeext)
	-rm -rf $(bindir)/gcov$(exeext)
	-rm -rf $(mandir)/$(GCC_INSTALL_NAME)$(manext)
	-rm -rf $(mandir)/$(GCC_CROSS_NAME)$(manext)
	-rm -rf $(mandir)/cccp$(manext)
	-rm -rf $(mandir)/protoize$(manext)
	-rm -rf $(mandir)/unprotoize$(manext)
	-rm -f $(infodir)/cpp.info* $(infodir)/gcc.info*
#
# These targets are for the dejagnu testsuites. The file site.exp 
# contains global variables that all the testsuites will use.

# Set to $(target_alias)/ for cross.
target_subdir = 

site.exp: ./config.status Makefile
	@echo "Making a new config file..."
	-@rm -f ./tmp?
	@touch site.exp
	-@mv site.exp site.bak
	@echo "## these variables are automatically generated by make ##" > ./tmp0
	@echo "# Do not edit here. If you wish to override these values" >> ./tmp0
	@echo "# add them to the last section" >> ./tmp0
	@echo "set rootme \"`pwd`\"" >> ./tmp0
	@echo "set srcdir \"`cd ${srcdir}; pwd`\"" >> ./tmp0
	@echo "set host_triplet $(host_canonical)" >> ./tmp0
	@echo "set build_triplet $(build_canonical)" >> ./tmp0
	@echo "set target_triplet $(target)" >> ./tmp0
	@echo "set target_alias $(target_alias)" >> ./tmp0
# CFLAGS is set even though it's empty to show we reserve the right to set it.
	@echo "set CFLAGS \"\"" >> ./tmp0
	@echo "set CXXFLAGS \"-I$(objdir)/../$(target_subdir)libio -I\$$srcdir/../libg++/src -I\$$srcdir/../libio -I\$$srcdir/../libstdc++ -I\$$srcdir/../libstdc++/stl -L$(objdir)/../$(target_subdir)libg++ -L$(objdir)/../$(target_subdir)libstdc++\"" >> ./tmp0
# If newlib has been configured, we need to pass -B to gcc so it can find
# newlib's crt0.o if it exists.  This will cause a "path prefix not used"
# message if it doesn't, but the testsuite is supposed to ignore the message -
# it's too difficult to tell when to and when not to pass -B (not all targets
# have crt0's).  We could only add the -B if ../newlib/crt0.o exists, but that
# seems like too selective a test.
# ??? Another way to solve this might be to rely on linker scripts.  Then
# theoretically the -B won't be needed.
# We also need to pass -L ../ld so that the linker can find ldscripts.
	@if [ -d $(objdir)/../$(target_subdir)newlib ] ; then \
	  echo "set newlib_cflags \"-I$(objdir)/../$(target_subdir)newlib/targ-include -I\$$srcdir/../newlib/libc/include\"" >> ./tmp0; \
	  echo "set newlib_ldflags \"-B$(objdir)/../$(target_subdir)newlib/\"" >> ./tmp0; \
	  echo "append CFLAGS \" \$$newlib_cflags\"" >> ./tmp0; \
	  echo "append CXXFLAGS \" \$$newlib_cflags\"" >> ./tmp0; \
	  echo "append LDFLAGS \" \$$newlib_ldflags\"" >> ./tmp0; \
	else true; \
	fi
	@if [ -d $(objdir)/../ld ] ; then \
	  echo "append LDFLAGS \" -L$(objdir)/../ld\"" >> ./tmp0; \
	else true; \
	fi
	echo "set tmpdir $(objdir)/testsuite" >> ./tmp0
	@echo "set srcdir \"\$${srcdir}/testsuite\"" >> ./tmp0
	@echo "## All variables above are generated by configure. Do Not Edit ##" >> ./tmp0
	@cat ./tmp0 > site.exp
	@cat site.bak | sed \
		-e '1,/^## All variables above are.*##/ d' >> site.exp
	-@rm -f ./tmp?

CHECK_TARGETS = check-gcc check-g++ check-g77

check: $(CHECK_TARGETS)

testsuite/site.exp: site.exp
	if [ -d testsuite ]; then \
	  true; \
	else \
	  mkdir testsuite; \
	fi
	rm -rf testsuite/site.exp
	cp site.exp testsuite/site.exp

check-g++: testsuite/site.exp
	-rootme=`pwd`; export rootme; \
	srcdir=`cd ${srcdir}; pwd` ; export srcdir ; \
	cd testsuite; \
	EXPECT=${EXPECT} ; export EXPECT ; \
	if [ -f $${rootme}/../expect/expect ] ; then  \
	   TCL_LIBRARY=$${srcdir}/../tcl/library ; \
	    export TCL_LIBRARY ; fi ; \
	$(RUNTEST) --tool g++ $(RUNTESTFLAGS)

check-gcc: testsuite/site.exp
	-rootme=`pwd`; export rootme; \
	srcdir=`cd ${srcdir}; pwd` ; export srcdir ; \
	cd testsuite; \
	EXPECT=${EXPECT} ; export EXPECT ; \
	if [ -f $${rootme}/../expect/expect ] ; then  \
	   TCL_LIBRARY=$${srcdir}/../tcl/library ; \
	   export TCL_LIBRARY ; fi ; \
	$(RUNTEST) --tool gcc $(RUNTESTFLAGS)

check-g77: testsuite/site.exp
	-rootme=`pwd`; export rootme; \
	srcdir=`cd ${srcdir}; pwd` ; export srcdir ; \
	cd testsuite; \
	EXPECT=${EXPECT} ; export EXPECT ; \
	if [ -f $${rootme}/../expect/expect ] ; then  \
	   TCL_LIBRARY=$${srcdir}/../tcl/library ; \
	   export TCL_LIBRARY ; fi ; \
	$(RUNTEST) --tool g77 $(RUNTESTFLAGS)

# These exist for maintenance purposes.

# Update the tags table.
TAGS: force
	cd $(srcdir);							\
	mkdir tmp-tags;							\
	mv -f c-parse.[ch] cexp.c =*.[chy] tmp-tags;			\
	etags *.y *.h *.c;						\
	mv tmp-tags/* .;						\
	rmdir tmp-tags

# Create the distribution tar.gz file.
dist: tmp-gcc.xtar
	gzip --best < tmp-gcc.xtar > tmp-gcc.xtar.gz
	mv tmp-gcc.xtar.gz gcc-$(version).tar.gz

tmp-gcc.xtar: distdir
# Make the distribution.
	tar -chf tmp-gcc.xtar gcc-$(version)

distdir-cvs: force
	if [ -d $(srcdir)/CVS ]; then cvs -r update; fi

# This target exists to do the initial work before the language specific
# stuff gets done.
distdir-start: doc $(srcdir)/INSTALL $(srcdir)/c-parse.y $(srcdir)/c-gperf.h \
  $(srcdir)/c-parse.c $(srcdir)/cexp.c $(srcdir)/config.in \
  $(srcdir)/version.c TAGS
	@if grep -s "for version ${mainversion}" gcc.texi > /dev/null; \
	then true; \
	else echo "You must update the version number in \`gcc.texi'"; sleep 10;\
	fi
# Update the version number in README
	awk '$$1 " " $$2 " " $$3 == "This directory contains" \
		{ $$6 = version; print $$0 } \
	     $$1 " " $$2 " " $$3 != "This directory contains"' \
	  version=$(version) README > tmp.README
	mv tmp.README README
	-rm -rf gcc-$(version) tmp	
# Put all the files in a temporary subdirectory
# which has the name that we want to have in the tar file.
	mkdir tmp
	mkdir tmp/config
	mkdir tmp/ginclude
	for file in *[0-9a-zA-Z+]; do \
	  $(LN) $$file tmp; \
	done
	cd config; \
	for file in *[0-9a-zA-Z+]; do \
	  if test -d $$file && test "$$file" != RCS && test "$$file" != CVS; then \
	    mkdir ../tmp/config/$$file; \
	    cd $$file; \
	    for subfile in *[0-9a-zA-Z+]; do \
	      $(LN) $$subfile ../../tmp/config/$$file; \
	    done; \
	    cd ..; \
	  else \
	    $(LN) $$file ../tmp/config; \
	  fi; \
	done
	cd ginclude; \
	for file in *[0-9a-zA-Z+]; do \
	  $(LN) $$file ../tmp/ginclude; \
	done
	cd objc; \
	for file in *[0-9a-zA-Z+]; do \
	  $(LN) $$file ../tmp/objc; \
	done
	$(LN) .gdbinit tmp

# Finish making `distdir', after the languages have done their thing.
distdir-finish:
	mv tmp gcc-$(version)
# Get rid of everything we don't want in the distribution.  We'd want
# this to use Makefile.in, but it doesn't have the `lang.foo' targets
# expanded.
	cd gcc-$(version); make extraclean VERSION_DEP=

distdir: distdir-cvs distdir-start lang.distdir distdir-finish

# make diff oldversion=M.N 
# creates a diff file between an older distribution and this one.
# The -P option assumes this is GNU diff.
diff:
	diff -rc2P -x c-parse.y -x c-parse.c -x c-parse.h -x c-gperf.h \
	  -x cexp.c -x -x TAGS -x INSTALL \
	  -x configure -x config.in \
	  -x "gcc.??" -x "gcc.??s" -x gcc.aux -x "gcc.info*" \
	  -x "cpp.??" -x "cpp.??s" -x cpp.aux -x "cpp.info*" \
	  $(LANG_DIFF_EXCLUDES) \
	  gcc-$(oldversion) gcc-$(version) > gcc-$(oldversion)-$(version).diff

bootstrap bootstrap-lean: force
# Only build the C compiler for stage1, because that is the only one that
# we can guarantee will build with the native compiler, and also it is the
# only thing useful for building stage2.
	$(MAKE) CC="$(CC)" libdir=$(libdir) LANGUAGES="$(BOOT_LANGUAGES)"
	$(MAKE) stage1
# This used to define ALLOCA as empty, but that would lead to bad results
# for a subsequent `make install' since that would not have ALLOCA empty.
# To prevent `make install' from compiling alloca.o and then relinking cc1
# because alloca.o is newer, we permit these recursive makes to compile
# alloca.o.  Then cc1 is newer, so it won't have to be relinked.
	$(MAKE) CC="stage1/xgcc$(exeext) -Bstage1/" CFLAGS="$(WARN_CFLAGS) $(BOOT_CFLAGS)" LDFLAGS="$(BOOT_LDFLAGS)" libdir=$(libdir) STAGE_PREFIX=stage1/ LANGUAGES="$(LANGUAGES)"
	$(MAKE) stage2
	-if test $@ = bootstrap-lean; then rm -rf stage1; else true; fi
	$(MAKE) CC="stage2/xgcc$(exeext) -Bstage2/" CFLAGS="$(WARN_CFLAGS) $(BOOT_CFLAGS)" LDFLAGS="$(BOOT_LDFLAGS)" libdir=$(libdir) STAGE_PREFIX=stage2/ LANGUAGES="$(LANGUAGES)"

bootstrap2 bootstrap2-lean: force
	$(MAKE) CC="stage1/xgcc$(exeext) -Bstage1/" CFLAGS="$(WARN_CFLAGS) $(BOOT_CFLAGS)" LDFLAGS="$(BOOT_LDFLAGS)" libdir=$(libdir) STAGE_PREFIX=stage1/ LANGUAGES="$(LANGUAGES)"
	$(MAKE) stage2
	-if test $@ = bootstrap2-lean; then rm -rf stage1; else true; fi
	$(MAKE) CC="stage2/xgcc$(exeext) -Bstage2/" CFLAGS="$(WARN_CFLAGS) $(BOOT_CFLAGS)" LDFLAGS="$(BOOT_LDFLAGS)" libdir=$(libdir) STAGE_PREFIX=stage2/ LANGUAGES="$(LANGUAGES)"

bootstrap3 bootstrap3-lean: force
	$(MAKE) CC="stage2/xgcc$(exeext) -Bstage2/" CFLAGS="$(WARN_CFLAGS) $(BOOT_CFLAGS)" LDFLAGS="$(BOOT_LDFLAGS)" libdir=$(libdir) STAGE_PREFIX=stage2/ LANGUAGES="$(LANGUAGES)"

bootstrap4 bootstrap4-lean: force
	$(MAKE) CC="stage3/xgcc$(exeext) -Bstage3/" CFLAGS="$(WARN_CFLAGS) $(BOOT_CFLAGS)" LDFLAGS="$(BOOT_LDFLAGS)" libdir=$(libdir) STAGE_PREFIX=stage3/ LANGUAGES="$(LANGUAGES)"

# Compare the object files in the current directory with those in the
# stage2 directory.

# ./ avoids bug in some versions of tail.
compare compare3 compare4 compare-lean compare3-lean compare4-lean: force
	-rm -f .bad_compare
	case "$@" in compare | compare-lean ) stage=2 ;; * ) stage=`echo $@ | sed -e 's,^compare\([0-9][0-9]*\).*,\1,'` ;; esac; \
	for file in *$(objext); do \
	  tail +16c ./$$file > tmp-foo1; \
	  tail +16c stage$$stage/$$file > tmp-foo2 \
	    && (cmp tmp-foo1 tmp-foo2 > /dev/null 2>&1 || echo $$file differs >> .bad_compare) || true; \
	done
	case "$@" in compare | compare-lean ) stage=2 ;; * ) stage=`echo $@ | sed -e 's,^compare\([0-9][0-9]*\).*,\1,'` ;; esac; \
	for dir in tmp-foo $(SUBDIRS); do \
	  if [ "`echo $$dir/*$(objext)`" != "$$dir/*$(objext)" ] ; then \
	    for file in $$dir/*$(objext); do \
	      if [ $$file != objc/NXConstStr.o -a $$file != objc/Object.o -a $$file != objc/Protocol.o -a $$file != objc/linking.o ] ; then \
		tail +16c ./$$file > tmp-foo1; \
		tail +16c stage$$stage/$$file > tmp-foo2 \
		  && (cmp tmp-foo1 tmp-foo2 > /dev/null 2>&1 || echo $$file differs >> .bad_compare) || true; \
	      else true; fi; \
	    done; \
	  fi; \
	done
	-rm -f tmp-foo*
	case "$@" in compare | compare-lean ) stage=2 ;; * ) stage=`echo $@ | sed -e 's,^compare\([0-9][0-9]*\).*,\1,'` ;; esac; \
	if [ -f .bad_compare ]; then \
	  echo "Bootstrap comparison failure!"; \
	  cat .bad_compare; \
	  exit 1; \
	else \
	  case "$@" in \
	    *-lean ) rm -rf stage$$stage ;; \
	    *) ;; \
	  esac; true; \
	fi

# Compare the object files in the current directory with those in the
# stage2 directory.  Use gnu cmp (diffutils v2.4 or later) to avoid
# running tail and the overhead of twice copying each object file.

gnucompare gnucompare3 gnucompare4 gnucompare-lean gnucompare3-lean gnucompare4-lean: force
	-rm -f .bad_compare
	case "$@" in gnucompare | gnucompare-lean ) stage=2 ;; * ) stage=`echo $@ | sed -e 's,^gnucompare\([0-9][0-9]*\).*,\1,'` ;; esac; \
	for file in *$(objext); do \
	  (cmp --ignore-initial=16 $$file stage$$stage/$$file > /dev/null 2>&1 || echo $$file differs >> .bad_compare) || true; \
	done
	case "$@" in gnucompare | gnucompare-lean ) stage=2 ;; * ) stage=`echo $@ | sed -e 's,^gnucompare\([0-9][0-9]*\).*,\1,'` ;; esac; \
	for dir in tmp-foo $(SUBDIRS); do \
	  if [ "`echo $$dir/*$(objext)`" != "$$dir/*$(objext)" ] ; then \
	    for file in $$dir/*$(objext); do \
	      if [ $$file != objc/NXConstStr.o -a $$file != objc/Object.o -a $$file != objc/Protocol.o -a $$file != objc/linking.o ] ; then \
	        (cmp --ignore-initial=16 $$file stage$$stage/$$file > /dev/null 2>&1 || echo $$file differs >> .bad_compare) || true; \
	      else true; fi; \
	    done; \
	  fi; \
	done
	case "$@" in gnucompare | gnucompare-lean ) stage=2 ;; * ) stage=`echo $@ | sed -e 's,^gnucompare\([0-9][0-9]*\).*,\1,'` ;; esac; \
	if [ -f .bad_compare ]; then \
	  echo "Bootstrap comparison failure!"; \
	  cat .bad_compare; \
	  exit 1; \
	else \
	  case "$@" in \
	    *-lean ) rm -rf stage$$stage ;; \
	  esac; true; \
	fi

# Copy the object files from a particular stage into a subdirectory.
stage1-start:
	-if [ -d stage1 ] ; then true ; else mkdir stage1 ; fi
	-for dir in . $(SUBDIRS) ; \
	 do \
	   if [ -d stage1/$$dir ] ; then true ; else mkdir stage1/$$dir ; fi ; \
	 done
	-mv $(STAGESTUFF) stage1
# Copy as/ld if they exist to stage dir, so that running xgcc from the stage
# dir will work properly.
	-if [ -f as$(exeext) ] ; then $(LN_S) ../as$(exeext) stage1 ; else true ; fi
	-if [ -f ld$(exeext) ] ; then $(LN_S) ../ld$(exeext) stage1 ; else true ; fi
	-if [ -f collect-ld$(exeext) ] ; then $(LN_S) ../collect-ld$(exeext) stage1 ; else true ; fi
	-rm -f stage1/libgcc.a
	-cp libgcc.a stage1
	-if $(RANLIB_TEST) ; then $(RANLIB) stage1/libgcc.a; else true; fi
	-for f in .. $(EXTRA_MULTILIB_PARTS); do if [ x$${f} != x.. ]; then \
	  cp stage1/$${f} . ; \
	else true; \
	fi; done
stage1: force stage1-start lang.stage1

stage2-start:
	-if [ -d stage2 ] ; then true ; else mkdir stage2 ; fi
	-for dir in . $(SUBDIRS) ; \
	 do \
	   if [ -d stage2/$$dir ] ; then true ; else mkdir stage2/$$dir ; fi ; \
	 done
	-mv $(STAGESTUFF) stage2
# Copy as/ld if they exist to stage dir, so that running xgcc from the stage
# dir will work properly.
	-if [ -f as$(exeext) ] ; then $(LN_S) ../as$(exeext) stage2 ; else true ; fi
	-if [ -f ld$(exeext) ] ; then $(LN_S) ../ld$(exeext) stage2 ; else true ; fi
	-if [ -f collect-ld ] ; then $(LN_S) ../collect-ld$(exeext) stage2 ; else true ; fi
	-rm -f stage2/libgcc.a
	-cp libgcc.a stage2
	-if $(RANLIB_TEST) ; then $(RANLIB) stage2/libgcc.a; else true; fi
	-for f in .. $(EXTRA_MULTILIB_PARTS); do if [ x$${f} != x.. ]; then \
	  cp stage2/$${f} . ; \
	else true; \
	fi; done
stage2: force stage2-start lang.stage2

stage3-start:
	-if [ -d stage3 ] ; then true ; else mkdir stage3 ; fi
	-for dir in . $(SUBDIRS) ; \
	 do \
	   if [ -d stage3/$$dir ] ; then true ; else mkdir stage3/$$dir ; fi ; \
	 done
	-mv $(STAGESTUFF) stage3
# Copy as/ld if they exist to stage dir, so that running xgcc from the stage
# dir will work properly.
	-if [ -f as$(exeext) ] ; then $(LN_S) ../as$(exeext) stage3 ; else true ; fi
	-if [ -f ld$(exeext) ] ; then $(LN_S) ../ld$(exeext) stage3 ; else true ; fi
	-if [ -f collect-ld$(exeext) ] ; then $(LN_S) ../collect-ld$(exeext) stage3 ; else true ; fi
	-rm -f stage3/libgcc.a
	-cp libgcc.a stage3
	-if $(RANLIB_TEST) ; then $(RANLIB) stage3/libgcc.a; else true; fi
	-for f in .. $(EXTRA_MULTILIB_PARTS); do if [ x$${f} != x.. ]; then \
	  cp stage3/$${f} . ; \
	else true; \
	fi; done
stage3: force stage3-start lang.stage3

stage4-start:
	-if [ -d stage4 ] ; then true ; else mkdir stage4 ; fi
	-for dir in . $(SUBDIRS) ; \
	 do \
	   if [ -d stage4/$$dir ] ; then true ; else mkdir stage4/$$dir ; fi ; \
	 done
	-mv $(STAGESTUFF) stage4
# Copy as/ld if they exist to stage dir, so that running xgcc from the stage
# dir will work properly.
	-if [ -f as$(exeext) ] ; then $(LN_S) ../as$(exeext) stage4 ; else true ; fi
	-if [ -f ld$(exeext) ] ; then $(LN_S) ../ld$(exeext) stage4 ; else true ; fi
	-if [ -f collect-ld$(exeext) ] ; then $(LN_S) ../collect-ld$(exeext) stage4 ; else true ; fi
	-rm -f stage4/libgcc.a
	-cp libgcc.a stage4
	-if $(RANLIB_TEST) ; then $(RANLIB) stage4/libgcc.a; else true; fi
	-for f in .. $(EXTRA_MULTILIB_PARTS); do if [ x$${f} != x.. ]; then \
	  cp stage4/$${f} . ; \
	else true; \
	fi; done
stage4: force stage4-start lang.stage4

# Copy just the executable files from a particular stage into a subdirectory,
# and delete the object files.  Use this if you're just verifying a version
# that is pretty sure to work, and you are short of disk space.
risky-stage1: stage1
	-make clean

risky-stage2: stage2
	-make clean

risky-stage3: stage3
	-make clean

risky-stage4: stage4
	-make clean

#In GNU Make, ignore whether `stage*' exists.
.PHONY: stage1 stage2 stage3 stage4 clean maintainer-clean TAGS bootstrap
.PHONY: risky-stage1 risky-stage2 risky-stage3 risky-stage4

force:

# ---
# The enquire rules are still useful for building new float-anything.h.
# Special flags for compiling enquire.
# We disable optimization to make floating point more reliable.
ENQUIRE_CFLAGS = -DNO_MEM -DNO_LONG_DOUBLE_IO -O0
ENQUIRE_LDFLAGS = $(LDFLAGS)

# Enquire target (This is a variable so that a target can choose not to
# build it.)
ENQUIRE = enquire

# Test to see whether <float.h> exists in the system header files,
# and is not derived from GCC.
FLOAT_H_TEST = \
  [ -f $(SYSTEM_HEADER_DIR)/float.h ] && \
  if grep 'ifndef _FLOAT_H___' $(SYSTEM_HEADER_DIR)/float.h >/dev/null; \
  then false; \
  else :; fi
# We pretend to not having a usable <float.h>, hence disable the FLOAT_H_TEST
# to ensure, we're emitting a full blown <float.h> ourselves.
FLOAT_H_TEST = false

# Used to compile enquire with standard cc, but have forgotten why.
# Let's try with GCC.
enquire: enquire.o $(GCC_PARTS)
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(ENQUIRE_LDFLAGS) enquire.o -o $@
enquire.o: $(srcdir)/enquire.c $(GCC_PASSES) stmp-int-hdrs
	if $(FLOAT_H_TEST); then \
	  rm -f include/float.h; \
	  SYS_FLOAT_H_WRAP=1; \
	else :; \
	  SYS_FLOAT_H_WRAP=0; \
	fi; \
	$(GCC_FOR_TARGET) $(GCC_CFLAGS) $(ALL_CPPFLAGS) $(ENQUIRE_CFLAGS) \
	  -DSYS_FLOAT_H_WRAP=$$SYS_FLOAT_H_WRAP \
	  -I. -c $(srcdir)/enquire.c

# Create float.h source for the native machine.
# Make it empty if we can use the system float.h without changes.
float.h-nat: enquire
	-./enquire -f > tmp-float.h
	grep '#define [^_]' tmp-float.h >/dev/null || true > tmp-float.h
	mv tmp-float.h float.h-nat

# Create a dummy float.h source for a cross-compiler.
# ??? This isn't used anymore.  Should we create config/float-unkn.h
# and make that the default float_format in configure?
float.h-cross:
	echo "#ifndef	__GCC_FLOAT_NOT_NEEDED" > t-float.h-cross
	echo "#error float.h values not known for cross-compiler" >> t-float.h-cross
	echo "#endif" >> t-float.h-cross
	mv t-float.h-cross float.h-cross

