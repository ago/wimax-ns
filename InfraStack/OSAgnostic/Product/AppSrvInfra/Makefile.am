
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
		$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/KDapi/KDapi.c \
		$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/KDapi/KDapiForSim.c \
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

EXTRA_DIST =	$(srcdir)/i2400m_idle_mode.conf \
		$(srcdir)/iwmxsdk.rules.in

pkglocalstate_DATA = $(top_srcdir)/InfraStack/OSAgnostic/WiMax/Agents/NDnS/XML_Files/WiMAX_DB.bin \
		$(top_srcdir)/InfraStack/OSAgnostic/WiMax/Agents/NDnS/XML_Files/WiMAX_Def.bin 

pkgdata_DATA =  ../../WiMax/Agents/Supplicant/Source/Cert/cacert.pem \
		../../WiMax/Agents/Supplicant/Source/Cert/supplicant_key.pem \
		../../WiMax/Agents/Supplicant/Source/Cert/supplicant_cert.pem \
		../Instrumantation/DnDAgent/DefaultTracesAndMonitors.xml \
		$(top_srcdir)/InfraStack/OSDependent/Linux/Config/Ver_info.bin \
		$(top_srcdir)/InfraStack/OSDependent/Linux/Config/dhcp_renew.sh 

configdir = $(sysconfdir)/$(PACKAGE)
config_DATA = config.xml
config.xml: $(top_srcdir)/InfraStack/OSDependent/Linux/Config/config.xml.in
	sed \
	-e "s|@@pkgdatadir@@|$(pkgdatadir)|g" \
	-e "s|@@lib@@dir@@|$(libdir)|g" \
	-e "s|@@use_inst@@|$(USE_INST)|g" \
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
