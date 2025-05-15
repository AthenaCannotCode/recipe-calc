#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>





std::vector<const char*> ids = {
    "ore_copper",
    "ore_iron",
    "plate_copper",
    "plate_iron",
    "gear",
    "pack_red"
};
struct Item {
    const char* id;
    const char* name;
    int amount;
};
struct Ingredient {
    Item item;
    bool FINAL;
};
struct Recipe {
    Item item;
    std::vector<Ingredient> ingredients = {};
};
std::vector<Recipe> recipes;


struct Command {
    const char *cmd;
    int (* callback)(const int argc, const char* args[]);
    const char* description[2];
};
/* Declare callback functions for commands here */
int print_help(int argc, const char* args[]);
int test(int argc, const char* args[]);
int list_recipes(int argc, const char* args[]);
int calc(int argc, const char* args[]);

std::vector<Command> cmds = {
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
};
/* Define the callback functions here */
int print_help(const int argc, const char* args[]) {
    size_t max_cmd_len = 0;
    for (const Command &cmd : cmds) {
        max_cmd_len = std::max(max_cmd_len, std::strlen(cmd.cmd));
    }
    for (const Command &cmd : cmds) {
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
int test(const int argc, const char* args[]) {
    std::cout << "Hello World!\n";
    return 0;
}
int list_recipes(const int argc, const char* args[]) {
    for (Recipe &recipe : recipes) {
        std::stringstream s;
        for (size_t i = 0; i < recipe.ingredients.size(); ++i) {
            s << recipe.ingredients[i].item.name << " x " << recipe.ingredients[i].item.amount << "   ";
            if (i < recipe.ingredients.size() - 1) {
                s << "+   ";
            }
        }
        s << "->   ";
        s << recipe.item.name << " x " << recipe.item.amount << "\n";
        std::cout << s.str();
    }
    return 0;
}
int calc(const int argc, const char* args[]) {
    switch (argc) {
        case 2:
            std::cerr << "[ERROR] Not enough arguments given.\n";
            return 1;
        case 3:
            std::cout << "3\n";
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

//TODO: implement loading recipes from external source
void load_recipes() {
    recipes = {
        {
            {
                "plate_copper",
                "Copper plate",
                1
            },
            {
                {
                    {
                        "ore_copper",
                        "Copper ore",
                        2
                    },
                    true
                }
            }
        },
        {
            {
                "plate_iron",
                "Iron plate",
                1
            },
            {
                {
                    {
                        "ore_iron",
                        "Iron ore",
                        2
                    },
                    true
                }
            }
        },
        {
            {
                "gear",
                "Iron gear wheel",
                1
            },
            {
                {
                    {
                        "plate_iron",
                        "Iron plate",
                        2
                    },
                    false
                }
            }
        },
        {
            {
                "pack_red",
                "Automation science pack",
                1
            },
            {
                {
                    {
                        "gear",
                        "Iron gear wheel",
                        1
                    },
                    false
                },
                {
                    {
                        "plate_copper",
                        "Copper plate",
                        1
                    },
                    false
                }
            }
        }
    };
}

bool has(const std::vector<Command> *vec, const char* element) {
    for (const Command command: *vec) {
        if (!std::strcmp(command.cmd, element)) return true;
    }
    return false;
}

int execute_command(const int argc, const char* argv[]) {
    if (argc == 1) {
        cmds[0].callback(argc, argv);
        return 1;
    }
    if (!has(&cmds, argv[1])) {
        std::cout << "Command '" << argv[1] << "' not found\nPossible commands:\n\n";
        cmds[0].callback(argc, argv);
        return 1;
    }

    load_recipes();
    for (const Command &cmd : cmds) {
        if (!std::strcmp(cmd.cmd, argv[1])) {
            return cmd.callback(argc, argv);
        }
    }
    return 1;
}


int main(const int argc, const char* argv[]) {
    return execute_command(argc, argv);
}