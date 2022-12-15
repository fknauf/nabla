AC_INIT([Nabla], [0.0.1], , [nabla])
AM_INIT_AUTOMAKE([foreign 1.11 -Wall -Werror subdir-objects])

#AC_CONFIG_MACRO_DIR([m4])
AC_PREFIX_DEFAULT([/usr])

CXXFLAGS+=" -Wall -Wextra -pedantic -std=c++20"

AC_PROG_CXX

AX_BOOST_BASE([1.55.0])
AM_SILENT_RULES([yes])

AC_CONFIG_FILES([
	Makefile
])

AC_OUTPUT
