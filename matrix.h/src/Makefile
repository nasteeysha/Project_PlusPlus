CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -O3 -lstdc++

all:
	$(MAKE) clean
	$(MAKE) build
	$(MAKE) s21_matrix_oop.a
	$(MAKE) test

build:
	$(CC) -c $(CFLAGS) s21_matrix_oop.cc -o s21_matrix_oop.a

clean:
	rm -rf *.a *.o test

test:
	$(CC) $(CFLAGS) test.cc s21_matrix_oop.a -o test -lgtest
	./test

s21_matrix_oop.a:
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a
	rm -rf *.o

leaks:
	leaks --atExit -- ./test

stylecheck:
	cp ../materials/linters/.clang-format ./

	clang-format -n *.cc *.h
	cppcheck --language=c++ --std=c++17 *.cc *.h

