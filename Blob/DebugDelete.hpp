#ifndef DEBUGDELETE_HPP
#define DEBUGDELETE_HPP

#include <iostream>

class DebugDelete {
   public:
    template <typename T>
    void operator()(T* p) {
        std::cout << "DebugDelete deleting " << typeid(p).name() << std::endl;
        delete p;
    }
};

#endif