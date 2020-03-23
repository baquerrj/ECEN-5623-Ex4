#!/bin/bash

SRC=${PWD}
cd ../
DST=${PWD}

echo ${SRC}
echo ${DST}
scp -r ${SRC} jetsonnano:${DST}
cd -
