#ifndef DOORTRIGGER_HPP
#define DOORTRIGGER_HPP

#include <entities/scenenode.hpp>

class DoorTrigger : public SceneNode
{
public:
    DoorTrigger();

    virtual unsigned int    getCategory() const
    {
        return Category::DoorTrigger;
    }

    virtual bool            isCollidable() const
    {
        return true;
    }

    virtual sf::FloatRect   getBoundingRect() const
    {
        return sf::FloatRect(0, 0, 70.f, 720.f);
    }

};

#endif // DOORTRIGGER_HPP
