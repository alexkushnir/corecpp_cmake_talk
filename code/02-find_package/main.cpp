#include <boost/bimap.hpp>
#include <iostream>
#include <string>

template<class MapType>
void print_map(const MapType& m)
{
    for (const auto& iter : m)
    {
        std::cout << iter.first << "-->" << iter.second << std::endl;
    }
}

int main()
{
    boost::bimap<int, std::string> bm;
    
    bm.insert(boost::bimap<int, std::string>::value_type(1, "one"));
    bm.insert(boost::bimap<int, std::string>::value_type(2, "two"));
    bm.insert(boost::bimap<int, std::string>::value_type(3, "three"));

    print_map(bm.left);
    std::cout << "\n";
    print_map(bm.right);

    return 0;
}
