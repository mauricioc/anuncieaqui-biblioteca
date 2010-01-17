#!/bin/sh
md5sum $1 | cut -d' ' -f1 > $2
