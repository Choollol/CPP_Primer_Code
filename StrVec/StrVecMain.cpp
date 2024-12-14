#include <algorithm>
#include <cstring>
#include <deque>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

#include "../../test_util.hpp"
#include "StrVec.hpp"

int main(int argc, char* argv[]) {
    StrVec v1{"aa", "bb"}, v2{"aa", "bb"}, v3;
    v3.emplace_back(10, 'b');
    std::cout << v3 << std::endl;
    return 0;
}
