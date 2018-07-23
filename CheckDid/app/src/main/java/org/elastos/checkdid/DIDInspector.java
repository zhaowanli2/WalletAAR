package org.elastos.checkdid;

public class DIDInspector {
    private static long sDIDInspectorProxy = 0;
    static {
        System.loadLibrary("didInspector");
        InitDIDInspector();
    }

    public static boolean CheckDID(String publicKey, String did) {
        return nativeCheckDID(sDIDInspectorProxy, publicKey, did);
    }

    public static boolean CheckSign(String publicKey, String message, String signature) {
        return nativeCheckSign(sDIDInspectorProxy, publicKey, message, signature);
    }

    private static void InitDIDInspector() {
        sDIDInspectorProxy = nativeInitDIDInspector();
    }

    private static native long nativeInitDIDInspector();
    private static native boolean nativeCheckDID(long proxy, String publicKey, String did);
    private static native boolean nativeCheckSign(long proxy, String publicKey, String message, String signature);
}
