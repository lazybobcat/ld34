#include <entities/wall.hpp>

Wall::Wall(TextureHolder &textures, float &speed) :
    Entity(100),
    mSpeed(speed),
    mSprite(textures.get(Textures::Wall))
{

}


sf::FloatRect Wall::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Wall::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    move(sf::Vector2f(-dt.asSeconds() * mSpeed, 0.f));

    Entity::updateCurrent(dt, commands);
}

void Wall::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
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

bool Wall::isMarkedForRemoval() const
{
    return getPosition().x < (0.f - mSprite.getGlobalBounds().width);
}
