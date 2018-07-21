#include <iostream>

#include "Key.h"
#include "Utils.h"

using namespace Elastos::ElaWallet;

int main( int argc , char * argv[] )
{
	std::string publicKeyStr = "031d15c3d151fef9a347e635c736d3d5492bf20626e2ab821d44496964d5656eab";
	//由public key生成id
	CMBlock pubKey = Utils::decodeHex(publicKeyStr);
	BRKey key;
	memcpy(key.pubKey, pubKey, pubKey.GetSize());
	key.compressed = (pubKey.GetSize() <= 33);
	std::string id = Key::publicKeyToIdAddress(&key);
	std::cout << "Result id is: " << id << std::endl;

	//验证签名
	std::string message = "MyMessage";
	std::string signature = "4067e0bc591b797f9a88385b686242f7b5d110db0fb3821f9f8b5ec55ca66ec66e926f3f342d7a73a93b60b4a865a18e6df81e83ae690f8903fa90d24b6f41f49f";
	if(Key::verifyByPublicKey(publicKeyStr, message, signature)) {
		std::cout << "Success!" << std::endl;
	}

	return 0;
}
