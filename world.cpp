#include <world.hpp>


////////////////////////////////////////////////////

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    if(type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if(type1 & category2 && type2 & category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }

    return false;
}

////////////////////////////////////////////////////


World::World(sf::RenderWindow& window, TextureHolder &textures, FontHolder &fonts, MusicPlayer &music, SoundPlayer &sounds, ScriptPlayer &scripts, PlayerController &player) :
    mWindow(window),
    mWorldView(window.getDefaultView()),
    mTextures(textures),
    mFonts(fonts),
    mMusic(music),
    mSounds(sounds),
    mScripts(scripts),
    mPlayer(player),
    mSceneGraph(),
    mSceneLayers(),
    mSpeed(360.f)
{
    loadTextures();
    buildScene();

    // Other things here, like setting the view center on the player, scores, etc...
    std::unique_ptr<SoundNode> sound(new SoundNode(sounds));
    mSceneGraph.attachChild(std::move(sound));
}


void World::loadTextures()
{
    //mTextures.load(Textures::MyTextureIDHere, "assets/textures/whatever.png");
}

void World::buildScene()
{
    mSceneTexture.create(mWindow.getSize().x, mWindow.getSize().y);

    // Initialize layers
    for(std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Background
    std::unique_ptr<SpriteNode> background(new SpriteNode(mTextures.get(Textures::Background)));
    mSceneLayers[Background]->attachChild(std::move(background));


    // Add particle node to the scene

    // Player
    std::unique_ptr<Player> player(new Player(mTextures));
    player->setOrigin(35, 25);
    player->setPosition(70.f, mWindow.getSize().y / 2.f);
    mPlayerEntity = player.get();
    mSceneLayers[Foreground]->attachChild(std::move(player));

    // Walls
    sf::Vector2f wallPosBottom(30 / 2.f, 720.f);
    sf::Vector2f wallPosTop(30 / 2.f, 0.f);

    std::unique_ptr<Wall> wall1(new Wall(mTextures, mSpeed));
    wall1->setOrigin(wallPosBottom);
    wall1->setPosition(1300.f, mWindow.getSize().y / 2.f - 25.f);
    mSceneLayers[Foreground]->attachChild(std::move(wall1));

    std::unique_ptr<Wall> wall2(new Wall(mTextures, mSpeed));
    wall2->setOrigin(wallPosTop);
    wall2->setPosition(1300.f, mWindow.getSize().y / 2.f + 25.f);
    mSceneLayers[Foreground]->attachChild(std::move(wall2));

    // Crates
    std::unique_ptr<Crate> crate1(new Crate(mTextures, mSpeed));
    crate1->setPosition(1370.f, mWindow.getSize().y / 2.f);
    mSceneLayers[Foreground]->attachChild(std::move(crate1));

    // ...
}

void World::update(sf::Time dt)
{
    // Game logic here

    // check if player isn't out of screen
    sf::Vector2f pos = mPlayerEntity->getPosition();
    float margin = 25.f;
    if(pos.y < margin)
    {
        mPlayerEntity->setPosition(sf::Vector2f(pos.x, margin));
    }
    else if(pos.y > (720 - margin))
    {
        mPlayerEntity->setPosition(sf::Vector2f(pos.x, (720 - margin)));
    }

    // Forward commands to scene
    while(!mCommandQueue.isEmpty())
    {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }

    // Handle collisions
    handleCollisions();

    // Remove useless entities
    mSceneGraph.removeWrecks();

    // Set the listener position

    mSceneGraph.update(dt, mCommandQueue);
}

void World::handleCollisions()
{
    std::set<SceneNode::Pair> collisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

    for(SceneNode::Pair pair : collisionPairs)
    {
        if (matchesCategories(pair, Category::Player, Category::Wall))
        {
            auto& player = static_cast<Player&>(*pair.first);
            auto& wall = static_cast<Wall&>(*pair.second);

            player.destroy();
        }
        else if(matchesCategories(pair, Category::Player, Category::Crate))
        {
            auto& player = static_cast<Player&>(*pair.first);
            auto& crate = static_cast<Crate&>(*pair.second);

            crate.destroy();

            // play sound
            // add points
        }
    }
}

void World::draw()
{
    if(PostEffect::isSupported())
    {
        mSceneTexture.clear();
        mSceneTexture.setView(mWorldView);
        mSceneTexture.draw(*mSceneLayers[Background]);
        mSceneTexture.draw(*mSceneLayers[Foreground]);
        mBloomEffect.apply(mSceneTexture, mWindow);
        mWindow.draw(*mSceneLayers[Ui]);
    }
    else
    {
        mWindow.setView(mWorldView);
        mWindow.draw(mSceneGraph);
    }

}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}
