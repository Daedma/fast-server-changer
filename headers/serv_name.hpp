#pragma once
#include <string>
#include <iosfwd>
#include <filesystem>

class server_name
{
    friend std::ostream& operator<<(std::ostream&, const server_name&);
    friend std::ostream& operator<<(std::ostream&, const server_name&);
    std::string _name;
    static const std::string _prefix;
public:
    server_name(const std::string& Name) :
        _name(Name) {}
    server_name(const char* Name) :
        _name(Name) {}
    server_name() = default; //default contstructor
    std::string& name();
    const std::string& name() const;
    void push(const std::filesystem::path&) const;
};

bool operator==(const server_name&, const server_name&);

std::ostream& operator<<(std::ostream&, const server_name&);

std::istream& operator>>(std::istream&, server_name&);