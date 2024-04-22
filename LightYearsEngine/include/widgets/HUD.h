#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Object.h"

namespace ly
{
    class HUD : public Object
    {
    public:
        virtual void Draw(sf::RenderWindow& windowRef) = 0;
        void NativeInit(const sf::RenderWindow& windowRef);

        bool HasInit() const { return mAlreadyInit; }

        virtual bool HandleEvent(const sf::Event& event);

    protected:
        HUD();

    private:
        virtual void Init(const sf::RenderWindow& windowRef);

        bool mAlreadyInit;

    };
}