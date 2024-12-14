#include "Message.hpp"

void Message::add_to_folders(const Message& msg) {
    for (Folder* f : msg.folders) {
        f->addMsg(this);
    }
}

void Message::remove_from_folders() {
    for (Folder* f : folders) {
        f->remMsg(this);
    }
    folders.clear();
}

Message::Message(const Message& rhs) : contents(rhs.contents), folders(rhs.folders) {
    add_to_folders(rhs);
}

Message& Message::operator=(const Message& rhs) {
    remove_from_folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs);
    return *this;
}

void Message::move_folders(Message& msg) {
    std::set<Folder*> folders = std::move(msg.folders);
    for (Folder* f : folders) {
        f->remMsg(&msg);
        f->addMsg(this);
    }
    msg.folders.clear();
}

Message::Message(Message&& rhs) : contents(std::move(rhs.contents)), folders(std::move(rhs.folders)) {
    move_folders(rhs);
}
Message& Message::operator=(Message&& rhs) {
    if (this != &rhs) {
        remove_from_folders();

        contents = std::move(rhs.contents);

        move_folders(rhs);
    }

    return *this;
}

void Message::save(Folder& folder) {
    folders.insert(&folder);
    folder.addMsg(this);
}

void Message::remove(Folder& folder) {
    folders.erase(&folder);
    folder.remMsg(this);
}

void Message::save_p(Folder* f) {
    folders.insert(f);
    f->addMsg(this);
}
void Message::remove_p(Folder* f) {
    folders.erase(f);
    f->remMsg(this);
}

Message::~Message() {
    remove_from_folders();
}

void swap(Message& lhs, Message& rhs) {
    using std::swap;
    for (Folder* f : lhs.folders) {
        f->remMsg(&lhs);
    }
    for (Folder* f : rhs.folders) {
        f->remMsg(&rhs);
    }
    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);
    for (Folder* f : lhs.folders) {
        f->addMsg(&lhs);
    }
    for (Folder* f : rhs.folders) {
        f->addMsg(&rhs);
    }
}