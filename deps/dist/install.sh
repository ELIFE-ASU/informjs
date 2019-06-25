#!/usr/bin/env bash

function usage {
    echo "Usage: ${0##*/} [--prefix=<prefix>]"
    exit 1
}

if [[ $# -eq 0 ]]; then
    prefix=/usr/local
elif [[ $# -eq 1 ]]; then
    prefix=${1#"--prefix="}
    if [[ $prefix == $1 ]]; then
        prefix=${1#"--PREFIX="}
        if [[ $prefix == $1 ]]; then
            usage
        fi
    fi
else
    usage
fi

mkdir -p $prefix
cp -R include $prefix
cp -R lib $prefix
