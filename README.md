# libjaylink

libjaylink is a shared library written in C to access SEGGER J-Link and
compatible devices.


## Requirements

libjaylink requires the following packages:

 - GCC (>= 4.0) or Clang
 - Make
 - pkg-config >= 0.23
 - libusb >= 1.0.9 (optional)
 - Doxygen (optional, only required for API documentation)

If you're building libjaylink from Git, the following packages are additionally
required:

 - Git
 - Libtool
 - Autoconf >= 2.64
 - Automake >= 1.9


## Building and installing

In order to get and build the latest Git version of libjaylink, run the
following commands:

    $ git clone https://gitlab.zapb.de/libjaylink/libjaylink.git
    $ cd libjaylink
    $ ./autogen.sh
    $ ./configure
    $ make

After `make` finishes without any errors, use the following command to install
libjaylink:

    $ make install


## Portability

libjaylink supports the following operating systems:

 - GNU/Linux
 - FreeBSD
 - OpenBSD
 - NetBSD
 - Microsoft Windows
   - Cygwin, MinGW and MSYS2
 - OS X


## Support

If you appreciate the project, feel free to donate on Liberapay:

[![Liberapay donation link](https://liberapay.com/assets/widgets/donate.svg)](https://liberapay.com/zapb/donate)


## Copyright and license

libjaylink is licensed under the terms of the GNU General Public License (GPL),
version 2 or later. See COPYING file for details.

## Website

<https://gitlab.zapb.de/libjaylink/libjaylink.git>
