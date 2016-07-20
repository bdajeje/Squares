#ifndef JENGINE_DIRECTORY_HPP
#define JENGINE_DIRECTORY_HPP

#include <string>
#include <vector>

namespace utils {

// Ensure '/' and the end of directory string
std::string ensureDirectoryEnd(const std::string& path);

/*! List files under directory */
std::vector<std::string> listFiles(const std::string& directory_path, const std::string& regex_str, bool sort = true);

}

#endif // JENGINE_DIRECTORY_HPP
