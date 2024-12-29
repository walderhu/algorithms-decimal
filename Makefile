CC = gcc
OS = $(shell uname)
CFLAGS = -Wall -Werror -Wextra -g -std=c11 

ALL_FUNC = $(wildcard ./*.c)

SOURCE_TESTS_FUNC = $(wildcard ./tests/*.c)

ifeq ($(OS), Darwin)
	det_OS = -lcheck
	GCOV_FLAGS = -fprofile-arcs -ftest-coverage
else
	det_OS = -lcheck -lsubunit -lm -pthread -lrt
endif

all: s21_decimal.a 

test: 
	@$(CC) $(ALL_FUNC) $(CFLAGS) $(SOURCE_TESTS_FUNC) $(GCOV_FLAGS) --coverage s21_decimal.a -o s21_test_decimal $(det_OS)
	@./s21_test_decimal

s21_decimal.a:
	@$(CC) $(ALL_FUNC) $(CFLAGS) -c
	@ar rc s21_decimal.a *.o
	@ranlib s21_decimal.a

gcov_report: clean s21_decimal.a test
	@lcov -t "s21_test_decimal" -o test.info --no-external -c -d .
	@genhtml -o report test.info
	@open report/index.html
	@rm -rf *.gcno *gcda *.gco

clean:
	@rm -rf test *.gcda *.gcno *.o *.info *.a *.h.gch tests/*.gcno report 
	@rm -rf s21_test_decimal.dSYM s21_test_decimal
	@rm -rf tests/*.h.gch 

style:
	@clang-format -n -style=google *.h $(ALL_FUNC) $(SOURCE_TESTS_FUNC)
	@rm -rf .clang-format

style_repair:
	@cp ../materials/linters/.clang-format ../src  
	@clang-format -i -style=google *.h $(ALL_FUNC) $(SOURCE_TESTS_FUNC)

leaks:
	valgrind --tool=memcheck --leak-check=yes ./s21_test_decimal

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov