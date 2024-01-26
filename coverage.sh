#!/bin/bash

cd ./build/Cenpy/tests/CMakeFiles/cenpy-common_tests.dir/src
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/usr/*' --output-file coverage.info
lcov --remove coverage.info '*conan*' --output-file coverage.info
lcov --remove coverage.info '*test*' --output-file coverage.info
lcov --list coverage.info 
#genhtml coverage.info --output-directory out