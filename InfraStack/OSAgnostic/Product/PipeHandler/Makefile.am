noinst_LTLIBRARIES = libPipeHandler.la

libPipeHandler_la_SOURCES = \
				$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/Skeletons/PipeHandler/PipeHandlerMain.c \
				$(srcdir)/ConnGateKeeper.c \
			  	$(srcdir)/L5Connector.c \
			  	$(srcdir)/PipeHandler_Ctrl.c \
			  	$(srcdir)/PipeServices_Ctrl.c \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/L5Common/L5CommonUtils.c \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/L5Common/EventSubscribers.c \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/VersionHandshake.c \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/L5Common/IndicatorsSubscribers.c \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/Messenger.c \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/VersionUtils.c \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/WrappersCommon/WrappersCommon.c \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/WrappersCommon/WrappersUtils.c \
			  	$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/TraceModule/TraceModule.c \
			  	$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/TraceModule/TraceAgentInternal.h \
				$(srcdir)/Defs.h \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/L5Common/EventSubscribers.h \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/L5Common/IndicatorsSubscribers.h \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/Messenger.h \
				$(srcdir)/PipeHandler_Ctrl.h \
				$(srcdir)/PipeHandler.h \
				$(srcdir)/PipeHandlerInternal.h \
				$(srcdir)/PipeHandlerVersion.h \
				$(srcdir)/PipeServices_Ctrl.h \
			  	$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules/TraceModule.h \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/VersionUtils.h \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/WrappersCommon/WrappersCommon.h \
			  	$(top_srcdir)/InfraStack/OSAgnostic/Common/WrappersCommon/WrappersUtils.h 



# TODO: Check if these files can be safely excluded from the build
#			  	$(srcdir)/PipeHandler_CtrlInternal.c 
#				$(srcdir)/PipeHandler_CtrlInternal.h 



libPipeHandler_la_CFLAGS = 	-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices" \
			   	-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives" \
			   	-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Services" \
			   	-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL" \
			   	-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules" \
			   	-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/XmlParser" \
			   	-I "$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated" \
				-I "$(srcdir)/../../Common/L5Common" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/WrappersCommon" \
			  	-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
			  	-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/L4BufMan" \
			   	-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
			  	-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/AppSrvInfra" \
			  	-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/Instrumantation/MOCHandler/UDapiL5" \
			   	-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" \
			  	-I "$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/TraceModule/" \
			  	-D _GNU_SOURCE \
			  	-D "L5_USE_CLIENT_SOCKETS" -D "_USE_TRACE" \
				@LIBWIMAX_CFLAGS@				\
			  	-D "BMI_MACHINE_ENDIANNESS_LITTLE" -D "_LINUX"

libPipeHandler_la_LIBADD = \
	$(top_builddir)/InfraStack/OSDependent/Linux/InfraStackModules/IPCs/libSockets.la \
	@LIBWIMAX_LIBS@




