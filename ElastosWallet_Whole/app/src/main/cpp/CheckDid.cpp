
#include "ElaUtils.h"
#include "Elastos.DIDInspector.h"

static jlong JNICALL nativeInitDIDInspector(JNIEnv *env, jobject clazz)
{
    IDIDInspector* ididInspector = NULL;
    CDIDInspector::New(&ididInspector);

    return (jlong)ididInspector;
}

static jboolean JNICALL nativeCheckDID(JNIEnv *env, jobject clazz, jlong proxy, jstring jpublicKey, jstring jdid)
{
    const char* publicKey = env->GetStringUTFChars(jpublicKey, NULL);
    const char* did = env->GetStringUTFChars(jdid, NULL);
    IDIDInspector* ididInspector = (IDIDInspector*)proxy;

    Boolean matched = FALSE;
    ididInspector->CheckDID(String(publicKey), String(did), &matched);
    return (jboolean)matched;
}

static jboolean JNICALL nativeCheckSign(JNIEnv *env, jobject clazz, jlong proxy, jstring jpublicKey, jstring jmessage, jstring jsignature)
{
    const char* publicKey = env->GetStringUTFChars(jpublicKey, NULL);
    const char* message = env->GetStringUTFChars(jmessage, NULL);
    const char* signature = env->GetStringUTFChars(jsignature, NULL);

    IDIDInspector* ididInspector = (IDIDInspector*)proxy;

    Boolean matched = FALSE;
    ididInspector->CheckSign(String(publicKey), String(message), String(signature), &matched);

    env->ReleaseStringUTFChars(jpublicKey, publicKey);
    env->ReleaseStringUTFChars(jmessage, message);
    env->ReleaseStringUTFChars(jsignature, signature);
    return (jboolean)matched;
}

static const JNINativeMethod gMethods[] = {
    {"nativeInitDIDInspector", "()J", (void*)nativeInitDIDInspector},
    {"nativeCheckDID", "(JLjava/lang/String;Ljava/lang/String;)Z", (void*)nativeCheckDID},
    {"nativeCheckSign", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", (void*)nativeCheckSign},
};

jint register_elastos_checkdid(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "org/elastos/elastoswallet/DIDInspector",
                                    gMethods, NELEM(gMethods));
}
