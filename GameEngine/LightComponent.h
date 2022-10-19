#pragma once
#include "Component.h"

class LightComponent :
    public Component
{
    
    public:
        LightComponent(int controlKey, int updateOrder = 100);

        ~LightComponent();

        virtual void update(const float& deltaTime) override;

    protected:

        int controlKey;
       
        bool KeyDown = false;

        static int lightIndex = 0;
};


