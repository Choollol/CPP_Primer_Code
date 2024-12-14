#include "StrBLobPtrPtr.hpp"

std::string* StrBlobPtrPtr::operator->() {
    return ptr->operator->();
}