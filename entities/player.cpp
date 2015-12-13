#include <entities/player.hpp>

sf::FloatRect shipCollisionRect = sf::FloatRect(0.f, 5.f, 50.f, 40.f);

Player::Player(TextureHolder &textures) :
    Entity(100),
    mDirection(Straight),
    mSpeed(360.f),
    mDefaultSprite(textures.get(Textures::Ship), sf::IntRect(0, 50, 70, 50)),
    mDownSprite(textures.get(Textures::Ship), sf::IntRect(0, 100, 70, 50)),
    mUpSprite(textures.get(Textures::Ship), sf::IntRect(0, 0, 70, 50)),
    mEmitter(nullptr),
    mTrail(nullptr)
{
    std::unique_ptr<EmitterNode> particles(new EmitterNode(Particle::Default));
    particles->setPosition(mDefaultSprite.getGlobalBounds().width / 2, mDefaultSprite.getGlobalBounds().height / 2);
    mEmitter = particles.get();
    attachChild(std::move(particles));

    std::unique_ptr<SpriteNode> trail(new SpriteNode(textures.get(Textures::UiBonus)));
    trail->setOrigin(sf::Vector2f(115.f, 14.f));
    trail->setPosition(sf::Vector2f(0, mDefaultSprite.getGlobalBounds().height / 2));
    mTrail = trail.get();
    attachChild(std::move(trail));
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

void Player::destroy()
{
    if(!isDestroyed())
    {
        if(mEmitter) mEmitter->emitExposionParticles();
        if(mTrail)
        {
            detachChild(*mTrail);
            mTrail = nullptr;
        }
    }

    Entity::destroy();
}

void Player::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    if(isDestroyed()) return;

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
    if(isDestroyed()) return;

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
