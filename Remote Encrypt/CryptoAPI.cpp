#include "CryptoAPI.h"


bool CryptoAPI::AES128EncDec(wstring filePath, char *key, bool encrypt)
{
	FileHandler fileHandler;

	HANDLE hFile = INVALID_HANDLE_VALUE;

	HCRYPTPROV hCryptProv = NULL;
	HCRYPTKEY hKey = NULL;
	HCRYPTKEY hXchgKey = NULL;
	HCRYPTHASH hHash = NULL;

	PBYTE pbKeyBlob = NULL;
	DWORD dwKeyBlobLen;

	PBYTE pbBuffer = NULL;
	DWORD dwBlockLen;
	DWORD dwBufferLen;
	DWORD dwCount;

	hFile = CreateFile(filePath.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0)) return false;
	if (!CryptCreateHash(hCryptProv, CALG_SHA, 0, 0, &hHash)) return false;
	if (!CryptHashData(hHash, (BYTE*)key, lstrlenA(key), 0)) return false;
	if (!CryptDeriveKey(hCryptProv, ENCRYPT_ALGORITHM, hHash, KEYLENGTH, &hKey))
		cout << GetLastError();

	dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;

	if (ENCRYPT_BLOCK_SIZE > 1)
		dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE;
	else
		dwBufferLen = dwBlockLen;

	pbBuffer = (BYTE *)malloc(dwBufferLen);
	bool fEOF = FALSE;

	do
	{
		ReadFile(hFile, pbBuffer, dwBlockLen, &dwCount, NULL);

		if (dwCount < dwBlockLen)
			fEOF = TRUE;

		SetFilePointer(hFile, -dwCount, NULL, FILE_CURRENT);
		//TODO: Find a way to read/write at same time o.o
		CryptEncrypt(hKey, NULL, fEOF, 0, pbBuffer, &dwCount, dwBufferLen);
		WriteFile(hFile, pbBuffer, dwCount, &dwCount, NULL);

	} while (!fEOF);

	if (hFile)
		CloseHandle(hFile);

	if (hHash)
		CryptDestroyHash(hHash);

	if (hKey)
		CryptDestroyKey(hKey);

	if (hCryptProv)
		CryptReleaseContext(hCryptProv, 0);

	return true;
}


CryptoAPI::CryptoAPI()
{
	AES128EncDec(L"C:\\tmp\\putty.exe", "passswordd", true);
	AES128EncDec(L"C:\\tmp\\putty.exe", "passswordd", false);
}


CryptoAPI::~CryptoAPI()
{
}
