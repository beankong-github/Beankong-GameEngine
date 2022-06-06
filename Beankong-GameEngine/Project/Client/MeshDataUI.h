#pragma once
#include "ResInfoUI.h"
class MeshDataUI :
    public ResInfoUI
{
private:

public:
    virtual void update() override;
    virtual void render_update() override;

public:
    MeshDataUI();
    ~MeshDataUI();
};

