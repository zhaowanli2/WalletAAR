# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

include_directories(src/main/cpp/elastos/include)
link_directories(src/main/cpp/elastos/libs)
add_library(didInspector SHARED
    src/main/cpp/CheckDid.cpp
)

target_link_libraries(didInspector
    Elastos.Runtime
    Elastos.Runtime_static
    Elastos.CoreLibrary
    Elastos.DIDInspector
    crypto
)