#include "tools.h"

#include <type_list.hpp>
#include <fixed_string.hpp>
#include <meta_struct.hpp>
#include <functional.hpp>

#include <string>

using namespace std;

template <meta::fixed_string S>
struct T {
};

using Person = meta::meta_struct<
	meta::member<"id", int>,
	meta::member<"name", std::string>
	>;


template <typename T>
struct tcmp {
	template <typename Arg>
	using apply = typename std::is_same<Arg, int>::type;
};

template <typename T>
struct fop : std::is_same<T, int> {};


int main()
{

	using t_t = meta::tl<int, double>;

	static_assert(std::is_same_v<meta::head_t<t_t>, int>);
	static_assert(std::is_same_v<meta::tail_t<t_t>, meta::tl<double>>);
	static_assert(std::is_same_v<meta::push_head_t<char, t_t>, meta::tl<char, int, double>>);
	static_assert(std::is_same_v<meta::push_back_t<t_t, char>, meta::tl<int, double, char>>);
	static_assert(meta::empty_v<t_t> == false);
	static_assert(meta::empty_v<meta::tl<>> == true);
	static_assert(std::is_same_v<meta::reverse_t<t_t>, meta::tl<double, int>>);

	static_assert(std::is_same_v<meta::transform_t<t_t, tcmp<int>>,
		meta::tl<std::true_type, std::false_type>>);

	static_assert(std::is_same_v<
			meta::concat_t<meta::tl<int, double>, meta::tl<char>>,
			meta::tl<int, double, char>
		>);

	static_assert(std::is_same_v<meta::filter_t<fop, t_t>, meta::tl<int>>);


	T<"abc"> t;
	Person p{meta::arg<"id"> = 1, meta::arg<"name"> = "Denis"};
	//get<"id">(p) = 1;
	//get<"name">(p) = "Denis";

	cout << get<"id">(p) << get<"name">(p);

	cout << "Hello CMake." << endl;

	auto v = func::compose([](int i) constexpr { return i + 1; })(
		func::compose([](int i) constexpr { return i * 2; })(
			func::identity
			)
		);

	return v(5);
}
