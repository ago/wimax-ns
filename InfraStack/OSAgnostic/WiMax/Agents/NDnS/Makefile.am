noinst_LTLIBRARIES = libNDnSAgent.la


libNDnSAgent_la_SOURCES = $(srcdir)/Source/FormatConversions.c \
			  $(srcdir)/Source/NDnS_TinyFSM.c \
			$(srcdir)/Source/NDnSAgent.c \
			$(srcdir)/Source/NDnSAgent_CBs.c \
			$(srcdir)/Source/NDnSAgent_Ctrl.c \
			$(srcdir)/Source/NDnSAgent_Internals.c \
			$(srcdir)/Source/NDnSAgent_Utils.c \
			$(srcdir)/Source/NDnSAgent_L4P.c \
			$(srcdir)/Source/NDnSAgent_Monitor.c \
			$(srcdir)/Source/NDnS_Coex.c \
			$(srcdir)/Source/NDnSAgent_NSPsList.c \
			$(srcdir)/APDO/NDnSAgent_APDO_CBs.c \
			$(srcdir)/APDO/NDnSAgent_APDO.c \
			$(srcdir)/L4Publisher/NDnS_L4Publisher.c \
			$(srcdir)/L4_db/NDnSAgent_DB.c \
			$(srcdir)/L4_db/NDnSAgent_DB_Common.c \
			$(srcdir)/L4_db/NDnSAgent_DB_Restore.c \
			$(srcdir)/L4_db/NDnSAgent_DB_Save.c \
			$(srcdir)/L4_db/NDnSAgent_DB_Update.c \
			$(srcdir)/L4Scanner/NDnS_L4Scanner.c \
			$(srcdir)/L4Scanner/NDnSAgent_L4S_CBs.c \
			$(srcdir)/L4Scanner/NDnS_L4Scanner.h \
			$(srcdir)/L4_db/NDnSAgent_DB_if.h \
			$(srcdir)/Source/ver_info.h \
			$(srcdir)/Source/NDnSAgent_Monitor.h \
			$(srcdir)/Source/NDnS_Coex.h \
			$(srcdir)/L4Publisher/NDnS_L4Publisher.h \
			$(srcdir)/Source/FormatConversions.h \
			$(srcdir)/Source/NDnSAgent_DB.h \
			$(srcdir)/Source/NDnSAgent.h \
			$(srcdir)/Source/NDnSAgent_Internals.h \
			$(srcdir)/Source/NDnSAgent_L4P.h \
			$(srcdir)/Source/NDnSAgent_Utils.h \
			$(srcdir)/Source/NDnS_TinyFSM.h \
			$(srcdir)/APDO/NDnSAgent_APDO.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/L4DmMonitorGroups.h \
			$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated/BM_Chiplab_Common.h \
			$(srcdir)/../../Wrappers/Apdo/AES.c \
			$(srcdir)/../../Wrappers/Apdo/AES_CCM.c \
			$(srcdir)/../../Wrappers/Apdo/wmxSDK_Apdo_Internals.c \
			$(srcdir)/../../Wrappers/Apdo/wmxSDK_Apdo_L5.c \
			$(srcdir)/../../Wrappers/Apdo/wmxSDK_Apdo_Utils.c \
			$(srcdir)/../../Wrappers/Apdo/wmxSDK_Apdo_Impl.c \
			$(srcdir)/../../Wrappers/Miscellaneous/wmxSDK_Msc_Impl.c \
			$(srcdir)/../../Wrappers/Apdo/wmxSDK_Apdo_IndHandler.c \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Nds_1.c \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Nds_2.c \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Nds_CtrlAgent.c \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Nds_IndHandler.c \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Nds_Internals.c \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Nds_L5.c \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Nds_Utils.c \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Coex_1.c \
			$(srcdir)/../../Wrappers/Apdo/AES_CCM.h \
			$(srcdir)/../../Wrappers/Apdo/AES.h \
			$(srcdir)/../../Wrappers/Apdo/AES_private.h \
			$(srcdir)/../../Wrappers/Apdo/bootstrap.h \
			$(srcdir)/../../Wrappers/Apdo/wmxSDK_Apdo_IndHandler.h \
			$(srcdir)/../../Wrappers/Apdo/wmxSDK_Apdo_Internals.h \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Nds_IndHandler.h \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Nds_Internals.h \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Nds_InternalStructs.h \
			$(srcdir)/../../Wrappers/NDnS/wmxSDK_Nds_Utils.h \
			$(srcdir)/../../Wrappers/Include/wmxSDK_Coex_1.h

# TODO:: Need to bring some functionality from these files
#	$(srcdir)/APDO/watcher.c 
#			$(srcdir)/APDO/watcher.h 


libNDnSAgent_la_CFLAGS = \
			-I "$(srcdir)/Source/" \
			-I "$(srcdir)/../Wrappers/NDnS" \
			-I "$(srcdir)/../Wrappers/Include" \
			-I "$(srcdir)/../Wrappers/Apdo" \
			-I "$(srcdir)/./L4_db/" \
			-I "$(srcdir)/./L4Publisher/" \
			-I "$(srcdir)/./APDO/" \
			-I "$(srcdir)/./L4Scanner/" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/L4Generated" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Primitives" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/OSAL/Services" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/OSInterface/InfraStackModules" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/CommonServices/XmlParser" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L5Common" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/WrappersCommon" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/PipeHandler" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/AppSrvInfra" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/Instrumantation/DnDAgent" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Product/Instrumantation/MOCHandler/UDapiL5" \
			-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Primitives" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/OSAL/Services" \
			-I "$(top_srcdir)/InfraStack/OSDependent/Linux/InfraStackModules/CommonAPIHeaders" \
			-I "$(srcdir)/../../Wrappers/Include" \
			-I "$(srcdir)/../../Wrappers/NDnS" \
			-I "$(srcdir)/../../Wrappers/Apdo" \
			-I "$(srcdir)/../../Wrappers/Miscellaneous/" \
			-D _GNU_SOURCE \
			-D PKG_DATA_DIR="\"${pkgdatadir}\"" \
			  -D  "BMI_MACHINE_ENDIANNESS_LITTLE" -D "_LINUX"



