#pragma once
#include <iosfwd>
#include <filesystem>
#include <vector>
#include "serv_name.hpp"


class server_cache
{
    std::filesystem::path _path;
    std::vector<server_name> _cache;
    bool _flag;
public:
    server_cache(const std::filesystem::path&);
    void edit_path(const std::filesystem::path&);
    void update();//обновление файла кэша в соотвествии с внесёнными изменениями
    bool status() const;//проверка актуальности данных в кэше без внесения обновлений
    server_name& operator[](size_t);
    const server_name& operator[](size_t) const;
    void add(const server_name&);
    bool remove(size_t);
    size_t size() const;
    bool fail() const;
    const std::filesystem::path& get_path() const;
};

std::ostream& operator<<(std::ostream&, const server_cache&);