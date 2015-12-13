#ifndef UIBONUS_HPP
#define UIBONUS_HPP

#include <entities/scenenode.hpp>
#include <resources/resourceidentifiers.hpp>
#include <resources/resourceholder.hpp>

class UiBonus : public SceneNode
{
public:
    UiBonus(TextureHolder& textures, FontHolder& fonts);

    void        activate();
    bool        isActive() const;

private:
    virtual void    updateCurrent(sf::Time dt, CommandQueue &commands);
    virtual void    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Time        mBonusTimer;
    sf::Text        mText;
    sf::Sprite      mBackground;
};

#endif // UIBONUS_HPP
