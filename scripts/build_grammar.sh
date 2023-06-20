#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NORMAL_OUTPUT='\033[0m'

BUILD_TYPE="Debug"

# If an argument is provided, use it as the BUILD_TYPE
if [ ! -z "$1" ]; then
    BUILD_TYPE="$1"
fi

# Work at the root directory
# Should have conanfile.py present there.
cd "$(dirname "$0")"
cd ..

# Regenerate the antlr autogenerated files.
cd build/${BUILD_TYPE}
make grammar
cd ../../
conan build . -s build_type=${BUILD_TYPE} -s:h compiler=gcc \
              -s:h compiler.cppstd=gnu20 -s:h compiler.version=12.2\
              --build missing -vquiet
