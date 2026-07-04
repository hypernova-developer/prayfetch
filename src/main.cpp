#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include <cstdlib>
#include "config.hpp"
#include "locales.hpp"
#include "utils.hpp"
#include "prayer_manager.hpp"
#include "verse_manager.hpp"

namespace prayfetch
{
    struct SystemTime
    {
        std::string date_key;
        int hour;
        int minute;
    };

    SystemTime get_system_time()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* local_time = std::localtime(&now_time);

        std::ostringstream oss;
        oss << (local_time->tm_year + 1900) << "-"
            << std::setw(2) << std::setfill('0') << (local_time->tm_mon + 1) << "-"
            << std::setw(2) << std::setfill('0') << local_time->tm_mday;

        return { oss.str(), local_time->tm_hour, local_time->tm_min };
    }

    bool file_exists(const std::string& filename)
    {
        struct stat buffer;   
        return (stat(filename.c_str(), &buffer) == 0); 
    }

    void bootstrap_data(const std::string& city)
    {
        if (!file_exists("verses.txt") || std::ifstream("verses.txt").peek() == std::ifstream::traits_type::eof())
        {
            std::ofstream file("verses.txt");
            file << "Fâtiha|Al-Fatiha|1|Rahmân ve Rahîm olan Allah'ın ismiyle.|In the name of Allah, the Entirely Merciful, the Especially Merciful.\n";
        }

        if (!file_exists("times_cache.txt") || std::ifstream("times_cache.txt").peek() == std::ifstream::traits_type::eof())
        {
            std::ofstream file("times_cache.txt");
            file << "2026-07-04:03:32:05:32:13:14:17:14:20:41:22:31\n";
        }
    }
}

int main(int argc, char* argv[])
{
    std::string arg_mode = (argc > 1) ? argv[1] : "--full";

    prayfetch::Config config;
    if (!config.load("prayfetch.conf"))
    {
        return 1;
    }

    std::string city = config.settings.count("city") ? config.settings["city"] : "Istanbul";
    
    prayfetch::bootstrap_data(city);

    prayfetch::Lang current_lang = (config.settings["lang"] == "en") ? prayfetch::Lang::EN : prayfetch::Lang::TR;
    const auto& txt = prayfetch::locales.at(current_lang);

    prayfetch::SystemTime sys = prayfetch::get_system_time();
    prayfetch::PrayerManager pm;
    prayfetch::PrayerTimes times;

    if (!pm.get_today_times("times_cache.txt", sys.date_key, times))
    {
        return 1;
    }

    std::string next_name;
    int left_minutes = 0;
    pm.calculate_next_prayer(times, sys.hour, sys.minute, next_name, left_minutes);

    int hours_left = left_minutes / 60;
    int mins_left = left_minutes % 60;
    std::string time_left_str = std::to_string(hours_left) + ":" + (mins_left < 10 ? "0" : "") + std::to_string(mins_left);

    if (arg_mode == "--minimal")
    {
        std::cout << "🕌 " << next_name << " - " << time_left_str << std::endl;
        return 0;
    }

    std::cout << BOLD << CYAN << "prayfetch v0.1.0" << RESET << std::endl;
    std::cout << txt.location << city << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    std::string weather = config.settings.count("weather_status") ? config.settings["weather_status"] : "clear";
    prayfetch::print_ascii(weather, sys.hour);

    std::cout << "--------------------------------------" << std::endl;
    
    if (pm.is_kerahat(sys.hour, sys.minute, times.gunes, times.aksam))
    {
        std::cout << BOLD << RED << txt.kerahat_warn << RESET << std::endl;
    }
    else
    {
        std::cout << GREEN << txt.safe_zone << RESET << std::endl;
    }

    std::cout << txt.next_vakit << next_name << " (" << txt.remaining << time_left_str << ")" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    prayfetch::VerseManager vm;
    std::string mode = config.settings.count("verse_mode") ? config.settings["verse_mode"] : "sequential";
    std::string lang_str = (current_lang == prayfetch::Lang::EN) ? "en" : "tr";
    std::string verse = vm.get_next_verse("verses.txt", "state.txt", mode, lang_str);
    
    std::cout << txt.verse_title << verse << std::endl;

    return 0;
}
