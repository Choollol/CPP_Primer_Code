#ifndef MESSAGE_H
#define MESSAGE_H

#include <set>
#include <string>

#include "Folder.hpp"

class Message {
    friend class Folder;

    friend void swap(Message&, Message&);

   public:
    explicit Message(const std::string& s = "") : contents(s) {}

    Message(const Message&);
    Message& operator=(const Message&);
    Message(Message&&);
    Message& operator=(Message&&);
    ~Message();

    void save(Folder&);
    void remove(Folder&);

    void save_p(Folder*);
    void remove_p(Folder*);

   private:
    std::string contents;
    std::set<Folder*> folders;

    void add_to_folders(const Message&);
    void remove_from_folders();

    void move_folders(Message& msg);
};
#endif