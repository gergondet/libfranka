#!/bin/sh

set -e

rm -rf build-lint
mkdir build-lint
cd build-lint
cmake -DBUILD_COVERAGE=OFF -DBUILD_DOCUMENTATION=OFF -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF ..
cmake --build . --target check-format
cmake --build . --target check-tidy
