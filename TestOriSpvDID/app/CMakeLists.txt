# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

include_directories(src/main/cpp/did/include)
include_directories(src/main/cpp/wallet/include)
include_directories(src/main/cpp/DIDChecker)
link_directories(src/main/cpp/did/lib)
link_directories(src/main/cpp/wallet/lib)

add_library(testspvdid SHARED
    src/main/cpp/ElaSpv.cpp
    src/main/cpp/ElaMasterWalletManager.cpp
    src/main/cpp/ElaMasterWallet.cpp
    src/main/cpp/ElaSubWallet.cpp
    src/main/cpp/ElaMainchainSubWallet.cpp
    src/main/cpp/ElaSidechainSubWallet.cpp
    src/main/cpp/ElaIdChainSubWallet.cpp
    src/main/cpp/ElaIdManagerFactory.cpp
    src/main/cpp/ElaDidManager.cpp
    src/main/cpp/ElaDid.cpp
    src/main/cpp/ElaUtils.cpp

    #did checker codes
    src/main/cpp/CheckDid.cpp
    src/main/cpp/DIDChecker/Utils.cpp
    src/main/cpp/DIDChecker/Key.cpp
    src/main/cpp/DIDChecker/ByteStream.cpp
    src/main/cpp/DIDChecker/BTCKey.cpp
    src/main/cpp/DIDChecker/BTCBase58.cpp
    src/main/cpp/DIDChecker/BRInt.c
    src/main/cpp/DIDChecker/BRCrypto.c
    src/main/cpp/DIDChecker/BRAddress.c
)

target_link_libraries(testspvdid
    spvsdk
    idchain
    log
)