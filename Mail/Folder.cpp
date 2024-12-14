#include "Folder.hpp"
#include "Message.hpp"

void Folder::addMsg(Message* msg) {
    messages.insert(msg);
}

void Folder::remMsg(Message* msg) {
    messages.erase(msg);
}