#include "gmb.h"

#include <check.h>
#include <stdlib.h>

START_TEST(test_init) {
    gmb_t buf;
    ck_assert_int_eq(gmb_init(&buf), 0);
    ck_assert_ptr_nonnull(buf.data);
    gmb_free(&buf);
}
END_TEST

START_TEST(test_append) {
    gmb_t buf;
    gmb_init(&buf);
    ck_assert_int_eq(gmb_append(&buf, "abc", 3), 0);
    ck_assert_int_eq(buf.size, 3);
    ck_assert(buf.data[0] == 'a');
    gmb_free(&buf);
}
END_TEST

Suite *gmb_suite(void) {
    Suite *s = suite_create("GMB");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_init);
    tcase_add_test(tc_core, test_append);
    
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite *s = gmb_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
