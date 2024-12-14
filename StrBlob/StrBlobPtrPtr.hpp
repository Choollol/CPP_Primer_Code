#ifndef STRBLOBPTRPTR_HPP
#define STRBLOBPTRPTR_HPP

#include <memory>

#include "StrBlobPtr.hpp"

class StrBlobPtrPtr {
   public:
    std::string* operator->();

   private:
    std::shared_ptr<StrBlobPtr> ptr;
};

#endif