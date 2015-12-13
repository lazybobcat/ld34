#include <entities/uibonus.hpp>
#include <math.h>

float bonusTime = 5.f;

UiBonus::UiBonus(TextureHolder &textures, FontHolder &fonts)
{
    mBackground.setTexture(textures.get(Textures::UiBonus));
    mBackground.setOrigin(sf::Vector2f(mBackground.getGlobalBounds().width, mBackground.getGlobalBounds().height / 2));

    mText.setFont(fonts.get(Fonts::Main));
    mText.setCharacterSize(15);
    mText.setString("bonus");
    mText.setOrigin(mText.getGlobalBounds().width, mText.getGlobalBounds().height / 2);
    mText.setPosition(-10.f, -5.f);
}

bool UiBonus::isActive() const
{
    return (mBonusTimer > sf::Time::Zero);
}

void UiBonus::activate()
{
    mBonusTimer = sf::seconds(bonusTime);
    mBackground.setColor(sf::Color(255,255,255, 255));
}


void UiBonus::updateCurrent(sf::Time dt, CommandQueue &commands)
{
    if(mBonusTimer > sf::Time::Zero)
    {
        mBonusTimer -= dt;
        if(mBonusTimer < sf::Time::Zero)
        {
            playLocalSound(commands, Sounds::BonusEnds);
            mBonusTimer = sf::Time::Zero;
        }
        if(mBonusTimer.asSeconds() < 3.f)
        {
            mBackground.setColor(sf::Color(255,255,255, (int)(255 * ((int)(100*mBonusTimer.asSeconds()) % 100) / 100.f)));
        }
    }
}

void UiBonus::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(isActive())
    {
        target.draw(mBackground, states);
        target.draw(mText, states);
    }
}
