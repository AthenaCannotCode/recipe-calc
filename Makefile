#####################################################################################
##																				   ##
##	  LICENSE																	   ##
##																				   ##
##    'recipe-calc', a simple crafting chain calculator.						   ##
##    Copyright (C) 2025 https://github.com/AthenaCannotCode					   ##
##																				   ##
##    This program is free software: you can redistribute it and/or modify		   ##
##    it under the terms of the GNU General Public License as published by		   ##
##    the Free Software Foundation, either version 3 of the License, or			   ##
##    (at your option) any later version.										   ##
##																				   ##
##    This program is distributed in the hope that it will be useful,			   ##
##    but WITHOUT ANY WARRANTY; without even the implied warranty of			   ##
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				   ##
##    GNU General Public License for more details.								   ##
##																				   ##
##    You should have received a copy of the GNU General Public License			   ##
##    along with this program.  It can be found in the file LICENSE.			   ##
##    If not, see <https://www.gnu.org/licenses/>.								   ##
#																				   ##
#    Contact: E-Mail: athena.bonzel@proton.me								   	   ##
##																				   ##
#####################################################################################


file := main.cpp
exe  := main

G++-ARGS = -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable

build:
	@echo ""
	@echo "[COMPILE]"
	g++ $(file) -o $(exe) $(G++-ARGS)

run: build
	@echo ""
	@echo "[RUN]"
	./$(exe)
	@echo ""

test: build
	@echo ""
	@echo "[TEST]"
	./$(exe) $(ARGS)
	@echo ""

clean:
	@echo ""
	@echo "[CLEAN]"
	rm $(exe)
	@echo ""
