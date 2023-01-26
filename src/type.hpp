#ifndef LC_TYPE_HPP
#define LC_TYPE_HPP

#define SZ(t, sz) static_assert(sizeof(t) == sz)

namespace lc {
	using u8 = unsigned char;
	using u16 = unsigned short;
	using u32 = unsigned int;
	using u64 = unsigned long long;

	using i8 = signed char;
	using i16 = signed short;
	using i32 = signed int;
	using i64 = signed long long;

	using size_t = unsigned long;
	using ssize_t = signed long;

	using f32 = float;
	using f64 = double;

	SZ(u8, 1);
	SZ(u16, 2);
	SZ(u32, 4);
	SZ(u64, 8);

	SZ(i8, 1);
	SZ(i16, 2);
	SZ(i32, 4);
	SZ(i64, 8);

	SZ(f32, 4);
	SZ(f64, 8);
}

#undef SZ

#endif
