#include "pch.h"
#include "CFileDirectory.h"

CFileDirectory::CFileDirectory()
{

}
CFileDirectory::~CFileDirectory()
{

}

CString CFileDirectory::GetCurrentDirectory()
{
	DWORD dwSize = 0;
	LPTSTR lpStr = NULL;
	CString csString;

	dwSize = ::GetCurrentDirectory(dwSize, lpStr);
	lpStr = new TCHAR[dwSize + 1];
	dwSize = ::GetCurrentDirectory(dwSize, lpStr);

	csString.Format(_T("%s"), lpStr);
	delete[] lpStr;
	lpStr = NULL;
	return csString;
}

CString CFileDirectory::OpenFile()
{

	TCHAR szFilters[] = _T("IMG Templates (*.bmp)|*.bmp|");
	SetCurrentDirectory(GetCurrentDirectory());

	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog dlg(TRUE, _T("bmp"), _T("*.bmp"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);



	dlg.DoModal();

	return dlg.GetFolderPath() + _T("\\") + dlg.GetFileName();
}