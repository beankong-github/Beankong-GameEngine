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