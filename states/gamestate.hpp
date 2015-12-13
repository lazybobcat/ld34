#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <states/state.hpp>
#include <world.hpp>
#include <controllers/playercontroller.hpp>
#include <GUI/container.hpp>
#include <GUI/button.hpp>
#include <GUI/label.hpp>
#include <GUI/lineedit.hpp>

class GameState : public State
{
public:
    GameState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &event);

    void    sendScoreOnline();
    void    retry();
    void    displayHighscores();

private:
    PlayerController&   mPlayer;
    World               mWorld;

    bool                mIsGameOver;
    sf::Time            mGameOverTimer;

    // Game over UI
    bool                mShowGameOverGUI;
    sf::Sprite          mContainerBackground;
    GUI::Container      mContainer;
    GUI::Label*         mScoreLabel;
    GUI::LineEdit*      mNickname;
};

#endif // GAMESTATE_HPP
