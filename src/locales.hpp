#pragma once
#include <string>
#include <unordered_map>

namespace prayfetch
{
    enum class Lang { TR, EN };

    struct LocaleStrings
    {
        std::string location;
        std::string current_vakit;
        std::string kerahat_warn;
        std::string safe_zone;
        std::string remaining;
        std::string next_vakit;
        std::string verse_title;
    };

    const std::unordered_map<Lang, LocaleStrings> locales = 
    {
        {Lang::TR, 
            {
                "Konum: ",
                "Mevcut Vakit: ",
                "Uyarı: Şu an kerahat vaktidir! Namaz kılmak mekruhtur.",
                "Dini Durum: Namaz kılmak için uygun vakit.",
                "Kalan Süre: ",
                "Sıradaki Vakit: ",
                "📖 Ayet: "
            }
        },
        {Lang::EN, 
            {
                "Location: ",
                "Current Time: ",
                "Warning: It is Karahat time! Solat is disliked right now.",
                "Spiritual Status: Suitable time for solat.",
                "Remaining: ",
                "Next Vakit: ",
                "📖 Verse: "
            }
        }
    };
}
