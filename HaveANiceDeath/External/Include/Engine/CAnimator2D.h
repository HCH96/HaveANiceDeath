#pragma once

#include "CComponent.h"

#include "CTexture.h"

class CAnim;


class CAnimator2D :
    public CComponent
{
private:
    map<wstring, CAnim*>    m_mapAnim;
    CAnim*                  m_CurAnim;
    bool                    m_bRepeat;

public:
    const map<wstring, CAnim*>& GetAnimations() { return m_mapAnim; }
    CAnim* GetCurAnimInst() { return m_CurAnim;}
    bool IsCurAnimFinished();

    int GetCurAnimFrame();
    int GetPrevAnimFrame();


public:
    int DeleteAnim(const wstring& _AnimationKey);
    void AddAnimation(CAnim* _Anim);



public:
    wstring GetCurAnim();

    virtual void finaltick() override;

    void UpdateData();
    static void Clear();

    // _LeftTop, _SliceSize, _Offset : Pixel Unit
    void Create(const wstring& _strKey, Ptr<CTexture> _AtlasTex, Vec2 _LeftTop, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS);

    CAnim* FindAnim(const wstring& _strAnimName);
    void Play(const wstring& _strAnimName, bool _bRepeat = true);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CAnimator2D);
    CAnimator2D();
    CAnimator2D(const CAnimator2D& _OriginAnimator);
    ~CAnimator2D();
};

