cmake_minimum_required(VERSION 3.10)

project(RewasdCloneCore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define an executable for the Core Service
add_executable(CoreService WIN32 src/CoreService/Main.cpp
                                 src/CoreService/VirtualController.cpp
                                 src/CoreService/DeviceEnumerator.cpp
                                 src/CoreService/RawInputHandler.cpp
                                 src/CoreService/MappingEngine.cpp)

# Specify include directories
target_include_directories(CoreService PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

# Link against User32 for windowing and message functions
target_link_libraries(CoreService PRIVATE User32)

# In a real scenario, you would link ViGEmBus and SetupAPI here:
# find_package(ViGEmClient REQUIRED)
# target_link_libraries(CoreService PRIVATE ViGEmClient::ViGEmClient Setupapi)
# Note: SetupAPI is often linked via pragma comment, but this is the explicit way.

# Specify include directories
target_include_directories(CoreService PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

# In a real scenario, you would link ViGEmBus here:
# find_package(ViGEmClient REQUIRED)
# target_link_libraries(CoreService PRIVATE ViGEmClient::ViGEmClient)

# For now, we don't have the actual library, so this is commented out.
# If you have the ViGEmClient.lib and headers, you would configure
# CMake to find them or add them directly.

# Example of adding a library if it was located in a 'lib' folder:
# link_directories(${PROJECT_SOURCE_DIR}/lib)
# And then link it:
# target_link_libraries(CoreService PRIVATE ViGEmClientStatic) # Or whatever the .lib is named

install(TARGETS CoreService DESTINATION bin)
