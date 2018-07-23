// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ElaUtils.h"
#include "IMasterWallet.h"
#include "nlohmann/json.hpp"

using namespace Elastos::ElaWallet;

extern const char* ToStringFromJson(const nlohmann::json& jsonValue);

//"(J)Ljava/lang/String;"
static jstring JNICALL nativeGetId(JNIEnv *env, jobject clazz, jlong jMasterProxy)
{
    IMasterWallet* masterWallet = (IMasterWallet*)jMasterProxy;
    std::string key = masterWallet->GetId();
    return env->NewStringUTF(key.c_str());
}

//"(J)[J"
static jlongArray JNICALL nativeGetAllSubWallets(JNIEnv *env, jobject clazz, jlong jMasterProxy)
{
    IMasterWallet* masterWallet = (IMasterWallet*)jMasterProxy;
    std::vector<ISubWallet *> array = masterWallet->GetAllSubWallets();

    const int length = array.size();
    jlong* proxies = new jlong[length];
    for (int i = 0; i < length; ++i) {
        proxies[i] = (jlong)array[i];
    }

    jlongArray jarray = env->NewLongArray(length);
    env->SetLongArrayRegion(jarray, 0, length, proxies);
    delete[] proxies;
    return jarray;
}

//"(JLjava/lang/String;Ljava/lang/String;ZJ)J"
static jlong JNICALL nativeCreateSubWallet(JNIEnv *env, jobject clazz, jlong jMasterProxy, jstring jChainID,
        jstring jpayPassword, jboolean jSingleAddress, jlong jFeePerKb)
{
    const char* chainID = env->GetStringUTFChars(jChainID, NULL);
    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);

    IMasterWallet* masterWallet = (IMasterWallet*)jMasterProxy;
    ISubWallet* subWallet = NULL;
    try {
        subWallet = masterWallet->CreateSubWallet(chainID, payPassword, jSingleAddress, jFeePerKb);
    }
    catch (std::invalid_argument& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::logic_error& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::runtime_error& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::exception& e) {
        ThrowWalletException(env, e.what());
    }

    LOGI("?????????????? subWallet = %p", subWallet);

    env->ReleaseStringUTFChars(jChainID, chainID);
    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    return (jlong)subWallet;
}

//"(JLjava/lang/String;Ljava/lang/String;ZIJ)J"
static jlong JNICALL nativeRecoverSubWallet(JNIEnv *env, jobject clazz, jlong jMasterProxy, jstring jChainID,
        jstring jpayPassword, jboolean jSingleAddress, jint limitGap, jlong jFeePerKb)
{
    const char* chainID = env->GetStringUTFChars(jChainID, NULL);
    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);

    IMasterWallet* masterWallet = (IMasterWallet*)jMasterProxy;
    ISubWallet* subWallet = NULL;
    try {
        subWallet = masterWallet->RecoverSubWallet(chainID, payPassword, jSingleAddress, limitGap, jFeePerKb);
    }
    catch (std::invalid_argument& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::logic_error& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::runtime_error& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::exception& e) {
        ThrowWalletException(env, e.what());
    }

    env->ReleaseStringUTFChars(jChainID, chainID);
    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    return (jlong)subWallet;
}

//"(JJ)V"
static void JNICALL nativeDestroyWallet(JNIEnv *env, jobject clazz, jlong jMasterProxy, jlong jsubWalletProxy)
{
    IMasterWallet* masterWallet = (IMasterWallet*)jMasterProxy;
    ISubWallet* subWallet = (ISubWallet*)jsubWalletProxy;
    masterWallet->DestroyWallet(subWallet);
}

//"(J)Ljava/lang/String;"
static jstring JNICALL nativeGetPublicKey(JNIEnv *env, jobject clazz, jlong jMasterProxy)
{
    IMasterWallet* masterWallet = (IMasterWallet*)jMasterProxy;
    std::string key = masterWallet->GetPublicKey();
    return env->NewStringUTF(key.c_str());
}

//"(JLjava/lang/String;Ljava/lang/String;)Ljava/lang/String;"
static jstring JNICALL nativeSign(JNIEnv *env, jobject clazz, jlong jMasterProxy, jstring jmessage, jstring jpayPassword)
{
    const char* message = env->GetStringUTFChars(jmessage, NULL);
    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);

    IMasterWallet* masterWallet = (IMasterWallet*)jMasterProxy;
    std::string result;
    try {
        result = masterWallet->Sign(message, payPassword);
    }
    catch (std::invalid_argument& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::logic_error& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::runtime_error& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::exception& e) {
        ThrowWalletException(env, e.what());
    }

    env->ReleaseStringUTFChars(jmessage, message);
    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    return env->NewStringUTF(result.c_str());
}

