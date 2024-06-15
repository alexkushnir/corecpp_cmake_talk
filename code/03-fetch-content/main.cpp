#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

int main()
{
    nlohmann::json data = nlohmann::json::parse(
        std::ifstream{"./example.json"});

    for (const auto& field : data.items())
    {
        std::cout << field.key() << ": " 
            << field.value() << std::endl;
    }

    return 0;
}