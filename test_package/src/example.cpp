#include "mumu/world/Export.h"
#include <vector>
#include <string>

int main()
{
    mumu();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    mumu_print_vector(vec);
}
