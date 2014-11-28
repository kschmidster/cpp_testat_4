#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "dynArray.h"

void test_create_dyArray_no_args() {
	dynArray<int> test1 { };
	dynArray<char> test2 { };
	dynArray<std::string> test3 { };

	ASSERT(test1.empty());
	ASSERT(test2.empty());
	ASSERT(test3.empty());
}

void test_create_dyArray_init_list() {
	dynArray<int> test { 1, 2, 3, 4, 5 };

	ASSERT(!test.empty());
	ASSERT_EQUAL(5, test.size());
}

void test_create_dyArray_eql_val() {
	dynArray<int> test(3, 42);

	ASSERT(!test.empty());
	ASSERT_EQUAL(3, test.size());
}

void test_create_dyArray_istr_iter() {
	std::istringstream in { "bla bla just some text..." };
	std::istringstream end { };
	dynArray<std::string> test { in, end };

	ASSERT(!test.empty());
	ASSERT_EQUAL(5, test.size());
}

void test_at_func() {
	dynArray<int> test(3, 42);

	ASSERT_EQUAL(42, test.at(2));
}

void test_at_func_lval() {
	dynArray<double> test(3, 3.14);

	test.at(2) = 2.78;

	ASSERT_EQUAL(2.78, test.at(2));
}

void test_at_func_const() {
	using vec = dynArray<int>;
	using const_reference = vec::const_reference;
	vec test(4, 42);
	vec const &test2 {test};

	ASSERT_EQUAL(42, test2.at(3));
}

void test_at_func_neg_index() {
	dynArray<std::string> test { "this", "is", "a", "test" };

	ASSERT_EQUAL("test", test.at(-1));
	ASSERT_EQUAL("a", test.at(-2));
	ASSERT_EQUAL("is", test.at(-3));
	ASSERT_EQUAL("this", test.at(-4));
}

void test_oper_sqr_brac_lval() {
	dynArray<std::string> test { "hello this is a text" };

	test[test.size() - 1] = "test";

	ASSERT_EQUAL("test", test[test.size() - 1]);
}

void test_oper_sqr_brac_neg_index() {
	dynArray<int> test { 1, 3, 7, 42, 9 };

	ASSERT_EQUAL(42, test[-2]);
}

void test_func_front() {
	dynArray<double> test { 1.0, 2.0, 3.0, 4.0 };

	ASSERT_EQUAL(1.0, test.front());
}

void test_func_front_lval() {
	dynArray<std::string> test { "hello i'm writing cute tests" };

	test.front() = "hi";

	ASSERT_EQUAL("hi", test.front());
}

void test_func_back() {
	dynArray<int> test { 1, 3, 5, 7, 9 };

	ASSERT_EQUAL(9, test.back());
}

void test_func_back_lval() {
	dynArray<int> test { 2, 4, 6, 8 };

	test.back() = 42;

	ASSERT_EQUAL(42, test.back());
}

void test_func_capacity() {
	using vec = std::vector<int>;
	dynArray<vec> test { vec { 1, 2, 4 }, vec { 4, 5, 6 }, vec { 7, 8, 9 } };

	ASSERT_EQUAL(3, test.capacity());
	ASSERT_EQUAL(3, test.size());
}

void test_func_clear() {
	dynArray<double> test { 1.0, 2.0, 3.0, 4.0 };

	test.clear();

	ASSERT(!test.size());
	ASSERT(test.empty());
	ASSERT_EQUAL(4, test.capacity());
}

void test_func_push_back() {
	dynArray<std::string> test { "hallo" };

	test.push_back("this");
	test.push_back("is");
	test.push_back("a");

	ASSERT_EQUAL("a", test.at(-1));
	ASSERT_EQUAL("is", test.at(-2));
	ASSERT_EQUAL("this", test.at(-3));
	ASSERT_EQUAL("hallo", test.at(-4));
}

void test_func_pop_back() {
	using pair = std::pair<int, std::string>;
	dynArray<pair> test { { 3, "3" }, { 5, "5" }, { 7, "7" } };

	test.pop_back();

	ASSERT_EQUAL(2, test.size());
	ASSERT_EQUAL(3, test.capacity());
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s { };

	//My tests
	s.push_back(CUTE(test_create_dyArray_no_args));
	s.push_back(CUTE(test_create_dyArray_init_list));
	s.push_back(CUTE(test_create_dyArray_eql_val));
	s.push_back(CUTE(test_create_dyArray_istr_iter));
	s.push_back(CUTE(test_at_func));
	s.push_back(CUTE(test_at_func_lval));
	s.push_back(CUTE(test_at_func_const));
	s.push_back(CUTE(test_at_func_neg_index));
	s.push_back(CUTE(test_oper_sqr_brac_lval));
	s.push_back(CUTE(test_oper_sqr_brac_neg_index));
	s.push_back(CUTE(test_func_front));
	s.push_back(CUTE(test_func_front_lval));
	s.push_back(CUTE(test_func_back));
	s.push_back(CUTE(test_func_back_lval));
	s.push_back(CUTE(test_func_capacity));
	s.push_back(CUTE(test_func_clear));
	s.push_back(CUTE(test_func_push_back));
	s.push_back(CUTE(test_func_pop_back));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}
