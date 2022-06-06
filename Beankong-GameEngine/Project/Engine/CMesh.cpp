#include "pch.h"
#include "CMesh.h"

#include "CDevice.h"

CMesh::CMesh()
	: m_tVBDesc{}
	, m_tIBDesc{}
	, m_iVtxCount(0)
	, m_iIdxCount(0)
	, m_pVtxSys(nullptr)
	, m_pIdxSys(nullptr)
{
}

CMesh::~CMesh()
{
	SAFE_DELETE(m_pVtxSys);
	SAFE_DELETE(m_pIdxSys);
}

int CMesh::Create(void* _pVtxSys, UINT _iVtxCount, void* _pIdxSys, UINT _iIdxCount)
{
	m_iVtxCount = _iVtxCount;
	m_iIdxCount = _iIdxCount;

	// ========================
	//	 Create Vertex Buffer
	// ========================
	
	// 버텍스 버퍼 크기
	m_tVBDesc.ByteWidth = sizeof(Vertex) * _iVtxCount;

	// 정점 버퍼는 처음 생성이후에 버퍼를 수정하지 않는다.
	m_tVBDesc.CPUAccessFlags = 0;
	m_tVBDesc.Usage = D3D11_USAGE_DEFAULT;

	// 버텍스 버퍼 용도 : 정점 버퍼
	m_tVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	m_tVBDesc.MiscFlags = 0;
	m_tVBDesc.StructureByteStride = 0;

	// 초기 데이터를 넘겨주기 위한 정보 구조체
	D3D11_SUBRESOURCE_DATA tSubDesc = {};
	tSubDesc.pSysMem = _pVtxSys;

	if (FAILED(DEVICE->CreateBuffer(&m_tVBDesc, &tSubDesc, m_VB.GetAddressOf())))
	{
		return E_FAIL;
	}


	// ========================
	//	 Create Index Buffer
	// ========================
	m_tIBDesc.ByteWidth = sizeof(UINT) * _iIdxCount;

	// 버퍼 생성 이후에도, 버퍼의 내용을 수정 할 수 있는 옵션
	m_tIBDesc.CPUAccessFlags = 0;
	m_tIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	// 정점을 저장하는 목적의 버퍼 임을 알림
	m_tIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	m_tIBDesc.MiscFlags = 0;
	m_tIBDesc.StructureByteStride = 0;

	// 초기 데이터를 넘겨주기 위한 정보 구조체
	tSubDesc = {};
	tSubDesc.pSysMem = _pIdxSys;

	if (FAILED(DEVICE->CreateBuffer(&m_tIBDesc, &tSubDesc, m_IB.GetAddressOf())))
	{
		return E_FAIL;
	}

	// 시스템 메모리 할당
	m_pVtxSys = new Vtx[m_iVtxCount];
	memcpy(m_pVtxSys, _pVtxSys, sizeof(Vtx) * m_iVtxCount);

	m_pIdxSys = new UINT[m_iIdxCount];
	memcpy(m_pIdxSys, _pIdxSys, sizeof(UINT) * m_iIdxCount);

	return S_OK;

}

void CMesh::Render()
{
	UpdateData();

	// 인덱싱된 도형을 그린다. 
	CONTEXT->DrawIndexed(m_iIdxCount, 0, 0);
}

void CMesh::Render_Particle(UINT _iCount)
{
	UpdateData();

	// 인덱싱된 도형을 인스턴싱하여 그린다. ( 파티클은 여러 오브젝트를 많이 그려야하므로 인스턴싱하여 그린다.)
	CONTEXT->DrawIndexedInstanced(m_iIdxCount, _iCount, 0, 0, 0);
}

void CMesh::UpdateData()
{
	UINT iStride = sizeof(Vtx);
	UINT iOffset = 0;

	// Mesh의 정점 정보가 담긴 버텍스 버퍼와 인덱스 버퍼를 DC에 세팅해둔다.
	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
}
