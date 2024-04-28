#include "pch.h"
#include "CAnimator2D.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAnim.h"
#include "CTransform.h"

CAnimator2D::CAnimator2D()
	: CComponent(COMPONENT_TYPE::ANIMATOR2D)
{

}

CAnimator2D::CAnimator2D(const CAnimator2D& _OriginAnimator)
	: CComponent(_OriginAnimator)
	, m_CurAnim(nullptr)
	, m_bRepeat(_OriginAnimator.m_bRepeat)
{
	map<wstring, CAnim*>::const_iterator iter = _OriginAnimator.m_mapAnim.begin();
	for (; iter != _OriginAnimator.m_mapAnim.end(); ++iter)
	{
		CAnim* pCloneAnim = iter->second->Clone();

		pCloneAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(iter->first, pCloneAnim));
	}

	if (nullptr != _OriginAnimator.m_CurAnim)
	{
		m_CurAnim = FindAnim(_OriginAnimator.m_CurAnim->GetName());
	}
}

CAnimator2D::~CAnimator2D()
{
	Delete_Map(m_mapAnim);
}

bool CAnimator2D::IsCurAnimFinished()
{
	return m_CurAnim->IsFinish();
}

int CAnimator2D::GetCurAnimFrame()
{
	return m_CurAnim->GetCurAnimIdx();
}

int CAnimator2D::GetPrevAnimFrame()
{
	return m_CurAnim->GetPrevAnimIdx();
}

int CAnimator2D::DeleteAnim(const wstring& _AnimationKey)
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	if (LEVEL_STATE::PLAY == CurLevel->GetState())
	{
		return E_FAIL;
	}

	CAnim* SelectedAnim = FindAnim(_AnimationKey);
	if (nullptr == SelectedAnim)
	{
		MessageBox(nullptr, L"애니메이션이 존재하지 않습니다.", L"Animation Delete Failed", MB_OK);
		return E_FAIL;
	}

	delete SelectedAnim;
	m_mapAnim.erase(_AnimationKey);

	return S_OK;
}

void CAnimator2D::AddAnimation(CAnim* _Anim)
{
	_Anim->m_Animator = this;
	m_mapAnim.insert(make_pair(_Anim->GetName(), _Anim));
}

wstring CAnimator2D::GetCurAnim()
{
	wstring CurAnimName = L"";

	if (m_CurAnim)
		CurAnimName = m_CurAnim->GetName();


	return CurAnimName;
}

void CAnimator2D::finaltick()
{
	if (nullptr == m_CurAnim)
		return;

	if (m_CurAnim->IsFinish() && m_bRepeat)
	{
		m_CurAnim->Reset();
	}

	m_CurAnim->finaltick();
}

void CAnimator2D::UpdateData()
{
	if (nullptr == m_CurAnim)
		return;

	m_CurAnim->UpdateData();
}

void CAnimator2D::Clear()
{
	CAnim::Clear();
}

void CAnimator2D::Create(const wstring& _strKey, Ptr<CTexture> _AtlasTex, Vec2 _LeftTop, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS)
{
	CAnim* pAnim = FindAnim(_strKey);
	assert(!pAnim);


	if (_AtlasTex == nullptr)
	{
		MessageBox(nullptr, L"애니메이션의 아틀라스가 존재하지 않습니다.", L"Animation Create Failed", MB_OK);
		return;
	}

	pAnim = new CAnim;
	pAnim->Create(this, _AtlasTex, _LeftTop, _vSliceSize, _OffsetSize, _Background, _FrmCount, _FPS);
	pAnim->SetName(_strKey);
	m_mapAnim.insert(make_pair(_strKey, pAnim));
}

CAnim* CAnimator2D::FindAnim(const wstring& _strKey)
{
	map<wstring, CAnim*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator2D::Play(const wstring& _strAnimName, bool _bRepeat)
{
	CAnim* pAnim = FindAnim(_strAnimName);
	if (nullptr == pAnim)
		return;

	m_bRepeat = _bRepeat;

	m_CurAnim = pAnim;
	m_CurAnim->Reset();

	// 새로 생긴 애니메이션의 크기에 맞게 트랜스폼 정보를 업데이트
	Vec2 FrmSize = m_CurAnim->m_vecFrm[m_CurAnim->m_CurFrmIdx].vSlice;
	FrmSize.x = FrmSize.x * m_CurAnim->m_AtlasTex->GetWidth();
	FrmSize.y = FrmSize.y * m_CurAnim->m_AtlasTex->GetHeight();

	Transform()->SetRelativeScale(Vec3(FrmSize.x, FrmSize.y, 1));
}

void CAnimator2D::SaveToFile(FILE* _File)
{
	// 애니메이션 개수 저장
	size_t AnimCount = m_mapAnim.size();
	fwrite(&AnimCount, sizeof(size_t), 1, _File);

	for (const auto& pair : m_mapAnim)
	{
		pair.second->SaveToFile(_File);
	}

	// 플레이 중이던 애니메이션의 키를 저장한다.
	wstring PlayAnimName;

	if (nullptr != m_CurAnim)
	{
		PlayAnimName = m_CurAnim->GetName();
	}

	SaveWString(PlayAnimName, _File);
	fwrite(&m_bRepeat, sizeof(bool), 1, _File);
}

void CAnimator2D::LoadFromFile(FILE* _File)
{
	// 애니메이션 개수 로드
	size_t AnimCount = 0;
	fread(&AnimCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < AnimCount; ++i)
	{
		CAnim* pAnim = new CAnim;
		pAnim->LoadFromFile(_File);

		pAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
	}

	// 플레이 중이던 애니메이션의 키를 불러온다
	wstring PlayAnimName;
	LoadWString(PlayAnimName, _File);

	if (!PlayAnimName.empty())
	{
		m_CurAnim = FindAnim(PlayAnimName);
	}

	fread(&m_bRepeat, sizeof(bool), 1, _File);
}