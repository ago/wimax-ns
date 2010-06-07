SUBDIRS = XmlParser 
noinst_LTLIBRARIES = libServices.la

varlogdir = ${localstatedir}/log
pkgvarlogdir = ${varlogdir}/$(PACKAGE)
pkgsysconfdir = ${sysconfdir}/$(PACKAGE)

libServices_la_SOURCES = $(srcdir)/List.c \
			 $(srcdir)/L4ConfigurationManager.c \
			 $(srcdir)/Queue.c \
			 $(srcdir)/Services_Ctrl.c \
			$(srcdir)/CommonServices.h \
			$(srcdir)/L4ConfigurationManager.h \
			$(srcdir)/../L5Common/L5Common.h \
			$(srcdir)/../L5Common/L5CommonUtils.h \
			$(srcdir)/../L5Common/L5OpCodes.h \
			$(srcdir)/List.h \
			$(srcdir)/Queue.h \
			$(srcdir)/Services_Ctrl.h \
			$(srcdir)/Versions.h 

# Un-resolved headers...
# $(srcdir)/UDapiCommonDefines.h 

#EXTRA_DIST = 	config.xml
libServices_la_CFLAGS =  -I "$(srcdir)/XmlParser" \
			 -I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives" \
			 -I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Services" \
			 -I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL" \
			 -I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules" \
			 -I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
			 -I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" \
			 -I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L5Common" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/WrappersCommon" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/PipeHandler" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
			 -I "$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/WiMax/Wrappers/Include" \
			 -I "$(top_srcdir)" \
			 -D PKG_VAR_LOG_DIR="\"$(pkgvarlogdir)\"" \
			 -D PKG_SYSCONF_DIR="\"$(pkgsysconfdir)\"" \
			 -D LIB_DIR="\"$(libdir)\""  \
			 -D PKG_DATA_DIR="\"$(pkgdatadir)\"" 

libServices_la_LIBADD = XmlParser/libXmlParser.la $(top_builddir)/InfraStack/OSDependent/Linux/OSAL/libosal.la
