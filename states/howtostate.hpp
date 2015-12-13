#ifndef HOWTOSTATE_HPP
#define HOWTOSTATE_HPP

#include <SFML/Graphics.hpp>
#include <resources/bloomeffect.hpp>
#include <states/state.hpp>
#include <array>

class HowtoState : public State
{
public:
    enum Helpmsgs
    {
        HelpWalls,
        HelpCrates,
        HelpScore
    };

public:
    HowtoState(StateStack& stack, Context context);
    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event &event);

private:
    std::array<sf::Text, 3> mHelps;
    sf::Text                mStartText;
    sf::Sprite              mBackground;
    bool                    mShowText;
    sf::Time                mTextEffectTime;

    sf::RenderTexture       mSceneTexture;
    BloomEffect             mBloomEffect;

};

#endif // HOWTOSTATE_HPP