//"(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;"
static /*nlohmann::json*/jstring JNICALL nativeCheckSign(JNIEnv *env, jobject clazz, jlong jMasterProxy, jstring jaddress, jstring jmessage,
        jstring jsignature)
{
    const char* address = env->GetStringUTFChars(jaddress, NULL);
    const char* message = env->GetStringUTFChars(jmessage, NULL);
    const char* signature = env->GetStringUTFChars(jsignature, NULL);

    IMasterWallet* masterWallet = (IMasterWallet*)jMasterProxy;
    nlohmann::json jsonVal;
    try {
        jsonVal = masterWallet->CheckSign(address, message, signature);
    }
    catch (std::invalid_argument& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::logic_error& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::runtime_error& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::exception& e) {
        ThrowWalletException(env, e.what());
    }

    env->ReleaseStringUTFChars(jaddress, address);
    env->ReleaseStringUTFChars(jmessage, message);
    env->ReleaseStringUTFChars(jsignature, signature);

    return env->NewStringUTF(ToStringFromJson(jsonVal));
}

//"(JLjava/lang/String;)Z"
static jboolean JNICALL nativeIsAddressValid(JNIEnv *env, jobject clazz, jlong jMasterProxy, jstring jaddress)
{
    const char* address = env->GetStringUTFChars(jaddress, NULL);

    IMasterWallet* masterWallet = (IMasterWallet*)jMasterProxy;
    bool valid = masterWallet->IsAddressValid(address);

    env->ReleaseStringUTFChars(jaddress, address);

    return (jboolean)valid;
}

//"(J)[Ljava/lang/String;"
static jobjectArray JNICALL nativeGetSupportedChains(JNIEnv *env, jobject clazz, jlong jMasterProxy)
{
    IMasterWallet* masterWallet = (IMasterWallet*)jMasterProxy;
    std::vector<std::string> chains = masterWallet->GetSupportedChains();

    const int length = chains.size();
    if (length < 1) {
        return NULL;
    }

    jclass objClass = env->FindClass("java/lang/String");
    jobjectArray objArray = env->NewObjectArray(length, objClass, 0);
    for (int i = 0; i < length; ++i) {
        env->SetObjectArrayElement(objArray, i, env->NewStringUTF(chains[i].c_str()));
    }

    return objArray;
}

//"(JLjava/lang/String;Ljava/lang/String;)V"
static void JNICALL nativeChangePassword(JNIEnv *env, jobject clazz, jlong jMasterProxy, jstring joldPassword, jstring jnewPassword)
{
    const char* oldPassword = env->GetStringUTFChars(joldPassword, NULL);
    const char* newPassword = env->GetStringUTFChars(jnewPassword, NULL);

    IMasterWallet* masterWallet = (IMasterWallet*)jMasterProxy;

    try {
        masterWallet->ChangePassword(oldPassword, newPassword);
    }
    catch (std::invalid_argument& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::logic_error& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::runtime_error& e) {
        ThrowWalletException(env, e.what());
    }
    catch (std::exception& e) {
        ThrowWalletException(env, e.what());
    }

    env->ReleaseStringUTFChars(joldPassword, oldPassword);
    env->ReleaseStringUTFChars(jnewPassword, newPassword);
}

static const JNINativeMethod gMethods[] = {
    {"nativeGetId", "(J)Ljava/lang/String;", (void*)nativeGetId},
    {"nativeGetAllSubWallets", "(J)[J", (void*)nativeGetAllSubWallets},
    {"nativeCreateSubWallet","(JLjava/lang/String;Ljava/lang/String;ZJ)J", (void*)nativeCreateSubWallet},
    {"nativeRecoverSubWallet", "(JLjava/lang/String;Ljava/lang/String;ZIJ)J", (void*)nativeRecoverSubWallet},
    {"nativeDestroyWallet", "(JJ)V", (void*)nativeDestroyWallet},
    {"nativeGetPublicKey", "(J)Ljava/lang/String;", (void*)nativeGetPublicKey},
    {"nativeSign", "(JLjava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void*)nativeSign},
    {"nativeCheckSign", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void*)nativeCheckSign},
    {"nativeIsAddressValid", "(JLjava/lang/String;)Z", (void*)nativeIsAddressValid},
    {"nativeGetSupportedChains", "(J)[Ljava/lang/String;", (void*)nativeGetSupportedChains},
    {"nativeChangePassword", "(JLjava/lang/String;Ljava/lang/String;)V", (void*)nativeChangePassword},
};

jint register_elastos_spv_IMasterWallet(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "org/elastos/testorispvdid/IMasterWallet",
        gMethods, NELEM(gMethods));
}
