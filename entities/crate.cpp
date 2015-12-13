#include <entities/crate.hpp>

Crate::Crate(TextureHolder &textures, float &speed) :
    Entity(100),
    mSpeed(speed),
    mSprite(textures.get(Textures::Crate)),
    mEmitter(nullptr)
{
    sf::Vector2f origin(mSprite.getGlobalBounds().width / 2.f, mSprite.getGlobalBounds().height / 2.f);
    setOrigin(origin);

    std::unique_ptr<EmitterNode> particles(new EmitterNode(Particle::Default));
    particles->setPosition(origin);
    mEmitter = particles.get();
    attachChild(std::move(particles));
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
    if(!isDestroyed()) target.draw(mSprite, states);

    /*sf::FloatRect bound(mSprite.getGlobalBounds());
    sf::RectangleShape shape(sf::Vector2f(bound.width, bound.height));
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1.f);
    shape.setFillColor(sf::Color(255,255,255, 0));
    shape.setPosition(bound.left, bound.top);
    target.draw(shape, states);*/
}

void Crate::destroy()
{
    if(!isDestroyed()) mEmitter->emitCrateParticles();

    Entity::destroy();
}

bool Crate::isMarkedForRemoval() const
{
    return getPosition().x < (-(1.6f * mSpeed));
}
