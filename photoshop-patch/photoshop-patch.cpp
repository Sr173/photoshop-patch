// photoshop-patch.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "windows.h"
#include "vector"

using namespace std;

#pragma comment (lib,"Mincore.lib")
#pragma comment (lib,"Version.lib")
#pragma warning(disable:4996);

char* search_pattern(char* begin, char* end, std::string pattern) {
	for (auto i = begin; i < end - pattern.length(); i++) {
		int flag = true;
		for (auto j = 0; j < pattern.length() && (flag = (*(i + j) == pattern[j])); j++);
		if (flag) return i;
	}
	return nullptr;
}

int main()
{
	OPENFILENAME ofn;    
	char szFile[MAX_PATH];          
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "photoshop.exe";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (!GetOpenFileName(&ofn))
	{
		cout << "打开文件失败:" << GetLastError() << endl;
		return 0;
	}

	DWORD dwLen = GetFileVersionInfoSize(szFile, NULL);
	VS_FIXEDFILEINFO* pFileInfo(NULL);
	char* pszAppVersion = new char[dwLen + 1];
	if (pszAppVersion)
	{
		memset(pszAppVersion, 0, sizeof(char) * (dwLen + 1));
		GetFileVersionInfo(szFile, NULL, dwLen, pszAppVersion);
		UINT nLen(0);
		VerQueryValue(pszAppVersion, "\\", (LPVOID*)& pFileInfo, &nLen);
	}


	if (pFileInfo->dwFileVersionLS != 13785) {
		cout << "暂时只支持13785版本";
	}
	cout << "选择了文件：" << szFile << ",文件版本"
		<< pFileInfo->dwFileVersionLS
		<< endl
		<< "开始破解" << endl;
	cout << szFile << endl;
	auto file = fopen(szFile, "rb");
	fseek(file, 0L, SEEK_END);
	unsigned int size = ftell(file);
	fseek(file, 0L, SEEK_SET);
	auto buffer = new unsigned char[size];
	fread(buffer, size, 1, file);

	buffer[0x7EF848D] = 0x74;//90
	buffer[0x7EF848E] = 0x06;//90
	buffer[0x7EF87FD] = 0x72;//90
	buffer[0x7EF87FE] = 0x03;//90
	buffer[0x7EF8824] = 0x0F;//90
	buffer[0x7EF8825] = 0x84;//90
	buffer[0x7EF8826] = 0xFC;//90
	buffer[0x7EF8827] = 0x03;//90
	buffer[0x7EF8828] = 0x00;//90
	buffer[0x7EF8829] = 0x00;//90
	buffer[0x7EF8852] = 0x74;//90
	buffer[0x7EF8853] = 0x2A;//90
	buffer[0x7EF888A] = 0x72;//EB
	buffer[0x7EF88EA] = 0x74;//90
	buffer[0x7EF88EB] = 0x25;//90
	buffer[0x7EF891A] = 0x72;//EB
	buffer[0x7EF8979] = 0x74;//90
	buffer[0x7EF897A] = 0x25;//90
	buffer[0x7EF89A9] = 0x72;//EB
	buffer[0x7EF8A08] = 0x74;//90
	buffer[0x7EF8A09] = 0x25;//90
	buffer[0x7EF8A38] = 0x72;//EB
	buffer[0x7EF8A9A] = 0x74;//90
	buffer[0x7EF8A9B] = 0x25;//90
	buffer[0x7EF8ACA] = 0x72;//EB
	buffer[0x7EF8B2C] = 0x74;//90
	buffer[0x7EF8B2D] = 0x25;//90
	buffer[0x7EF8B5C] = 0x72;//EB
	buffer[0x7EF8BBE] = 0x74;//90
	buffer[0x7EF8BBF] = 0x25;//90
	buffer[0x7EF8BEE] = 0x72;//EB
	buffer[0x7EF8C40] = 0x72;//EB
	buffer[0x7F0E3ED] = 0x74;//90
	buffer[0x7F0E3EE] = 0x75;//90
	buffer[0x7F0E43F] = 0x75;//EB
	buffer[0x7F1AEFA] = 0x74;//90
	buffer[0x7F1AEFB] = 0x16;//90
	buffer[0x7F1AF04] = 0x72;//EB
	buffer[0x7F1AF29] = 0x74;//90
	buffer[0x7F1AF2A] = 0x16;//90
	buffer[0x7F1AF33] = 0x72;//EB
	buffer[0x7F1AF58] = 0x74;//90
	buffer[0x7F1AF59] = 0x16;//90
	buffer[0x7F1AF62] = 0x72;//EB
	buffer[0x7F1AF87] = 0x74;//90
	buffer[0x7F1AF88] = 0x16;//90
	buffer[0x7F1AF91] = 0x72;//EB
	buffer[0x7F1AFB6] = 0x74;//90
	buffer[0x7F1AFB7] = 0x16;//90
	buffer[0x7F1AFC0] = 0x72;//EB
	buffer[0x7F1AFE5] = 0x74;//90
	buffer[0x7F1AFE6] = 0x16;//90
	buffer[0x7F1AFEF] = 0x72;//EB
	buffer[0x7F1B014] = 0x74;//90
	buffer[0x7F1B015] = 0x17;//90
	buffer[0x7F1B01E] = 0x72;//EB
	buffer[0x7F6ED49] = 0x0F;//90
	buffer[0x7F6ED4A] = 0xB6;//90
	buffer[0x7F6ED4B] = 0x08;//90
	buffer[0x7F6EF93] = 0x0F;//90
	buffer[0x7F6EF94] = 0xB6;//90
	buffer[0x7F6EF95] = 0x01;//90
	buffer[0x7F71E99] = 0xB0;//84
	buffer[0x7F71E9A] = 0x01;//C0
	buffer[0x7F726C0] = 0x0F;//90
	buffer[0x7F726C1] = 0xB6;//90
	buffer[0x7F726C2] = 0x10;//90
	buffer[0x7F726DB] = 0x75;//90
	buffer[0x7F726DC] = 0xE3;//90
	buffer[0x8170823] = 0x90;//0F
	buffer[0x8170824] = 0x90;//84
	buffer[0x8170825] = 0x90;//1D
	buffer[0x8170826] = 0x90;//01
	buffer[0x8170827] = 0x90;//00
	buffer[0x8170828] = 0x90;//00
	buffer[0x8170830] = 0x90;//8B
	buffer[0x8170831] = 0x90;//11
	buffer[0x8170835] = 0x90;//0F
	buffer[0x8170836] = 0x90;//84
	buffer[0x8170837] = 0x90;//CE
	buffer[0x8170838] = 0x90;//00
	buffer[0x8170839] = 0x90;//00
	buffer[0x817083A] = 0x90;//00
	buffer[0x817083E] = 0xE9;//0F
	buffer[0x817083F] = 0x89;//84
	buffer[0x8170840] = 0x00;//88
	


	auto wfile = fopen("photoshop2.exe","wb");
	fwrite(buffer, size, 1, wfile);
	cout << "破解完毕 在同目录生成photoshop.exe";
	fclose(wfile);
	fclose(file);

}
