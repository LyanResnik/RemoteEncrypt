#pragma once
#include "FileHandler.h"

using namespace std;

#define KEYLENGTH  0x00800000
#define ENCRYPT_ALGORITHM CALG_AES_128
#define ENCRYPT_BLOCK_SIZE 128

class CryptoAPI
{
private:
	bool AES128EncDec(wstring filePath, char *key, bool encrypt);
	bool DecryptFile(wstring filePath);
public:
	CryptoAPI();
	~CryptoAPI();
};

