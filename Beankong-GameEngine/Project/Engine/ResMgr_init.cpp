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

	// ============
	//	POINT MESH
	// ============
	// 1. ���� ����
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);
	vecIdx.push_back(0);

	// 2. �޽� ����
	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes<CMesh>(L"PointMesh", pMesh);
	vecVtx.clear();
	vecIdx.clear();

	// =============
	//	 RECT MESH
	//	  0 --- 1
	//	  |  \  |
	//	  3 --- 2
	// =============
	// 1. ���� ����
	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(1.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(0.f, 1.f);
	vecVtx.push_back(v);

	// 2-1. �Ϲ����� �簢�� �޽� ����
	vecIdx.push_back(0); vecIdx.push_back(2); vecIdx.push_back(3);
	vecIdx.push_back(0); vecIdx.push_back(1); vecIdx.push_back(2);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes<CMesh>(L"RectMesh", pMesh);
	vecIdx.clear();

	// 2-2. �ܰ����� �������ϴ� �簢�� �޽� ����
	vecIdx.push_back(0); vecIdx.push_back(1); vecIdx.push_back(2); vecIdx.push_back(3); vecIdx.push_back(0);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes<CMesh>(L"RectMesh_LineStrip", pMesh);
	vecVtx.clear(); vecIdx.clear();

	// =============
	//	CIRCLE MESH
	// =============
}

void ResMgr::CreateEngineShader()
{
	MakeInputLayoutInfo();

	CGraphicsShader* pShader = nullptr;
	
	// 

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

Ptr<CTexture> ResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight, DXGI_FORMAT _format, UINT _flag, bool _bEngineRes)
{
	return Ptr<CTexture>();
}

`Ptr<CTexture> ResMgr::CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _pTex2D, bool _bEngineRes)
{
	return Ptr<CTexture>();
}
