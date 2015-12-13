#include <entities/uiscore.hpp>
#include <utils.hpp>

UiScore::UiScore(TextureHolder& textures, FontHolder& fonts, unsigned int& points) :
    mPoints(points)
{
    mBackground.setTexture(textures.get(Textures::UiScore));
    mBackground.setOrigin(sf::Vector2f(mBackground.getGlobalBounds().width, mBackground.getGlobalBounds().height / 2));

    mText.setFont(fonts.get(Fonts::Main));
    mText.setCharacterSize(18);
    mText.setString(toString(mPoints));
    mText.setOrigin(mText.getGlobalBounds().width, mText.getGlobalBounds().height / 2);
    mText.setPosition(-10.f, -5.f);
}


void UiScore::updateCurrent(sf::Time /*dt*/, CommandQueue &/*commands*/)
{
    mText.setString(toString(mPoints));
    mText.setOrigin(mText.getGlobalBounds().width, mText.getGlobalBounds().height / 2);
    mText.setPosition(-10.f, -5.f);
}

void UiScore::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mBackground, states);
    target.draw(mText, states);
}
