
SUBDIRS = DnDAgent MocMsgProxy


lib_LTLIBRARIES = libWmxInstrument.la

libWmxInstrument_la_SOURCES = $(srcdir)/instrument.c

pkgdata_DATA =  DnDAgent/DefaultTracesAndMonitors.xml 

libWmxInstrument_la_CFLAGS =  \
			-I "$(srcdir)/DnDAgent" \
			-I "$(srcdir)/MocMsgProxy" \
			-I "$(srcdir)/../AppSrvInfra" \
			-I "$(srcdir)/../PipeHandler" \
			-I "$(srcdir)/../../Common/CommonServices" \
			-I "$(srcdir)/../../Common/CommonServices/XmlParser" \
			-I "$(srcdir)/../../OSInterface/OSAL/Primitives" \
			-I "$(srcdir)/../../OSInterface/OSAL/Services" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/IPCs" \
			-D "_LINUX" 

libWmxInstrument_la_LIBADD = DnDAgent/libDnDAgent.la \
			MocMsgProxy/libMocMsgProxy.la \
			$(top_builddir)/InfraStack/OSDependent/Linux/InfraStackModules/IPCs/libSockets.la

# FIXME: where do these header files really belong?
EXTRA_DIST = \
	MOCHandler/UDapiL5/ApplicationMocTaskDesc.h \
	MOCHandler/UDapiL5/UDapiCommonDefines.h \
	MOCHandler/UDapiL5/UDapiDll.h \
	MOCHandler/UDapiL5/UDapiL5.h
