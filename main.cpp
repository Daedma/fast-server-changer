#include "headers\\realm_changer.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    std::cout << "Fast realm changer v0.1\n\nTo get the list of available commands, use the command -help\n";
    std::fstream fs;
    fs.open("frc.cache", std::ios_base::in | std::ios_base::out);
    std::string dir_str;
    std::filesystem::path wow_fold;
    if (!(std::getline(fs, dir_str)))
    {
        wow_fold = "unknow";
    }
    else
        wow_fold = dir_str;
    fs.close();
    server_cache realms { wow_fold };
    std::cout << "Current path to the catalog containing realmlist.wtf: " << wow_fold << std::endl;
    std::cout << "List of saved servers: \n";
    if (realms.fail())
    {
        std::cout << "Failed to get data, make sure that the entered way\nTo change the current path, use the command -path" << std::endl;
    }
    else
    {
        std::cout << realms << std::endl;
    }
    bool status = true;
    while (status)
    {
        std::string query, comm, arg, tmp;
        std::stringstream ss;
        std::cout << "Enter the command: ";
        std::getline(std::cin, query);
        ss.str(query);
        ss >> comm;
        ss >> tmp;
        arg += tmp;
        while (ss >> tmp)
        {
            arg += std::string { " " } + tmp;
        }
        if (comm == "-quit")
            break;
        if (!commands.count(comm))
        {
            std::cout << "Unidentified command" << std::endl;
            continue;
        }
        if (!commands.at(comm)(arg, realms))
        {
            std::cout << "The command was not successful.\n";
            continue;
        }
    }
}