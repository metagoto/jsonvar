#pragma once

#include <vector>
#include <unordered_map>
#include <boost/variant.hpp>
#include <boost/variant/static_visitor.hpp>

typedef boost::make_recursive_variant
<
    int
  , double
  , bool
  , std::string
  , std::unordered_map<std::string, boost::recursive_variant_> // object
  , std::vector<boost::recursive_variant_> // array

>::type json_type; // generic json type

typedef std::unordered_map<std::string, json_type> json_object;

typedef std::vector<json_type> json_array;
