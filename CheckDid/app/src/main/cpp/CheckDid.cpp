
#include <jni.h>
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

#ifndef NELEM
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

int jniRegisterNativeMethods(JNIEnv* env, const char* className, const JNINativeMethod* gMethods, int numMethods);

static const JNINativeMethod gMethods[] = {
    {"nativeInitDIDInspector", "()J", (void*)nativeInitDIDInspector},
    {"nativeCheckDID", "(JLjava/lang/String;Ljava/lang/String;)Z", (void*)nativeCheckDID},
    {"nativeCheckSign", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z", (void*)nativeCheckSign},
};

jint register_elastos_checkdid(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "org/elastos/checkdid/DIDInspector",
        gMethods, NELEM(gMethods));
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv * env;
    jclass cls;
    jint result = -1;
    if(vm->GetEnv((void **)&env,JNI_VERSION_1_6) != JNI_OK){
        return JNI_ERR;
    }

    register_elastos_checkdid(env);

    return JNI_VERSION_1_6;
}

int jniRegisterNativeMethods(JNIEnv* env, const char* className,
    const JNINativeMethod* gMethods, int numMethods)
{
    jclass cls = env->FindClass(className);
    env->RegisterNatives(cls, gMethods, numMethods);

    return 0;
}
