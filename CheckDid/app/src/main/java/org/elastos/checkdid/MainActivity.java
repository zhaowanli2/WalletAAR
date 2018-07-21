package org.elastos.checkdid;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private static String TAG = "CheckDID";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TestCheckDid();
    }

    private void TestCheckDid() {
        String publicKeyStr = "031d15c3d151fef9a347e635c736d3d5492bf20626e2ab821d44496964d5656eab";
        String id = CheckDid.PublicKeyToIdAddress(publicKeyStr);
        Log.d(TAG, "TestCheckDid==========================id=["+id+"]");

        String message = "MyMessage";
        String signature = "4067e0bc591b797f9a88385b686242f7b5d110db0fb3821f9f8b5ec55ca66ec66e926f3f342d7a73a93b60b4a865a18e6df81e83ae690f8903fa90d24b6f41f49f";
        boolean check = CheckDid.VerifyByPublicKey(publicKeyStr, message, signature);
        Log.d(TAG, "TestCheckDid==========================check=["+check+"]");
    }
}
