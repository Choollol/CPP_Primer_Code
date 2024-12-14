#ifndef FOLDER_H
#define FOLDER_H

#include "Message.hpp"

class Folder {
   public:
    void addMsg(Message*);
    void remMsg(Message*);

   private:
    std::set<Message*> messages;
};
#endif