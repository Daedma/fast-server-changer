#pragma once
#include <string>
#include <map>
#include <functional>
#include "serv_cache.hpp"

namespace COMMANDS{
    bool add(const std::string&, server_cache&);
    bool remove(const std::string&, server_cache&);
    bool set(const std::string&, server_cache&);
    bool help(const std::string&, server_cache&);
    bool path(const std::string&, server_cache&);
    bool list(const std::string&, server_cache&);
    bool current(const std::string&, server_cache&);
}
/*
command list:
-add,
-remove,
-set,
-help,
-path
*/
static const std::map<std::string, std::function<bool(const std::string&, server_cache&)>> commands
{
    std::pair <std::string, std::function<bool(const std::string&, server_cache&)>>{ std::string { "-add" }, std::function<bool(const std::string&, server_cache&)>{COMMANDS::add} },
    std::pair <std::string, std::function<bool(const std::string&, server_cache&)>>{ std::string { "-remove" }, std::function<bool(const std::string&, server_cache&)>{COMMANDS::remove} },
    std::pair <std::string, std::function<bool(const std::string&, server_cache&)>>{ std::string { "-set" }, std::function<bool(const std::string&, server_cache&)>{COMMANDS::set} },
    std::pair <std::string, std::function<bool(const std::string&, server_cache&)>>{ std::string { "-path" }, std::function<bool(const std::string&, server_cache&)>{COMMANDS::path} },
    std::pair <std::string, std::function<bool(const std::string&, server_cache&)>>{ std::string { "-help" }, std::function<bool(const std::string&, server_cache&)>{COMMANDS::help} },
    std::pair <std::string, std::function<bool(const std::string&, server_cache&)>>{ std::string { "-list" }, std::function<bool(const std::string&, server_cache&)>{COMMANDS::list} },
    std::pair <std::string, std::function<bool(const std::string&, server_cache&)>>{ std::string { "-cur" }, std::function<bool(const std::string&, server_cache&)>{COMMANDS::current} },
    std::pair <std::string, std::function<bool(const std::string&, server_cache&)>>{ std::string { "-current" }, std::function<bool(const std::string&, server_cache&)>{COMMANDS::current} }
};