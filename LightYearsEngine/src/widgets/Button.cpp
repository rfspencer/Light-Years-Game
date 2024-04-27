#include "widgets/Button.h"
#include "framework/AssetManager.h"

namespace ly
{

    Button::Button(const std::string &textSTring, const std::string &buttonTexturePath)
        : mButtonTexture{AssetManager::Get().LoadTexture(buttonTexturePath)},
        mButtonSprite{*(mButtonTexture.get())},
        mButtonFont{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")},
        mButtonText{textSTring, *(mButtonFont.get())},
        mButtonDefaultColor{128, 128, 128, 255},
        mButtonDownColor{64, 64, 64, 255},
        mButtonHoverColor{190, 190, 190, 255},
        mIsButtonDown{false}
    {

    }

    sf::FloatRect Button::GetBound() const
    {
        return mButtonSprite.getGlobalBounds();
    }

    void Button::Draw(sf::RenderWindow &windowRef)
    {
        windowRef.draw(mButtonSprite);
        windowRef.draw(mButtonText);
    }

    void Button::LocationUpdated(const sf::Vector2f &newLocation)
    {
        mButtonSprite.setPosition(newLocation);
        mButtonText.setPosition(newLocation);
    }

    void Button::RotationUpdated(float newRotation)
    {
        mButtonSprite.setRotation(newRotation);
        mButtonText.setRotation(newRotation);
    }
}