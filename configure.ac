AC_INIT([wimax],[1.5.2.35],[wimax-linux@wimaxlinux.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_PROG_LIBTOOL
AC_CONFIG_HEADERS([config.h])


# For multiple installations
if test x$program_prefix = xNONE
   then
   cooked_program_prefix=
else
   cooked_program_prefix=$program_prefix
fi
AC_SUBST(program_prefix, $cooked_program_prefix)
if test x$program_suffix = xNONE
   then
   cooked_program_suffix=
else
   cooked_program_suffix=$program_suffix
fi
AC_SUBST(program_suffix, $cooked_program_suffix)


#if (test "${CFLAGS}" = ""); then
CFLAGS="-O2 -g -Wall -D _USE_TRACE -ldl -lm"
#fi

AC_ARG_ENABLE(debug, AC_HELP_STRING([--enable-debug],
			[enable compiling with debugging information]), [
	if (test "${enableval}" = "yes" &&
				test "${ac_cv_prog_cc_g}" = "yes"); then
		CFLAGS="-g -Wall -D _DEBUG -D _USE_TRACE -ldl -lm"
	fi
])


# If libnl-1 is installed
# We do this only when we use the included wimax-tools, as we can't
# rely on the pkg-config infoprmation being available
AC_ARG_WITH(libnl1, 
            AC_HELP_STRING([--with-libnl1],
			   [prefix to libnl (>=1.0-pre7) installation; defaults to
                            whichever is found in the system with pkg-config.
                            USE ABSOLUTE PATHS.]), 
            export PKG_CONFIG_PATH="$withval:$withval/lib/pkgconfig")
PKG_CHECK_MODULES(LIBNL1, libnl-1 >= 1.0-pre7)
libnl1_prefix=`pkg-config "libnl-1 >= 1.0-pre7" --variable=prefix`
AC_MSG_RESULT(Using libnl1 from $libnl1_prefix)
AC_SUBST(LIBNL1_CFLAGS)
AC_SUBST(LIBNL1_LIBS)

# If libwimaxll is installed
AC_ARG_WITH(libwimaxll, 
            AC_HELP_STRING([--with-libwimaxll],
			   [path to where libwimaxll is installed. USE ABSOLUTE PATHS.]), 
             [
                export PKG_CONFIG_PATH="$withval:$withval/lib/pkgconfig"
                AC_MSG_RESULT(Using libwimaxll from $withval)
                PKG_CHECK_MODULES(LIBWIMAX, libwimaxll-0, dummy=yes,
                                  AC_MSG_ERROR(libwimaxll is required))                                
                wimaxtools_use_included=false
             ],
             [
                # Hardwire using the internal copy of wimax-tools
                #
                # Fake what pkg-config would do -- the subpackage
                # still is not configured, so we can't rely on it the
                # .pc files being generated for pkg-config to do the
                # right thing.
                AC_CONFIG_SUBDIRS([wimax-tools])
                wimaxtools_use_included=true
                export LIBWIMAX_CFLAGS="-I$ac_pwd/$srcdir/wimax-tools/include"
                export LIBWIMAX_LIBS="-L$ac_pwd/wimax-tools/lib -lwimaxll $LIBNL1_LIBS"
                AC_MSG_RESULT(Using included libwimaxll from $srcdir/wimax-tools)
		AC_SUBST(WIMAX_TOOLS, "wimax-tools")
             ])


LDFLAGS_save="$LDFLAGS"
LDFLAGS="$LIBWIMAX_LIBS $LDFLAGS"
AC_CHECK_FUNCS(wimaxll_state_get)
LDFLAGS="$LDFLAGS_save"

# Linux WiMAX stack
LINUX_KERNEL=/usr
AC_ARG_WITH(linux,
            AC_HELP_STRING([--with-linux],
			   [path to the Linux kernel headers/source (containing the
                            definitions for the WiMAX stack); defaults to what
                            is installed in your system's /usr/include/linux.
                            USE ABSOLUTE PATHS.]),
            [
                LINUX_KERNEL="$withval"
            ])
# Old, for backwards compat
AC_ARG_WITH(i2400m, 
            AC_HELP_STRING([--with-i2400m],
			   [path to the Linux kernel headers/source (containing the
                            definitions for the WiMAX stack); defaults to what
                            is installed in your system's /usr/include/linux.
                            DEPRECATED: this option will be removed soon.
                            USE ABSOLUTE PATHS.]),
            [
                LINUX_KERNEL="$withval"
            ])

AC_CHECK_FILE([$LINUX_KERNEL/include/linux/wimax.h],
                [AC_DEFINE([HAVE_WIMAX_H], 1, [Define to 1 if you have <linux/wimax.h>.])],
                [AC_MSG_ERROR([Can't locate include/linux/wimax.h in
 $LINUX_KERNEL])])

AC_SUBST(I2400M_INCLUDES, "-I${LINUX_KERNEL}/include")
AC_SUBST(LINUX_INCLUDE_PATH, "${LINUX_KERNEL}/include")

AC_ARG_ENABLE(instrument, 
	      AC_HELP_STRING([--enable-instrument],[enable support for instrumentation]), 
	      [
		AC_MSG_RESULT(Instrument has been enabled)
		AC_SUBST(USE_INST, "1")
	      ],
	      [
		AC_MSG_RESULT(Instrument has been disabled)
		AC_SUBST(USE_INST, "0")
	      ])

AC_ARG_ENABLE(bindb, 
	      AC_HELP_STRING([--enable-bindb],[enable support for binary databases (disabled by default)]), 
	      __BINDB_ENABLED=$enable_bindb,
	      __BINDB_ENABLED=no)
if test x$__BINDB_ENABLED = xyes
then
	AC_MSG_RESULT(Database support will be in binary format)
else
	AC_MSG_RESULT(Database support will be in clear text format)
fi
AM_CONDITIONAL([BINDB_ENABLED], [test x$__BINDB_ENABLED = xyes])

AC_ARG_WITH(wimax-db-bin, 
            AC_HELP_STRING([--with-wimax-db-bin],
			   [path to the pre-generated binary WiMAX
                            configuration database; this is only used
                            when --enable-bindb is specified. USE
                            ABSOLUTE PATHS.]),
            [],
            with_wimax_db_bin="InfraStack/OSAgnostic/WiMAX/Agents/NDnS/XML_Files/WiMAX_DB.bin")
            
if test x$__BINDB_ENABLED = xyes
then
        AC_CHECK_FILE([$with_wimax_db_bin],
                      [],
                      [AC_MSG_ERROR([Can't locate $with_wimax_db_bin])])
fi
AC_SUBST(WIMAX_DB_BIN, $with_wimax_db_bin)

curr_dir=`pwd`
cd $srcdir/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders
ln -sf ../../../../OSAgnostic/OSInterface/OSAL/Primitives/wimax_osal_types.h wimax_osal_types.h
ln -sf ../../OSAL/Primitives/wimax_osal_basictypes.h wimax_osal_basictypes.h
ln -sf ../../OSAL/Primitives/wimax_osal_linux_types.h wimax_osal_linux_types.h
ln -sf ../../OSAL/Primitives/wimax_consts.h wimax_consts.h
ln -sf ../../OSAL/Primitives/windows_error.h windows_error.h
ln -sf ../../OSAL/Primitives/wimax_osal_error.h wimax_osal_error.h
cd $curr_dir

AC_CONFIG_FILES([
	Makefile
	wns-version.h
	InfraStack/OSDependent/Linux/OSAL/Makefile
	InfraStack/OSDependent/Linux/InfraStackModules/IPCs/Makefile
	InfraStack/OSAgnostic/Common/CommonServices/Makefile
	InfraStack/OSAgnostic/Common/CommonServices/XmlParser/Makefile
	InfraStack/OSAgnostic/Common/L4Common/Makefile
	InfraStack/OSAgnostic/Product/PipeHandler/Makefile
	InfraStack/OSAgnostic/WiMax/Agents/NDnS/Makefile
	InfraStack/OSAgnostic/WiMax/Agents/Supplicant/Makefile
	InfraStack/OSAgnostic/Product/Instrumantation/Makefile
	InfraStack/OSAgnostic/Product/Instrumantation/DnDAgent/Makefile
	InfraStack/OSAgnostic/Product/Instrumantation/MocMsgProxy/Makefile
	InfraStack/OSAgnostic/Product/AppSrvInfra/Makefile
	InfraStack/OSAgnostic/WiMax/Wrappers/iWmxSDK/Makefile
	InfraStack/OSAgnostic/WiMax/Wrappers/iWmxSDK/libiWmxSdk-0.pc
	InfraStack/OSAgnostic/WiMax/Wrappers/iWmxSDK/libiWmxSdk-0-uninstalled.pc
	InfraStack/OSDependent/Linux/wimaxcu/Makefile
	InfraStack/OSDependent/Linux/wimax_utils/wimax_monitor/Makefile
	])
AC_OUTPUT

