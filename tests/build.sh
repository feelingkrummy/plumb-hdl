#!/bin/sh

SRC_FILES="../src/common/str.c \
    ../src/common/utf8.c \
    ../src/plumb_elab/lex.c \
    ../src/plumb_elab/tokens.c"

clang -lcriterion -I../src $SRC_FILES 01-utf8.c 02-plumb_elab.c -o test
