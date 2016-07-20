#ifndef JUKEBOX_HPP
#define JUKEBOX_HPP

#include <thread>
#include <memory>

#include <SFML/Audio/Music.hpp>

namespace audio {

class Jukebox final
{
  public:

    Jukebox(const std::string& directory);

    /*! Start jukebox
     *  \returns true if a music has been started, false otherwise
     */
    bool play();

    void autoPlayNext();

  protected:

    size_t _current_music_offset {0};
    std::string _directory;
    std::vector<std::string> _music_files;
    sf::Music _music;

    // Thread responsibled for playing next music when ones is finished
    std::unique_ptr<std::thread> _thread;
};

}

#endif // JUKEBOX_HPP
