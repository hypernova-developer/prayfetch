#pragma once
#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define BOLD    "\033[1m"

namespace prayfetch
{
    void print_ascii(const std::string& weather, int hour)
    {
        if (weather == "rainy")
        {
            std::cout << "       .--.\n"
                         "    .-(    ).\n"
                         "   (___.__)__)\n"
                         "    / / / / /\n"
                         "  =============\n"
                         "  |   " GREEN "🕌 🕌" RESET "   |\n";
        }
        else if (weather == "snowy")
        {
            std::cout << "      * * *\n"
                         "    * * *\n"
                         "  =============\n"
                         "  |   " GREEN "🕌 🕌" RESET "   |\n";
        }
        else
        {
            if (hour >= 5 && hour < 11)
            {
                std::cout << "       .---.       \n"
                             "      /     \\      \n"
                             "  " YELLOW "*" RESET " |       |     \n"
                             "      \\     /      \n"
                             "  =============\n"
                             "  |   " GREEN "🕌 🕌" RESET "   |\n";
            }
            else if (hour >= 11 && hour < 16)
            {
                std::cout << "         " YELLOW "O" RESET "         \n"
                             "       .---.       \n"
                             "      /     \\      \n"
                             "     |       |     \n"
                             "      \\     /      \n"
                             "  =============\n"
                             "  |   " GREEN "🕌 🕌" RESET "   |\n";
            }
            else if (hour >= 16 && hour < 20)
            {
                std::cout << "       .---.       \n"
                             "      /     \\      \n"
                             "     |       |  " YELLOW "*" RESET "  \n"
                             "      \\     /      \n"
                             "  =============\n"
                             "  |   " GREEN "🕌 🕌" RESET "   |\n";
            }
            else
            {
                std::cout << "    * " YELLOW "_.._" RESET "      \n"
                             "       " YELLOW ".' .-'`" RESET "     \n"
                             "   * " YELLOW "|  |" RESET "        \n"
                             "       " YELLOW "'. '._.._" RESET "   \n"
                             "  =============\n"
                             "  |   " GREEN "🕌 🕌" RESET "   |\n";
            }
        }
    }
}
