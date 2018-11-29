#include <Windows.h>
#include <stdio.h>
#include <iostream>

#define BUFFER_LENGTH 50;

using namespace std;

wstring toLowerCase(wstring str)
{
	for (int i = 0; i < str.length(); i++)
		str[i] = towlower(str[i]);
	return str;
}

bool CloseKey(HKEY &hKey)
{
	LSTATUS result;

	result = RegCloseKey(hKey);
	return (result == ERROR_SUCCESS);
}

bool OpenKey(HKEY mainKey, LPCWSTR lpSubKey, HKEY &hKey)
{
	LSTATUS result;

	result = RegOpenKeyEx(mainKey, lpSubKey,0,KEY_ALL_ACCESS,&hKey);
	return (result == ERROR_SUCCESS);
}

bool CreateValue(HKEY &hKey,LPCWSTR lpValueName,DWORD dwType,LPCVOID data,DWORD length)
{
	LSTATUS result;
	result = RegSetKeyValue(hKey,L"", lpValueName, dwType, data, length);
	return (result == ERROR_SUCCESS);
}

bool CreateKey(HKEY mainKey,LPCWSTR lpSubKey,HKEY &hKey)
{
	LSTATUS result;
		
	result = RegCreateKeyEx(mainKey, lpSubKey, 0, L"", REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hKey, NULL);
	CloseKey(hKey);
	return (result == ERROR_SUCCESS);
}

void GetKeys(HKEY &hKey,LPWSTR searchStr)
{
	DWORD index = 0;
	DWORD length = BUFFER_LENGTH+1;
	LPWSTR buffer = (LPWSTR)calloc(length-1, sizeof(WCHAR));
	
	while (RegEnumKeyEx(hKey, index, buffer,&length, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
	{		
		length = BUFFER_LENGTH+1;
		if(wcsstr(toLowerCase(buffer).c_str(), toLowerCase(searchStr).c_str()) != NULL)
			wcout << buffer << endl;
		index++;
	}
}

int main()
{
	HKEY hKey = NULL,tmp = NULL;
	DWORD dw32 = 13;
	DWORD64 dw64 = 123;

	//создание ключа
	if (CreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\OSISP-LAB4", hKey))
		cout << "Key HKEY_CURRENT_USER\\SOFTWARE\\OSISP-LAB4 was created" << endl;
	else
		cout << "Cannot create key" << endl;
	getchar();
	//открытие ключа
	if (OpenKey(HKEY_CURRENT_USER, L"SOFTWARE\\OSISP-LAB4", hKey))
		cout << "Key HKEY_CURRENT_USER\\SOFTWARE\\OSISP-LAB4 was oppened"<<endl;
	else
		cout << "Cannot open key" << endl;
	getchar();
	//добавление значения по умолчанию
	if (CreateValue(hKey, L"", REG_SZ, (LPCVOID)L"Default", (wcslen(L"Default") * sizeof(WCHAR))+1) )
		cout << "Default value was changed" << endl;
	else
		cout << "Cannot change default value" << endl;
	getchar();
	//добавление остальных значений
	CreateValue(hKey, L"STRING", REG_SZ, (LPCVOID)L"SomeString", (wcslen(L"SomeString") * sizeof(WCHAR))+1 );
	CreateValue(hKey, L"DWORD", REG_DWORD, (LPCVOID)&dw32, sizeof(DWORD));
	CreateValue(hKey, L"DWORD_BE", REG_DWORD_BIG_ENDIAN, (LPCVOID)&dw32, sizeof(DWORD));
	CreateValue(hKey, L"BINARY", REG_BINARY, (LPCVOID)&dw32, sizeof(DWORD));
	CreateValue(hKey, L"QWORD", REG_QWORD, (LPCVOID)&dw64, sizeof(DWORD64));
	//поиск ключа(выборка)
	cout << "Search keys with 'os':" << endl;
	OpenKey(HKEY_CURRENT_USER, L"SOFTWARE", tmp);
	GetKeys(tmp,L"os");
	CloseKey(tmp);
	getchar();
	//закрытие ключа
	if (CloseKey(hKey))
		cout << "Key HKEY_CURRENT_USER\\SOFTWARE\\OSISP-LAB4 was closed" << endl;
	else
		cout << "Cannot close key" << endl;

	cout << "Complete" << endl;
}