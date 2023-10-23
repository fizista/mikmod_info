A simple program that displays the file information provided by the libmikmod library.

Required libraries (ubuntu):

apt install libmikmod3-dev

Code compilation:

make

Code instalation:

make install

or

checkinstall --install=no --fstrans=yes --requires libmikmod3 --pkgname mikmod-info --pkgversion 0.1 --pkgrelease 1 --pkglicense MIT --maintainer fizista+mikmod@gmail.com --nodoc
apt install mikmod-info_0.1-1_amd64.deb

How to use:

mikmod_info <some music file>
