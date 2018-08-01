package org.elastos.testorispvdid;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity {
    private static String TAG = "Test_Ori_SpvDid";
    private MasterWalletManager mWalletManager;
    private IMasterWallet mMasterWallet;

    static {
        System.loadLibrary("spvsdk");
        System.loadLibrary("idchain");
        System.loadLibrary("testspvdid");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Test
        TestWallet();
    }


    private void TestDID(IMasterWallet masterWallet, String rootPath, String payPassword) {
        IDidManager didManager = IdManagerFactory.CreateIdManager(masterWallet, rootPath);
        IDid did = didManager.CreateDID(payPassword);
        String didName = did.GetDIDName();
        Log.d(TAG, "didName =============[" + didName + "]");

        //
        String publicKeyStr = did.GetPublicKey();
        boolean matched = DIDInspector.CheckDID(publicKeyStr, didName);
        Log.d(TAG, "TestDID=============1=============matched=["+matched+"]");

        String message = "i am a message.";
        String signature = did.Sign(message, payPassword);
        matched = DIDInspector.CheckSign(publicKeyStr, message, signature);
        Log.d(TAG, "TestDID==============2============matched=["+matched+"]");
    }

    private void TestWallet() {
        try {
            //1. 初始化钱包所需的数据
            ElastosWalletUtils.InitConfig(this);

            //2. 传递一个可读写的路径，创建 MasterWalletManager
            String rootPath = getApplicationContext().getFilesDir().getParent();
            mWalletManager = new MasterWalletManager(rootPath);

            //3. 生成助记词
            String language = "english";
            String mnemonic = mWalletManager.GenerateMnemonic(language);
            Log.d(TAG, "mnemonic =============[" + mnemonic + "]");

            //4. 创建主钱包
            String masterWalletId = "masterWalletId";
            String phrasePassword = "masterWalletId";
            String payPassword = "masterWalletId";
            mMasterWallet = mWalletManager.CreateMasterWallet(masterWalletId, mnemonic,
                    phrasePassword, payPassword, language);
            TestDID(mMasterWallet, rootPath, payPassword);
        }
        catch (WalletException e) {
            e.printStackTrace();
        }
    }

}
