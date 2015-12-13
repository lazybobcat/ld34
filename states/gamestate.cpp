#include <states/gamestate.hpp>
#include <utils.hpp>

#include <SFML/Network.hpp>
#include <sstream>
#include <iostream>

GameState::GameState(StateStack &stack, Context context) :
    State(stack, context),
    mPlayer(*context.player),
    mWorld(*context.window, *context.textures, *context.fonts, *context.music, *context.sounds, *context.scripts, mPlayer),
    mIsGameOver(false),
    mShowGameOverGUI(false)
{
    context.music->play(Musics::MainTheme);
    context.music->setLoop(true);
    context.music->setVolume(10.f);

    // GUI
    mContainerBackground.setTexture(context.textures->get(Textures::UiScreen));

    GUI::Label::Ptr label_gameover = GUI::Label::Ptr(new GUI::Label("Game Over", *context.fonts));
    label_gameover->setCharSize(46);
    label_gameover->setOrigin(label_gameover->getBoundingRect().width / 2, label_gameover->getBoundingRect().height / 2);
    label_gameover->setPosition(sf::Vector2f(context.window->getSize().x / 2, 70.f));
    mScoreLabel = label_gameover.get();
    mContainer.pack(std::move(label_gameover));

    GUI::Label::Ptr label_nickname = GUI::Label::Ptr(new GUI::Label("Enter your nickname to save your score:", *context.fonts));
    label_nickname->setCharSize(22);
    label_nickname->setOrigin(label_nickname->getBoundingRect().width / 2, label_nickname->getBoundingRect().height / 2);
    label_nickname->setPosition(sf::Vector2f(context.window->getSize().x / 2, 180.f));
    mContainer.pack(std::move(label_nickname));

    GUI::LineEdit::Ptr lineedit_nickname = GUI::LineEdit::Ptr(new GUI::LineEdit(*context.fonts));
    lineedit_nickname->setSize(500, 50);
    lineedit_nickname->setOrigin(250, 25);
    lineedit_nickname->setPosition(sf::Vector2f(context.window->getSize().x / 2, 230.f));
    lineedit_nickname->setOnLostFocus([this]() {
        mContainer.selectNext();
    });
    mNickname = lineedit_nickname.get();
    mContainer.pack(std::move(lineedit_nickname));

    GUI::Button::Ptr button_validate = GUI::Button::Ptr(new GUI::Button(*context.fonts, *context.textures));
    button_validate->setText("Send score");
    button_validate->setCallback([this]() {
        sendScoreOnline();
    });
    button_validate->move(390, 300.f);
    mContainer.pack(button_validate);

    GUI::Button::Ptr button_retry = GUI::Button::Ptr(new GUI::Button(*context.fonts, *context.textures));
    button_retry->setText("Retry");
    button_retry->setCallback([this]() {
        retry();
    });
    button_retry->move(390, 350.f);
    mContainer.pack(button_retry);

    GUI::Button::Ptr button_quit = GUI::Button::Ptr(new GUI::Button(*context.fonts, *context.textures));
    button_quit->setText("Quit");
    button_quit->setCallback([this]() {
        requestStackClear();
    });
    button_quit->move(390, 400.f);
    mContainer.pack(button_quit);
}


void GameState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    if(!mShowGameOverGUI)
    {
        mWorld.draw();
    }
    else
    {
        window.draw(mContainerBackground);
        window.draw(mContainer);
    }
}


bool GameState::update(sf::Time dt)
{

    // Mission status check
    if(mWorld.getPlayerEntity() && mWorld.getPlayerEntity()->isDestroyed())
    {
        mGameOverTimer += dt;

        if(!mIsGameOver)
        {
            mIsGameOver = true;
            mScoreLabel->setText("Score: " + toString(mWorld.getScore()));
            mScoreLabel->setOrigin(mScoreLabel->getBoundingRect().width / 2, mScoreLabel->getBoundingRect().height / 2);
            mScoreLabel->setPosition(sf::Vector2f(getContext().window->getSize().x / 2, 70.f));
        }

        if(mGameOverTimer.asSeconds() >= 1.2f)
        {
            mShowGameOverGUI = true;
        }
    }

    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealtimeInput(commands);

    mWorld.update(dt);
    // If time, updte some scripted events

    return true;
}


bool GameState::handleEvent(const sf::Event &event)
{
    CommandQueue& commands = mWorld.getCommandQueue();

    if(!mShowGameOverGUI)
    {
        mPlayer.handleEvent(event, commands);

        // If ESC key is pressed, we leave
        if (event.type == sf::Event::KeyReleased)
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Escape:
                    if(!mIsGameOver) requestStackPush(States::Pause);
                    break;

                default:break;
            }
        }
        else if(event.type == sf::Event::LostFocus)
        {
            if(!mIsGameOver) requestStackPush(States::Pause);
        }
    }
    else
    {
        mContainer.handleEvent(event);
    }

    return true;
}


void GameState::sendScoreOnline()
{
    sf::Http http;
    http.setHost("http://monstruosor.com/");

    sf::Http::Request request;
    request.setMethod(sf::Http::Request::Post);
    request.setUri("/save.php");

    // encodage des paramètres dans le corps de la requête
    std::ostringstream stream;
    stream << "nickname=" << mNickname->getString() << "&score=" << mWorld.getScore();
    request.setBody(stream.str());

    sf::Http::Response response = http.sendRequest(request);
    // vérification du statut
    if(response.getStatus() == sf::Http::Response::Ok)
    {
        displayHighscores();
    }
    else
    {
        std::cout << "http request failed" << std::endl;
    }
}

void GameState::retry()
{
    requestStackClear();
    requestStackPush(States::Game);
}

void GameState::displayHighscores()
{
    requestStackClear();
    requestStackPush(States::Highscores);
}
