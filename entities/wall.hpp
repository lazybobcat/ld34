#ifndef WALL_HPP
#define WALL_HPP

#include <entities/entity.hpp>

class Wall : public Entity
{
public:
    Wall(TextureHolder& textures, float& speed);

    float   getSpeed() const { return mSpeed; }

    virtual bool isCollidable() const { return true; }

    virtual sf::FloatRect   getBoundingRect() const;
    virtual unsigned int    getCategory() const { return Category::Wall; }

    virtual bool isMarkedForRemoval() const;

protected:
    virtual void updateCurrent(sf::Time dt, CommandQueue &commands);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    float&          mSpeed;

    sf::Sprite      mSprite;
};

#endif // WALL_HPP
