#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <optional>
#include <fstream>

//#define FILE_DEBUG
//#define DEBUG


template<typename T, std::size_t N>
std::ostream& operator << (std::ostream& o, const std::array<T, N>& arr)
{
    o << '[';
    for (const auto& l: arr)
        o << l << ", ";
    o << ']';

    return o;
}

template<typename T>
std::ostream& operator << (std::ostream& o, const std::vector<T>& vec)
{
    o << '{';
    for (const auto& l: vec)
        o << l << ", ";
    o << '}';

    return o;
}

template<typename T, typename T2>
std::ostream& operator<<(std::ostream& o, const std::pair<T, T2>& pair)
{
    o << '(' << pair.first << ' ' << pair.second << ')';
    return o;
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::optional<T>& optional)
{
    if (optional.has_value())
        o << '*' << optional.value << '*';
    else
        o << "**";
    return o;
}

struct logger
{
    template<typename... EmptyArgs>
    static void debug() { }
    template<typename T, typename... Args>
    static void debug(const T& arg1, const Args&... args)
    {
        #ifdef DEBUG
        #ifndef FILE_DEBUG
        std::cout<<arg1<<std::flush;
        #else
        file << arg1;
        #endif
        debug(args...);
        #endif
    }

    static void init()
    {
        file.open("logs.txt");
    }
    static void destruct()
    {
        file.close();
    }
    static std::ofstream file;
};

class LoggerHandeler
{
public:
    LoggerHandeler()
    {
        logger::init();
    }
    ~LoggerHandeler()
    {
        logger::destruct();
    }
};
