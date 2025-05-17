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
