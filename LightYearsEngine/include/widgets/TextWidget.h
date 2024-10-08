#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "widgets/Widget.h"

namespace ly
{
    class TextWidget : public Widget
    {
    public:
        TextWidget(const std::string& textStr, const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf", unsigned int characterSize = 10);

        void SetString(const std::string& newStr);
        void SetTextSize(unsigned int newSize);
        sf::FloatRect GetBound() const override;

    private:
        void LocationUpdated(const sf::Vector2f& newLocation) override;
        void RotationUpdated(float newRotation) override;
        void Draw(sf::RenderWindow &windowRef) override;

        shared<sf::Font> mFont;
        sf::Text mText;
    };
}
