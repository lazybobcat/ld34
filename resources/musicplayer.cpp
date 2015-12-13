#include <resources/musicplayer.hpp>

MusicPlayer::MusicPlayer() :
    mMusic(),
    mFilenames(),
    mVolume(100.f)
{
    // Fill mFilenames table here :
    mFilenames[Musics::MainTheme] = "assets/musics/main_theme.ogg";
}

void MusicPlayer::play(Musics::ID song)
{
    std::string filename = mFilenames[song];

    if (!mMusic.openFromFile(filename))
        throw std::runtime_error("Music " + filename + " could not be loaded.");

    mMusic.setVolume(mVolume);
    mMusic.setLoop(true);
    mMusic.play();
}

void MusicPlayer::stop()
{
    mMusic.stop();
}

void MusicPlayer::setVolume(float volume)
{
    mVolume = volume;
    mMusic.setVolume(volume);
}

void MusicPlayer::pause(bool flag)
{
    if (flag)
        mMusic.pause();
    else
        mMusic.play();
}

void MusicPlayer::setLoop(bool flag)
{
    mMusic.setLoop(flag);
}
