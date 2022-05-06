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

    UINT            m_iFPS; // Frame per Second �ʴ� ������

    float           m_fDT;          // delta time (1 �����ӿ� �ɸ� �ð�)
    float           m_fFixedDT;     // TimeScale�� ������ �޴� DT
    float           m_fTimeScale;   // 0.f ~ 1.f DT ����

    float           m_fAddTime;
    float           m_fCurTime;

    bool            m_bPause;

public:
    void    init();
    void    update();

public:
    float   GetDT() { return m_fFixedDT; }
    float   GetCurTime() { return m_fCurTime; }
    float   GetTimeScale() { return m_fTimeScale; }

    void    SetTimeScale(float _fTimeScale) { m_fTimeScale = m_bPause ? 0 :_fTimeScale; }

public:
    void Pause()
    {
        if (!m_bPause)
        {
            m_bPause = true;
            m_fTimeScale = 0;
        }
    }
    void Play()
    {
        if (m_bPause)
        {
            m_bPause = false;
            m_fTimeScale = 1;
        }
    }
    
    bool IsPaused() { return m_bPause; }
};

