#! /bin/sh
#
# build.sh
# Copyright (C) 2018 hzshang <hzshang15@gmail.com>
#
# Distributed under terms of the MIT license.
#
if [ -z $1  ]
then
    echo "Usage: $0 file"
    exit 1
fi
./parse $1 -O | ./gotree draw cyjs --with-node-labels 2>/dev/null > abs.html
if [ $? -eq '0' ]
then
    echo "open ./abs.html with your favorite brower!"
fi

