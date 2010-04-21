
CLEANFILES = iwmxsdk.rules config.xml

export LD_RUN_PATH=$(libdir)

bin_PROGRAMS = wimaxd
WIMAXD_NAME = @program_prefix@wimaxd@program_suffix@
varrundir = $(localstatedir)/run
pkgvarlogdir = ${varlogdir}/$(PACKAGE)
pkglocalstatedir = ${localstatedir}/lib/$(PACKAGE)

wimaxd_SOURCES = \
		$(srcdir)/Act.c \
		$(srcdir)/L4MsgProxy.c \
		$(srcdir)/L5SocketsDispatcher.c \
		$(srcdir)/L5Dispatcher.c \
		$(srcdir)/../../Common/L5Common/L5CommonUtils.c \
		$(srcdir)/KDapiAdapter.c \
		$(srcdir)/SVstatus.h \
		$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/KDapi/KDapi.c \
		$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/KDapi/KDapiForSim.c \
		$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/KDapi/KDapiForLinuxNlsock.h \
		$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/Skeletons/AppSrv/GenericMain.c \
		$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/Skeletons/AppSrv/GenericConsole.c \
		$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/Skeletons/AppSrv/GenericDaemon.c \
		$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/Instrumentation/LoadInstrumentation.c \
		$(srcdir)/DeviceConfiguration.c \
		$(srcdir)/Act.h \
		$(srcdir)/L4MsgProxy.h \
		$(srcdir)/L4MsgProxyIf.h \
		$(srcdir)/L5SocketsDispatcher.h \
		$(srcdir)/L5Dispatcher.h \
		$(srcdir)/KDapiAdapter.h \
		$(srcdir)/DeviceConfiguration.h \
		$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules/KDapi.h \
		$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules/KDapiForSim.h \
		$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/Skeletons/AppSrv/GenericMain.h 

EXTRA_DIST =	$(srcdir)/i2400m.conf \
		$(srcdir)/iwmxsdk.rules.in \
		$(top_srcdir)/InfraStack/OSDependent/Linux/Config/config.xml.in \
		$(top_srcdir)/InfraStack/OSDependent/Linux/Config/dhcp_renew.sh

noinst_DATA = $(top_srcdir)/InfraStack/OSAgnostic/WiMax/Agents/NDnS/XML_Files/NDnSAgentConfig_forDriver.xml \
		$(top_srcdir)/$(VER_INFO_BIN_FILE_SRC)

pkgdata_DATA =  ../../WiMax/Agents/Supplicant/Source/Cert/cacert.pem \
		../../WiMax/Agents/Supplicant/Source/Cert/supplicant_key.pem \
		../../WiMax/Agents/Supplicant/Source/Cert/supplicant_cert.pem \
		../Instrumantation/DnDAgent/DefaultTracesAndMonitors.xml \
		$(top_srcdir)/InfraStack/OSDependent/Linux/Config/dhcp_renew.sh \
		Ver_info.bin

pkglocalstate_DATA = WiMAX_DB.bin WiMAX_Def.bin

DISTCLEANFILES = WiMAX_DB.bin WiMAX_Def.bin Ver_info.bin

configdir = $(sysconfdir)/$(PACKAGE)
config_DATA = config.xml

VER_INFO_BIN_FILE_SRC = InfraStack/OSDependent/Linux/Ver_info.bin

if BINDB_ENABLED
DISABLE_OBFUSCATE = 0
WIMAX_DB_BIN_FILE = @WIMAX_DB_BIN@
VER_INFO_BIN_FILE = @VER_INFO_BIN@
else
DISABLE_OBFUSCATE = 1
WIMAX_DB_BIN_FILE = $(top_srcdir)/InfraStack/OSAgnostic/WiMax/Agents/NDnS/XML_Files/NDnSAgentConfig_forDriver.xml
VER_INFO_BIN_FILE = $(top_srcdir)/$(VER_INFO_BIN_FILE_SRC)
endif

WiMAX_DB.bin WiMAX_Def.bin: $(WIMAX_DB_BIN_FILE)
	cp $(WIMAX_DB_BIN_FILE) $@

git_version = $(shell cd $(top_srcdir) && git describe --abbrev=128 --always)

# If we get here, this means the file has to be generated
$(top_distdir)/$(VER_INFO_BIN_FILE_SRC) \
$(top_buildir)/$(VER_INFO_BIN_FILE_SRC) \
	::
	@echo $@: generating distribution version
	@[ -z "$(git_version)" ] \
		&& echo "git-version-n/a" > $@ \
		|| echo $(git_version) > $@
# FIXME: find a better sollution for this
	@echo 3.5.2 >> $@
	@[ -z "$(git_version)" ] \
		&& echo "WARNING: Git version not available" 1>&2 \
		|| true

dist-hook: $(top_distdir)/$(VER_INFO_BIN_FILE_SRC)

