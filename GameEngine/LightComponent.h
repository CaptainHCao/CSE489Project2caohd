#pragma once
#include "Component.h"

class LightComponent :
    public Component
{
    
    public:
        LightComponent(int controlKey, int updateOrder = 100);

        ~LightComponent();

        //Component methods
        virtual void update(const float& deltaTime) override;
        virtual void processInput() override;

        //shared mathod for all light types
        void setAmbientColor(vec4 mat);
        void setDiffuseColor(vec4 mat);
        void setSpecularColor(vec4 mat);
        void setEnabled(bool on);
        bool getEnabled();

        //atenuation
        void setAttenuationFactors(vec3 factor);
        void setConstantAttenuation(float factor);
        void setLinearAttenuation(float factor);
        void setQuadraticAttenuation(float factor);

        //spot
        void setSpotCutoffCos(float cutoffCos);
        void setSpotDirection(glm::vec3 spotDirect);
        bool getIsSpot();

    protected:

        int controlKey;
       
        bool KeyDown = false;

        int lightIndex;
};


