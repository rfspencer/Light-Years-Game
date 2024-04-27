#pragma once

#include <SFML/Graphics.hpp>
#include "widgets/Widget.h"

namespace ly
{
    class ImageWidget : public Widget
    {
    public:
        ImageWidget(const std::string& imagePath);

        void SetImage(const shared<sf::Texture>& newTexture);
        sf::FloatRect GetBound() const override;

    private:
        void LocationUpdated(const sf::Vector2f &newLocation) override;
        void RotationUpdated(float newRotation) override;
        void Draw(sf::RenderWindow &windowRef) override;

        shared<sf::Texture> mTexture;
        sf::Sprite mSprite;
    };
}