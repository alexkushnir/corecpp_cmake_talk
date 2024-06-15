#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>


int main()
{
    std::ifstream f("example.json");
    nlohmann::json data = nlohmann::json::parse(f);

    for (const auto& field : data)
    {
        std::cout << field << std::endl;
    }
    return 0;
}