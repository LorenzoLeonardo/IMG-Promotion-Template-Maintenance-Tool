#pragma once
#include <vector>

using namespace std;
class CFileDirectory
{
public:
	CFileDirectory();
	~CFileDirectory();
	CString GetCurrentDirectory();
	CString OpenFile();
};

