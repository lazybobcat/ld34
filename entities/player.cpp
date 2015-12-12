#include <entities/player.hpp>

sf::FloatRect shipCollisionRect = sf::FloatRect(0.f, 5.f, 50.f, 40.f);

Player::Player(TextureHolder &textures) :
    Entity(100),
    mDirection(Straight),
    mSpeed(360.f),
    mDefaultSprite(textures.get(Textures::Ship), sf::IntRect(0, 50, 70, 50)),
    mDownSprite(textures.get(Textures::Ship), sf::IntRect(0, 100, 70, 50)),
    mUpSprite(textures.get(Textures::Ship), sf::IntRect(0, 0, 70, 50))
{

}

void Player::setDirection(Direction dir)
{
    mDirection = dir;
}

sf::FloatRect Player::getBoundingRect() const
{
    //return getWorldTransform().transformRect(mDefaultSprite.getGlobalBounds());
    return getWorldTransform().transformRect(shipCollisionRect);
}

void Player::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    // Update
    switch (mDirection) {
        case Up:
            move(sf::Vector2f(0.f, -dt.asSeconds() * mSpeed));
            break;

        case Down:
            move(sf::Vector2f(0.f, dt.asSeconds() * mSpeed));
            break;

        default:
            break;
    }

    Entity::updateCurrent(dt, commands);
}

void Player::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    switch(mDirection)
    {
        case Straight:
            target.draw(mDefaultSprite, states);
            break;

        case Up:
            target.draw(mUpSprite, states);
            break;

        case Down:
            target.draw(mDownSprite, states);
            break;

        default:
            target.draw(mDefaultSprite, states);
            break;
    }

    sf::FloatRect bound(shipCollisionRect);
    sf::RectangleShape shape(sf::Vector2f(bound.width, bound.height));
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1.f);
    shape.setFillColor(sf::Color(255,255,255, 0));
    shape.setPosition(bound.left, bound.top);
    target.draw(shape, states);
}
