
noinst_LTLIBRARIES = libSockets.la
libSockets_la_SOURCES = $(srcdir)/Socket.c \
			$(srcdir)/ClientsSockets.c \
			$(srcdir)/ServerSocket.c \
			$(srcdir)/DnDServerSocket.c \
			$(srcdir)/DnDServerSocket.h \
			$(srcdir)/NPipe.c \
			$(srcdir)/ClientNPipe.c \
			$(srcdir)/ServerNPipe.c \
			$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules/IPC_Common.h \
			$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules/IPC_Client.h \
			$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules/IPC_Server.h

libSockets_la_CFLAGS = \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Services" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/XmlParser" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" 

