#include "..\\serv_cache.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

server_cache::server_cache(const std::filesystem::path& Path) :
    _path(Path), _flag(true)
{
    std::ifstream ifs { Path.generic_string() + std::string { "/realms.cache" }, std::ios_base::in };
    if (!ifs)
    {
        std::fstream fs { Path.generic_string() + std::string { "/realmlist.wtf" }, std::ios_base::in };
        if (fs)
        {
            fs.close();
            fs.open(_path.generic_string() + std::string { "/realms.cache" }, std::ios::out);
            fs.close();
            return;
        }
        else
        {
            _flag = false;
            return;
        }
    }
    std::string s;
    while (std::getline(ifs, s))
    {
        _cache.emplace_back(s);
    }
}

void server_cache::edit_path(const std::filesystem::path& Path)
{
    _flag = true;
    _path = Path;
    std::ifstream ifs { Path.generic_string() + std::string { "/realms.cache" }, std::ios_base::in };
    if (!ifs)
    {
        std::fstream fs { Path.generic_string() + std::string { "/realmlist.wtf" }, std::ios_base::in };
        if (fs)
        {
            fs.close();
            fs.open(_path.generic_string() + std::string { "/realms.cache" }, std::ios::out);
            fs.close();
            return;
        }
        else
        {
            _flag = false;
            return;
        }
    }
    std::string s;
    _cache.clear();
    while (std::getline(ifs, s))
    {
        _cache.emplace_back(s);
    }
}

void server_cache::update()
{
    if (_flag)
    {
        std::ofstream ofs { _path.generic_string() + std::string { "/realms.cache" }, std::ios::trunc };
        for (const auto& i : _cache)
        {
            ofs << i.name() << '\n';
        }
    }
}

bool server_cache::status() const
{
    server_cache Cache(_path);
    for (const auto& rhs : _cache)
    {
        if (std::find(Cache._cache.cbegin(), Cache._cache.cend(), rhs) == Cache._cache.cend())
            return false;
    }
    return true;
}

server_name& server_cache::operator[](size_t ind)
{
    return _cache[ind];
}

const server_name& server_cache::operator[](size_t ind) const
{
    return _cache[ind];
}

void server_cache::add(const server_name& Name)
{
    _cache.emplace_back(Name);
}

bool server_cache::remove(size_t ind)
{
    if (ind >= _cache.size())
        return false;
    _cache.erase(std::next(_cache.begin(), ind));
    return true;
}

size_t server_cache::size() const
{
    return _cache.size();
}

bool server_cache::fail() const
{
    return !_flag;
}

const std::filesystem::path& server_cache::get_path() const
{
    return _path;
}

std::ostream& operator<<(std::ostream& _os, const server_cache& Cache)
{
    for (size_t i = 0; i != Cache.size(); ++i)
    {
        _os << (i + 1) << ". " << Cache[i].name() << std::endl;
    }
    return _os;
}