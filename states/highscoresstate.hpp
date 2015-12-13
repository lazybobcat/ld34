#ifndef HIGHSCORESSTATE_HPP
#define HIGHSCORESSTATE_HPP

#include <states/state.hpp>

class HighscoresState : public State
{
public:
    HighscoresState(StateStack& stack, Context context);
    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event &event);

private:
    sf::Text            mTitle;
    sf::Text            mContinue;
    sf::Text            mScores;
    sf::Sprite          mBackground;
};

#endif // HIGHSCORESSTATE_HPP
