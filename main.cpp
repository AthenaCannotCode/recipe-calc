#include <algorithm>
#include <assert.h>
#include <cstring>
#include <iostream>
#include <fstream>
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
{
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
        }
    },
    {}
};



//TODO: implement loading recipes from external source
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

    load_recipes();
    for (const Command &cmd : globals.cmds) {
        if (!std::strcmp(cmd.cmd, argv[1])) {
            Cus_Ret ret = cmd.callback(argc, argv, &globals);
            if (std::holds_alternative<int>(ret)) {
                return std::get<int>(ret);
            }
            if (std::holds_alternative<std::vector<Item>>(ret)) {
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