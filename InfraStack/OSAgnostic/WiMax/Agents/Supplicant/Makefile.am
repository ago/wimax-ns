noinst_LTLIBRARIES = libSupplicantAgent.la

DS_SUP_SOURCES = \
	$(srcdir)/Source/ds/aes_wrap.h \
	$(srcdir)/Source/ds/base64.h \
	$(srcdir)/Source/ds/build_config.h \
	$(srcdir)/Source/ds/ccx_aei.h \
	$(srcdir)/Source/ds/ccx.h \
	$(srcdir)/Source/ds/ccx_oid.h \
	$(srcdir)/Source/ds/ccx_pani.h \
	$(srcdir)/Source/ds/cfgdefs.h \
	$(srcdir)/Source/ds/common.h \
	$(srcdir)/Source/ds/config_api.h \
	$(srcdir)/Source/ds/config_defs.h \
	$(srcdir)/Source/ds/config.h \
	$(srcdir)/Source/ds/config_registry.h \
	$(srcdir)/Source/ds/config_ssid.h \
	$(srcdir)/Source/ds/config_types.h \
	$(srcdir)/Source/ds/config_vx.h \
	$(srcdir)/Source/ds/crypto.h \
	$(srcdir)/Source/ds/ctrl_iface.h \
	$(srcdir)/Source/ds/defs.h \
	$(srcdir)/Source/ds/driver_broadcom.h \
	$(srcdir)/Source/ds/driver.h \
	$(srcdir)/Source/ds/driver_hostap.h \
	$(srcdir)/Source/ds/driver_ndis.h \
	$(srcdir)/Source/ds/driver_ndisuio.h \
	$(srcdir)/Source/ds/driver_wext.h \
	$(srcdir)/Source/ds/eap_defs.h \
	$(srcdir)/Source/ds/eap.h \
	$(srcdir)/Source/ds/eap_host.h \
	$(srcdir)/Source/ds/eap_i.h \
	$(srcdir)/Source/ds/eapol_sm.h \
	$(srcdir)/Source/ds/eap_pax_common.h \
	$(srcdir)/Source/ds/eap_psk_common.h \
	$(srcdir)/Source/ds/eap_sim_common.h \
	$(srcdir)/Source/ds/eap_tls_common.h \
	$(srcdir)/Source/ds/eap_tlv.h \
	$(srcdir)/Source/ds/eap_ttls.h \
	$(srcdir)/Source/ds/eloop.h \
	$(srcdir)/Source/ds/event_ndisuio.h \
	$(srcdir)/Source/ds/hostapd.h \
	$(srcdir)/Source/ds/idrvccx.h \
	$(srcdir)/Source/ds/includes.h \
	$(srcdir)/Source/ds/l2_helper.h \
	$(srcdir)/Source/ds/l2_packet.h \
	$(srcdir)/Source/ds/md5.h \
	$(srcdir)/Source/ds/ms_funcs.h \
	$(srcdir)/Source/ds/ndisuio_common.h \
	$(srcdir)/Source/ds/oid_debug.h \
	$(srcdir)/Source/ds/os.h \
	$(srcdir)/Source/ds/pcsc_funcs.h \
	$(srcdir)/Source/ds/pmksa_cache.h \
	$(srcdir)/Source/ds/preauth.h \
	$(srcdir)/Source/ds/priv_netlink.h \
	$(srcdir)/Source/ds/radius_client.h \
	$(srcdir)/Source/ds/radius.h \
	$(srcdir)/Source/ds/rc4.h \
	$(srcdir)/Source/ds/sha1.h \
	$(srcdir)/Source/ds/simple_config.h \
	$(srcdir)/Source/ds/state_machine.h \
	$(srcdir)/Source/ds/swcserv.h \
	$(srcdir)/Source/ds/tls.h \
	$(srcdir)/Source/ds/version.h \
	$(srcdir)/Source/ds/wireless_copy.h \
	$(srcdir)/Source/ds/wpa2defs.h \
	$(srcdir)/Source/ds/wpa_common.h \
	$(srcdir)/Source/ds/wpa_ctrl.h \
	$(srcdir)/Source/ds/wpa.h \
	$(srcdir)/Source/ds/wpa_i.h \
	$(srcdir)/Source/ds/wpa_supplicant.h \
	$(srcdir)/Source/ds/wpa_supplicant_i.h \
	$(srcdir)/Source/ds/wsc_attributes.h \
	$(srcdir)/Source/ds/wsc_common.h \
	$(srcdir)/Source/ds/wsc_controller.h \
	$(srcdir)/Source/ds/wsc_debug.h \
	$(srcdir)/Source/ds/wsc_eap.h \
	$(srcdir)/Source/ds/wsc_eapol.h \
	$(srcdir)/Source/ds/wsc_types.h 

WPA_SUP_SOURCES = \
	$(top_srcdir)/InfraStack/OSAgnostic/WiMax/Wrappers/Supplicant/tls-wpa.h 

WPA_SUP_CFLAGS = \
	-D "WPA_OPEN_SOURCE" -D "USE_STANDARD_TLS_H_ONLY" \
	$(LIBEAP0_CFLAGS)


libSupplicantAgent_la_SOURCES = $(srcdir)/Source/SupplicantAgent.c \
				$(top_srcdir)/InfraStack/OSAgnostic/WiMax/Wrappers/Supplicant/wmxSDK_Sup_Impl.c \
				$(srcdir)/Source/SupplicantAgent.h

EXTRA_DIST = $(srcdir)/Source/Cert/supplicant_key.pem \
	     $(srcdir)/Source/Cert/supplicant_cert.pem \
	     $(srcdir)/Source/Cert/cacert.pem 



libSupplicantAgent_la_CFLAGS = 	-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/PipeHandler" \
				-I "$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/WrappersCommon" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L5Common" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Services" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/XmlParser" \
				-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
				-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" \
				-I "$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders" \
				-I "$(srcdir)/../../Wrappers/Include" \
				-I "$(srcdir)/../../Wrappers/Supplicant" \
				-I "$(srcdir)/../../Wrappers/Apdo" \
				-I "$(srcdir)/../NDnS/L4_db" \
				-I "$(srcdir)/../NDnS/Source" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/AppSrvInfra" \
				-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/Instrumantation/MOCHandler/UDapiL5" \
				-I "$(srcdir)/../NDnS/APDO" \
				-I "$(srcdir)/../../Wrappers/NDnS" \
				-I "$(srcdir)/../../Wrappers/Apdo" \
				-I "$(srcdir)/Source/ds" \
				-D _GNU_SOURCE \
				-D "_USE_TRACE" -D "BMI_MACHINE_ENDIANNESS_LITTLE" \
				-D "IEEE8021X_EAPOL" -D "_OS_WIN32SIM" -D "_LINUX"

# Depending on which supplicant we are using (device scape's vs open
# source), adjust targets and distribute anything else needed.
if WPA_SUP_ENABLE
libSupplicantAgent_la_SOURCES += $(WPA_SUP_SOURCES)
libSupplicantAgent_la_CFLAGS += $(WPA_SUP_CFLAGS)
EXTRA_DIST += $(DS_SUP_SOURCES)
else
libSupplicantAgent_la_SOURCES += $(DS_SUP_SOURCES)
EXTRA_DIST += $(WPA_SUP_SOURCES)
endif

