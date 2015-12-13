#ifndef UISCORE_HPP
#define UISCORE_HPP

#include <entities/scenenode.hpp>
#include <resources/resourceidentifiers.hpp>
#include <resources/resourceholder.hpp>


class UiScore : public SceneNode
{
public:
    UiScore(TextureHolder& textures, FontHolder& fonts, unsigned int& points);

private:
    virtual void    updateCurrent(sf::Time dt, CommandQueue &commands);
    virtual void    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    unsigned int&   mPoints;
    sf::Text        mText;
    sf::Sprite      mBackground;
};

#endif // UISCORE_HPP
