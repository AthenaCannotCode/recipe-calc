/*

    LICENSE

    'recipe-calc', a simple crafting chain calculator.
    Copyright (C) 2025 https://github.com/AthenaCannotCode

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  It can be found in the file LICENSE.
    If not, see <https://www.gnu.org/licenses/>.

    Contact: E-Mail: athena.bonzel@proton.me

*/


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