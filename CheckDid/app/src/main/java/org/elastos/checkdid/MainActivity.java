package org.elastos.checkdid;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import org.elastos.elastoswallet.ElastosWalletUtils;
import org.elastos.elastoswallet.IDid;
import org.elastos.elastoswallet.IDidManager;
import org.elastos.elastoswallet.IMasterWallet;
import org.elastos.elastoswallet.IdManagerFactory;
import org.elastos.elastoswallet.MasterWalletManager;
import org.elastos.elastoswallet.WalletException;

public class MainActivity extends AppCompatActivity {
    private static String TAG = "CheckDID";
    private MasterWalletManager mWalletManager;
    private IMasterWallet mMasterWallet;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        TestCheckDid();
//        TestWallet();
        String tmp = DIDInspector.TestString();
        Log.d(TAG, "tmp =============[" + tmp + "]");
    }

    private void TestDID(IMasterWallet masterWallet, String rootPath, String payPassword) {
        IDidManager didManager = IdManagerFactory.CreateIdManager(masterWallet, rootPath);
        IDid did = didManager.CreateDID(payPassword);
        String didName = did.GetDIDName();
        Log.d(TAG, "didName =============[" + didName + "]");

        //
        String publicKeyStr = did.GetPublicKey();
        boolean matched = DIDInspector.CheckDID(publicKeyStr, didName);
        Log.d(TAG, "TestDID==========================matched=["+matched+"]");
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

    private void TestCheckDid(String didName) {
        String publicKeyStr = "031d15c3d151fef9a347e635c736d3d5492bf20626e2ab821d44496964d5656eab";
        boolean matched = DIDInspector.CheckDID(publicKeyStr, didName);
        Log.d(TAG, "TestCheckDid=============1=============matched=["+matched+"]");

        String message = "MyMessage";
        String signature = "4067e0bc591b797f9a88385b686242f7b5d110db0fb3821f9f8b5ec55ca66ec66e926f3f342d7a73a93b60b4a865a18e6df81e83ae690f8903fa90d24b6f41f49f";
        matched = DIDInspector.CheckSign(publicKeyStr, message, signature);
        Log.d(TAG, "TestCheckDid=============2=============matched=["+matched+"]");
    }
}
