#pragma once
#include "Component.h"

class LightComponent :
    public Component
{
    
    public:
        LightComponent(int controlKey, int updateOrder = 100);

        ~LightComponent();

        virtual void update(const float& deltaTime) override;

        void setAmbientColor(vec4 mat);
        void setDiffuseColor(vec4 mat);
        void setSpecularColor(vec4 mat));

    protected:

        int controlKey;
       
        bool KeyDown = false;

        int lightIndex;
};


