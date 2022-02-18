#pragma once
#include "TextObject.h"
namespace dae
{
    class FPSCounter final : public TextObject
    {
    public:
        void Update() override;
    private:
    };
}

