#pragma once
#include "Component.h"

class LightComponent :
    public Component
{
    
    public:
        LightComponent(int controlKey, int updateOrder = 100);

        ~LightComponent();

        virtual void update(const float& deltaTime) override;
        virtual void processInput() override;

        void setAmbientColor(vec4 mat);
        void setDiffuseColor(vec4 mat);
        void setSpecularColor(vec4 mat);
        void setEnabled(bool on);
        void setAttenuation(vec3 factor);
        bool getEnabled();

        //spot
        void setSpotCutoffCos(float cutoffCos);
        void setSpotDirection(glm::vec3 spotDirect);

    protected:

        int controlKey;
       
        bool KeyDown = false;

        int lightIndex;
};


