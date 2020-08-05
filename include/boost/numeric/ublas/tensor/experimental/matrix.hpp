//
//  Copyright (c) 2018-2020, Cem Bassoy, cem.bassoy@gmail.com
//  Copyright (c) 2019-2020, Amit Singh, amitsingh19975@gmail.com
//  Copyright (c) 2020-2020, Ashar Khan, ashar786khan@gmail.com
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Google and Fraunhofer IOSB, Ettlingen, Germany
//

#ifndef BOOST_NUMERIC_UBLAS_EXPERIMENTAL_MATRIX
#define BOOST_NUMERIC_UBLAS_EXPERIMENTAL_MATRIX

#include <boost/numeric/ublas/tensor/tensor_engine.hpp>


namespace boost::numeric::ublas::experimental{
template <typename ValueType, typename Layout = layout::first_order >
  using dynamic_matrix = tensor_core<
    tensor_engine<
      dynamic_extents<2>,
        Layout,
        strides<dynamic_extents<2>>,
        std::vector<ValueType, std::allocator<ValueType>>
    >
  >;

template <typename ValueType, typename ExtentsType, typename Layout = layout::first_order>
using static_matrix = tensor_core <
    tensor_engine<
      ExtentsType,
      Layout,
      strides<ExtentsType>,
      std::array<ValueType, static_product_v<ExtentsType>>
    >
  >;
}
#endif
