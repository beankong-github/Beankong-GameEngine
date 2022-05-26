#include "pch.h"
#include "ResMgr.h"

#include "CMesh.h"

void ResMgr::Init()
{
	CreateEngineMesh();
	CreateEngineTexture();
	CreateEngineShader();
	CreateEngineMaterial();

	CreateEngineComputeShader();
}

void ResMgr::CreateEngineMesh()
{
	CMesh* pMesh = nullptr;

	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;

	Vtx v;

	// =============
	//	POINT MESH
	// =============
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);
	vecIdx.push_back(0);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes<CMesh>(L"PointMesh", pMesh);
	vecVtx.clear();
	vecIdx.clear();

	// =============
	//	 RECT MESH
	// =============

	// =============
	//	CIRCLE MESH
	// =============
}

void ResMgr::CreateEngineShader()
{
}

void ResMgr::CreateEngineComputeShader()
{
}

void ResMgr::CreateEngineMaterial()
{
}

void ResMgr::CreateEngineTexture()
{
}

void ResMgr::MakeInputLayoutInfo()
{
}