// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ElaUtils.h"
#include "ididManager.h"

using namespace Elastos::DID;

extern const char* ToStringFromJson(const nlohmann::json& jsonValue);

//"(JLjava/lang/String;)J"
static jlong JNICALL nativeCreateDID(JNIEnv *env, jobject clazz, jlong jDidMgrProxy, jstring jpassword)
{
    const char* password = env->GetStringUTFChars(jpassword, NULL);
    IDIDManager* didMgr = (IDIDManager*)jDidMgrProxy;
    IDID* did = didMgr->CreateDID(password);
    env->ReleaseStringUTFChars(jpassword, password);
    return (jlong)did;
}

//"(JLjava/lang/String;)J"
static jlong JNICALL nativeGetDID(JNIEnv *env, jobject clazz, jlong jDidMgrProxy, jstring jdidName)
{
    const char* didName = env->GetStringUTFChars(jdidName, NULL);
    IDIDManager* didMgr = (IDIDManager*)jDidMgrProxy;
    IDID* did = didMgr->GetDID(didName);
    env->ReleaseStringUTFChars(jdidName, didName);
    return (jlong)did;
}

//"(J)Ljava/lang/String;"
static /*nlohmann::json*/ jstring JNICALL nativeGetDIDList(JNIEnv *env, jobject clazz, jlong jDidMgrProxy)
{
    IDIDManager* didMgr = (IDIDManager*)jDidMgrProxy;
    nlohmann::json jsonValue = didMgr->GetDIDList();
    LOGD("FUNC=[%s]========================value=[%s]", __FUNCTION__, jsonValue.dump().c_str());
    return env->NewStringUTF(jsonValue.dump().c_str());
}

//"(JLjava/lang/String;)V"
static void JNICALL nativeDestoryDID(JNIEnv *env, jobject clazz, jlong jDidMgrProxy, jstring jdidName)
{
    const char* didName = env->GetStringUTFChars(jdidName, NULL);
    IDIDManager* didMgr = (IDIDManager*)jDidMgrProxy;
    didMgr->DestoryDID(didName);
    env->ReleaseStringUTFChars(jdidName, didName);
}


class ElaIdManagerCallback: public IIdManagerCallback
{
public:
    virtual void OnIdStatusChanged(
        const std::string &id,
        const std::string &path,
        const nlohmann::json &value);

    ElaIdManagerCallback(
        /* [in] */ JNIEnv* env,
        /* [in] */ jobject jobj);

    ~ElaIdManagerCallback();

private:
    JNIEnv* GetEnv();
    void Detach();

private:
    JavaVM* mVM;
    jobject mObj;
};

static std::map<jstring, ElaIdManagerCallback*> sIdCallbackMap;
static jboolean JNICALL nativeRegisterCallback(JNIEnv *env, jobject clazz, jlong jDidMgrProxy, jstring jdidName, jobject jidCallback)
{
    LOGD("FUNC=[%s]========================LINE=[%d]", __FUNCTION__, __LINE__);
    const char* didName = env->GetStringUTFChars(jdidName, NULL);
    ElaIdManagerCallback* idCallback = new ElaIdManagerCallback(env, jidCallback);
    IDIDManager* didMgr = (IDIDManager*)jDidMgrProxy;
    jboolean status = didMgr->RegisterCallback(didName, idCallback);
    sIdCallbackMap[jdidName] = idCallback;

    env->ReleaseStringUTFChars(jdidName, didName);
    return status;
}

static jboolean JNICALL nativeUnregisterCallback(JNIEnv *env, jobject clazz, jlong jDidMgrProxy, jstring jdidName)
{
    const char* didName = env->GetStringUTFChars(jdidName, NULL);

    IDIDManager* didMgr = (IDIDManager*)jDidMgrProxy;
    std::map<jstring, ElaIdManagerCallback*>::iterator it;
    jboolean status = false;
    for (it = sIdCallbackMap.begin(); it != sIdCallbackMap.end(); it++) {
        if (jdidName == it->first) {
            status = didMgr->UnregisterCallback(didName);
            delete it->second;
            sIdCallbackMap.erase(it);
            break;
        }
    }

    env->ReleaseStringUTFChars(jdidName, didName);
    return status;
}

static const JNINativeMethod gMethods[] = {
    {"nativeCreateDID", "(JLjava/lang/String;)J", (void*)nativeCreateDID},
    {"nativeGetDID", "(JLjava/lang/String;)J", (void*)nativeGetDID},
    {"nativeGetDIDList", "(J)Ljava/lang/String;", (void*)nativeGetDIDList},
    {"nativeDestoryDID", "(JLjava/lang/String;)V", (void*)nativeDestoryDID},
    {"nativeRegisterCallback", "(JLjava/lang/String;Lorg/elastos/testorispvdid/IIdManagerCallback;)Z", (void*)nativeRegisterCallback},
    {"nativeUnregisterCallback", "(JLjava/lang/String;)Z", (void*)nativeUnregisterCallback},
};

jint register_elastos_spv_IDidManager(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "org/elastos/testorispvdid/IDidManager",
        gMethods, NELEM(gMethods));
}

ElaIdManagerCallback::ElaIdManagerCallback(
    /* [in] */ JNIEnv* env,
    /* [in] */ jobject jobj)
{
    LOGD("FUNC=[%s]========================LINE=[%d]", __FUNCTION__, __LINE__);
    mObj = env->NewGlobalRef(jobj);
    env->GetJavaVM(&mVM);
}

ElaIdManagerCallback::~ElaIdManagerCallback()
{
    LOGD("FUNC=[%s]========================LINE=[%d]", __FUNCTION__, __LINE__);
    if (mObj) {
        GetEnv()->DeleteGlobalRef(mObj);
    }
}

JNIEnv* ElaIdManagerCallback::GetEnv()
{
    JNIEnv* env;
    assert(mVM != NULL);
    mVM->AttachCurrentThread(&env, NULL);
    return env;
}

void ElaIdManagerCallback::Detach()
{
    assert(mVM != NULL);
    mVM->DetachCurrentThread();
}

void ElaIdManagerCallback::OnIdStatusChanged(const std::string &id,
    const std::string &path, const nlohmann::json &value)
{
    JNIEnv* env = GetEnv();
    LOGD("FUNC=[%s]========================LINE=[%d]", __FUNCTION__, __LINE__);

    jclass clazz = env->GetObjectClass(mObj);
    //"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V"
    jmethodID methodId = env->GetMethodID(clazz, "OnIdStatusChanged","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    jstring jid = env->NewStringUTF(id.c_str());
    jstring jpath = env->NewStringUTF(path.c_str());
    jstring jvalue = env->NewStringUTF(ToStringFromJson(value));

    env->CallVoidMethod(mObj, methodId, jid, jpath, jvalue);

    Detach();
}
