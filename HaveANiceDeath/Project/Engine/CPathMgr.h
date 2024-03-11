#pragma once

class CPathMgr
{
private:
	static path g_ContentPath;

public:
	static const wchar_t* GetContentPath() { return g_ContentPath.c_str(); }
	static wstring GetRelativePath(const wstring& _AbsolutePath);

public:
	static void init();

};

