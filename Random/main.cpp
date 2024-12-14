#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>

size_t get_rand(size_t min, size_t max) {
    static std::default_random_engine engine;
    std::uniform_int_distribution<size_t> dist(min, max);
    return dist(engine);
}

int main() {
    std::ifstream text("text.txt");
    std::ifstream trans_file("transforms.txt");
    std::map<std::string, std::vector<std::string>> transforms;
    std::string line;
    std::string word;
    while (std::getline(trans_file, line)) {
        std::istringstream iss(line);
        std::string s;
        iss >> s;
        transforms[s] = std::vector<std::string>();
        while (iss >> word) {
            transforms[s].push_back(word);
        }
    }
    while (std::getline(text, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            if (transforms.find(word) != transforms.end()) {
                std::cout << transforms[word][get_rand(0, transforms[word].size() - 1)] << ' ';
            }
            else {
                std::cout << word << ' ';
            }
        }
        std::cout << std::endl;
    }
    return 0;
}