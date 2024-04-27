#include "widgets/Widget.h"


namespace ly
{

    Widget::Widget()
            : mIsVisible{true},
              mWidgetTransform{}
    {

    }

    void Widget::NativeDraw(sf::RenderWindow &widowRef)
    {
        if (mIsVisible)
        {
            Draw(widowRef);
        }
    }

    bool Widget::HandleEvent(const sf::Event &windowEvent)
    {
        return false;
    }

    void Widget::SetWidgetLocation(const sf::Vector2f &newLocation)
    {
        mWidgetTransform.setPosition(newLocation);
        LocationUpdated(newLocation);
    }

    void Widget::SetWidgetRotation(float newRotation)
    {
        mWidgetTransform.setRotation(newRotation);
        RotationUpdated(newRotation);
    }

    void Widget::SetVisibility(bool newVisibility)
    {
        mIsVisible = newVisibility;
    }

    sf::Vector2f Widget::GetCenterPosition() const
    {
        sf::FloatRect bound = GetBound();
        return sf::Vector2f{bound.left + bound.width / 2.f, bound.top + bound.height / 2.f};
    }

    void Widget::Draw(sf::RenderWindow &windowRef)
    {

    }

    void Widget::LocationUpdated(const sf::Vector2f &newLocation)
    {

    }

    void Widget::RotationUpdated(float newRotation)
    {

    }
}
