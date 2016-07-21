#include "file.hpp"

#include <boost/regex.hpp>
#include <iostream>
#include <fstream>
#include <regex>

namespace utils {
namespace files {

bool read( const std::string& filepath, std::string& result )
{
  std::ifstream file(filepath.c_str());
  if( !file.is_open() )
    return false;

  // Get length of file
  file.seekg(0, file.end);
  const int length = file.tellg();
  file.seekg(0, file.beg);

  // If file content is empty, exit
  if( length < 1 )
    return true;

  // Read the file
  result.resize( length );
  file.read(&result[0], length);

  // Close the file and return good read
  file.close();
  return true;
}

bool create( const std::string& filepath, const std::string& content, bool override )
{
  if( !override && exists(filepath) )
    return false;

  // Try to open the file
  std::ofstream new_file(filepath, std::ios::trunc);
  if( !new_file.is_open() )
    return false;

  // Write content into
  new_file << content;

  // Closing file
  new_file.close();

  return true;
}

std::string sanitize(const std::string& input)
{
  return std::regex_replace(input, std::regex{"[^a-z^A-Z^0-9]"}, "_");
}

} // namespace files
} // namespace utils


