package org.elastos.elastoswallettest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import org.elastos.elastoswallet.ElastosWalletUtils;
import org.elastos.elastoswallet.IMasterWallet;
import org.elastos.elastoswallet.ISubWallet;
import org.elastos.elastoswallet.ISubWalletCallback;
import org.elastos.elastoswallet.MasterWalletManager;
import org.elastos.elastoswallet.WalletException;

public class MainActivity extends AppCompatActivity {
    static String TAG = "Elastos-SPV-Test";
    private MasterWalletManager mWalletManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Test
        TestWallet();
    }

    private void TestDID() {

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
            Log.d(TAG, "mnemonic =============["+mnemonic+"]");

            //4. 创建主钱包
            String masterWalletId = "masterWalletId";
            String phrasePassword = "masterWalletId";
            String payPassword = "masterWalletId";
            IMasterWallet masterWallet = mWalletManager.CreateMasterWallet(masterWalletId, mnemonic,
                    phrasePassword, payPassword, language);

            //5. 创建ELA子钱包, chainID必须是"ELA"
            String chainID = "ELA";
            boolean singleAddress = false;
            long feePerKb = 10000; //SELA
            ISubWallet subWallet = masterWallet.CreateSubWallet(chainID, payPassword, singleAddress, feePerKb);
            Log.d(TAG, "subWallet============================"+subWallet);

            //6. CreateTransaction
            String fromAddress = "";
            String toAddress = "the other address";
            long amount = 500; //ELA
            long fee = 0;
            String memo = "";
            String remark = "";
            Log.d(TAG, "subWallet============================1");
            String transaction = subWallet.CreateTransaction(fromAddress, toAddress, amount, memo, remark);
            Log.d(TAG, "subWallet============================2");
            //7. 计算费用 CalculateTransactionFee
            fee = subWallet.CalculateTransactionFee(transaction, feePerKb);

            //8. 发送交易 SendRawTransaction

            Log.d(TAG, "subWallet============================3");
            String transactionId = subWallet.SendRawTransaction(transaction, fee, payPassword);

            Log.d(TAG, "subWallet============================4");
            //交易回调
            subWallet.AddCallback(new ISubWalletCallback() {
                @Override
                public void OnTransactionStatusChanged(String txId, String status, String desc, int confirms) {
                    //TOOD 确认数变动会触发该回调.
                }
                @Override
                public void OnBlockSyncStarted() {
                    //TOOD 区块同步时触发
                }
                @Override
                public void OnBlockHeightIncreased(int currentBlockHeight, double progress) {
                    //TOOD 同步过程中的回调
                }
                @Override
                public void OnBlockSyncStopped() {
                    //TOOD 同步结束
                }
            });

            //9. 其他接口: 获取ChainID、获取子钱包余额
            String _chainId = subWallet.GetChainId();
            long balance = subWallet.GetBalance();
        }
        catch (WalletException e) {
            e.printStackTrace();
        }
    }
}
