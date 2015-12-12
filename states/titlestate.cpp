#include <states/titlestate.hpp>
#include <utils.hpp>

float titleStateDuration = 3.5f;

TitleState::TitleState(StateStack &stack, Context context) :
    State(stack, context),
    mTitle(),
    mTitleOpacity(0),
    mTextEffectTime(sf::Time::Zero)
{
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
}


void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackground);
    window.draw(mTrail);
    window.draw(mShip);
    window.draw(mTitle);
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;
    int a = (int) 255 * mTextEffectTime.asSeconds() / titleStateDuration;
    if(a > 255) a = 255;
    static float v = (1280.f + 100.f) / titleStateDuration;

    mTitle.setColor(sf::Color(255,255,255, a));
    mShip.move(sf::Vector2f(v * dt.asSeconds(), 0));
    mTrail.move(sf::Vector2f(v * dt.asSeconds(), 0));

    if(mTextEffectTime.asSeconds() > titleStateDuration)
    {
        requestStackPop();
        //requestStackPush(States::Menu);
    }

    return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    return true;
}
