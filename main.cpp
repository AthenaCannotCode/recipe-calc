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


#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <variant>
#include <map>

#include "helper.cpp"
#include "callbacks.cpp"



Globals globals = {
    {
        {
            "help",
             print_help,
             {"[DESC] Print this help message"}
        },
        {
            "test",
            test,
            {"[DESC] test command"}
        },
        {
            "list",
            list_recipes,
            {"[DESC] List all recipes"}
        },
        {
            "calc",
            calc,
            {"[DESC] Calculate a specific recipe", "[USAGE] calc <item id> <amount>"}
        }
    },
    {},
    {}
};



//TODO: implement loading item and recipes from external source
void load_items() {
    globals.items = {
        {
            "ore_copper",
            {
                "ore_copper",
                "Copper ore",
                0,
                true
            }
        },
        {
            "ore_iron",
            {
                "ore_iron",
                "Iron ore",
                0,
                true
            }
        },
        {
            "plate_copper",
            {
                "plate_copper",
                "Copper plate",
                0,
                false
            }
        },
        {
            "plate_iron",
            {
                "plate_iron",
                "Iron plate",
                0,
                false
            }
        },
        {
            "gear",
            {
                "gear",
                "Iron gear wheel",
                0,
                false
            }
        },
        {
            "pack_red",
            {
                "pack_red",
                "Automation science pack",
                0,
                false
            }
        },
        {
            "module_speed_3",
            {
                "module_speed_3",
                "Speed module 3",
                0,
                false
            }
        },
        {
            "module_speed_2",
            {
                "module_speed_2",
                "Speed module 2",
                0,
                false
            }
        },
        {
            "module_speed_1",
            {
                "module_speed_1",
                "Speed module 1",
                0,
                true
            }
        },
        {
            "circuit_blue",
            {
                "circuit_blue",
                "Processing Unit",
                0,
                true
            }
        },
        {
            "circuit_red",
            {
                "circuit_red",
                "Advanced Circuit",
                0,
                true
            }
        },
    };
}
void load_recipes() {
    globals.recipes = {
        {
            "plate_copper",
            {
                get_item_with_amount("plate_copper", 1, &globals),
                {
                    get_item_with_amount("ore_copper", 2, &globals)
                }
            }
        },
        {
            "plate_iron",
            {
                get_item_with_amount("plate_iron", 1, &globals),
                {
                    get_item_with_amount("ore_iron", 2, &globals)
                }
            }
        },
        {
            "gear",
            {
                get_item_with_amount("gear", 1, &globals),
                {
                    get_item_with_amount("plate_iron", 2, &globals)
                }
            }
        },
        {
            "pack_red",
            {
                get_item_with_amount("pack_red", 1, &globals),
                {
                   get_item_with_amount("gear", 1, &globals),
                   get_item_with_amount("plate_copper", 1, &globals)
                }
            }
        },
        {
            "module_speed_3",
            {
                get_item_with_amount("module_speed_3", 1, &globals),
                {
                    get_item_with_amount("module_speed_2", 4, &globals),
                    get_item_with_amount("circuit_blue", 5, &globals),
                    get_item_with_amount("circuit_red", 5, &globals)
                }

            }
        },
        {
            "module_speed_2",
            {
                get_item_with_amount("module_speed_2", 1, &globals),
                    {
                        get_item_with_amount("module_speed_1", 4, &globals),
                       get_item_with_amount("circuit_blue", 5, &globals),
                       get_item_with_amount("circuit_red", 5, &globals)
                    }
            }
        }
    };
}

int execute_command(const int argc, const char* argv[]) {
    if (argc == 1) {
        globals.cmds[0].callback(argc, argv, &globals);
        return 1;
    }
    if (!has<Command>(&globals.cmds, argv[1])) {
        std::cout << "Command '" << argv[1] << "' not found\nPossible commands:\n\n";
        globals.cmds[0].callback(argc, argv, &globals);
        return 1;
    }

    load_items();
    load_recipes();
    for (const Command &cmd : globals.cmds) {
        if (!std::strcmp(cmd.cmd, argv[1])) {
            Cus_Ret ret = cmd.callback(argc, argv, &globals);
            if (std::holds_alternative<int>(ret)) {
                return std::get<int>(ret);
            }
            if (std::holds_alternative<std::vector<Item>>(ret)) {
                std::cout << "\n";
                std::cout << "[INFO] Total resources needed for recipe:\n";
                print_item_vec(std::get<std::vector<Item>>(ret));
                return 0;
            }
        }
    }
    return 1;
}


int main(const int argc, const char* argv[]) {
    return execute_command(argc, argv);
}