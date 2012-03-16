#!/bin/bash
rm ./debian/usr/bin/*
cp ../egcs-1.1.2/gcc/cc1 ./debian/usr/bin/cc1-jvm
cp ../egcs-1.1.2/gcc/cpp ./debian/usr/bin/cpp-jvm
dpkg-deb --build debian 
mv debian.deb egcs-jvm-1.1.2-1_amd64.deb
