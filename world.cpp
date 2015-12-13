#include <world.hpp>
#include <math.h>
#include <utils.hpp>

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

int pointsForCrate(bool bonusActive = false)
{
    int points = 10;

    if(bonusActive)
    {
        return points * 2;
    }

    return points;
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
    mBonus(nullptr),
    mSceneGraph(),
    mSceneLayers(),
    mSpeed(360.f),
    mPoints(0)
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
    std::unique_ptr<ParticleNode> pnode(new ParticleNode(Particle::Default, mTextures));
    pnode->addAffector([](Particle &p, sf::Time dt) {
        p.position.x += 300.f * std::cos(p.direction * 2 * 3.1416f / 360.f) * dt.asSeconds();
        p.position.y += 300.f * std::sin(p.direction * 2 * 3.1416f / 360.f) * dt.asSeconds();
    });
    pnode->addAffector([](Particle &p, sf::Time dt) {
        if(p.color.a > 0) {
            p.color.a = p.color.a - 1;
        }
    });
    mSceneLayers[Foreground]->attachChild(std::move(pnode));

    // DoorTrigger
    std::unique_ptr<DoorTrigger> trigger(new DoorTrigger());
    trigger->setPosition(-50.f, 0);
    mSceneLayers[Foreground]->attachChild(std::move(trigger));

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
    wall1->setPosition(100 + mWindow.getSize().x / 2, mWindow.getSize().y / 2.f - 50.f);
    mSceneLayers[Foreground]->attachChild(std::move(wall1));

    std::unique_ptr<Wall> wall2(new Wall(mTextures, mSpeed));
    wall2->setOrigin(wallPosTop);
    wall2->setPosition(100 + mWindow.getSize().x / 2, mWindow.getSize().y / 2.f + 50.f);
    mSceneLayers[Foreground]->attachChild(std::move(wall2));

    std::unique_ptr<Wall> wall3(new Wall(mTextures, mSpeed));
    wall3->setOrigin(wallPosBottom);
    wall3->setPosition(100.f + mWindow.getSize().x, mWindow.getSize().y / 2.f - 50.f);
    mSceneLayers[Foreground]->attachChild(std::move(wall3));

    std::unique_ptr<Wall> wall4(new Wall(mTextures, mSpeed));
    wall4->setOrigin(wallPosTop);
    wall4->setPosition(100.f + mWindow.getSize().x, mWindow.getSize().y / 2.f + 50.f);
    mSceneLayers[Foreground]->attachChild(std::move(wall4));


    // Crates
    /*std::unique_ptr<Crate> crate1(new Crate(mTextures, mSpeed));
    crate1->setPosition(1370.f, mWindow.getSize().y / 2.f);
    mSceneLayers[Foreground]->attachChild(std::move(crate1));*/

    // UI
    std::unique_ptr<UiScore> score(new UiScore(mTextures, mFonts, mPoints));
    score->setPosition(mWindow.getSize().x, 35);
    mSceneLayers[Ui]->attachChild(std::move(score));

    std::unique_ptr<UiBonus> bonus(new UiBonus(mTextures, mFonts));
    bonus->setPosition(mWindow.getSize().x, 35+30);
    mBonus = bonus.get();
    mSceneLayers[Ui]->attachChild(std::move(bonus));
}

void World::update(sf::Time dt)
{
    // Game logic here

    if(!mPlayerEntity->isDestroyed())
    {
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

    }
    else
    {
        mSpeed = 0;
    }

    mSceneGraph.update(dt, mCommandQueue);
}

void World::handleCollisions()
{
    std::set<SceneNode::Pair> collisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);
    bool ignoreNextWall = false;

    for(SceneNode::Pair pair : collisionPairs)
    {
        if (matchesCategories(pair, Category::Player, Category::Wall))
        {
            auto& player = static_cast<Player&>(*pair.first);
            auto& wall = static_cast<Wall&>(*pair.second);

            player.destroy();
        }
        else if(matchesCategories(pair, Category::DoorTrigger, Category::Wall))
        {
            auto& wall = static_cast<Wall&>(*pair.second);
            wall.destroy();

            if(!ignoreNextWall)
            {
                ignoreNextWall = true;
                spawnDoor();
                mPoints += pointsForCrate(mBonus->isActive());
            }
        }
        else if(matchesCategories(pair, Category::Player, Category::Crate))
        {
            auto& player = static_cast<Player&>(*pair.first);
            auto& crate = static_cast<Crate&>(*pair.second);

            crate.destroy();

            // play sound

            mPoints += pointsForCrate(mBonus->isActive());
            mBonus->activate();
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

#include <iostream>

void World::spawnDoor()
{
    static sf::Vector2f wallPosBottom(30 / 2.f, 720.f);
    static sf::Vector2f wallPosTop(30 / 2.f, 0.f);
    static float previous_y = mWindow.getSize().y/2.f;
    static float door_margin = 60.f;

    float player_speed = mPlayerEntity->getSpeed();
    float max_distance = ((mWindow.getSize().x / 3) / mSpeed) * player_speed;
    float min_distance = max_distance / 2;
    float border_margin = 70.f;
    sf::Vector2f door_position(1300.f, 0);

    int sign = randomInt(0, 1);
    float distance = randomFloat(min_distance, max_distance);
    if(sign == 1)
    {
        door_position.y = previous_y + distance;
    }
    else
    {
        door_position.y = previous_y - distance;
    }

    if(door_position.y > (mWindow.getSize().y - border_margin))
    {
        door_position.y = mWindow.getSize().y - border_margin;
    }
    else if(door_position.y < border_margin)
    {
        door_position.y = border_margin;
    }

    float crate_position_y = (previous_y + door_position.y) / 2;
    previous_y = door_position.y;

    std::unique_ptr<Wall> wall1(new Wall(mTextures, mSpeed));
    wall1->setOrigin(wallPosBottom);
    wall1->setPosition(door_position.x, door_position.y - door_margin);
    mSceneLayers[Foreground]->attachChild(std::move(wall1));

    std::unique_ptr<Wall> wall2(new Wall(mTextures, mSpeed));
    wall2->setOrigin(wallPosTop);
    wall2->setPosition(door_position.x, door_position.y + door_margin);
    mSceneLayers[Foreground]->attachChild(std::move(wall2));

    std::unique_ptr<Crate> crate1(new Crate(mTextures, mSpeed));
    crate1->setPosition(door_position.x + mWindow.getSize().x / 4, crate_position_y);
    mSceneLayers[Foreground]->attachChild(std::move(crate1));

    mSpeed += 5;
    if(door_margin > 40.f)
    {
        door_margin = door_margin - 1.f;
    }
}
