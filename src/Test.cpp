#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "dynArray.h"

#include <numeric>

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
	using it = std::istream_iterator<std::string>;
	dynArray<std::string> test { it { in }, it { } };

	ASSERT(!test.empty());
	ASSERT_EQUAL(5, test.size());
}

void test_create_dynArray_iter() {
	std::vector<char> test_vec { '1', '2', '3' };
	dynArray<char> test { test_vec.begin(), test_vec.end() };

	ASSERT_EQUAL(3, test.size());
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
	dynArray<int> const &test { 1, 3, 5, 42, 9 };

	ASSERT_EQUAL(42, test.at(3));
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

void test_oper_sqr_brac_const() {
	dynArray<int> const &test { 1, 3, 7, 42, 9 };

	ASSERT_EQUAL(42, test[3]);
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

void test_func_front_const() {
	dynArray<double> const &test { 42.0, 2.0, 3.0, 4.0 };

	ASSERT_EQUAL(42.0, test.front());
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

void test_func_back_const() {
	dynArray<std::string> const &test { "hello", "what's", "up" };

	ASSERT_EQUAL("up", test.back());
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

void test_func_resize_bigger() {
	using pair = std::pair<int, std::string>;
	dynArray<pair> test { { 3, "3" }, { 5, "5" }, { 7, "7" } };

	test.resize(5);

	ASSERT_EQUAL(5, test.size());
}

void test_func_resize_smaller() {
	dynArray<int> test { 7, 5, 3, 1 };

	test.resize(3);

	ASSERT_EQUAL(3, test.size());
}

void test_func_resize_values() {
	dynArray<double> test { 1.0, 2.0, 3.0, 4.0 };

	test.resize(7, 42.0);

	ASSERT_EQUAL(7, test.size());
}

void test_rand_acc_iter() {
	std::ostringstream out { };
	std::ostream_iterator<std::string> out_iter(out, " ");
	dynArray<std::string> test { "the", "answer", "is", "42" };

	std::copy(test.begin(), test.end(), out_iter);

	ASSERT_EQUAL("the answer is 42 ", out.str());
}

void test_rand_acc_iter_const() {
	std::ostringstream out { };
	std::ostream_iterator<std::string> out_iter(out, " ");
	dynArray<std::string> const &test { "42", "is", "always", "the", "answer" };

	std::copy(test.begin(), test.end(), out_iter);

	ASSERT_EQUAL("42 is always the answer ", out.str());
}

void test_const_rand_acc_iter_const() {
	dynArray<int> const &test { 1, 2, 3, 4, 5, 6, 7, 8, 6 };

	int erg { std::accumulate(test.cbegin(), test.cend(), 0) };

	ASSERT_EQUAL(42, erg);
}

void test_rev_iter() {
	std::ostringstream out { };
	std::ostream_iterator<char> out_iter(out, "");
	dynArray<char> test { 't', 's', 'e', 't' };

	std::copy(test.rbegin(), test.rend(), out_iter);

	ASSERT_EQUAL("test", out.str());
}

void test_rev_iter_const() {
	std::ostringstream out { };
	std::ostream_iterator<int> out_iter(out, "");
	dynArray<int> const &test { 2, 4 };

	std::copy(test.rbegin(), test.rend(), out_iter);

	ASSERT_EQUAL("42", out.str());
}

void test_const_rev_iter_const() {
	std::ostringstream out { };
	std::ostream_iterator<int> out_iter(out, " ");
	dynArray<int> test { 13, 8, 5, 3, 2, 1, 1 };

	std::copy(test.crbegin(), test.crend(), out_iter);

	ASSERT_EQUAL("1 1 2 3 5 8 13 ", out.str());
}

void test_func_erase() {
	std::ostringstream out { };
	std::ostream_iterator<std::string> out_iter(out, " ");
	dynArray<std::string> test { "this", "lköhjasf", "is", "a test" };

	test.erase(test.begin() + 1);

	std::copy(test.begin(), test.end(), out_iter);

	ASSERT_EQUAL("this is a test ", out.str());
}

void test_func_erase_cont_iter() {
	std::ostringstream out { };
	std::ostream_iterator<int> out_iter(out, "");
	dynArray<int> test { 4, 3, 2, 1 };

	test.erase(test.erase(test.cbegin() + 1) + 1);

	std::copy(test.begin(), test.end(), out_iter);

	ASSERT_EQUAL("42", out.str());
}

void test_func_erase_two_iter() {
	std::ostringstream out { };
	std::ostream_iterator<std::string> out_iter(out, " ");
	dynArray<std::string> test { "this", "is", "a", "test", "this", "will", "be", "erased" };

	test.erase(test.begin() + 4, test.end());

	std::copy(test.begin(), test.end(), out_iter);

	ASSERT_EQUAL("this is a test ", out.str());
}

void test_func_erase_two_const_iter() {
	std::ostringstream out { };
	std::ostream_iterator<std::string> out_iter(out, " ");
	dynArray<std::string> test { "this", "will", "be", "erased", "this", "is", "another", "test" };

	test.erase(test.begin(), test.begin() + 4);

	std::copy(test.begin(), test.end(), out_iter);

	ASSERT_EQUAL("this is another test ", out.str());
}

void test_make_dynArray() {
	std::ostringstream out { };
	std::ostream_iterator<std::string> out_iter(out, " ");
	auto test = dynArray<std::string>::makedynArray( { "this", "is", "my", "last", "test" });

	std::copy(test.begin(), test.end(), out_iter);

	ASSERT_EQUAL("this is my last test ", out.str());
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s { };

	//My tests
	s.push_back(CUTE(test_create_dyArray_no_args));
	s.push_back(CUTE(test_create_dyArray_init_list));
	s.push_back(CUTE(test_create_dyArray_eql_val));
	s.push_back(CUTE(test_create_dyArray_istr_iter));
	s.push_back(CUTE(test_create_dynArray_iter));
	s.push_back(CUTE(test_at_func));
	s.push_back(CUTE(test_at_func_lval));
	s.push_back(CUTE(test_at_func_const));
	s.push_back(CUTE(test_at_func_neg_index));
	s.push_back(CUTE(test_oper_sqr_brac_lval));
	s.push_back(CUTE(test_oper_sqr_brac_neg_index));
	s.push_back(CUTE(test_oper_sqr_brac_const));
	s.push_back(CUTE(test_func_front));
	s.push_back(CUTE(test_func_front_lval));
	s.push_back(CUTE(test_func_front_const));
	s.push_back(CUTE(test_func_back));
	s.push_back(CUTE(test_func_back_lval));
	s.push_back(CUTE(test_func_back_const));
	s.push_back(CUTE(test_func_capacity));
	s.push_back(CUTE(test_func_clear));
	s.push_back(CUTE(test_func_push_back));
	s.push_back(CUTE(test_func_pop_back));
	s.push_back(CUTE(test_func_resize_bigger));
	s.push_back(CUTE(test_func_resize_smaller));
	s.push_back(CUTE(test_func_resize_values));
	s.push_back(CUTE(test_rand_acc_iter));
	s.push_back(CUTE(test_rand_acc_iter_const));
	s.push_back(CUTE(test_const_rand_acc_iter_const));
	s.push_back(CUTE(test_rev_iter));
	s.push_back(CUTE(test_rev_iter_const));
	s.push_back(CUTE(test_const_rev_iter_const));
	s.push_back(CUTE(test_func_erase));
	s.push_back(CUTE(test_func_erase_cont_iter));
	s.push_back(CUTE(test_func_erase_two_iter));
	s.push_back(CUTE(test_func_erase_two_const_iter));
	s.push_back(CUTE(test_make_dynArray));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}
