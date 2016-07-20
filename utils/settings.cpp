#include "settings.hpp"

#include <iostream>

#include <boost/algorithm/string.hpp>

#include "utils/file.hpp"

namespace utils {

const std::string Settings::SoundVolume {"sound_volume"};
const std::string Settings::MusicVolume {"music_volume"};
const std::string Settings::WindowWidth {"window_width"};
const std::string Settings::WindowHeight {"window_height"};
const std::array<std::string, 4> Settings::s_setting_keys = {
  Settings::SoundVolume,
  Settings::MusicVolume,
  Settings::WindowWidth,
  Settings::WindowHeight
};

Settings::Settings(const std::string& filepath)
  : _filepath {filepath}
{
  load();
}

void Settings::load()
{
  std::string content;
  if(!files::read(_filepath, content))
  {
    std::cerr << "Can't read settings file: " << _filepath << std::endl;
    return;
  }

  // Split settings content by line
  std::vector<std::string> lines;
  boost::algorithm::split(lines, content, boost::is_any_of("\n"));

  // Read every setting line and update setting variables
  for(const std::string& line : lines)
  {
    // Split line in two parts, key and value, seperated by '='
    const size_t delimiter_offset = line.find("=");
    if(delimiter_offset == std::string::npos)
      continue;

    // Is this a known setting key?
    const std::string setting_key = line.substr(0, delimiter_offset);
    const auto last = std::end(s_setting_keys);
    if(std::find(std::begin(s_setting_keys), last, setting_key) == last)
      continue;

    // Register found setting
    const std::string setting_value = line.substr(delimiter_offset + 1);
    _setting_values[setting_key] = setting_value;
  }
}

bool Settings::save()
{
  std::string result;
  for(const std::string& setting_key : s_setting_keys)
    result += setting_key + "=" + _setting_values[setting_key] + "\n";

  return files::create(_filepath, result, true);
}

}
