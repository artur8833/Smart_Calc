CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
MAIN_FILES= *.c 
TEST_FILES=  unit_test/*.c
CHECK_LINK= $(shell pkg-config --libs --cflags check)
GCOVFLAGS= -fprofile-arcs -ftest-coverage
LIBNAME= s21_smartcalc.a
GLFLAGS= --coverage
LIBS= -lcheck -lsubunit -lm -lgcov

all: s21_smartcalc.a

object:
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(GLFLAGS) -c $(MAIN_FILES)

lib:
	ar rcs s21_smartcalc.a *.o

s21_smartcalc.a:
	$(CC) $(CFLAGS) -c $(MAIN_FILES)
	ar rc s21_smartcalc.a *.o
	ranlib s21_smartcalc.a

test: s21_smartcalc.a
	$(CC) $(CFLAGS) $(TEST_FILES) -L. s21_smartcalc.a $(CHECK_LINK) $(GLFLAGS) $(GCOVFLAGS) -o s21_smartcalc_test
	chmod 777 s21_smartcalc_test
	./s21_smartcalc_test

gcov_report: object lib test
	gcov *.gcno *.gcda
	~/.local/bin/gcovr -r . --html --html-details -o s21_smartcalc.html
	open s21_smartcalc.html

clean:
	rm -f *.o
	rm -f *.a
	rm -f unit_tests/*.o
	rm -f unit_tests/*.a
	rm -f string/*.o
	rm -f string/*.a
	rm -rf *.gcno
	rm -rf *.gcov
	rm -rf *.gcda
	rm -rf *.info
	rm -rf *.html
	rm -rf *.css
	rm -f ./s21_matrix_test
