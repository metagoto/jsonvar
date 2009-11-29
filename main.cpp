
#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "jsonvar.hpp"


struct json_conv_visitor : public boost::static_visitor<std::string>
{
    std::string operator()(const json_object& val) const
    {
        std::ostringstream os;
        os << "{";
        for (json_object::const_iterator i(val.begin()), e(val.end())
            ; i != e; ++i)
        {
            os << i->first << ": "
               << boost::apply_visitor(json_conv_visitor(), i->second)
               << ", ";
        }
        os << "}";
        return os.str();
    }

    std::string operator()(const json_array& val) const
    {
        std::ostringstream os;
        os << "[";
        for (json_array::const_iterator i(val.begin()), e(val.end())
            ; i != e; ++i)
        {
            os << boost::apply_visitor(json_conv_visitor(), *i) 
               << ", ";
        }
        os << "]";
        return os.str();
    }

    std::string operator()(const std::string& val) const
    {
        return std::string("\"").append(val).append("\"");
    }
    
    template<typename T> 
    std::string operator()(const T& val) const
    {
        return boost::lexical_cast<std::string>(val);
    }
};


template<typename T>
T conv_to(const json_type& from)
{
   return boost::apply_visitor(json_conv_visitor(), from);
}


int main()
{
    json_array arr {3.14, 21, true};
  
    json_object obj;
    obj["key"] = 42;
    obj["str"] = std::string("hello");
    obj["arr"] = arr;
   
    std::cout << conv_to<std::string>(obj) << std::endl;
    
    return 0;
}



