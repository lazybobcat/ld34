#include <controllers/playercontroller.hpp>
#include <events/commandqueue.hpp>
#include <entities/player.hpp>

PlayerController::PlayerController()
{
    // Default keybindings
    mKeyBinding[sf::Keyboard::Up] = MoveUp;
    mKeyBinding[sf::Keyboard::Z] = MoveUp;
    mKeyBinding[sf::Keyboard::W] = MoveUp;
    mKeyBinding[sf::Keyboard::Down] = MoveDown;
    mKeyBinding[sf::Keyboard::S] = MoveDown;

    // initialize actions
    initializeActions();
}

void PlayerController::handleEvent(const sf::Event &event, CommandQueue &commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Check if pressed key appears in key binding, trigger command if so
        auto found = mKeyBinding.find(event.key.code);
        if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
            commands.push(mActionBinding[found->second]);
    }
    else if(event.type == sf::Event::KeyReleased)
    {
        commands.push(mGoStraightCommand);
    }
}

void PlayerController::handleRealtimeInput(CommandQueue &commands)
{
    for(auto pair : mKeyBinding)
    {
        if(sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
        {
            commands.push(mActionBinding[pair.second]);
        }
    }
}

void PlayerController::assignKey(Action action, sf::Keyboard::Key key)
{
    // Remove all keys that already map to action
    for(auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
    {
        if (itr->second == action)
            mKeyBinding.erase(itr++);
        else
            ++itr;
    }

    // Insert new binding
    mKeyBinding[key] = action;
}

sf::Keyboard::Key PlayerController::getAssignedKey(Action action) const
{
    for(auto pair : mKeyBinding)
    {
        if (pair.second == action)
            return pair.first;
    }

    return sf::Keyboard::Unknown;
}

void PlayerController::initializeActions()
{
    mGoStraightCommand.action = derivedAction<Player>([](Player& player, sf::Time) {
            player.setDirection(Player::Straight);
    });
    mGoStraightCommand.category = Category::Player;

    mActionBinding[MoveUp].action = derivedAction<Player>([](Player& player, sf::Time) {
            player.setDirection(Player::Up);
    });
    mActionBinding[MoveUp].category = Category::Player;

    mActionBinding[MoveDown].action = derivedAction<Player>([](Player& player, sf::Time) {
            player.setDirection(Player::Down);
    });
    mActionBinding[MoveDown].category = Category::Player;
}

bool PlayerController::isRealtimeAction(Action action)
{
    switch (action)
    {
        case MoveDown:
        case MoveUp:
            return true;

        default:
            return false;
    }
}

