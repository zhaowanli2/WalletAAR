
package org.elastos.elastoswallet;


public interface ISubWalletCallback {
    /**
     * Call back method fired when status of a transaction changed.
     * @param txid indicate hash of the transaction.
     * @param status can be "Added", "Deleted" or "Updated".
     * @param desc is an detail description of transaction status.
     * @param confirms is confirm count util this callback fired.
     */
    public void OnTransactionStatusChanged(String txId, String status, String desc,int confirms);
}
