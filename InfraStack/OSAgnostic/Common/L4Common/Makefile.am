noinst_LTLIBRARIES = libL4Common.la


libL4Common_la_SOURCES = $(srcdir)/SourceControl/BitmanCommon.c \
	  	   	 $(srcdir)/SourceControl/L4BufMan_L4Common.c \
			 $(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/L4BufMan_L3L4Structs.c \
			 $(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/L4BufMan_L3L4DmStructs.c \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/BasicBitmanTypes.h \
			$(srcdir)/SourceControl/BitmanCommon.h \
			$(srcdir)/SourceControl/Intel_80216_L4_interface.h \
			$(srcdir)/SourceControl/Intel_80216_L4_interface_OS.h \
			$(srcdir)/SourceControl/L3L4CommonDefines.h \
			$(srcdir)/SourceControl/L4BufMan_L4Common_Desc.h \
			$(srcdir)/SourceControl/L4BufMan_L4Common.h \
			$(srcdir)/SourceControl/L4DnDMonitorHeader.h \
			$(srcdir)/SourceControl/L4MonitorGroups.h \
			$(srcdir)/SourceControl/Pal_General.h \
			$(srcdir)/SourceControl/CommonDefinitions.h \
			$(srcdir)/SourceControl/TypesProxy.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/l2l3_api_ranging_enums.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/L3L4Structs.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/L3L4TlvTypes.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/L4BufMan_L3L4Structs_Desc.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/L4BufMan_L3L4Structs.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/L4Common.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/LedDefinitions.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/MonitorGeneral.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/TraceSubSystem.h
		

AM_CFLAGS = -I "$(srcdir)/SourceControl" \
	    -I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL" \
	    -I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives" \
	    -I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Services" \
	    -I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" \
	    -I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
	    -I "$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated" \
	    -D "BMI_MACHINE_ENDIANNESS_LITTLE" -D "_LINUX"

