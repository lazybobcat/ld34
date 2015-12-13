#include <states/howtostate.hpp>
#include <utils.hpp>

HowtoState::HowtoState(StateStack &stack, Context context) :
    State(stack, context),
    mShowText(true)
{
    mSceneTexture.create(context.window->getSize().x, context.window->getSize().y);
    mBackground.setTexture(context.textures->get(Textures::UiHowto));

    mHelps[HelpWalls].setFont(context.fonts->get(Fonts::Main));
    mHelps[HelpWalls].setString("Use UP and DOWN arrows to avoid the walls you'll encounter,\nyour ship will go faster with time");
    mHelps[HelpWalls].setCharacterSize(22);
    centerOrigin(mHelps[HelpWalls]);
    mHelps[HelpWalls].setPosition(context.window->getView().getSize().x / 2.f, 95);

    mHelps[HelpCrates].setFont(context.fonts->get(Fonts::Main));
    mHelps[HelpCrates].setString("Try to collect cargo crates on the way,\nthey'll activate bonus points");
    mHelps[HelpCrates].setCharacterSize(22);
    centerOrigin(mHelps[HelpCrates]);
    mHelps[HelpCrates].setPosition(context.window->getView().getSize().x / 2.f, 305);

    mHelps[HelpScore].setFont(context.fonts->get(Fonts::Main));
    mHelps[HelpScore].setString("The farther you go, the more you collect points.\nHighscores are saved online, try to beat other players!");
    mHelps[HelpScore].setCharacterSize(22);
    centerOrigin(mHelps[HelpScore]);
    mHelps[HelpScore].setPosition(context.window->getView().getSize().x / 2.f, 505);

    mStartText.setFont(context.fonts->get(Fonts::Main));
    mStartText.setString("Press SPACE to start");
    mStartText.setCharacterSize(28);
    centerOrigin(mStartText);
    mStartText.setPosition(context.window->getView().getSize().x / 2.f, 605);
}

void HowtoState::draw()
{
    sf::RenderWindow& window = *getContext().window;


    if(PostEffect::isSupported())
    {
        mSceneTexture.clear();
        mSceneTexture.draw(mBackground);
        for(auto it = mHelps.begin(); it != mHelps.end(); ++it)
        {
            mSceneTexture.draw(*it);
        }
        if(mShowText) mSceneTexture.draw(mStartText);
        mSceneTexture.display();
        mBloomEffect.apply(mSceneTexture, window);
    }
    else
    {
        window.draw(mBackground);
        for(auto it = mHelps.begin(); it != mHelps.end(); ++it)
        {
            window.draw(*it);
        }
        if(mShowText) window.draw(mStartText);
    }
}

bool HowtoState::update(sf::Time dt)
{
    mTextEffectTime += dt;

    if (mTextEffectTime >= sf::seconds(0.55f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }

    return false;
}

bool HowtoState::handleEvent(const sf::Event& event)
{
    if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
    {
        requestStackPop();
    }

    return false;
}
