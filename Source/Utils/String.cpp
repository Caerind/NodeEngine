#include "String.hpp"
#include <algorithm>

namespace NString
{

void toLower(std::string& str)
{
    std::transform(str.begin(), str.end(),str.begin(), tolower);
}

void toUpper(std::string& str)
{
    std::transform(str.begin(), str.end(),str.begin(), toupper);
}

std::string split(std::string& base, char separator)
{
    std::size_t found = base.find(separator);
    if (found != std::string::npos)
    {
        std::string t = base.substr(0, found);
        base = base.substr(found + 1);
        return t;
    }
    return "";
}

std::string split(std::string& base, std::string const& separator)
{
    std::size_t found = base.find(separator);
    if (found != std::string::npos)
    {
        std::string t = base.substr(0, found);
        base = base.substr(found + 1);
        return t;
    }
    return "";
}

bool contains(std::string const& str, char c)
{
    return str.find(c) != std::string::npos;
}

bool contains(std::string const& str, std::string const& c)
{
    return str.find(c) != std::string::npos;
}

} // namespace NString