# These rules are only used during build time, so packaging (make
# dist) is not affected.
#
# If the bindb is enabled, the version information comes from the
# build prepared and it has to be used yes-or-yes. If bindb is
# disabled, we either use the one that comes prepackaged or generate
# it on the run with git.
#
# FIXME: find a better sollution for the 3.5.2 thingie
#
# When generating, we take the original always as a reference and if
# the new one is different to the original, we just update it :)
Ver_info.bin: $(VER_INFO_BIN_FILE)
	cp $(VER_INFO_BIN_FILE) $@
if ! BINDB_ENABLED
	@if ! [ -z "$(git_version)" ]; \
	then \
		echo $@: Generating, git version $(git_version); \
		echo $(git_version) > $@.new; \
		echo 3.5.2 >> $@.new; \
		cmp $@ $@.new || mv $@.new $@ && rm -f $@.new; \
	else \
		echo $@: Git n/a, copying from original $(VER_INFO_BIN_FILE); \
	fi 
endif

if WPA_SUP_ENABLE
sup_lib_path=@LIBEAP0_PREFIX@/lib/libeap.so.0
else
sup_lib_path=$(libdir)/wimax/libwpa_wimax_supplicant.so
endif

config.xml: $(top_srcdir)/InfraStack/OSDependent/Linux/Config/config.xml.in
	sed \
	-e "s|@@pkgdatadir@@|$(pkgdatadir)|g" \
	-e "s|@@lib@@dir@@|$(libdir)|g" \
	-e "s|@@sup_lib_path@@|$(sup_lib_path)|g" \
	-e "s|@@use_inst@@|$(USE_INST)|g" \
	-e "s|<DisableObfuscate>.*\<DisableObfuscate>|<DisableObfuscate>$(DISABLE_OBFUSCATE)</DisableObfuscate>|" \
	$< > $@

# Driver option
modprobedir = $(sysconfdir)/modprobe.d/
modprobe_DATA = i2400m.conf

# UDEV rules
udevrulesdir = $(sysconfdir)/udev/rules.d
udevrules_DATA = iwmxsdk.rules

iwmxsdk.rules: iwmxsdk.rules.in
	sed \
	-e "s|@@bin@@dir@@|$(bindir)|g" \
	-e "s|@@WIMAXD_NAME@@|$(WIMAXD_NAME)|g" \
	$< > $@

EXTRA_DIST += iwmxsdk.rules.in

daemondir = ${sysconfdir}/init.d
LOGDIR = ${localstatedir}/log/$(PACKAGE)

wimaxd_CFLAGS = \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/WiMax/Wrappers/Include" \
		-I "$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Services" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/XmlParser" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/PipeHandler" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/Instrumantation/MOCHandler/UDapiL5" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L5Common" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/WrappersCommon" \
		-I "../../WiMax/Agents/NDnS/Source" \
		-I "../../WiMax/Agents/Supplicant/Source" \
		-I "../../WiMax/Agents/Supplicant/Source/ds" \
		-I "$(srcdir)/../Handlers/MOCHandler/UDapiL5/"\
		-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules" \
		-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
		-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" \
		-I "$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders" \
		-I "$(srcdir)/../IPCs/Sockets"  \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/WiMax/Wrappers/NDnS" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/WiMax/Wrappers/Apdo" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/WiMax/Agents/NDnS/Source" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/WiMax/Agents/Supplicant/Source" \
		-I "$(top_srcdir)/InfraStack/OSAgnostic/WiMax/Agents/Supplicant/Source/ds"\
		@LIBWIMAX_CFLAGS@ \
		@I2400M_INCLUDES@ \
		-D "_USE_TRACE" -D "BMI_MACHINE_ENDIANNESS_LITTLE" -D "L5_USE_SERVER_SOCKETS" -D "LINUX" \
		-D "_OS_WIN32SIM" $(DEBUGSWITCH) \
		-D PKG_VAR_LOG_DIR="\"${pkgvarlogdir}\"" \
		-D VAR_RUN_DIR="\"$(varrundir)\"" \
		-D WIMAXD_NAME="\"$(WIMAXD_NAME)\"" \
		-D LIB_DIR="\"$(libdir)\""

wimaxd_LDADD = \
	../../WiMax/Agents/NDnS/libNDnSAgent.la \
	../../WiMax/Agents/Supplicant/libSupplicantAgent.la \
	../PipeHandler/libPipeHandler.la \
	../Instrumantation/libWmxInstrument.la \
	../../Common/CommonServices/libServices.la \
	@LIBWIMAX_LIBS@ \
	../../Common/L4Common/libL4Common.la \
	-lpthread \
	-ldl

wimaxd_LDFLAGS = "-rdynamic" -rdynamic

install-data-hook:
# 	  Create log directory
	  test -z $(DESTDIR)$(LOGDIR) || $(MKDIR_P) $(DESTDIR)$(LOGDIR) 
	  chmod 777 $(DESTDIR)$(LOGDIR)	

#	  Set the permissions on the dhcp script.
	  chmod +x $(DESTDIR)$(pkgdatadir)/dhcp_renew.sh

uninstall-hook:
	rm -fr $(DESTDIR)$(LOGDIR)
	rm -f iwmxsdk.rules
