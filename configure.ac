#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# AC_PREREQ(2.59)
AC_INIT([knights-dinner], [0.1])
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME,AC_PACKAGE_VERSION)
AC_CONFIG_HEADER(config.h)

dnl Initialize maintainer mode
AM_MAINTAINER_MODE

dnl Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

ASTYLE_OPT="-A1 -T -C -S -N -L -w -Y -M -f -p --mode=c --lineend=linux --align-reference=type --align-pointer=type --suffix=none --style=ansi"
AC_SUBST(ASTYLE_OPT)

# Checks for libraries.

CXXFLAGS="-I\$(top_builddir)/include -std=c++03 -pthread"

AC_SUBST(LDFLAGS)
AC_SUBST(CXXFLAGS)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_STRUCT_TM

# Checks for library functions.
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
				 src/Makefile
				 src/Objects/Makefile
				 src/Objects/Table/Makefile
				 src/Objects/Knight/Makefile
				 src/Objects/Knife/Makefile
				 src/Algorithms/Makefile
				 src/Algorithms/Dinner/Makefile
				 src/Algorithms/SimpleDinner/Makefile
				 src/GUI/Makefile
				 lib/Various/Makefile
				 lib/Makefile])


AC_OUTPUT
