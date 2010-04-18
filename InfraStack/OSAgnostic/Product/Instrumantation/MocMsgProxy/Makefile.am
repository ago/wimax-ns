noinst_LTLIBRARIES = libMocMsgProxy.la


libMocMsgProxy_la_SOURCES = $(srcdir)/MocMsgProxy.c \
	$(srcdir)/MocMsgProxy.h \
	$(srcdir)/MocMsgProxyIF.h \
	$(srcdir)/MOC_Types.h \
	$(srcdir)/MOC_Utils.h \
	$(srcdir)/Osal_TaskTypes.h

libMocMsgProxy_la_CFLAGS = \
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
			-D "_USE_TRACE" -D "BMI_ENDIANNESS_LITTLE" -D "_LINUX" -D "_OS_WIN32SIM" 


