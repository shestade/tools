#include <type_list.hpp>
#include <fixed_string.hpp>
#include <meta_struct.hpp>
#include <functional.hpp>

#include <iostream>
#include <string>

#define TEST(x) \
std::cout << x << "\n"; \


#define CHECK(x) \
std::cout << '\t' << #x << "... "; \
if (x) { \
	std::cout << "passed\n"; \
} else { \
	std::cout << "failed\n"; \
}

template <typename T>
struct tcmp {
	template <typename Arg>
	using apply = typename std::is_same<Arg, T>::type;
};

template <typename T>
struct fop : std::is_same<T, int> {};

[[maybe_unused]]
bool test_typelist() {
	using namespace meta::tl;
	using t_t = tl<int, double>;

	static_assert(std::is_same_v<head_t<t_t>, int>);
	static_assert(std::is_same_v<tail_t<t_t>, tl<double>>);
	static_assert(std::is_same_v<push_head_t<char, t_t>, tl<char, int, double>>);
	static_assert(std::is_same_v<push_back_t<t_t, char>, tl<int, double, char>>);
	static_assert(empty_v<t_t> == false);
	static_assert(empty_v<tl<>> == true);
	static_assert(std::is_same_v<reverse_t<t_t>, tl<double, int>>);

	static_assert(std::is_same_v<transform_t<t_t, tcmp<int>>,
		tl<std::true_type, std::false_type>>);

	static_assert(std::is_same_v<
		concat_t<tl<int, double>, tl<char>>,
		tl<int, double, char>
	>);

	static_assert(std::is_same_v<filter_t<fop, t_t>, tl<int>>);
	return true;
}

template <meta::fixed_string S>
struct T {
};

using Person = meta::meta_struct<
	meta::member<"id", int>,
	meta::member<"name", std::string>
>;

bool test_metastruct() {
	TEST("metastruct")

	[[maybe_unused]] T<"abc"> t;
	Person p{meta::arg<"id"> = 1, meta::arg<"name"> = "Denis"};
	get<"id">(p) = 1;
	get<"name">(p) = "Denis";

	std::cout << "{" << get<"id">(p) << ", " << get<"name">(p) << "}\n";
	return true;
}

bool test_functional() {
	using namespace std;

	auto v = func::compose([](int i) constexpr { return i + 1; })(
		func::compose([](int i) constexpr { return i * 2; })(
			func::identity
			)
		);

	TEST("func")
	CHECK(12 == v(5));
	return true;
}

int main()
{
	test_metastruct();
	//test_functional();
}

