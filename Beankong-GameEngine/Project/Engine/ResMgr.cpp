#include "pch.h"
#include "ResMgr.h"

ResMgr::ResMgr()
{}

ResMgr::~ResMgr()
{
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		Safe_Del_Map(m_Res[i]);
	}
}

void ResMgr::Init()
{}

void ResMgr::CreateEngineMesh()
{
}

void ResMgr::CreateEngineTexture()
{
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

void ResMgr::MakeInputLayoutInfo()
{
}
