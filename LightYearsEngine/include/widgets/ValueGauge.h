#pragma once

#include "widgets/Widget.h"

namespace ly
{
    class ValueGauge : public Widget
    {
    public:
        ValueGauge(const sf::Vector2f& size = sf::Vector2f{300.f, 40.f},
                   float initialPercent = 0.75,
                   const sf::Color& foregroundColor = sf::Color{128, 255, 128, 255},
                   const sf::Color& backgrouncColor = sf::Color{128, 128, 128, 255});

        void UpdateValue(float value, float maxValue);

    private:
        void Draw(sf::RenderWindow &windowRef) override;
        void LocationUpdated(const sf::Vector2f& newLocation) override;
        void RotationUpdated(float newRotation) override;

        shared<sf::Font> mTextFont;
        sf::Text mText;

        sf::RectangleShape mBarFront;
        sf::RectangleShape mBarBack;

        float mPercent;

        sf::Color mForegroundColor;
        sf::Color mBackgroundColor;
    };
}
