#include <map>

#include <iostream>


template <typename T>
void print_map(std::string_view comment, const std::map<std::string, T>& m)
{
    std::cout << comment << std::endl;
    // Iterate using C++17 facilities
    for (const auto& [key, value] : m)
        std::cout << '[' << key << "] = " << value << "; ";

    std::cout << '\n';
}




int main()
{
    std::map<std::string, std::string> m1;

    m1["Programmieren1"] = "Brauer";
    m1["THI"] = "Göhner";
    m1["Computer Vision"] = "Ulhaas";

    print_map("Hier die Modulverantwortlichen:", m1);


    std::map<std::string, int> m2;

    m2["Programmieren1"] = 70;
    m2["THI"] = 60;
    m2["Computer Vision"] = 30;

    print_map("Hier die Prüfungsanmeldezahlen:", m2);
}