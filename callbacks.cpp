//
// Created by athena on 16.05.25.
//

#include <sstream>
//#include "helper.h"
#include <complex.h>
#include <cxxabi.h>

/* Define the callback functions here */
Cus_Ret print_help(int argc, const char* args[], Globals *globals) {
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
            materials.push_back(globals->items[args[2]]);
            while (!materials.empty()) {
                if (!materials.size()) return 1;
                materials = sort_mats(materials, globals);
                if (materials[0].final) return 0;
                pop_ret<Item> ret = pop_first<Item>(materials);
                Item first = ret.i;
                materials = ret.v;
                std::vector<Item> ingredients = globals->recipes[first.id].ingredients;
                std::cout << "Ingredients: \n";
                print_item_vec(ingredients);
                std::cout << "\n";
                for (Item ingredient : ingredients) {
                    std::cerr << "hit outer\n";
                    std::cerr << ingredient.name << "\n";
                    for (Item &material : materials) {
                        if (ingredient.id == material.id) {
                            material.amount += ingredient.amount;
                            break;
                        }
                    }
                    std::cerr << "hit\n";
                    materials.push_back(ingredient);
                }
                std::cout << "Materials: \n";
                print_item_vec(materials);
            }
            return 0;
        case 4:
            //TODO: calculating multiple items
            std::cout << "4\n";
            return 0;

        default:
            //TODO: implement additional arguments
            std::cerr << "[ERROR] Too many arguments given. " << argc << "\n";
            return 1;
    }
}
