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