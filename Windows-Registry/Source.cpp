#include <Windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

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
	//result = RegSetValueEx(hKey,lpValueName,0, REG_SZ,data, 7 * sizeof(WCHAR))
	//result = RegSetValue(hKey, lpValueName,REG_SZ, L"Message", 7 * sizeof(WCHAR));
	return (result == ERROR_SUCCESS);
}

bool CreateKey(HKEY mainKey,LPCWSTR lpSubKey,HKEY &hKey)
{
	LSTATUS result;
		
	result = RegCreateKeyEx(mainKey, lpSubKey, 0, L"", REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hKey, NULL);
	CloseKey(hKey);
	return (result == ERROR_SUCCESS);
}

int main()
{
	HKEY hKey = NULL;
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
	getchar;
	//добавление остальных значений
	CreateValue(hKey, L"STRING", REG_SZ, (LPCVOID)L"SomeString", (wcslen(L"SomeString") * sizeof(WCHAR))+1 );
	CreateValue(hKey, L"DWORD", REG_DWORD, (LPCVOID)&dw32, sizeof(DWORD));
	CreateValue(hKey, L"DWORD_BE", REG_DWORD_BIG_ENDIAN, (LPCVOID)&dw32, sizeof(DWORD));
	CreateValue(hKey, L"BINARY", REG_BINARY, (LPCVOID)&dw32, sizeof(DWORD));
	CreateValue(hKey, L"QWORD", REG_QWORD, (LPCVOID)&dw64, sizeof(DWORD64));
	
/*
	BYTE* data = (BYTE*)calloc(4, 1);
	data[1] = 1;
	//Создаёт пару ключ-значение
	LSTATUS status1 = RegSetValueEx(hKey, L"PARAM", NULL, REG_DWORD, data, 4);
	LSTATUS status2 = RegDeleteValue(hKey, L"PARAM");

	DWORD iIndex = 0;
	LPWSTR wstr = (LPWSTR)calloc(SIZE_STR + 1, sizeof(WCHAR));

	while (RegEnumKey(hKey, iIndex, wstr, SIZE_STR) ==
		ERROR_SUCCESS)
	{
		++iIndex;
	}*/
	//RegCloseKey(hKey);

	//закрытие ключа
	cout << CloseKey(hKey) << endl;

	cout << "Complete" << endl;
}