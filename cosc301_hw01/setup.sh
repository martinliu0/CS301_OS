#!/bin/bash

mkdir -p a/b/c
mkdir -p a/b/d
dd if=/dev/zero of=./a/b/x bs=1024 count=55
dd if=/dev/zero of=./a/b/y bs=1024 count=50
dd if=/dev/zero of=./a/b/d/z bs=1024 count=46
dd if=/dev/zero of=./a/.w bs=1024 count=75

