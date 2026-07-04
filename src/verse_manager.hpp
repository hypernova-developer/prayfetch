#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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

            json verses_json;
            verses_file >> verses_json;
            int total_verses = verses_json.size();
            if (total_verses == 0) return "";

            int current_index = 0;

            if (mode == "sequential")
            {
                std::ifstream state_file(state_path);
                json state_json;
                if (state_file.is_open())
                {
                    state_file >> state_json;
                    current_index = state_json.value("last_verse_index", 0);
                }
                
                int next_index = (current_index + 1) % total_verses;
                std::ofstream out_state(state_path);
                json new_state;
                new_state["last_verse_index"] = next_index;
                out_state << new_state.dump(4);
            }
            else
            {
                std::srand(std::time(nullptr));
                current_index = std::rand() % total_verses;
            }

            auto verse = verses_json[current_index];
            std::string text_key = (lang == "en") ? "text_en" : "text_tr";
            std::string surah_key = (lang == "en") ? "surah_name_en" : "surah_name_tr";
            
            return "\"" + verse.value(text_key, "") + "\" (" + verse.value(surah_key, "") + ", " + std::to_string(verse.value("ayah_no", 0)) + ")";
        }
    };
}
