%define ver 3.4.4
%define rel 1

Name:           qrencode
Version:        %{ver}
Release:        %{rel}%{?dist}
Summary:        Libqrencode is a library for encoding data in a QR Code symbol, a kind of 2D symbology that can be scanned by handy terminals such as a mobile phone with CCD. The capacity of QR Code is up to 7000 digits or 4000 characters, and has high robustness.

Group:          System Environment/Libraries
License:        LGPLv2+
URL:            http://fukuchi.org/works/qrencode/
Source0:        http://fukuchi.org/works/qrencode/%{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

%description
Libqrencode supports QR Code model 2, described in JIS (Japanese Industrial Standards) X0510:2004 or ISO/IEC 18004. Currently the following features are not supported: ECI and FNC1 mode, Micro QR Code, QR Code model 1.

%package        devel
Summary:        Development files for libqrencode
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}

%description    devel
Libqrencode supports QR Code model 2, described in JIS (Japanese Industrial Standards) X0510:2004 or ISO/IEC 18004. Currently the following features are not supported: ECI and FNC1 mode, Micro QR Code, QR Code model 1.

This package contains development files for libqrencode.

%prep
%setup -q


%build
%configure --without-tests
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
rm -f $RPM_BUILD_ROOT%{_libdir}/*.la


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%doc COPYING TODO ChangeLog NEWS README
%{_libdir}/libqrencode.so.*
%{_bindir}/qrencode
%{_mandir}/man1/qrencode.1.gz

%files devel
%defattr(-,root,root,-)
%{_includedir}/qrencode.h
%{_libdir}/libqrencode.so
%{_libdir}/pkgconfig/libqrencode.pc

%changelog
* Sat Oct 09 2010 Kentaro Fukuchi <kentaro at fukuchi.org> 3.9.0-1
- URL and Source0 have been updated.
* Fri May 01 2008 Kentaro Fukuchi <fukuchi at megaui.net> 3.0.1-1
- The man page has been packaged correctly.
* Tue May 15 2007 Kentaro Fukuchi <fukuchi at megaui.net> 1.0.2-2
- Summary has been synchronized to README.
* Thu May 09 2007 Katsumi Saito <katsumi at jo1upk.ymt.prug.or.jp> 1.0.2-1
- Initial RPM release
