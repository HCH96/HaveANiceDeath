#pragma once

class CGameObject;
class CAsset;

namespace GamePlayStatic
{
	void SpawnGameObject(CGameObject* _Target, int _LayerIdx);
	void DestroyGameObject(CGameObject* _Target);

	void AddAsset(CAsset* _Asset);

	// Debug Func
	void DrawDebugRect(const Matrix& _WorldMat, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);
	void DrawDebugRect(Vec3 _vWorldPos, Vec3 _vWorldScale, Vec3 _vWorldRot, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);
	void DrawDebugCircle(Vec3 _vWorldPos, float _fRadius, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);
	void DrawDebugCross(Vec3 _vWorldPos, float _fScale, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);

	void Play2DSound(const wstring& _SoundPath, int _Loop, float _Volume, bool _Overlap = true);
	void Play2DBGM(const wstring& _SoundPath, float _Volume);
}


string ToString(const wstring& _str);
wstring ToWString(const string& _str);

void SaveWString(const wstring& _str, FILE* _File);
void LoadWString(wstring& _str, FILE* _FILE);

// ===============
// Delete Function
// ===============

template<typename T, UINT SIZE>
void Delete_Array(T* (&Arr)[SIZE])
{
	for (int i = i = 0; i < SIZE; ++i)
	{
		if (nullptr != Arr[i])
		{
			delete Arr[i];
			Arr[i] = nullptr;
		}
	}
}

template<typename T>
void Delete_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
		{
			delete _vec[i];
		}
	}

	_vec.clear();
}

template<typename T1, typename T2>
void Delete_Map(map<T1, T2>& _map)
{
	for (const auto& pair : _map)
	{
		delete pair.second;
	}
	_map.clear();
}
