// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ElaUtils.h"
#include "IdManagerFactory.h"

using namespace Elastos::ElaWallet;
using namespace Elastos::DID;

//"(J)J"
static jlong JNICALL nativeCreateIdManager(JNIEnv *env, jobject clazz, jlong jmasterWalletProxy, jstring jrootPath)
{
    const char* rootPath = env->GetStringUTFChars(jrootPath, NULL);
    IMasterWallet* masterWallet = (IMasterWallet*)jmasterWalletProxy;
    IdManagerFactory idManagerFactory;
    IDIDManager* idManager = idManagerFactory.CreateIdManager(masterWallet, rootPath);
    env->ReleaseStringUTFChars(jrootPath, rootPath);
    return (jlong)idManager;
}

static const JNINativeMethod gMethods[] = {
    {"nativeCreateIdManager", "(JLjava/lang/String;)J", (void*)nativeCreateIdManager},
};

jint register_elastos_spv_IdManagerFactory(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "org/elastos/testorispvdid/IdManagerFactory",
        gMethods, NELEM(gMethods));
}
