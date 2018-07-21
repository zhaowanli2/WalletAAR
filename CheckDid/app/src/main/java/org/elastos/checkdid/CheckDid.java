package org.elastos.checkdid;

public class CheckDid {
    static {
        System.loadLibrary("checkdid");
    }

    public static String PublicKeyToIdAddress(String publicKey) {
        return nativePublicKeyToIdAddress(publicKey);
    }

    public static boolean VerifyByPublicKey(String publicKey, String message, String signature) {
        return nativeVerifyByPublicKey(publicKey, message, signature);
    }

    private static native String nativePublicKeyToIdAddress(String publicKey);
    private static native boolean nativeVerifyByPublicKey(String publicKey, String message, String signature);
}
