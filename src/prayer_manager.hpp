#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

namespace prayfetch
{
    struct PrayerTimes
    {
        std::string imsak, gunes, ogle, ikindi, aksam, yatsi;
    };

    class PrayerManager
    {
    public:
        bool get_today_times(const std::string& txt_path, const std::string& date_key, PrayerTimes& out_times)
        {
            std::ifstream file(txt_path);
            if (!file.is_open())
            {
                return false;
            }

            std::string line;
            while (std::getline(file, line))
            {
                if (line.rfind(date_key, 0) == 0)
                {
                    std::stringstream ss(line);
                    std::string token;
                    std::vector<std::string> tokens;
                    
                    while (std::getline(ss, token, ':'))
                    {
                        tokens.push_back(token);
                    }

                    if (tokens.size() >= 7)
                    {
                        out_times.imsak = tokens[1] + ":" + tokens[2];
                        out_times.gunes = tokens[3] + ":" + tokens[4];
                        out_times.ogle = tokens[5] + ":" + tokens[6];
                        out_times.ikindi = tokens[7] + ":" + tokens[8];
                        out_times.aksam = tokens[9] + ":" + tokens[10];
                        out_times.yatsi = tokens[11] + ":" + tokens[12];
                        return true;
                    }
                }
            }
            return false;
        }

        int time_to_minutes(const std::string& time_str)
        {
            if (time_str.length() < 5) return 0;
            int h = std::stoi(time_str.substr(0, 2));
            int m = std::stoi(time_str.substr(3, 2));
            return h * 60 + m;
        }

        void calculate_next_prayer(const PrayerTimes& times, int cur_hour, int cur_min, std::string& next_name, int& left_minutes)
        {
            int current = cur_hour * 60 + cur_min;
            
            std::vector<std::pair<std::string, int>> target_times = 
            {
                {"Imsak", time_to_minutes(times.imsak)},
                {"Gunes", time_to_minutes(times.gunes)},
                {"Ogle", time_to_minutes(times.ogle)},
                {"Ikindi", time_to_minutes(times.ikindi)},
                {"Aksam", time_to_minutes(times.aksam)},
                {"Yatsi", time_to_minutes(times.yatsi)}
            };

            for (const auto& p : target_times)
            {
                if (current < p.second)
                {
                    next_name = p.first;
                    left_minutes = p.second - current;
                    return;
                }
            }

            next_name = "Imsak";
            left_minutes = (24 * 60 - current) + target_times[0].second;
        }

        bool is_kerahat(int cur_hour, int cur_min, const std::string& sunrise_str, const std::string& sunset_str)
        {
            int cur_min_total = cur_hour * 60 + cur_min;
            int sun_min = time_to_minutes(sunrise_str);
            int set_min = time_to_minutes(sunset_str);

            if (cur_min_total >= sun_min && cur_min_total <= (sun_min + 45))
            {
                return true;
            }
            if (cur_min_total >= (set_min - 45) && cur_min_total <= set_min)
            {
                return true;
            }
            return false;
        }
    };
}
