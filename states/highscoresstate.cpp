#include <states/highscoresstate.hpp>
#include <utils.hpp>
#include <json/json/json.h>
#include <SFML/Network.hpp>
#include <iostream>

HighscoresState::HighscoresState(StateStack& stack, Context context) :
    State(stack, context)
{
    mBackground.setTexture(context.textures->get(Textures::UiScreen));

    mTitle.setFont(context.fonts->get(Fonts::Main));
    mTitle.setString("HIGHSCORES");
    mTitle.setCharacterSize(46);
    centerOrigin(mTitle);
    mTitle.setPosition(context.window->getView().getSize().x / 2.f, 80.f);

    mContinue.setFont(context.fonts->get(Fonts::Main));
    mContinue.setString("Press SPACE to play");
    mContinue.setCharacterSize(22);
    centerOrigin(mContinue);
    mContinue.setPosition(context.window->getView().getSize().x / 2.f, context.window->getView().getSize().y - 40);

    mScores.setFont(context.fonts->get(Fonts::Main));
    mScores.setCharacterSize(20);
    mScores.setPosition(100.f, 180.f);

    sf::Http http("http://monstruosor.com/");
    sf::Http::Request request;
    request.setMethod(sf::Http::Request::Get);
    request.setUri("/scores.php");
    request.setHttpVersion(1, 1); // HTTP 1.1

    sf::Http::Response response = http.sendRequest(request);
    std::string scores = response.getBody();

    std::cout << "Scores: " << std::endl;
    std::cout << scores << std::endl;

    Json::Value root;
    Json::Reader reader;
    reader.parse(scores, root);

    std::cout << root.size() << std::endl;

    std::string text_scores = "";
    for(int index = 0; index < root.size(); ++index)
    {
        text_scores += toString(index+1) + "/\t[" + root[index]["score"].asString() + " pts]\t" + root[index]["nickname"].asString() + '\n';
    }

    mScores.setString(text_scores);
}

void HighscoresState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackground);
    window.draw(mTitle);
    window.draw(mScores);
    window.draw(mContinue);
}

bool HighscoresState::update(sf::Time /*dt*/)
{
    return false;
}

bool HighscoresState::handleEvent(const sf::Event& event)
{
    if(event.type == sf::Event::KeyReleased &&
            (event.key.code == sf::Keyboard::Escape ||
             event.key.code == sf::Keyboard::Space ||
             event.key.code == sf::Keyboard::Return)
    )
    {
        requestStackClear();
        requestStackPush(States::Game);
    }

    return false;
}
