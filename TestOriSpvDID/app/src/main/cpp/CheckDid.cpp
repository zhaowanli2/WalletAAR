
#include "ElaUtils.h"
#include <string>
#include "Key.h"
#include "Utils.h"

using namespace Elastos::ElaWallet;

// static jlong JNICALL nativeInitDIDInspector(JNIEnv *env, jobject clazz)
// {
//     IDIDInspector* ididInspector = NULL;
//     CDIDInspector::New(&ididInspector);

//     return (jlong)ididInspector;
// }

static jboolean JNICALL nativeCheckDID(JNIEnv *env, jobject clazz, jlong proxy, jstring jpublicKey, jstring jdid)
{
    const char* publicKeyStr = env->GetStringUTFChars(jpublicKey, NULL);
    const char* did = env->GetStringUTFChars(jdid, NULL);
    CMBlock pubKey = Utils::decodeHex(publicKeyStr);
    BRKey key;
    memcpy(key.pubKey, pubKey, pubKey.GetSize());
    key.compressed = (pubKey.GetSize() <= 33);
    std::string nativeDid = Key::publicKeyToIdAddress(&key);

    jboolean matched = strcmp(nativeDid.c_str(), did) == 0;

    LOGD("FUNC=[%s]====Line=[%d], publicKeyStr=[%s], did=[%s], nativeDid=[%s]", __FUNCTION__, __LINE__ , publicKeyStr, did, nativeDid.c_str());

    env->ReleaseStringUTFChars(jpublicKey, publicKeyStr);
    env->ReleaseStringUTFChars(jdid, did);

    return (jboolean)matched;
}

static jboolean JNICALL nativeCheckSign(JNIEnv *env, jobject clazz, jlong proxy, jstring jpublicKey, jstring jmessage, jstring jsignature)
{
    const char* publicKey = env->GetStringUTFChars(jpublicKey, NULL);
    const char* message = env->GetStringUTFChars(jmessage, NULL);
    const char* signature = env->GetStringUTFChars(jsignature, NULL);

    jboolean matched = Key::verifyByPublicKey(publicKey, message, signature);

    env->ReleaseStringUTFChars(jpublicKey, publicKey);
    env->ReleaseStringUTFChars(jmessage, message);
    env->ReleaseStringUTFChars(jsignature, signature);
    return (jboolean)matched;
}

static const JNINativeMethod gMethods[] = {
    // {"nativeInitDIDInspector", "()J", (void*)nativeInitDIDInspector},
    {"nativeCheckDID", "(JLjava/lang/String;Ljava/lang/String;)Z", (void*)nativeCheckDID},
    {"nativeCheckSign", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", (void*)nativeCheckSign},
};

jint register_elastos_checkdid(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "org/elastos/testorispvdid/DIDInspector",
                                    gMethods, NELEM(gMethods));
}
