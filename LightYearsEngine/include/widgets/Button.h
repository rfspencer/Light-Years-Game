#pragma once

#include "widgets/Widget.h"
#include "framework/Delegate.h"

namespace ly
{
    class Button : public Widget
    {
    public:
        Button(const std::string& textSTring = "Button", const std::string& buttonTexturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");
        sf::FloatRect GetBound() const override;
        void SetTextString(const std::string& newString);
        void SetTextCharacterSize(unsigned int characterSize);

        bool HandleEvent(const sf::Event& windowEvent) override;
        Delegate<> onButtonClicked;

    private:
        void Draw(sf::RenderWindow &windowRef) override;
        void LocationUpdated(const sf::Vector2f &newLocation) override;
        void RotationUpdated(float newRotation) override;
        void CenterText();

        shared<sf::Texture> mButtonTexture;
        sf::Sprite mButtonSprite;

        shared<sf::Font> mButtonFont;
        sf::Text mButtonText;

        sf::Color mButtonDefaultColor;
        sf::Color mButtonDownColor;
        sf::Color mButtonHoverColor;

        bool mIsButtonDown;

        void ButtonUp();
        void ButtonDown();
        void MouseHovered();
    };
}