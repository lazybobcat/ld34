#include <resources/soundplayer.hpp>

#include <cmath>

namespace
{
    const float ListenerZ = 300.f;
    const float Attenuation = 8.f;
    const float MinDistance2D = 200.f;
    const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
}

/////////////////////////////////////////

SoundPlayer::SoundPlayer() :
    mSoundBuffers(),
    mSounds()
{
    // Fill buffers with sounds
    mSoundBuffers.load(Sounds::BonusEnds, "assets/sounds/bonus_ends.wav");
    mSoundBuffers.load(Sounds::Explosion, "assets/sounds/explosion.wav");
    mSoundBuffers.load(Sounds::Pickup, "assets/sounds/pickup.wav");
    mSoundBuffers.load(Sounds::Points, "assets/sounds/points.wav");
}

void SoundPlayer::play(Sounds::ID sound)
{
    play(sound, getListenerPosition());
}

void SoundPlayer::play(Sounds::ID effect, sf::Vector2f position)
{
    mSounds.push_back(sf::Sound());
    sf::Sound& sound = mSounds.back();

    sound.setBuffer(mSoundBuffers.get(effect));
    sound.setPosition(position.x, position.y, 0.f);
    sound.setAttenuation(Attenuation);
    sound.setMinDistance(MinDistance3D);
    sound.setVolume(50);
    // pitch ?

    sound.play();
}


void SoundPlayer::removeStoppedSounds()
{
    mSounds.remove_if([] (const sf::Sound& s) {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
    return sf::Vector2f(sf::Listener::getPosition().x, sf::Listener::getPosition().y);
}
