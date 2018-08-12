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

template <class T>
void print(T &);

template <class T>
void print(map<string, T> &);

template <class T>
void print(const map<string, T> &);

template <class T>
void print(const map<string, T> &);

template <class T>
void print(sys::EVENT &);

