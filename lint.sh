#!/usr/bin/env bash
clang-tidy ./include/kylestructs.h ./include/kylestructs/*.h src/*.c tests/*.c -- -I./include
exit $?
