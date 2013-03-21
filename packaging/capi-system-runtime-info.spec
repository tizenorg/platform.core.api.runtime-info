Name:       capi-system-runtime-info
Summary:    A Runtime Information library in Tizen Native API
Version:    0.0.3
Release:    0
Group:      System/Libraries
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(capi-base-common)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description


%package devel
Summary:  A Runtime Information library in Tizen Native API (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}
Requires:  pkgconfig(capi-base-common)

%description devel



%prep
%setup -q


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`  
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}

mkdir -p %{buildroot}/usr/share/license
cp -f LICENSE.APLv2 %{buildroot}/usr/share/license/%{name}

%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%{_libdir}/lib*.so.*
/usr/share/license/%{name}
%manifest runtime-info.manifest

%files devel
%{_includedir}/system/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/lib*.so


