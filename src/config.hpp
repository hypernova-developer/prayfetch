#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

namespace prayfetch
{
    class Config
    {
    public:
        std::unordered_map<std::string, std::string> settings;

        bool load(const std::string& filepath)
        {
            std::ifstream file(filepath);
            if (!file.is_open())
            {
                return false;
            }

            std::string line;
            while (std::getline(file, line))
            {
                if (line.empty() || line[0] == '#')
                {
                    continue;
                }

                auto delimiter_pos = line.find('=');
                if (delimiter_pos != std::string::npos)
                {
                    std::string key = line.substr(0, delimiter_pos);
                    std::string value = line.substr(delimiter_pos + 1);
                    
                    key.erase(key.find_last_not_of(" \t") + 1);
                    key.erase(0, key.find_first_not_of(" \t"));
                    value.erase(value.find_last_not_of(" \t") + 1);
                    value.erase(0, value.find_first_not_of(" \t"));
                    
                    settings[key] = value;
                }
            }
            return true;
        }
    };
}
