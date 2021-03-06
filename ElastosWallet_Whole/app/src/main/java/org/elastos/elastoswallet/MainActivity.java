package org.elastos.elastoswallet;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {
    private static String TAG = "ElastosWallet_Whole";
    private MasterWalletManager mWalletManager;
    private IMasterWallet mMasterWallet;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Test
        TestWallet();
    }


    private void TestDID(IMasterWallet masterWallet, String rootPath, String payPassword) {
        DIDInspector.InitDIDInspector();

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


//    private void TestWallet() {
//        try {
//            //1. 初始化钱包所需的数据
//            ElastosWalletUtils.InitConfig(this);
//
//            //2. 传递一个可读写的路径，创建 MasterWalletManager
//            String rootPath = getApplicationContext().getFilesDir().getParent();
//            mWalletManager = new MasterWalletManager(rootPath);
//
//            //3. 生成助记词
//            String language = "english";
//            String mnemonic = mWalletManager.GenerateMnemonic(language);
//
//            //4. 创建主钱包
//            String masterWalletId = "masterWalletId";
//            String phrasePassword = "masterWalletId";
//            String payPassword = "masterWalletId";
//            IMasterWallet masterWallet = mWalletManager.CreateMasterWallet(masterWalletId, mnemonic,
//                    phrasePassword, payPassword, language);
//
//            //5. 创建ELA子钱包, chainID必须是"ELA"
//            String chainID = "ELA";
//            boolean singleAddress = false;
//            long feePerKb = 10000; //SELA
//            ISubWallet subWallet = masterWallet.CreateSubWallet(chainID, payPassword, singleAddress, feePerKb);
//
//            //6. CreateTransaction
//            String fromAddress = "";
//            String toAddress = "the other address";
//            long amount = 500; //ELA
//            long fee = 0;
//            String memo = "";
//            String remark = "";
//            String transaction = subWallet.CreateTransaction(fromAddress, toAddress, amount, fee, memo, remark);
//
//            //7. 计算费用 CalculateTransactionFee
//            fee = subWallet.CalculateTransactionFee(transaction, feePerKb);
//
//            //8. 发送交易 SendRawTransaction
//
//            String transactionId = subWallet.SendRawTransaction(transaction, fee, payPassword);
//
//            //交易回调
//            subWallet.AddCallback(new ISubWalletCallback() {
//                @Override
//                public void OnTransactionStatusChanged(String txId, String status, String desc, int confirms) {
//                    //TOOD 确认数变动会触发该回调.
//                }
//            });
//
//            //9. 其他接口: 获取ChainID、获取子钱包余额
//            String _chainId = subWallet.GetChainId();
//            long balance = subWallet.GetBalance();
//        }
//        catch (WalletException e) {
//            e.printStackTrace();
//        }
//    }
}
