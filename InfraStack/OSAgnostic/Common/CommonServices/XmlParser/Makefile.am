noinst_LTLIBRARIES = libXmlParser.la


libXmlParser_la_SOURCES = $(srcdir)/XmlParser.c \
			  $(srcdir)/eXpat/xmlparse.c \
			  $(srcdir)/eXpat/xmltok.c \
			  $(srcdir)/eXpat/xmlrole.c \
			$(srcdir)/XmlParser.h \
			$(srcdir)/eXpat/amigaconfig.h \
			$(srcdir)/eXpat/ascii.h \
			$(srcdir)/eXpat/asciitab.h \
			$(srcdir)/eXpat/expat.h \
			$(srcdir)/eXpat/expat_external.h \
			$(srcdir)/eXpat/iasciitab.h \
			$(srcdir)/eXpat/internal.h \
			$(srcdir)/eXpat/latin1tab.h \
			$(srcdir)/eXpat/macconfig.h \
			$(srcdir)/eXpat/nametab.h \
			$(srcdir)/eXpat/utf8tab.h \
			$(srcdir)/eXpat/winconfig.h \
			$(srcdir)/eXpat/xmlrole.h \
			$(srcdir)/eXpat/xmltok.h \
			$(srcdir)/eXpat/xmltok_impl.h 

EXTRA_DIST = 	$(srcdir)/eXpat/xmltok_impl.c \
		$(srcdir)/eXpat/xmltok_ns.c

libXmlParser_la_CFLAGS = -I "$(srcdir)/../" \
			 -I "$(srcdir)/eXpat" \
			 -I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL" \
			 -I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives" \
			 -I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Services" \
			 -I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
			 -I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" \
			 -I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
			 -D _GNU_SOURCE \
			 -D "COMPILED_FROM_DSP" -D "XML_STATIC" -D "_LINUX" 

