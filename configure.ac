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
# check gtkmm
PKG_CHECK_MODULES(GTKMM, gtkmm-2.4,,exit)
AC_SUBST(GTKMM_LIBS)
AC_SUBST(GTKMM_CFLAGS)

# check libglade
PKG_CHECK_MODULES(GLADEMM,libglademm-2.4)
AC_SUBST(GLADEMM_LIBS)
AC_SUBST(GLADEMM_CFLAGS)

# check glade
PKG_CHECK_MODULES(GLADE, [libglade-2.0 >= 2.6.4],, AC_MSG_ERROR([Cannot find Glade]))
PKG_CHECK_MODULES(GLADEUI, [gladeui-1.0 >= 3.6.0],, AC_MSG_ERROR([Cannot find GladeUI]))

# check svg
PKG_CHECK_MODULES(RSVG, [librsvg-2.0 >= 2.26],, AC_MSG_ERROR([Cannot find RSVG]))

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
				 src/Algorithms/HungrySimpleDinner/Makefile
				 src/Algorithms/PriorityDinner/Makefile
				 src/GUI/Makefile
				 src/GUI/lib/Makefile
				 src/GUI/widgets/Makefile
				 lib/Various/Makefile
				 lib/Makefile])


AC_OUTPUT
