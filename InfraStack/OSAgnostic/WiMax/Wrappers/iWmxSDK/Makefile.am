lib_LTLIBRARIES = libiWmxSdk.la

pkgsysconfdir = ${sysconfdir}/$(PACKAGE)

libiWmxSdk_la_SOURCES = $(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/Skeletons/Wrappers/WrappersMain.c \
			$(srcdir)/iWmxSDK.c \
			$(srcdir)/../CommonAPI/wimaxapi.c \
			$(srcdir)/../Miscellaneous/wmxSDK_Msc_Impl.c \
			$(srcdir)/../NDnS/wmxSDK_Nds_2.c \
			$(srcdir)/../NDnS/wmxSDK_Nds_3.c \
			$(srcdir)/../NDnS/wmxSDK_Nds_Ctrl.c \
			$(srcdir)/../NDnS/wmxSDK_Nds_IndHandler.c \
			$(srcdir)/../NDnS/wmxSDK_Nds_Internals.c \
			$(srcdir)/../NDnS/wmxSDK_Nds_L5.c \
			$(srcdir)/../NDnS/wmxSDK_Nds_Utils.c \
			$(srcdir)/../NDnS/wmxSDK_Coex_3.c \
			$(srcdir)/../Apdo/wmxSDK_Apdo_Impl.c \
			$(srcdir)/../Apdo/wmxSDK_Apdo_Utils.c \
			$(srcdir)/../Apdo/wmxSDK_Apdo_L5.c \
			$(srcdir)/../Apdo/wmxSDK_Apdo_IndHandler.c \
			$(srcdir)/../Apdo/wmxSDK_Apdo_Internals.c \
			$(srcdir)/../Apdo/AES.c \
			$(srcdir)/../Apdo/AES_CCM.c \
			$(srcdir)/../Include/iWmxSDK.h \
			$(srcdir)/../Include/iWmxSDKVersion.h \
			$(srcdir)/../Include/wmxSDK_Apdo_3.h \
			$(srcdir)/../Include/wmxSDK_Apdo_Cmn.h \
			$(srcdir)/../Include/wmxSDK_Apdo_Ctrl.h \
			$(srcdir)/../Include/wmxSDK_Apdo_L5.h \
			$(srcdir)/../Include/wmxSDK_Apdo_Utils.h \
			$(srcdir)/../Include/wmxSDK_Msc_2.h \
			$(srcdir)/../Include/wmxSDK_Msc_CtrlAgent.h \
			$(srcdir)/../Include/wmxSDK_Msc_Ctrl.h \
			$(srcdir)/../Include/wmxSDK_Msc_L5.h \
			$(srcdir)/../Include/wmxSDK_Ndis_3.h \
			$(srcdir)/../Include/wmxSDK_Ndis_Ctrl.h \
			$(srcdir)/../Include/wmxSDK_Ndis_L5.h \
			$(srcdir)/../Include/wmxSDK_Nds_1.h \
			$(srcdir)/../Include/wmxSDK_Nds_2.h \
			$(srcdir)/../Include/wmxSDK_Nds_3.h \
			$(srcdir)/../Include/wmxSDK_Nds_Cmn.h \
			$(srcdir)/../Include/wmxSDK_Nds_CtrlAgent.h \
			$(srcdir)/../Include/wmxSDK_Nds_Ctrl.h \
			$(srcdir)/../Include/wmxSDK_Nds_L5.h \
			$(srcdir)/../Include/wmxSDK_Sup_1.h \
			$(srcdir)/../Include/wmxSDK_Sup_4.h \
			$(srcdir)/../Include/wmxSDK_Sup_CtrlAgent.h \
			$(srcdir)/../Include/wmxSDK_Sup_Ctrl.h \
			$(srcdir)/../Include/wmxSDK_Sup_Defines.h \
			$(srcdir)/../Include/wmxSDK_Coex_3.h \
			$(srcdir)/../Include/wmxSDK_Sup_L5.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders/CoexAPI.h 


# TODO :: What todo with these file??

#			$(srcdir)/../Supplicant/wmxSDK_Sup_Impl.c 



pkginclude_HEADERS = 	$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders/WiMaxAPI.h \
		  	$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders/WiMaxAPIEx.h \
		  	$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders/WiMaxType.h \
		  	$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders/WiMaxTypesEx.h \
		  	$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders/WiMaxError.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders/CoexAPI.h \
		  	$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives/wimax_osal_types.h \
		  	$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives/wimax_consts.h \
		  	$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives/wimax_osal_basictypes.h \
		  	$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives/wimax_osal_linux_types.h \
		  	$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives/windows_error.h \
		  	$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives/wimax_osal_error.h \
			$(srcdir)/../Include/wmxSDK_Apdo_3.h \
			$(srcdir)/../Include/wmxSDK_Apdo_Cmn.h \
			$(srcdir)/../Include/wmxSDK_Apdo_Ctrl.h 

libiWmxSdk_la_CFLAGS =  \
			-I "$(srcdir)/../Include" \
		  	-I "$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders" \
			-I "$(srcdir)/../CommonAPI" \
			-I "$(srcdir)/../NDnS" \
			-I "$(srcdir)/../Apdo/" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L5Common" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/WrappersCommon" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/PipeHandler" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Services" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/XmlParser" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/AppSrvInfra" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/Instrumantation/MOCHandler/UDapiL5" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules" \
			-I "$(srcdir)/../../Agents/NDnS/L4_db" \
			-I "$(srcdir)/../../Agents/NDnS/Source" \
			-I "$(srcdir)/../../Agents/NDnS/APDO/" \
			-I "$(srcdir)/../../Agents/Supplicant/Source/ds" \
			-D "_USE_TRACE" -D "BMI_ENDIANNESS_LITTLE" \
			-D "_OS_WIN32SIM" -D "OMADM_CLIENT_SIMULATOR" \
			-D _GNU_SOURCE \
			-D "_LINUX" -D "_WIMAX_SDK_" \
			-D PKG_SYSCONF_DIR="\"${pkgsysconfdir}\""

libiWmxSdk_la_LIBADD =  $(top_builddir)/InfraStack/OSAgnostic/Common/CommonServices/libServices.la \
			$(top_builddir)/InfraStack/OSAgnostic/Product/PipeHandler/libPipeHandler.la \
			$(top_builddir)/InfraStack/OSAgnostic/Common/L4Common/libL4Common.la \
			-lm


#			$(builddir)../CommonAPI/libCommonAPI.la

 
pkgconfigdir = ${libdir}/pkgconfig

pkgconfig_DATA = libiWmxSdk-0.pc

