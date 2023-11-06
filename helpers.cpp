#include <helpers.hpp>


std::unordered_map<std::string, std::string> read_configuration(const std::string &filename) {
    std::unordered_map<std::string, std::string> config;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            if (key[0] == '#') continue; // Skip comments
            if (std::getline(is_line, value)) {
                config[key] = value;
            }
        }
    }

    return config;
}
