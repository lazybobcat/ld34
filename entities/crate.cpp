#include <entities/crate.hpp>

Crate::Crate(TextureHolder &textures, float &speed) :
    Entity(100),
    mSpeed(speed),
    mSprite(textures.get(Textures::Crate))
{
    setOrigin(mSprite.getGlobalBounds().width / 2.f, mSprite.getGlobalBounds().height / 2.f);
}

sf::FloatRect Crate::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Crate::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    move(sf::Vector2f(-dt.asSeconds() * mSpeed, 0.f));
    rotate(2);

    Entity::updateCurrent(dt, commands);
}

void Crate::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);

    /*sf::FloatRect bound(mSprite.getGlobalBounds());
    sf::RectangleShape shape(sf::Vector2f(bound.width, bound.height));
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1.f);
    shape.setFillColor(sf::Color(255,255,255, 0));
    shape.setPosition(bound.left, bound.top);
    target.draw(shape, states);*/
}

bool Crate::isMarkedForRemoval() const
{
    return getPosition().x < (0.f - mSprite.getGlobalBounds().width);
}
