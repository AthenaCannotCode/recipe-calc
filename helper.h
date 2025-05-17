//
// Created by athena on 16.05.25.
//

#ifndef HELPER_H
#define HELPER_H

#endif //HELPER_H

#include <string>

struct Globals;

struct Item {
    std::string id;
    std::string name;
    int amount;
    bool final;

    bool operator>(const Item& rhs) const { return final > rhs.final; }
};
struct Recipe {
    Item item;
    std::vector<Item> ingredients = {};

    bool operator==(const std::string& item_id) const { return item.id == item_id; }
};
using Cus_Ret = std::variant<int, std::vector<Item>>;
struct Command {
    const char *cmd;
    Cus_Ret (* callback)(int argc, const char* args[], Globals *globals);
    const char* description[2];

    bool operator==(const char* ocmd) const { return !strcmp(cmd, ocmd);}
};

struct Globals {
    std::vector<Command> cmds;
    std::map<std::string, Item> items;
    std::map<std::string, Recipe> recipes;
};

template <typename T> struct pop_ret {
    T i;
    std::vector<T> v;
};