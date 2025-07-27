# Set the system name to Windows, indicating a cross-compilation
set(CMAKE_SYSTEM_NAME Windows)

# Specify the cross-compiler for C and C++
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Set the resource compiler
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# Specify the path to the target environment
# This is where CMake will look for headers and libraries.
# The mingw-w64 installation provides these under /usr/x86_64-w64-mingw32
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# Adjust the find behavior to search for programs in the host's path first
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Adjust the find behavior for libraries and headers to search only in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Add the mingw-w64 include directory to the include path
set(CMAKE_CXX_FLAGS "-I/usr/x86_64-w64-mingw32/include")
