#include <bitset>

#include "../../test_util.hpp"

template <size_t N>
class Quiz {
   public:
    Quiz() = default;
    Quiz(const std::string& s) : bits(s) {}

    void set(size_t n, bool val) { bits.set(n, val); }
    std::bitset<N> get() const { return bits; }

    std::bitset<N> operator~() const { return ~bits; }

   private:
    std::bitset<N> bits;
};

int main(int argc, char* argv[]) {
    std::bitset<10> answers("1010101010");
    Quiz<10> q1("1111111111"), q2("1000000000"), q3("1010101010");
    std::vector<Quiz<10>> quizzes{q1, q2, q3};
    std::vector<int> grades;
    for (const Quiz<10>& q : quizzes) {
        grades.push_back((answers.size() - (q.get() ^ answers).count()) * 100 / answers.size());
    }
    print(grades);
    return 0;
}