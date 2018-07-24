// Copyright (c) 2012-2018 The Elastos Open Source Project
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ElaUtils.h"
#include "MasterWalletManager.h"

using namespace Elastos::ElaWallet;

#define  CLASS_MASTERWALLET   "org/elastos/testorispvdid/IMasterWallet"
#define  FIELD_MASTERWALLET   "mMasterProxy"

extern const char* ToStringFromJson(const nlohmann::json& jsonValue);
extern nlohmann::json ToJosnFromString(const char* str);

static jlong JNICALL nativeInitMasterWalletManager(JNIEnv *env, jobject clazz, jstring jrootPath)
{
    const char* rootPath = env->GetStringUTFChars(jrootPath, NULL);

    MasterWalletManager* walletManager = new MasterWalletManager(rootPath);

    env->ReleaseStringUTFChars(jrootPath, rootPath);
    return (jlong)walletManager;
}

static void JNICALL nativeDisposeNative(JNIEnv *env, jobject clazz, jlong jWalletMgr)
{
    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    delete walletManager;
}

//"(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)J"
static jlong JNICALL nativeCreateMasterWallet(JNIEnv *env, jobject clazz, jlong jWalletMgr, jstring jmasterWalletId
    , jstring jmnemonic, jstring jphrasePassword, jstring jpayPassword, jstring jlanguage)
{
    const char* masterWalletId = env->GetStringUTFChars(jmasterWalletId, NULL);
    const char* mnemonic = env->GetStringUTFChars(jmnemonic, NULL);
    const char* phrasePassword = env->GetStringUTFChars(jphrasePassword, NULL);
    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);
    const char* language = env->GetStringUTFChars(jlanguage, NULL);

    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    IMasterWallet* masterWallet = NULL;

    try {
        masterWallet = walletManager->CreateMasterWallet(masterWalletId, mnemonic, phrasePassword, payPassword,language);
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

    env->ReleaseStringUTFChars(jmasterWalletId, masterWalletId);
    env->ReleaseStringUTFChars(jmnemonic, mnemonic);
    env->ReleaseStringUTFChars(jphrasePassword, phrasePassword);
    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    env->ReleaseStringUTFChars(jlanguage, language);
    return (jlong)masterWallet;
}

