#include <states/pausestate.hpp>
#include <utils.hpp>

PauseState::PauseState(StateStack &stack, Context context) :
    State(stack, context),
    mTitle()
{
    mBackground.setTexture(context.textures->get(Textures::UiScreen));

    mTitle.setFont(context.fonts->get(Fonts::Main));
    mTitle.setString("PAUSE");
    mTitle.setCharacterSize(46);
    centerOrigin(mTitle);
    mTitle.setPosition(context.window->getView().getSize().x / 2.f, 80.f);

    // GUI
    mContainer.setPosition((context.window->getView().getSize().x - 500) / 2.f, 300.f);

    GUI::Button::Ptr button_resume = GUI::Button::Ptr(new GUI::Button(*context.fonts, *context.textures));
    button_resume->setCallback([this]() {
        requestStackPop();
    });
    button_resume->setText("Resume");
    mContainer.pack(std::move(button_resume));

    GUI::Button::Ptr button_restart = GUI::Button::Ptr(new GUI::Button(*context.fonts, *context.textures));
    button_restart->setCallback([this]() {
        requestStackClear();
        requestStackPush(States::Game);
    });
    button_restart->setText("Restart");
    button_restart->move(0, 50.f);
    mContainer.pack(std::move(button_restart));

    GUI::Button::Ptr button_quit = GUI::Button::Ptr(new GUI::Button(*context.fonts, *context.textures));
    button_quit->setCallback([this]() {
        requestStackClear();
    });
    button_quit->setText("Quit");
    button_quit->move(0, 100.f);
    mContainer.pack(std::move(button_quit));
}

void PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackground);
    window.draw(mTitle);
    window.draw(mContainer);
}

bool PauseState::update(sf::Time dt)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
    {
        requestStackPop();
    }

    mContainer.handleEvent(event);

    return false;
}
