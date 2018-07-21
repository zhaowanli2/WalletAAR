# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

include_directories(src/main/cpp/openssl)
link_directories(src/main/cpp/openssl/libs)
add_library(checkdid SHARED
    src/main/cpp/CheckDid.cpp
    src/main/cpp/Utils.cpp
    src/main/cpp/Key.cpp
    src/main/cpp/ByteStream.cpp
    src/main/cpp/BTCKey.cpp
    src/main/cpp/BTCBase58.cpp
    src/main/cpp/BRInt.c
    src/main/cpp/BRCrypto.c
    src/main/cpp/BRAddress.c
)

target_link_libraries(checkdid crypto ssl)