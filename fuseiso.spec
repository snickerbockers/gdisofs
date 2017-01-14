%define reldate 20070116
Name:           fuseiso
Version:        1.3
Release:        0.%{reldate}%{?dist}
Summary:        Mount ISO filesystem images as a non-root user

Group:          System Environment/Base
License:        GPL
URL:            http://fuse.sourceforge.net/wiki/index.php/FuseIso
Source0:        %{name}-%{reldate}.tar.bz2
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  fuse-devel >= 2.2
BuildRequires:  glib2-devel >= 2.2
Requires:       fuse >= 2.2

%description
Mount ISO filesystem images as a non-root user. Currently supports
plain ISO9660 Level 1 and 2, Rock Ridge, Joliet, zisofs. 
Supported image types: ISO, BIN (single track only), NRG, MDF, IMG (CCD).

%prep
%setup -q -n %{name}-%{reldate}


%build
%configure
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT


%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%doc AUTHORS COPYING INSTALL NEWS README TODO ChangeLog
%{_bindir}/*


%changelog
* Fri Sep 28 2006 Dmitry Morozhnikov <dmiceman@mail.ru> - 1.3-0.20060928
- Update for 2006-09-28 snapshot.

* Fri Sep 25 2006 Dmitry Morozhnikov <dmiceman@mail.ru> - 1.2-0.20060925
- Update for 2006-09-25 snapshot.

* Fri Jul 31 2006 Dmitry Morozhnikov <dmiceman@mail.ru> - 1.1-0.20060731
- Update for 2006-07-31 snapshot.

* Fri Feb 17 2006 Dmitry Morozhnikov <dmiceman@mail.ru> - 1.0-0.20060217
- Update for 2006-02-17 snapshot.

* Sun Jan 15 2006 Richard Dawe <rich@phekda.gotadsl.co.uk> - 1.0-0.20060107
- Update to the 2006-01-07 snapshot.

* Sat Jan 07 2006 Richard Dawe <rich@phekda.gotadsl.co.uk> - 1.0-0.20051029
- Initial packaging.
