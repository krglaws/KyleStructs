#!/usr/bin/env bash
clang-format -i include/kylestructs.h include/kylestructs/*.h src/*.c tests/*.c
exit $?
