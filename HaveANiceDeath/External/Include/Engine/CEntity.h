#pragma once

class CEntity
{
private:
	static UINT g_NextID;

private:
	const UINT	m_ID;
	wstring		m_Name;

public:
	UINT GetID() const { return m_ID; }
	const wstring& GetName() const { return m_Name; }

	void SetName(const wstring& _strName) { m_Name = _strName; }


	virtual CEntity* Clone() = 0;
public:
	CEntity();
	CEntity(const CEntity& _Origin);
	virtual ~CEntity();
};