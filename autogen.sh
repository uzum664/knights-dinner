#! /bin/sh

# We run just autoreconf, updates all needed
autoreconf -fiv

./configure $*
exit 0
