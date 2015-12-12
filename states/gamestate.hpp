#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <states/state.hpp>
#include <world.hpp>
#include <controllers/playercontroller.hpp>

class GameState : public State
{
public:
    GameState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);

private:
    PlayerController& mPlayer;
    World             mWorld;

    bool              mIsGameOver;
    sf::Time          mGameOverTimer;
};

#endif // GAMESTATE_HPP
