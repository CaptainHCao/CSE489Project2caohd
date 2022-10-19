#pragma once
#include "Component.h"
class MakeVisableComponent : public Component
{
public:
    MakeVisableComponent(int controlKey, int updateOrder = 100);

    virtual void initialize() override;

    virtual void processInput() override;

protected:
    int controlKey;

    bool KeyDown = false;
};

