
#include <jni.h>
#include "Elastos.DIDInspector.h"
#include <string>

#include <android/log.h>
#define TAG "Elastos_TEST_Wallet"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)

String ToElString(const char* value) {
    return String (value);
}

static jstring JNICALL nativeTestString(JNIEnv *env, jobject clazz)
{
    char* value="{\"Attributes\":[{\"Data\":\"363736303839393031\",\"Usage\":0}],\"BlockHeight\":2147483647,\"Fee\":10000,\"Inputs\":[{\"Address\":\"EN7ysAQmCvX9unk4TXpSxYHzNNQHk4uvrk\",\"Amount\":10000000000,\"Index\":0,\"Script\":\"76a914367b725441a732fd2ecdbc7370d4c2c2ebe851f188ac\",\"Sequence\":4294967295,\"Signature\":\"\",\"TxHash\":\"f3391b7d4177acd4de8b6013915075a8146c0a3c6fef654fdad39e4e72f3ceed\"},{\"Address\":\"EJP3Q1bVpKHQLMD6TCUhvnHTmyEtpzErDo\",\"Amount\":5899940000,\"Index\":1,\"Script\":\"76a9140d742192664bae20b1a3a52a5339d878ecac419888ac\",\"Sequence\":4294967295,\"Signature\":\"\",\"TxHash\":\"f3391b7d4177acd4de8b6013915075a8146c0a3c6fef654fdad39e4e72f3ceed\"},{\"Address\":\"EaL6tNKgwrsisUYRAJvwTTAi1toAoG1i6k\",\"Amount\":10100000000,\"Index\":0,\"Script\":\"76a914bc67cee622c370a7cb432925b24408365a238b6988ac\",\"Sequence\":4294967295,\"Signature\":\"\",\"TxHash\":\"77eab23ec2d924bc0bde7a37dd4030265d0d7352fa5e405f3885133536124ec6\"},{\"Address\":\"EWUP61Bf7QoH8gcyCQWS6LhrKHYua42KYF\",\"Amount\":4699920000,\"Index\":1,\"Script\":\"76a914921828067a2e99dcc235b7dbf94c88a73b3879b788ac\",\"Sequence\":4294967295,\"Signature\":\"\",\"TxHash\":\"77eab23ec2d924bc0bde7a37dd4030265d0d7352fa5e405f3885133536124ec6\"}],\"IsRegistered\":false,\"LockTime\":0,\"Outputs\":[{\"Address\":\"ERuxy5fj2s1UzKVPfaXR9jPa49ZNefo8NH\",\"Amount\":26000000000,\"AssetId\":\"b037db964a231458d2d6ffd5ea18944c4f90e63d547c5d3b9874df66a4ead0a3\",\"OutputLock\":0,\"ProgramHash\":\"21601635678e687c9592c4b530f77fbef2723aef35\",\"Script\":\"76a914601635678e687c9592c4b530f77fbef2723aef3588ac\",\"ScriptLen\":25,\"SignType\":172},{\"Address\":\"EUTv24yo3CaSMgL9yqXHnyNMKu7kyeVwYu\",\"Amount\":4699850000,\"AssetId\":\"b037db964a231458d2d6ffd5ea18944c4f90e63d547c5d3b9874df66a4ead0a3\",\"OutputLock\":0,\"ProgramHash\":\"217c114f47c0d1f6f2c61e09c65987c121bead0d78\",\"Script\":\"76a9147c114f47c0d1f6f2c61e09c65987c121bead0d7888ac\",\"ScriptLen\":25,\"SignType\":172}],\"PayLoad\":null,\"PayloadVersion\":0,\"Programs\":[],\"Remark\":\"\",\"Timestamp\":0,\"TxHash\":\"4cc8178637cfba50896487b0692cd05ee6b28454e148fae759c56cfdff261d30\",\"Type\":2,\"Version\":1}";
    String result(value);

    const Int32 len = strlen(value);
    if (len > 800) {
        std::string str(value);
        Int32 tmpLen = 0;
        Int32 pos = 0;
        while(tmpLen >= 0) {
            LOGD("1===FUNC=[%s]======LINE=[%d], len=[%d], value[%d]=[%s]", __FUNCTION__, __LINE__,
                 len, pos, str.substr(pos * 800, 800).c_str());
            pos++;
            tmpLen = len - pos * 800;
        }

        tmpLen = 0;
        pos = 0;
        while(tmpLen >= 0) {
            LOGD("2===FUNC=[%s]======LINE=[%d], len=[%d], value[%d]=[%s]", __FUNCTION__, __LINE__,
                 len, pos, result.Substring(pos * 800, pos * 800 + 800).string());
            pos++;
            tmpLen = len - pos * 800;
        }
    }

    LOGD("FUNC=[%s]============================================================================LINE=[%d], len=[%d], strValue=[%s]"
                         , __FUNCTION__, __LINE__, result.GetLength(), result.string());
    String s = ToElString(value);
    LOGD("FUNC=[%s]============================================================================LINE=[%d], len=[%d], strValue=[%s]"
                         , __FUNCTION__, __LINE__, s.GetLength(), s.string());

    return env->NewStringUTF(s.string());
}

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
    {"nativeTestString", "()Ljava/lang/String;", (void*)nativeTestString},
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
