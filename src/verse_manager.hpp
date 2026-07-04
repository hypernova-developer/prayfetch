#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>

namespace prayfetch
{
    class VerseManager
    {
    public:
        std::string get_next_verse(const std::string& verses_path, const std::string& state_path, const std::string& mode, const std::string& lang)
        {
            std::ifstream verses_file(verses_path);
            if (!verses_file.is_open())
            {
                return "Verse database not found.";
            }

            std::vector<std::string> lines;
            std::string line;
            while (std::getline(verses_file, line))
            {
                if (!line.empty())
                {
                    lines.push_back(line);
                }
            }

            if (lines.empty()) return "";

            int current_index = 0;

            if (mode == "sequential")
            {
                std::ifstream state_file(state_path);
                if (state_file.is_open())
                {
                    state_file >> current_index;
                }
                
                int next_index = (current_index + 1) % lines.size();
                std::ofstream out_state(state_path);
                out_state << next_index;
            }
            else
            {
                std::srand(std::time(nullptr));
                current_index = std::rand() % lines.size();
            }

            std::stringstream ss(lines[current_index]);
            std::string surah_tr, surah_en, ayah_no, text_tr, text_en;
            
            std::getline(ss, surah_tr, '|');
            std::getline(ss, surah_en, '|');
            std::getline(ss, ayah_no, '|');
            std::getline(ss, text_tr, '|');
            std::getline(ss, text_en, '|');

            if (lang == "en")
            {
                return "\"" + text_en + "\" (" + surah_en + ", " + ayah_no + ")";
            }
            return "\"" + text_tr + "\" (" + surah_tr + ", " + ayah_no + ")";
        }
    };
}
