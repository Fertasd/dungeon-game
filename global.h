#pragma once

#include <istream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

template<typename _ValueT, _ValueT _DefaultV>
struct default_init
{
	constexpr inline default_init(_ValueT value = _DefaultV) : _value(value) { }
	inline default_init& operator=(const _ValueT& rhs) { _value = rhs; return *this; }
	constexpr inline operator _ValueT() const { return _value; }
private:
	_ValueT _value;
};

struct no_copy
{
	no_copy() = default;
	no_copy(no_copy&&) = default;
	no_copy& operator=(no_copy&&) = default;

	no_copy(const no_copy&) = delete;
	no_copy& operator=(const no_copy&) = delete;
};

template<typename _ClassT>
struct enable_pass_key_make_shared
{
	class key
	{
		constexpr key() { }
		friend enable_pass_key_make_shared<_ClassT>;
	};
public:
	template<typename... _Args>
	static inline std::shared_ptr<_ClassT> make_shared(_Args&&... args) { return std::make_shared<_ClassT>(key(), std::forward<_Args>(args)...); }
};

template<typename _ContainerT, typename _PredicateT>
void erase_if(_ContainerT& items, const _PredicateT& predicate)
{
	for (auto i = std::begin(items); i != std::end(items);)
		if(predicate(*i))
			i = items.erase(i);
		else
			++i;
};

template<typename _CharT, typename _Traits, typename _Alloc>
auto split(const std::basic_string<_CharT, _Traits, _Alloc>& src, typename std::basic_string<_CharT, _Traits, _Alloc>::value_type delim, typename std::basic_string<_CharT, _Traits, _Alloc>::size_type limit = std::numeric_limits<typename std::basic_string<_CharT, _Traits, _Alloc>::size_type>::max())
{
	std::vector<std::basic_string<_CharT, _Traits, _Alloc>> tokens;
	for(typename std::basic_string<_CharT, _Traits, _Alloc>::size_type start = 0, end, i = 0; end != std::basic_string<_CharT, _Traits, _Alloc>::npos && i < limit; start = end + 1, ++i)
	{
		end = src.find(delim, start);
		tokens.push_back(src.substr(start, end - start));
	}
	return tokens;
}

template<typename _CharT, typename _Traits, typename _Alloc>
auto& safe_getline(std::basic_istream<_CharT, _Traits>& is, std::basic_string<_CharT, _Traits, _Alloc>& t)
{
	t.clear();

	// The characters in the stream are read one-by-one using a std::streambuf.
	// That is faster than reading them one-by-one using the std::istream.
	// Code that uses streambuf this way must be guarded by a sentry object.
	// The sentry object performs various tasks,
	// such as thread synchronization and updating the stream state.

	typename std::basic_istream<_CharT, _Traits>::sentry se(is, true);
	auto* sb = is.rdbuf();

	for(;;)
	{
		auto c = sb->sbumpc();
		switch (c)
		{
		case '\n':
			return is;
		case '\r':
			if(sb->sgetc() == '\n')
				sb->sbumpc();
			return is;
		case EOF:
			// Also handle the case when the last line has no line ending
			if(t.empty())
				is.setstate(std::ios::eofbit);
			return is;
		default:
			t += c;
		}
	}
}
