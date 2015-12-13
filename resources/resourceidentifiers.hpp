#ifndef RESOURCE_IDENTIFIERS_H
#define RESOURCE_IDENTIFIERS_H

// Forward declarations
namespace sf
{
    class Texture;
    class Font;
    class Shader;
    class Music;
    class SoundBuffer;
}

template <typename Resource, typename Identifier>
class ResourceHolder;



// Textures
namespace Textures
{
    enum ID
    {
        Background,
        Crate,
        Particle,
        Shield,
        Ship,
        Trail,
        UiBonus,
        UiButton,
        UiHighscore,
        UiHowto,
        UiNext,
        UiScore,
        UiScreen,
        Wall,
        Logo
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;


// Fonts
namespace Fonts
{
    enum ID
    {
        Main,
        Monstruosor
    };
}

typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;


// Shaders
namespace Shaders
{
    enum ID
    {
        BrightnessPass,
        DownSamplePass,
        GaussianBlurPass,
        AddPass
    };
}
typedef ResourceHolder<sf::Shader, Shaders::ID> ShaderHolder;


// Musics
namespace Musics
{
    enum ID
    {
        MainTheme
    };
}


// Sounds
namespace Sounds
{
    enum ID
    {
        BonusEnds,
        Explosion,
        Pickup,
        Points
    };
}
typedef ResourceHolder<sf::SoundBuffer, Sounds::ID> SoundHolder;


// Scripts
namespace Scripts
{
    enum ID
    {
        HelloWorld
    };
}



#endif // RESOURCE_IDENTIFIERS_H
