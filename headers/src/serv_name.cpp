#include "..\\serv_name.hpp"
#include <iostream>
#include <fstream>

const std::string server_name::_prefix { "set realmlist " };

std::string& server_name::name()
{
    return _name;
}

const std::string& server_name::name() const
{
    return _name;
}

void server_name::push(const std::filesystem::path& Path) const
{
    std::ofstream ofs { Path.generic_string() + std::string { "/realmlist.wtf" }, std::ios::trunc };
    ofs << *this;
}

bool operator==(const server_name& lhs, const server_name& rhs)
{
    return lhs.name() == rhs.name();
}

std::ostream& operator<<(std::ostream& _os, const server_name& Name)
{
    _os << Name._prefix << Name.name();
    return _os;
}

std::istream& operator>>(std::istream& _is, server_name& Name)
{
    _is >> Name.name();
    return _is;
}