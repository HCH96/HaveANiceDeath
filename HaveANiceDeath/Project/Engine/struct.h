#pragma once


// 3���� ������ ��ġ�Ǵ� ����
struct Vtx
{
	Vec3 vPos;		 // ������ ��ǥ	
	Vec4 vColor;	 // ������ ���� ����
	Vec2 vUV;		 // UV ��ǥ�� or Texture Coodinate
};

// Debug ShapeInfo
struct tDebugShapeInfo
{
	DEBUG_SHAPE	eShape;

	Vec3		vWorldPos;
	Vec3		vWorldScale;
	Vec3		vWorldRot;
	Matrix		matWorld;

	Vec3		vColor;
	float		fLifeTime;
	float		fDuration;
	bool		bDepthTest;
};

// Light ����ü
struct tLightInfo
{
	Vec4	vColor;		// ���� ����	- ������ ���� ����
	Vec4	vSpecular;	// �ݻ籤	- ������ ��ü ǥ�鿡 �ݻ�� ����
	Vec4	vAmbient;	// ȯ�汤(�ֺ���) - ������ ���ؼ� ����Ǵ� �ּ����� ��

	Vec3	vWorldPos;	// ������ ��ġ
	Vec3	vWorldDir;	// ������ ���ϴ� ����
	float	fRadius;	// ������ ���� �ݰ�, �Ÿ� ����
	float	fAngle;		// ������ ���� ����

	int		LightType;	// ���� Ÿ��

	Vec3	vPadding;
};



// ==================
// ������� ���� ����ü
// ==================

struct tTransform
{
	Matrix	matWorld;
	Matrix	matWorldInv;

	Matrix	matView;
	Matrix	matViewInv;

	Matrix	matProj;
	Matrix	matProjInv;

	Matrix	matWV;
	Matrix	matWVP;
};
extern tTransform g_Transform;

struct tMtrlConst
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matArr[4];
	int	bTex[(UINT)TEX_PARAM::END];
	int iPadding[2];
};

struct tAnimData2D
{
	Vec2 vLeftTop;
	Vec2 vSlizeSize;
	Vec2 vBackGround;
	Vec2 vOffset;
	int  UseAnim2D;
	Vec3 vPadding;
};

struct tGlobalData
{
	Vec2	g_RenderResolution;		// ������ �ػ�
	Vec2	g_NoiseTexResolution;
	float	g_dt;					// Delta Time
	float	g_time;					// ���� �ð�
	int		g_Light2DCount;			// 2D ���� ����
	int		g_Light3DCount;			// 3D ���� ����	
};
extern tGlobalData g_global;