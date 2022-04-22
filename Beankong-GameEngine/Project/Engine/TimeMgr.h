#pragma once
#include "singleton.h"

class TimeMgr :
    public Singleton<TimeMgr>
{
    SINGLE(TimeMgr)

private:    
    LARGE_INTEGER   m_liFrequency;
    LARGE_INTEGER   m_liPrevCount;
    LARGE_INTEGER   m_liCurCount;

    UINT            m_iFPS; // Frame per Second 초당 프레임
    float           m_fDT;  // delta time (1 프레임에 걸린 시간)
    
    float           m_fAddTime;
    float           m_fCurTime;

public:
    void init();
    void update();

public:
    float GetDT() { return m_fDT; }
    float GetCurTime() { return m_fCurTime; }

};

