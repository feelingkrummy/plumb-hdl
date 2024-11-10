#!/bin/sh

SRC_FILES="../src/common/str.c \
	../src/common/utf8.c \
	../src/plumb-elab/lex.c \
	../src/plumb-elab/tokens.c"

clang -lcriterion -I../include $SRC_FILES 01-utf8.c 02-plumb-elab.c -o test
