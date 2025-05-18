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

#include <sstream>

/* Define the callback functions here */
Cus_Ret print_help(int argc, const char* args[], Globals *globals) {
    std::cout << "\n[COMMANDS]\n";
    size_t max_cmd_len = 0;
    for (const Command &cmd : globals->cmds) {
        max_cmd_len = std::max(max_cmd_len, std::strlen(cmd.cmd));
    }
    for (const Command &cmd : globals->cmds) {
        size_t l = 0;
        for (const char* line : cmd.description) {
            if (line != nullptr) {
                if (l >= 1) {
                    for (size_t i = 0; i < (max_cmd_len + 3); ++i) {
                        std::cout << " ";
                    }
                } else {
                    std::cout << cmd.cmd;
                    for (size_t i = 0; i < max_cmd_len - std::strlen(cmd.cmd); ++i) {
                        std::cout << " ";
                    }
                    std::cout << " - ";
                }
                l++;
                std::cout << line << "\n";
            }
        }
    }
    return 0;
}

Cus_Ret test(const int argc, const char* args[], Globals *globals) {
    std::cout << "Hello World!\n";
    return 0;
}

Cus_Ret list_recipes(const int argc, const char* args[], Globals *globals) {
    for (std::pair<std::string, Recipe> recipe : globals->recipes) {
        std::stringstream s;
        for (size_t i = 0; i < recipe.second.ingredients.size(); ++i) {
            s << recipe.second.ingredients[i].name << " x " << recipe.second.ingredients[i].amount << "   ";
            if (i < recipe.second.ingredients.size() - 1) {
                s << "+   ";
            }
        }
        s << "->   ";
        s << recipe.second.item.name << " x " << recipe.second.item.amount << "\n";
        std::cout << s.str();
    }
    return 0;
}

Cus_Ret calc(const int argc, const char* args[], Globals *globals) { // NOLINT(*-non-const-parameter)
    std::vector<Item> materials = {};
    Cus_Ret ret;
    long int amount;
    switch (argc) {
        case 2:
            std::cerr << "[ERROR] Not enough arguments given.\n";
            return 1;

        case 3:
            if (!contains(globals->items, args[2])) {
                std::cerr << "[ERROR] Item id not found or command not used correctly.\n";
                return 1;
            }
            if (is_final(args[2], globals)) {
                std::cout << "[INFO] Item does not have a recipe.\n";
                return 0;
            }
            if (args[3] == nullptr) {
                std::cout << "[INFO] Recipe: " << globals->items[args[2]].name << " x 1\n";
            }
            materials.push_back(globals->items[args[2]]);
            while (!materials.empty()) {
                if (!materials.size()) return 1;
                materials = sort_mats(materials, globals);
                if (materials[0].final) return materials;
                pop_ret<Item> ret = pop_first<Item>(materials);
                Item first = ret.i;
                materials = ret.v;
                std::vector<Item> ingredients = globals->recipes[first.id].ingredients;
                for (Item ingredient : ingredients) {
                    for (Item &material : materials) {
                        if (ingredient.id == material.id) {
                            material.amount += ingredient.amount;
                            break;
                        }
                    }
                    materials.push_back(ingredient);
                }
            }
            return 0;
        case 4:
            if (!contains(globals->items, args[2])) {
                std::cerr << "[ERROR] Item id '" << args[2] << "' not found or command not used correctly.\n";
                return 1;
            }
            if (is_final(args[2], globals)) {
                std::cout << "[INFO] Item '" << globals->items[args[2]].name << "' does not have a recipe.\n";
                return 0;
            }
            amount = std::strtol(args[3], nullptr, 10);
            std::cout << "[INFO] Recipe: " << globals->items[args[2]].name << " x " << amount << "\n";
            ret = calc(argc-1, args, globals);
            if (std::holds_alternative<std::vector<Item>>(ret)) {
                materials = std::get<std::vector<Item>>(ret);
                for (Item &item : materials) {
                    item.amount *= amount;
                }
                return materials;
            }
            return ret;

        default:
            //TODO: implement additional arguments
            std::cerr << "[ERROR] Too many arguments given. " << argc << "\n";
            return 1;
    }
}
