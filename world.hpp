#ifndef WORLD_H
#define WORLD_H

#include <array>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <resources/resourceholder.hpp>
#include <resources/resourceidentifiers.hpp>
#include <resources/musicplayer.hpp>
#include <resources/soundplayer.hpp>
#include <resources/scriptplayer.hpp>
#include <resources/bloomeffect.hpp>
#include <controllers/playercontroller.hpp>
#include <events/category.hpp>
#include <events/commandqueue.hpp>
#include <entities/spritenode.hpp>
#include <entities/player.hpp>
#include <entities/wall.hpp>
#include <entities/crate.hpp>
#include <entities/particlenode.hpp>
#include <entities/uiscore.hpp>
#include <entities/uibonus.hpp>
#include <entities/doortrigger.hpp>

class World : public sf::NonCopyable
{
public:
    World(sf::RenderWindow& window, TextureHolder &textures, FontHolder &fonts, MusicPlayer &music, SoundPlayer &sounds, ScriptPlayer &scripts, PlayerController &player);

    void        update(sf::Time dt);
    void        draw();

    CommandQueue&   getCommandQueue();

private:
    void        loadTextures();
    void        buildScene();
    void        handleCollisions();

    void        spawnDoor();

private:
    enum Layer
    {
        Background,
        Foreground,
        Ui,
        LayerCount
    };

private:
    sf::RenderWindow&                   mWindow;
    sf::View                            mWorldView;
    sf::RenderTexture                   mSceneTexture;
    TextureHolder&                      mTextures;
    FontHolder&                         mFonts;
    MusicPlayer&                        mMusic;
    SoundPlayer&                        mSounds;
    ScriptPlayer&                       mScripts;
    PlayerController&                   mPlayer;
    Player*                             mPlayerEntity;
    UiBonus*                            mBonus;
    BloomEffect                         mBloomEffect;

    SceneNode                           mSceneGraph;
    std::array<SceneNode*,LayerCount>   mSceneLayers;
    CommandQueue                        mCommandQueue;

    float                               mSpeed;
    unsigned int                        mPoints;
};

#endif // WORLD_H
