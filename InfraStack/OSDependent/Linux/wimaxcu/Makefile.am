
#export LD_RUN_PATH=$(pkglibdir)

bin_PROGRAMS = wimaxcu

wimaxcu_SOURCES = 	$(srcdir)/wimaxcu_main.c \
			$(srcdir)/wimaxcu_cmdhdlr.c \
			$(srcdir)/wimaxcu_apdo_op.c \
			$(srcdir)/wimaxcu_set_get_op.c \
			$(srcdir)/wimaxcu_connect_op.c \
			$(srcdir)/wimaxcu_scan_op.c \
			$(srcdir)/wimaxcu_util.c \
			wimaxcu.h \
			wimaxcu_defs.h \
			wimaxcu_util.h 

wimaxcu_CFLAGS = 	-I "$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders/" \
		 	-I "$(top_builddir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders/"  


#			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives/" 
#			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services/" 

wimaxcu_LDADD = \
	$(top_builddir)/InfraStack/OSAgnostic/WiMax/Wrappers/iWmxSDK/libiWmxSdk.la \
	-lpthread \
	-ldl \
	-lm

