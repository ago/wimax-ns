AC_INIT([wimax],[1.5],[wimax-linux@wimaxlinux.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign tar-ustar])
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


# Libwimax from wimax-tools
AC_ARG_WITH(libwimaxll, 
            AC_HELP_STRING([--with-libwimaxll],
			   [path to where libwimax is installed. USE ABSOLUTE PATHS.]), 
            export PKG_CONFIG_PATH="$withval:$withval/lib/pkgconfig:$PKG_CONFIG_PATH")
PKG_CHECK_MODULES(LIBWIMAX, libwimaxll-0)
libwimax_prefix=`pkg-config libwimaxll-0 --variable=prefix`
AC_MSG_RESULT(Using libwimax from $libwimax_prefix)
AC_SUBST(LIBWIMAX_CFLAGS)
AC_SUBST(LIBWIMAX_LIBS)

# Check if wimax-tools provide wimaxll_state_get()
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

AC_CHECK_HEADER(zlib.h, [],
             
   [AC_MSG_ERROR([Can't locate zlib.h; did you install zlib-devel?])])
AC_CHECK_LIB(z, gzopen, [],
             [AC_MSG_ERROR([Can't locate libz; did you install zlib-devel?])])

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

AC_ARG_WITH(ver-info-bin, 
            AC_HELP_STRING([--with-ver-info-bin],
			   [path to the pre-generated binary
                            ver_info.bin file; this is only used when
                            --enable-bindb is specified. USE ABSOLUTE
                            PATHS.]),
            [],
            with_ver_info_bin="InfraStack/OSDependent/Linux/Config/Ver_info.bin")

if test x$__BINDB_ENABLED = xyes
then
        AC_CHECK_FILE([$with_wimax_db_bin],
                      [],
                      [AC_MSG_ERROR([Can't locate $with_wimax_db_bin])])
        AC_CHECK_FILE([$with_ver_info_bin],
                      [],
                      [AC_MSG_ERROR([Can't locate $with_ver_info_bin])])
fi
AC_SUBST(WIMAX_DB_BIN, $with_wimax_db_bin)
AC_SUBST(VER_INFO_BIN, $with_ver_info_bin)

AC_ARG_ENABLE(sup-ds, 
            AC_HELP_STRING([--enable-sup-ds],
			   [Enable usage of the DS binary
                            supplicant (disabled by default)]),
            [], [enable_sup_ds=no])         

AC_ARG_WITH(sup-wpa, 
            AC_HELP_STRING([--with-sup-wpa],
			   [Specify prefix where the WPA supplicant
                            can be found. USE ABSOLUTE PATHS.]),
            [
                test -z "$with_sup_wpa" && with_sup_wpa=/usr
                test x"$with_sup_wpa" = xyes && with_sup_wpa=/usr
                enable_sup_wpa=yes
                enable_sup_ds=no
                export PKG_CONFIG_PATH="$with_sup_wpa:$with_sup_wpa/lib/pkgconfig:$PKG_CONFIG_PATH"
            ], 
            [
                with_sup_wpa=/usr
            ])

if test x$enable_sup_ds = xyes
then
	AC_MSG_RESULT([supplicant: configured DS binary supplicant])
        enable_sup_wpa=no
else
        enable_sup_wpa=yes
        PKG_CHECK_MODULES(LIBEAP0, libeap0)
        libeap0_prefix=`pkg-config libeap0 --variable=prefix`
        AC_MSG_RESULT(Using EAP library from $libeap0_prefix)
        AC_SUBST(LIBEAP0_CFLAGS)
        AC_SUBST(LIBEAP0_LIBS)
        AC_SUBST(LIBEAP0_PREFIX, $libeap0_prefix)
fi
AC_SUBST(WPA_SUP_PREFIX, $with_sup_wpa)
AM_CONDITIONAL(WPA_SUP_ENABLE, test x$enable_sup_wpa = xyes)


curr_dir=`pwd`
mkdir -p InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders
cd InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders
ln -sf $ac_abs_confdir/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives/wimax_osal_types.h
ln -sf $ac_abs_confdir/InfraStack/OSDependent/Linux/OSAL/Primitives/wimax_osal_basictypes.h
ln -sf $ac_abs_confdir/InfraStack/OSDependent/Linux/OSAL/Primitives/wimax_osal_linux_types.h
ln -sf $ac_abs_confdir/InfraStack/OSDependent/Linux/OSAL/Primitives/wimax_consts.h
ln -sf $ac_abs_confdir/InfraStack/OSDependent/Linux/OSAL/Primitives/windows_error.h
ln -sf $ac_abs_confdir/InfraStack/OSDependent/Linux/OSAL/Primitives/wimax_osal_error.h
ln -sf $ac_abs_confdir/InfraStack/OSDependent/Linux/OSAL/Services/wimax_osal_win_config_controller_defines.h
cd $curr_dir

AC_CONFIG_FILES([
	Makefile
	wns-version.h
        wimax.spec
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

