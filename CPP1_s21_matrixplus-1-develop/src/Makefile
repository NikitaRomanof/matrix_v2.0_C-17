.PHONY: all clean test s21_matrix.a check gcov_report
CC=g++
FILES= s21_matrix_oop.cpp\

LDFLAGS= -Wall -Wextra -Werror -std=c++17
OS := $(shell uname -s)


ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif

default: all

all: clean s21_matrix_oop.a

test: s21_matrix_oop.a
ifeq ($(OS), Darwin)
	$(CC) test.cpp s21_matrix_oop.a -o test -lgtest
else
	$(CC) test.cpp s21_matrix_oop.a -o test -lgtest
endif
	./test

clean:
	rm -rf test *.a *.o *.cfg *.gcda *.gcno *.html *.info *.dSYM report

s21_matrix_oop.a:
	$(CC) -c $(FILES)
	ar rcs s21_matrix_oop.a *.o
	ranlib $@
	cp $@ lib$@

check: lint test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test
endif

lint:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=cpp *.cpp *.h

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) --coverage s21_matrix_oop.cpp test.cpp -o test -lgtest
	./test
	lcov -t "test" -c -d . -o test.info
	genhtml test.info -o report
	open -a "Google Chrome" report/$(PWD)/index.html
else
	$(CC) -fprofile-arcs -ftest-coverage $(FILES) test.cpp -o test -lgtest
	./test
	lcov -t "test" -c -d . -o test.info
	genhtml test.info -o report
	xdg-open report/index.htm

endif
