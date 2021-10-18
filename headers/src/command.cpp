#include "../command.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

bool COMMANDS::add(const std::string& _Arg, server_cache& _Cache)
{
    if (_Cache.fail())
        return false;
    _Cache.add(_Arg);
    _Cache.update();
    std::cout << "The server successfully added" << std::endl;
    return true;
}

bool COMMANDS::remove(const std::string& _Arg, server_cache& _Cache)
{
    if (_Cache.fail())
        return false;
    std::istringstream is { _Arg };
    size_t ind;
    bool valid;
    if (is >> ind)
        valid = _Cache.remove(ind - 1);
    else
        return false;
    _Cache.update();
    if (valid)
    {
        std::cout << "The server successfully removed" << std::endl;
    }
    return valid;
}

bool COMMANDS::set(const std::string& _Arg, server_cache& _Cache)
{
    if (_Cache.fail())
        return false;
    std::istringstream is { _Arg };
    size_t ind;
    if (is >> ind)
    {
        _Cache[ind - 1].push(_Cache.get_path());
        std::cout << "Realm was successfully changed" << std::endl;
    }
    else
        return false;
    return true;
}

bool COMMANDS::path(const std::string& _Arg, server_cache& _Cache)
{
    if (_Arg.empty())
    {
        std::cout << "Current directory: " << _Cache.get_path() << std::endl;
        return true;
    }
    std::ofstream fs;
    fs.open("frc.cache");
    fs << _Arg;
    fs.close();
    _Cache.edit_path(_Arg);
    if (!_Cache.fail())
    {
        std::cout << "The path was successfully replaced" << std::endl;
    }
    return !_Cache.fail();
}

bool COMMANDS::help(const std::string& _Arg, server_cache& _Cache)
{
    std::cout <<
        "List of Commands:\n" <<
        "-list | Show list of saved servers\n" <<
        "-add | Saves server in cache\tAccepts the server name as an argument\n" <<
        "-remove | Deletes a cache server\tAccepts the serial number of the server as an argument in the list of saved servers\n" <<
        "-set | Replaces the current server to one of the preserved\tAccepts the server number as an argument in the list of saved servers\n" <<
        "-help | Get informatio\n" <<
        "-path | Get / Change Current Path to Reader with RealmList.wtf\tNothing / Full (Absolute) Path\n" <<
        "-quit | Exit program\n" <<
        "-cur | Show current server\n" <<
        "-current | The same as -cur\n" <<
        "Note: This program is not suitable for working with realmList.wtf servers which include more than one line (for example, Molten WOW and WOW Biz)" <<
        std::endl;
    return true;
}

bool COMMANDS::list(const std::string& _Arg, server_cache& _Cache)
{
    std::cout << "List of saved servers:\n" << _Cache << std::endl;
    return true;
}

bool COMMANDS::current(const std::string& _Arg, server_cache& _Cache)
{
    if (_Cache.fail())
        return false;
    std::ifstream ifs { _Cache.get_path().generic_string() + std::string { "/realmlist.wtf" } };
    std::string realm, line;
    std::getline(ifs, line);
    std::stringstream ss { line };
    ss >> realm >> realm >> realm;
    std::cout << "Current realm: " << realm << std::endl;
    ifs.close();
    return true;
}