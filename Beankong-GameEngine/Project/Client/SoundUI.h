#pragma once
#include "ResInfoUI.h"
class SoundUI :
    public ResInfoUI
{
private:

public:
    virtual void update() override;
    virtual void render_update() override;

public:
    SoundUI();
    ~SoundUI();
};

