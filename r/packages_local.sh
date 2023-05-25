#!/bin/bash

cd /tmp

# stringi
wget https://github.com/gagolews/stringi/archive/master.zip -O stringi.zip
unzip stringi.zip
sed -i '/\/icu..\/data/d' stringi-master/.Rbuildignore
R CMD build stringi-master
