#include <application.hpp>
#include <utils.hpp>
#include <states/titlestate.hpp>
#include <states/gamestate.hpp>
#include <states/pausestate.hpp>
#include <states/highscoresstate.hpp>
#include <states/howtostate.hpp>

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application(unsigned int width, unsigned int height, const std::string &title) :
    mWindow(sf::VideoMode(width,height), title.c_str(), sf::Style::Close),
    mTextures(),
    mFonts(),
    mSounds(),
    mMusic(),
    mScripts(),
    mPlayer(),
    mStateStack(State::Context(mWindow, mTextures, mFonts, mSounds, mMusic, mScripts, mPlayer)),
    mStatisticsText(),
    mStatisticsUpdateTime(),
    mStatisticsNumFrames(0)
{
    mWindow.setKeyRepeatEnabled(false);

    // Resources
    mFonts.load(Fonts::Main, "assets/fonts/sansation.ttf");
    mFonts.load(Fonts::Monstruosor, "assets/fonts/monstruosor.ttf");
    mTextures.load(Textures::Background, "assets/textures/background.png");
    mTextures.load(Textures::Crate, "assets/textures/crate.png");
    mTextures.load(Textures::Particle, "assets/textures/particle.png");
    mTextures.load(Textures::Shield, "assets/textures/shield.png");
    mTextures.load(Textures::Ship, "assets/textures/ship.png");
    mTextures.load(Textures::Trail, "assets/textures/trail.png");
    mTextures.load(Textures::UiBonus, "assets/textures/ui-bonus.png");
    mTextures.load(Textures::UiButton, "assets/textures/ui-button.png");
    mTextures.load(Textures::UiHighscore, "assets/textures/ui-highscores.png");
    mTextures.load(Textures::UiHowto, "assets/textures/ui-howto.png");
    mTextures.load(Textures::UiNext, "assets/textures/ui-next.png");
    mTextures.load(Textures::UiScore, "assets/textures/ui-score.png");
    mTextures.load(Textures::UiScreen, "assets/textures/ui-screen.png");
    mTextures.load(Textures::Wall, "assets/textures/wall.png");
    mTextures.load(Textures::Logo, "assets/textures/logo_monstruosor.png");
    //mScripts.registerFile(Scripts::HelloWorld, "assets/scripts/helloworld.lua");

    mStatisticsText.setFont(mFonts.get(Fonts::Main));
    mStatisticsText.setPosition(5.f,5.f);
    mStatisticsText.setCharacterSize(10);

    registerStates();
    mStateStack.pushState(States::Title);
}



void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);

            // Check inside this loop, because stack might be empty before update() call
            if (mStateStack.isEmpty())
                mWindow.close();
        }

        updateStatistics(elapsedTime);
        render();
    }
}

void Application::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);
        if(event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::render()
{
    mWindow.clear();
    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    //mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<HighscoresState>(States::Highscores);
    mStateStack.registerState<HowtoState>(States::Howto);
    /*mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<LoadingState>(States::Loading);
    mStateStack.registerState<GameOverState>(States::GameOver);*/
}

void Application::updateStatistics(sf::Time elapsedTime)
{
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if(mStatisticsUpdateTime >= sf::seconds(1.f))
    {
        mStatisticsText.setString(
                    "Frames/sec = " + toString(mStatisticsNumFrames) + "\n" +
                    "Time/update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us"
        );

        mStatisticsNumFrames = 0;
        mStatisticsUpdateTime -= sf::seconds(1.f);
    }
}
