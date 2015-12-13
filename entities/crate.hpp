#ifndef CRATE_HPP
#define CRATE_HPP

#include <entities/entity.hpp>
#include <entities/emitternode.hpp>

class Crate : public Entity
{
public:
    Crate(TextureHolder& textures, float& speed);

    float   getSpeed() const { return mSpeed; }

    virtual bool isCollidable() const { return true; }

    virtual sf::FloatRect   getBoundingRect() const;
    virtual unsigned int    getCategory() const { return Category::Crate; }

    virtual void destroy();
    virtual bool isMarkedForRemoval() const;

protected:
    virtual void updateCurrent(sf::Time dt, CommandQueue &commands);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    float&          mSpeed;

    sf::Sprite      mSprite;

    EmitterNode*    mEmitter;
};

#endif // CRATE_HPP
