#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <entities/entity.hpp>
#include <entities/emitternode.hpp>
#include <entities/spritenode.hpp>

class Player : public Entity
{
public:
    enum Direction
    {
        Up,
        Straight,
        Down
    };

public:
    Player(TextureHolder& textures);

    void    setDirection(Direction dir);
    float   getSpeed() const { return mSpeed; }

    virtual bool isCollidable() const { return true; }

    virtual sf::FloatRect   getBoundingRect() const;
    virtual unsigned int    getCategory() const { return Category::Player; }

    virtual void destroy();
    virtual bool isMarkedForRemoval() const { return false; }

protected:
    virtual void updateCurrent(sf::Time dt, CommandQueue &commands);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    Direction       mDirection;
    float           mSpeed;

    sf::Sprite      mDefaultSprite;
    sf::Sprite      mDownSprite;
    sf::Sprite      mUpSprite;

    EmitterNode*    mEmitter;
    EmitterNode*    mTrailEmitter;
    SpriteNode*     mTrail;
};

#endif // PLAYER_HPP
