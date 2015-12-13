#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include <states/state.hpp>
#include <GUI/container.hpp>
#include <GUI/button.hpp>

class PauseState : public State
{
public:
    PauseState(StateStack& stack, Context context);
    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event &event);

private:
    sf::Text            mTitle;
    sf::Sprite          mBackground;
    GUI::Container      mContainer;

};

#endif // PAUSESTATE_HPP
