//
//  Copyright (c) 2018, Cem Bassoy, cem.bassoy@gmail.com
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Fraunhofer IOSB, Ettlingen Germany
//


#ifndef _BOOST_UBLAS_TENSOR_STRIDES_
#define _BOOST_UBLAS_TENSOR_STRIDES_

#include <vector>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

#include <cassert>

// in order to include column and row major
#include <boost/numeric/ublas/functional.hpp> 

namespace boost { namespace numeric { namespace ublas {

using first_order = column_major;
using last_order = row_major;

template<class T>
class basic_extents;

template<class __int_type, class __layout>
class basic_strides
{
	using base_type = std::vector<__int_type>;

	static_assert( std::numeric_limits<typename base_type::value_type>::is_integer,
								 "Static error in boost::numeric::ublas::basic_strides: type must be of type integer.");
	static_assert(!std::numeric_limits<typename base_type::value_type>::is_signed,
								"Static error in boost::numeric::ublas::basic_strides: type must be of type unsigned integer.");
	static_assert(std::is_same<__layout,first_order>::value || std::is_same<__layout,last_order>::value,
								"Static error in boost::numeric::ublas::basic_strides: layout type must either first or last order");

public:

	using layout_type = __layout;
	using value_type = typename base_type::value_type;
	using reference = typename base_type::reference;
	using const_reference = typename base_type::const_reference;
	using size_type = typename base_type::size_type;
	using const_pointer = typename base_type::const_pointer;
	using const_iterator = typename base_type::const_iterator;


	constexpr explicit basic_strides()
		: _base{}
	{
	}

	template <class T>
	basic_strides(basic_extents<T> const& s)
			: _base(s.size(),1)
	{
		if(s.empty())
			return;

		if(!s.valid())
			throw std::runtime_error("Error in boost::numeric::ublas::basic_strides() : shape is not valid.");		

		if(s.is_vector() || s.is_scalar())
			return;

		if(this->size() < 2)
			throw std::runtime_error("Error in boost::numeric::ublas::basic_strides() : size of strides must be greater or equal 2.");


		if constexpr (std::is_same<layout_type,first_order>::value){
			auto k = 1ul, kend = this->size();
			for(; k < kend; ++k)
				_base[k] = _base[k-1] * s[k-1];
		}
		else {
			auto k = this->size()-2, kend = 0ul;
			for(; k > kend; --k)
				_base[k] = _base[k+1] * s[k+1];
			_base[0] = _base[1] * s[1];
		}
	}

	template<class other_layout>
	basic_strides(basic_strides<value_type,other_layout> const& l)
			: _base(l._base)
	{}

	basic_strides(basic_strides const& l)
	    : _base(l._base)
	{}

	basic_strides(basic_strides && l )
	    : _base(std::move(l._base))
	{}

	basic_strides(base_type const& l )
	    : _base(l)
	{}

	basic_strides(base_type && l )
			: _base(std::move(l))
	{}

	~basic_strides() = default;


	basic_strides& operator=(basic_strides other)
	{
		swap (*this, other);
		return *this;
	}

	friend void swap(basic_strides& lhs, basic_strides& rhs) {
		std::swap(lhs._base   , rhs._base);
	}

	const_reference operator[] (size_type p) const{
		return _base[p];
	}

	const_pointer data() const{
		return _base.data();
	}

	const_reference at (size_type p) const{
		return _base.at(p);
	}


	bool empty() const{
		return _base.empty();
	}

	size_type size() const{
		return _base.size();
	}

	bool operator == (basic_strides const& b) const{
		return b._base == _base;
	}

	bool operator != (basic_strides const& b) const{
		return b._base != _base;
	}

	const_iterator begin() const{
		return _base.begin();
	}

	const_iterator end() const{
		return _base.end();
	}

	void clear() {
		this->_base.clear();
	}

	base_type const& base() const{
		return this->_base;
	}


protected:
	base_type _base;
};

template<class layout_type>
using strides = basic_strides<std::size_t, layout_type>;

}}}

#endif
