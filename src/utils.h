#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;
namespace sys {
enum class EVENT;
}

template <typename T>
void print(T &);

template <typename T>
void print(map<string, T> &);

template <typename T>
void print(const map<string, T> &);

template <typename T>
void print(const map<string, T> &);

template <typename T>
void print(sys::EVENT &);


