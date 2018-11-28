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
	
	//�������� �����
	cout << CreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\OSISP-LAB4",hKey) << endl;
	//�������� �����
	cout << OpenKey(HKEY_CURRENT_USER, L"SOFTWARE\\OSISP-LAB4", hKey) << endl;
	//�������� �����
	cout << CloseKey(hKey) << endl;
	
	/*
	//������ ��������� + �������� �� ���������
	LSTATUS status0 = RegSetValue(hKey, L"Test", REG_SZ, L"Message", 7 * sizeof(WCHAR));
	//�������� - ��� � �������

	BYTE* data = (BYTE*)calloc(4, 1);
	data[1] = 1;
	//������ ���� ����-��������
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

	cout << "Complete" << endl;
}