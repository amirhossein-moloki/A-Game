/*
    __ _____ _____ _____
 __|  |   __|     |   | |  JSON for Modern C++
|  |  |__   |  |  | | | |  version 3.11.2
|_____|_____|_____|_|___|  https://github.com/nlohmann/json

SPDX-FileCopyrightText: 2013-2022 Niels Lohmann <https://nlohmann.me>
SPDX-License-Identifier: MIT
*/

#ifndef INCLUDE_NLOHMANN_JSON_HPP_
#define INCLUDE_NLOHMANN_JSON_HPP_

#define NLOHMANN_JSON_VERSION_MAJOR 3
#define NLOHMANN_JSON_VERSION_MINOR 11
#define NLOHMANN_JSON_VERSION_PATCH 2

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iosfwd>
#include <iterator>
#include <memory>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include <nlohmann/adl_serializer.hpp>
#include <nlohmann/byte_container_with_subtype.hpp>
#include <nlohmann/detail/conversions/from_json.hpp>
#include <nlohmann/detail/conversions/to_json.hpp>
#include <nlohmann/detail/exceptions.hpp>
#include <nlohmann/detail/hash.hpp>
#include <nlohmann/detail/input/binary_reader.hpp>
#include <nlohmann/detail/input/input_adapters.hpp>
#include <nlohmann/detail/input/json_sax.hpp>
#include <nlohmann/detail/input/lexer.hpp>
#include <nlohmann/detail/input/parser.hpp>
#include <nlohmann/detail/iterators/internal_iterator.hpp>
#include <nlohmann/detail/iterators/iter_impl.hpp>
#include <nlohmann/detail/iterators/iteration_proxy.hpp>
#include <nlohmann/detail/iterators/json_reverse_iterator.hpp>
#include <nlohmann/detail/iterators/primitive_iterator.hpp>
#include <nlohmann/detail/json_pointer.hpp>
#include <nlohmann/detail/json_ref.hpp>
#include <nlohmann/detail/macro_scope.hpp>
#include <nlohmann/detail/meta/cpp_future.hpp>
#include <nlohmann/detail/meta/type_traits.hpp>
#include <nlohmann/detail/output/binary_writer.hpp>
#include <nlohmann/detail/output/output_adapters.hpp>
#include <nlohmann/detail/output/serializer.hpp>
#include <nlohmann/detail/string_concat.hpp>
#include <nlohmann/detail/string_escape.hpp>
#include <nlohmann/detail/value_t.hpp>
#include <nlohmann/ordered_map.hpp>

#endif // INCLUDE_NLOHMANN_JSON_HPP_
