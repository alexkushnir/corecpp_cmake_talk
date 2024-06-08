#include <boost/bimap.hpp>
#include <iostream>
#include <string>

template<class MapType>
void print_map(const MapType& m)
{
    typedef typename MapType::const_iterator const_iterator;
    for(const_iterator iter = m.begin(), iend = m.end(); iter != iend; ++iter)
    {
        std::cout << iter->first << "-->" << iter->second << std::endl;
    }
}

int main()
{
    boost::bimap<int, std::string> bm;
    using bm_type = boost::bimap<int, std::string>;

    bm.insert(bm_type::value_type(1, "one"));
    bm.insert(bm_type::value_type(2, "two"));
    bm.insert(bm_type::value_type(3, "three"));

    print_map(bm.left);
    std::cout << "\n";
    print_map(bm.right);

    return 0;
}
