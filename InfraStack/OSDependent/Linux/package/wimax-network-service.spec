Summary:        Intel WiMAX Network Service
Name:           wimax-network-service
Version:        1.5.2.34
Release:        1
License:        BSD
Group:          Applications/Internet
Vendor:		Tedd (Ho Jeong) An <ho.jeong.an@intel.com>
URL:            http://www.linuxwimax.org/
Source:         %{name}-%{version}-%{release}.tar.gz
#Source1:	wimax-i2400m.tar.gz
# List any extra source needed here...
# e.g. Source2:        extra-source.file
# List patch files if there are any...
# e.g. Patch0:         %{name}-1.2.1-hotfix.patch

BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root

# List any required software to compile this application
BuildRequires: libnl-devel >= 1.1
BuildRequires: wimax-tools-devel
BuildRequires: zlib-devel

# List any required software to run this application
Requires:       libnl >= 1.1


%description
This is the Intel WiMAX Network Service Application include
L4 and connection utility. This application takes care of
handling network scan, discovery, and management. It provides
an API to link against and command line utilities.


%package devel
Summary: Development files for Intel WiMAX Network Service Application
Group: Development/Libraries

Requires: %{name} >= %{version}

%description devel
Header files and libraries needed to link to the WiMAX Network Service
This provides an implementation of the WiMAX Common API as documented
in http://linuxwimax.org/Download.

###############
#   Prepare
###############
%prep
%setup -q -n %{name}-%{version}-%{release}
# Apply patch file if there is any...
# e.g. %patch0 -p1 -b .hotfix
# clean the package
# untar the kernel source

############
#   Build
############
%build
# build wimax_appsrv
./configure --with-linux=/usr --with-libwimaxll=/usr --sysconfdir=/etc --localstatedir=/var --mandir=/usr/share/man --prefix=/usr --enable-instrument

make

##############
#   Install
##############
%install
rm -rf %{buildroot}
make install DESTDIR=%{buildroot}

############
#   Clean
############
%clean
rm -rf %{buildroot}

##############
#   Scripts
##############
%pre
# add any pre-install requirement here
echo ""
echo "Stopping WiMAX Network Service ..."
if [ -f /usr/bin/wimaxd ]; then
	/usr/bin/wimaxd -k
fi
echo ""

%preun
# add any pre-uninstall requirement here
echo ""
echo "Stopping WiMAX Network Service ..."
if [ -f /usr/bin/wimaxd ]; then
	/usr/bin/wimaxd -k
fi
echo ""

%post
# add any post-install requirement here
ldconfig

%postun
# add any post-uninstall requirement here
ldconfig

############
#   Files
############
%files
%defattr(-, root, root)
/etc/udev/rules.d/iwmxsdk.rules
/etc/modprobe.d/i2400m.conf
%config /etc/wimax/config.xml
/usr/bin/wimaxcu
/usr/bin/wimaxd
/usr/bin/wimax_monitor
/usr/lib/libWmxInstrument.la
/usr/lib/libWmxInstrument.so.0
/usr/lib/libWmxInstrument.a
/usr/lib/libWmxInstrument.so
/usr/lib/libWmxInstrument.so.0.0.0
/usr/lib/libiWmxSdk.so
/usr/lib/libiWmxSdk.a
/usr/lib/libiWmxSdk.la
/usr/lib/libiWmxSdk.so.0.0.0
/usr/lib/libiWmxSdk.so.0
/usr/share/wimax
/usr/share/wimax/supplicant_key.pem
/usr/share/wimax/supplicant_cert.pem
%config /usr/share/wimax/dhcp_renew.sh
/usr/share/wimax/cacert.pem
/var/lib/wimax/WiMAX_DB.bin
/var/lib/wimax/WiMAX_Def.bin
/usr/share/wimax/supplicant_cert.pem
/usr/share/wimax/DefaultTracesAndMonitors.xml
/usr/share/wimax/Ver_info.bin
/var/log/wimax
/usr/share/man/man1/wimaxcu.1.gz
/usr/share/man/man1/wimaxd.1.gz

%files devel
%defattr(-, root, root)
/usr/include/wimax
/usr/include/wimax/wmxSDK_Apdo_Ctrl.h
/usr/include/wimax/WiMaxError.h
/usr/include/wimax/wmxSDK_Apdo_Cmn.h
/usr/include/wimax/wmxSDK_Apdo_3.h
/usr/include/wimax/WiMaxAPIEx.h
/usr/include/wimax/WiMaxAPI.h
/usr/include/wimax/CoexAPI.h
/usr/include/wimax/wimax_consts.h
/usr/include/wimax/wimax_osal_basictypes.h
/usr/include/wimax/wimax_osal_linux_types.h
/usr/include/wimax/wimax_osal_types.h
/usr/include/wimax/wimax_osal_error.h
/usr/include/wimax/windows_error.h
/usr/include/wimax/WiMaxType.h
/usr/include/wimax/WiMaxTypesEx.h
/usr/lib/pkgconfig/libiWmxSdk-0.pc


