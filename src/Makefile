SHELL = /bin/sh

CFLAGS = -Wall -Wextra -Werror -std=c11 -g
LDFLAGS = -lcheck  -lm -pthread -lrt -lsubunit
SRC = brick_game/tetris/backend.c gui/cli/frontend.c brick_game.c
GCOV_FLAGS = --coverage -fprofile-arcs -ftest-coverage

OS_NAME = $(shell uname)

ifeq ($(OS_NAME),Linux)
OPEN = xdg-open
endif

ifeq ($(OS_NAME),Darwin)
OPEN = open
endif

all: clean install

build/libtetris.a: $(SRC)
	mkdir -p build
	gcc $(CFLAGS) -c $(SRC)
	ar rcs build/libtetris.a *.o
	mv *.o build

install: clean build/libtetris.a
	echo 0 > build/high_score.txt
	gcc $(CFLAGS) brick_game.c -lncurses -Lbuild -ltetris $(LDFLAGS) -o build/tetris

run: clean install
	build/tetris

uninstall:
	rm -rf build

clean:
	rm -rf build gcov
	rm -f unit_test/unit_test unit_test/high_score.txt
	rm -f tetris.tar.gz
	rm -rf gui/cli/frontend.h.gch
	rm -rf brick_game.h.gch
	rm -rf report
	rm -rf *.info *.gcda
	find dvi ! -name 'documentation.tex' -type f -exec rm -f {} +

dvi:
	xelatex -output-directory=dvi dvi/documentation.tex

dist: install
	tar -czvf tetris.tar.gz Makefile brick_game gui unit_test brick_game.c brick_game.h #Diagrama.pdf

test: clean build/libtetris.a
	echo 0 > unit_test/high_score.txt
	gcc $(CFLAGS) brick_game/tetris/backend.c gui/cli/frontend.c unit_test/unit_test.c -lncurses $(LDFLAGS) -o unit_test/unit_test
	cd unit_test && ./unit_test

gcov_report: clean build/libtetris.a
	echo 0 > unit_test/high_score.txt
	gcc $(CFLAGS) --coverage brick_game/tetris/backend.c gui/cli/frontend.c unit_test/unit_test.c -lncurses $(LDFLAGS) -o test
	./test
	lcov -t "test" -o test_report.info -c -d . --rc lcov_branch_coverage=1
	lcov --remove test_report.info '*unit_test/*' '*gui/*' --output-file test_report.info
	genhtml -o report test_report.info
	rm -rf *.o *.a *.gch *.gcno *.gcda test
	open ./report/index.html

clang_format:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	clang-format -i brick_game/tetris/*.c
	clang-format -i gui/cli/*.c
	clang-format -i unit_test/*.c unit_test/*.h
	rm -f .clang-format

clang_check:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h
	clang-format -n brick_game/tetris/*.c
	clang-format -n gui/cli/*.c
	clang-format -n unit_test/*.c unit_test/*.h
	rm -f .clang-format

valgrind: test
	cd unit_test && valgrind --tool=memcheck --leak-check=yes ./unit_test

clear:
	clear

# install gcovr: sudo apt install gcovr
# install ncurses: sudo apt-get install libncurses5-dev libncursesw5-dev
# install xelatex: sudo apt-get install texlive-xetex (or sudo apt-get install texlive-latex-extra)