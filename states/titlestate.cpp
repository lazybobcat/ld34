#include <states/titlestate.hpp>
#include <utils.hpp>

float titleStateDuration = 3.5f;

TitleState::TitleState(StateStack &stack, Context context) :
    State(stack, context),
    mTitle(),
    mTitleOpacity(0),
    mTextEffectTime(sf::Time::Zero)
{
    mSceneTexture.create(context.window->getSize().x, context.window->getSize().y);

    mTitle.setFont(context.fonts->get(Fonts::Main));
    mTitle.setString("THRUST");
    mTitle.setCharacterSize(46);
    centerOrigin(mTitle);
    mTitle.setPosition(context.window->getView().getSize() / 2.f);

    mBackground.setTexture(context.textures->get(Textures::Background));
    mShip.setTexture(context.textures->get(Textures::Ship));
    mShip.setTextureRect(sf::IntRect(0, 50, 70, 50));
    centerOrigin(mShip);
    mShip.setPosition(sf::Vector2f(-50.f, context.window->getView().getSize().y / 2.f));
    mTrail.setTexture(context.textures->get(Textures::UiBonus));
    mTrail.setOrigin(sf::Vector2f(mTrail.getLocalBounds().width, mTrail.getLocalBounds().height/2));
    mTrail.setPosition(sf::Vector2f(-50.f - mShip.getLocalBounds().width / 2, context.window->getView().getSize().y / 2.f));

    mLogo.setTexture(context.textures->get(Textures::Logo));
    mLogo.setPosition(sf::Vector2f(100, context.window->getSize().y - 100));
    mLogoText.setFont(context.fonts->get(Fonts::Monstruosor));
    mLogoText.setString("Made by Loic Boutter - in C++ with SFML");
    mLogoText.setCharacterSize(30);
    mLogoText.setPosition(sf::Vector2f(context.window->getSize().x - 500, context.window->getSize().y - 90));
}


void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;



    if(PostEffect::isSupported())
    {
        mSceneTexture.clear();
        mSceneTexture.draw(mBackground);
        mSceneTexture.draw(mTrail);
        mSceneTexture.draw(mShip);
        mSceneTexture.draw(mTitle);
        mSceneTexture.draw(mLogo);
        mSceneTexture.draw(mLogoText);
        mSceneTexture.display();
        mBloomEffect.apply(mSceneTexture, window);
    }
    else
    {
        window.draw(mBackground);
        window.draw(mTrail);
        window.draw(mShip);
        window.draw(mTitle);
        window.draw(mLogo);
        window.draw(mLogoText);
    }
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;
    int a = (int) 255 * mTextEffectTime.asSeconds() / titleStateDuration;
    if(a > 255) a = 255;
    static float v = (1280.f + 100.f) / titleStateDuration;

    mTitle.setColor(sf::Color(255,255,255, a));
    mLogo.setColor(sf::Color(255,255,255, a));
    mLogoText.setColor(sf::Color(255,255,255, a));
    mShip.move(sf::Vector2f(v * dt.asSeconds(), 0));
    mTrail.move(sf::Vector2f(v * dt.asSeconds(), 0));

    if(mTextEffectTime.asSeconds() > titleStateDuration)
    {
        requestStackPop();
        requestStackPush(States::Game);
        requestStackPush(States::Howto);
    }

    return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    /*if(event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Game);
        requestStackPush(States::Howto);
    }*/

    return false;
}
