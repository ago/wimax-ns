
bin_PROGRAMS = wimax_monitor

wimax_monitor_SOURCES = \
	wimax_monitor.c \
	wimax_monitor_utils.c

wimax_monitor_CFLAGS = \
	-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/XmlParser" \
	-I "$(top_srcdir)/InfraStack/OSAgnostic/WiMax/Wrappers/Include" \
	-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/WrappersCommon" \
	-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices" \
	-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL" \
	-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives" \
	-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Services" \
	-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
	-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
	-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" \
	-I "$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders"


wimax_monitor_LDADD = \
	$(top_builddir)/InfraStack/OSAgnostic/WiMax/Wrappers/iWmxSDK/libiWmxSdk.la \
	-lpthread \
	-ldl \
	-lm
