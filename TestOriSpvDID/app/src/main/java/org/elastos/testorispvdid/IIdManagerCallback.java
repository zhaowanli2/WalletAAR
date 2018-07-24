
package org.elastos.testorispvdid;


public interface IIdManagerCallback {
    public void OnIdStatusChanged(String id, String path, /*const nlohmann::json*/ String value);
}
