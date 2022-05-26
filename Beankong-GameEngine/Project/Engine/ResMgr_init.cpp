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
	// ���� �Է� ���� (Input Layout ����)
	UINT iOffset = 0;
	D3D11_INPUT_ELEMENT_DESC tInputDesc = {};

	tInputDesc.SemanticName = "POSITION";	// Semantic �̸�
	tInputDesc.SemanticIndex = 0;			// �ߺ� �̸��� ��� �ε����� ����
	tInputDesc.InputSlot = 0;
	tInputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tInputDesc.InstanceDataStepRate = 0;
	tInputDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
	tInputDesc.AlignedByteOffset = iOffset;	// Vertex�� ���� �ּҷκ��� �ش� ������ �ִ� ��ġ(in bytes)
	iOffset += 12;	// Vec3 ũ��

	CGraphicsShader::AddInputLayout(tInputDesc);

	tInputDesc.SemanticName = "COLOR";
	tInputDesc.SemanticIndex = 0;
	tInputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tInputDesc.InstanceDataStepRate = 0;
	tInputDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	tInputDesc.AlignedByteOffset = iOffset;
	iOffset += 16;	// Vec4 ũ��

	CGraphicsShader::AddInputLayout(tInputDesc);

	tInputDesc.SemanticName = "TEXCOORD";
	tInputDesc.SemanticIndex = 0;
	tInputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tInputDesc.InstanceDataStepRate = 0;
	tInputDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
	tInputDesc.AlignedByteOffset = iOffset;
	iOffset += 8;	// Vec2 ũ��

	CGraphicsShader::AddInputLayout(tInputDesc);
}