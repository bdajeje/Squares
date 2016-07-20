#include "jukebox.hpp"

#include <algorithm>
#include <iostream>

#include "utils/directory.hpp"

namespace audio {

Jukebox::Jukebox(const std::string& directory)
  : _directory {utils::ensureDirectoryEnd(directory)}
{
  // List all .ogg files under given directory
  _music_files = utils::listFiles(directory, ".*\\.ogg", false);

  // Then construct a randomly sorted list of those musics
  std::random_shuffle( _music_files.begin(), _music_files.end() );
}

bool Jukebox::play()
{
  if(_music_files.empty())
    return false;

  // Stop possible previous music
  _music.stop();

  // Open new music file
  const std::string& music_file = _music_files.at(_current_music_offset);
  if(!_music.openFromFile( _directory + music_file ))
  {
    std::cout << "Can't open music file: " << _directory << music_file << std::endl;
    return false;
  }

  // Start music
  _music.play();

  // Set some kind of "callback" which will auto play next music when current one is finished
  _thread.reset( new std::thread(std::bind(&Jukebox::autoPlayNext, this)) );

  return true;
}

void Jukebox::autoPlayNext()
{
  sf::Time duration = _music.getDuration();

  _current_music_offset++;
  if( _current_music_offset >= _music_files.size() )
    _current_music_offset = 0;

  std::this_thread::sleep_for(std::chrono::microseconds(duration.asMicroseconds()));
  play();
}


}
