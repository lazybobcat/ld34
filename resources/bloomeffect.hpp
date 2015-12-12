#ifndef BLOOMEFFECT_HPP
#define BLOOMEFFECT_HPP

#include <resources/posteffect.hpp>
#include <resources/resourceidentifiers.hpp>
#include <resources/resourceholder.hpp>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>

#include <array>

class BloomEffect : public PostEffect
{
private:
    typedef std::array<sf::RenderTexture, 2> RenderTextureArray;

public:
    BloomEffect();
    ~BloomEffect();

    virtual void apply(const sf::RenderTexture &input, sf::RenderTarget &output);

private:
    void    prepareTextures(sf::Vector2u size);

    void    filterBright(const sf::RenderTexture& input, sf::RenderTexture& output);
    void    blurMultipass(RenderTextureArray& renderTextures);
    void    blur(const sf::RenderTexture& input, sf::RenderTexture& output, sf::Vector2f offsetFactor);
    void    downsample(const sf::RenderTexture& input, sf::RenderTexture& output);
    void    add(const sf::RenderTexture& source, const sf::RenderTexture& bloom, sf::RenderTarget& target);

private:
    ShaderHolder		mShaders;

    sf::RenderTexture	mBrightnessTexture;
    RenderTextureArray	mFirstPassTextures;
    RenderTextureArray	mSecondPassTextures;
};

#endif // BLOOMEFFECT_HPP
