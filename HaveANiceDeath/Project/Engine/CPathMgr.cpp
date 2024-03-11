#include "pch.h"
#include "CPathMgr.h"

path CPathMgr::g_ContentPath;

wstring CPathMgr::GetRelativePath(const wstring& _AbsolutePath)
{
	path AbsolutePath = _AbsolutePath;
	path RelativePath = relative(AbsolutePath, g_ContentPath);

	return RelativePath.c_str();
}

void CPathMgr::init()
{
	// �������� ���
	g_ContentPath = current_path();
	g_ContentPath = g_ContentPath.parent_path();
	g_ContentPath = g_ContentPath / L"content\\";
}
