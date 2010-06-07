noinst_LTLIBRARIES = libDnDAgent.la


varlogdir = ${localstatedir}/log
pkgvarlogdir = ${varlogdir}/wimax

libDnDAgent_la_SOURCES = \
			 $(srcdir)/DnDAgent.c \
			 $(srcdir)/DnDUtils.c \
			 $(srcdir)/L4DnDHandler.c \
			 $(srcdir)/../DnDWrapper/wmxSDK_DnD_Common.c \
			 $(srcdir)/../DnDWrapper/wmxSDK_DnD_Common.h \
			 $(srcdir)/../DnDWrapper/wmxSDK_DnD_Cmn.h \
			 $(srcdir)/../DnDWrapper/wmxSDK_DnD.h \
			 $(srcdir)/RemoveExcessFiles.c \
			 $(srcdir)/RemoveExcessFiles.h \
			 $(srcdir)/DnDAgent.h \
			 $(srcdir)/DnDUtils.h \
			 $(srcdir)/DnDAgent_Internal.h \
			 $(srcdir)/L4DnDHandler.h \
			 $(srcdir)/L4DnDHandler_Internal.h \
			 $(srcdir)/TraceLogger.h



EXTRA_DIST = DefaultTracesAndMonitors.xml

libDnDAgent_la_CFLAGS = \
			-I "$(srcdir)/../MocMsgProxy" \
			-I "$(srcdir)/../DnDWrapper" \
			-I "$(srcdir)/../MOCHandler/UDapiL5" \
			-I "$(srcdir)/../../AppSrvInfra" \
			-I "$(srcdir)/../../PipeHandler" \
			-I "$(srcdir)/../../../Common/CommonServices" \
			-I "$(srcdir)/../../../Common/CommonServices/XmlParser" \
			-I "$(srcdir)/../../../Common/L5Common" \
			-I "$(srcdir)/../../../Common/WrappersCommon" \
			-I "$(srcdir)/../../../OSInterface/OSAL/Primitives" \
			-I "$(srcdir)/../../../OSInterface/OSAL/Services" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules"  \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/IPCs" \
 			@I2400M_INCLUDES@ \
			@LIBWIMAX_CFLAGS@ \
			-D "BMI_MACHINE_ENDIANNESS_LITTLE" -D "LINUX"  \
			-D VAR_LOG_DIR="\"${varlogdir}\"" \
			-D PKG_VAR_LOG_DIR="\"${pkgvarlogdir}\"" \
			-D PKG_DATA_DIR="\"${pkgdatadir}\""

