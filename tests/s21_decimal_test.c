#include "s21_decimal_test.h"

int main(void) {
  run_tests();
  return 0;
}

int run_testcase(Suite *testcase) {
  int result = 1;
  static int counter_testcase = 1;
  if (counter_testcase > 1) counter_testcase++;
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result;
}

void run_tests(void) {
  Suite *list_cases[] = {s21_from_decimal_to_int_suite(),
                         s21_from_decimal_to_float_suite(),
                         s21_from_float_to_decimal_suite(),
                         s21_from_int_to_decimal_suite(),
                         sub_tests(),
                         addition_tests(),
                         mul_suite(),
                         s21_floor_test_suite(),
                         s21_truncate_test_suite(),
                         s21_negate_test_suite(),
                         greater_tests(),
                         equal_tests(),
                         less_tests(),
                         s21_round_test_suite(),
                         s21_div_suite(),
                         NULL};
  int number_failed = 0;
  int number_success = 0;
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    if (run_testcase(*current_testcase) != 0)
      number_failed++;
    else
      number_success++;
  }
  printf("\e[32mSuccess: %d\e[0m\n\e[31mFailures: %d\e[0m\n", number_success,
         number_failed);
}