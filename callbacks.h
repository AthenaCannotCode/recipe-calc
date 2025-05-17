//
// Created by athena on 16.05.25.
//

#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "callbacks.cpp"
#include "helper.h"
#endif //CALLBACKS_H


/* Declare callback functions for commands here */
Cus_Ret print_help(int argc, const char* args[], Globals *globals);
Cus_Ret test(int argc, const char* args[], Globals *globals);
Cus_Ret list_recipes(int argc, const char* args[], Globals *globals);
Cus_Ret calc(int argc, const char* args[], Globals *globals);