static void JNICALL nativeDestroyWallet(JNIEnv *env, jobject clazz, jlong jWalletMgr, jstring jmasterWalletId)
{
    const char* masterWalletId = env->GetStringUTFChars(jmasterWalletId, NULL);

    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    LOGD("FUNC=[%s]===================LINE=[%d], masterWalletId=[%s], walletManager=[%p]", __FUNCTION__, __LINE__, masterWalletId, walletManager);

    try {
        walletManager->DestroyWallet(masterWalletId);
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

    LOGD("FUNC=[%s]===================LINE=[%d]", __FUNCTION__, __LINE__);

    env->ReleaseStringUTFChars(jmasterWalletId, masterWalletId);
}

static jlong JNICALL nativeImportWalletWithKeystore(JNIEnv *env, jobject clazz, jlong jWalletMgr, jstring jmasterWalletId, jstring jkeystoreContent,
        jstring jbackupPassword, jstring jpayPassword, jstring jphrasePassword)
{
    const char* masterWalletId = env->GetStringUTFChars(jmasterWalletId, NULL);
    const char* keystoreContent = env->GetStringUTFChars(jkeystoreContent, NULL);
    const char* backupPassword = env->GetStringUTFChars(jbackupPassword, NULL);
    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);
    const char* phrasePassword = env->GetStringUTFChars(jphrasePassword, NULL);

    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    IMasterWallet* masterWallet = NULL;

    try {
        masterWallet = walletManager->ImportWalletWithKeystore(masterWalletId, ToJosnFromString(keystoreContent), backupPassword, payPassword, phrasePassword);
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

    env->ReleaseStringUTFChars(jmasterWalletId, masterWalletId);
    env->ReleaseStringUTFChars(jkeystoreContent, keystoreContent);
    env->ReleaseStringUTFChars(jbackupPassword, backupPassword);
    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    env->ReleaseStringUTFChars(jphrasePassword, phrasePassword);
    return (jlong)masterWallet;
}

static jlong JNICALL nativeImportWalletWithMnemonic(JNIEnv *env, jobject clazz, jlong jWalletMgr, jstring jmasterWalletId,
        jstring jmnemonic, jstring jphrasePassword, jstring jpayPassword, jstring jlanguage)
{
    const char* masterWalletId = env->GetStringUTFChars(jmasterWalletId, NULL);
    const char* mnemonic = env->GetStringUTFChars(jmnemonic, NULL);
    const char* phrasePassword = env->GetStringUTFChars(jphrasePassword, NULL);
    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);
    const char* language = env->GetStringUTFChars(jlanguage, NULL);

    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    IMasterWallet* masterWallet = NULL;

    try {
        masterWallet = walletManager->ImportWalletWithMnemonic(masterWalletId, mnemonic, phrasePassword, payPassword, language);
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

    env->ReleaseStringUTFChars(jmasterWalletId, masterWalletId);
    env->ReleaseStringUTFChars(jmnemonic, mnemonic);
    env->ReleaseStringUTFChars(jphrasePassword, phrasePassword);
    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    env->ReleaseStringUTFChars(jlanguage, language);
    return (jlong)masterWallet;
}

static jstring JNICALL nativeExportWalletWithKeystore(JNIEnv *env, jobject clazz, jlong jWalletMgr, jobject jmasterWallet,
        jstring jbackupPassword, jstring jpayPassword)
{
    const char* backupPassword = env->GetStringUTFChars(jbackupPassword, NULL);
    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);

    jclass cls = env->FindClass(CLASS_MASTERWALLET);
    long masterProxy = GetJavaLongField(env, cls, jmasterWallet, FIELD_MASTERWALLET);
    CheckErrorAndLog(env, "nativeExportWalletWithKeystore", __LINE__);
    IMasterWallet* masterWallet = (IMasterWallet*)masterProxy;
    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    nlohmann::json result;

    try {
        result = walletManager->ExportWalletWithKeystore(masterWallet, backupPassword, payPassword);
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

    env->ReleaseStringUTFChars(jbackupPassword, backupPassword);
    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    return env->NewStringUTF(ToStringFromJson(result));
}

static jstring JNICALL nativeExportWalletWithMnemonic(JNIEnv *env, jobject clazz, jlong jWalletMgr,
        jobject jmasterWallet, jstring jpayPassword)
{
    jclass cls = env->FindClass(CLASS_MASTERWALLET);
    long masterProxy = GetJavaLongField(env, cls, jmasterWallet, FIELD_MASTERWALLET);
    CheckErrorAndLog(env, "nativeExportWalletWithMnemonic", __LINE__);
    IMasterWallet* masterWallet = (IMasterWallet*)masterProxy;

    const char* payPassword = env->GetStringUTFChars(jpayPassword, NULL);

    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    std::string str;

    try {
        str = walletManager->ExportWalletWithMnemonic(masterWallet, payPassword);
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

    env->ReleaseStringUTFChars(jpayPassword, payPassword);
    return env->NewStringUTF(str.c_str());
}

//"(J)[J"
static jlongArray JNICALL nativeGetAllMasterWallets(JNIEnv *env, jobject clazz, jlong jWalletMgr)
{
    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    std::vector<IMasterWallet *> array;

    try {
        array = walletManager->GetAllMasterWallets();
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

    const int length = array.size();
    if (length > 0) {
        jlong* proxies = new jlong[length];
        for (int i = 0; i < length; ++i) {
            proxies[i] = (jlong)array[i];
        }

        jlongArray jarray = env->NewLongArray(length);
        env->SetLongArrayRegion(jarray, 0, length, proxies);
        delete[] proxies;
        return jarray;
    }

    return NULL;
}

//"(JLjava/lang/String;)Ljava/lang/String;"
static jstring JNICALL nativeGenerateMnemonic(JNIEnv *env, jobject clazz, jlong jWalletMgr, jstring jlanguage)
{
    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    const char* language = env->GetStringUTFChars(jlanguage, NULL);
    std::string mnemonic;

    try {
        mnemonic = walletManager->GenerateMnemonic(language);
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

    env->ReleaseStringUTFChars(jlanguage, language);
    return env->NewStringUTF(mnemonic.c_str());
}

//"()V"
static void JNICALL nativeSaveConfigs(JNIEnv *env, jobject clazz, jlong jWalletMgr)
{
    MasterWalletManager* walletManager = (MasterWalletManager*)jWalletMgr;
    walletManager->SaveConfigs();
}


static const JNINativeMethod gMethods[] = {
    {"nativeInitMasterWalletManager", "(Ljava/lang/String;)J", (void*)nativeInitMasterWalletManager},
    {"nativeCreateMasterWallet", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)J"
            , (void*)nativeCreateMasterWallet},
    {"nativeDisposeNative", "(J)V", (void*)nativeDisposeNative},
    {"nativeDestroyWallet", "(JLjava/lang/String;)V", (void*)nativeDestroyWallet},
    {"nativeImportWalletWithKeystore", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)J", (void*)nativeImportWalletWithKeystore},
    {"nativeImportWalletWithMnemonic", "(JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)J", (void*)nativeImportWalletWithMnemonic},
    {"nativeExportWalletWithKeystore", "(JLorg/elastos/testorispvdid/IMasterWallet;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void*)nativeExportWalletWithKeystore},
    {"nativeExportWalletWithMnemonic", "(JLorg/elastos/testorispvdid/IMasterWallet;Ljava/lang/String;)Ljava/lang/String;", (void*)nativeExportWalletWithMnemonic},
    {"nativeGetAllMasterWallets", "(J)[J", (void*)nativeGetAllMasterWallets},
    {"nativeGenerateMnemonic", "(JLjava/lang/String;)Ljava/lang/String;", (void*)nativeGenerateMnemonic},
    {"nativeSaveConfigs", "(J)V", (void*)nativeSaveConfigs},
};

int register_elastos_spv_IMasterWalletManager(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "org/elastos/testorispvdid/MasterWalletManager",
        gMethods, NELEM(gMethods));
}
