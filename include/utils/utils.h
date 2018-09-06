#include "../Constants.h"
#include <algorithm>
#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#pragma once

namespace utils {
using namespace std::placeholders;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

class Log {
  public:
    Log() = delete;
    template <typename T>
    static void print(const T &object) {
        cout << object << endl;
    }

    template <typename T>
    static void print(map<string, T> &object) {
        cout << "Map:{";
        for (auto elem : object) {
            cout << "'" << elem.first << "'"
                 << ":" << elem.second << ", ";
        }
        cout << "}" << endl;
    }

    template <typename T>
    static void print(const map<string, T> &object) {
        cout << "const ";
        print(const_cast<map<string, T> &>(object));
    }

    template <typename T>
    static void print(vector<T> &object) {
        cout << "Vector:{";
        for (auto elem : object) {
            cout << elem << ',';
        }
        cout << "}" << endl;
    }

    template <typename T>
    static void print(const vector<T> &object) {
        cout << "const ";
        print(const_cast<vector<T> &>(object));
    }

    template <typename T>
    static int add_clock(T func) { //自行对局部进行计时
        auto t0 = clock();
        func();
        auto t1 = clock();
        return t1 - t0;
    }

    template <typename T>
    static void log_time(T func, int iter_times) { // func需要返回运行时间
        int result = 0;
        int max_time = 0;
        int min_time = 999999;
        for (int i = 0; i <= iter_times; ++i) {
            int times = func();
            max_time = std::max(times, max_time);
            min_time = std::min(times, min_time);
            result += (times);
        };
        double output = result / (iter_times * 1000.0);
        double max_output = max_time / 1000.0;
        double min_output = min_time / 1000.0;
        cout << "Average times: " << output << "s in " << iter_times << " loops." << endl;
        cout << "Max times: " << max_output << "s" << endl;
        cout << "Min times: " << min_output << "s" << endl;
        cout << "*------------------------------------*" << endl;
    }

    static void log_time(void (*func)(), int iter_times) { // func不需要返回运行时间
        auto new_func = [&] { return add_clock(func); };
        log_time(new_func, iter_times);
        cout << 1;
    }

    static void print(op::EVENT &event_type) {
        if (event_type == op::EVENT::Market_updated) {
            cout << "Market_updated" << endl;
        } else if (event_type == op::EVENT::Data_cleaned) {
            cout << "Data_cleaned" << endl;
        } else if (event_type == op::EVENT::Signal_generated) {
            cout << "Signal_generated" << endl;
        } else if (event_type == op::EVENT::Submit_order) {
            cout << "Submit_order" << endl;
        } else if (event_type == op::EVENT::Record_result) {
            cout << "Record_result" << endl;
        }
    };

    static void handle_error(const string &file, const int &line, const string &msg) {
        cout << "Error in File: " << file << ", Line: " << line << endl;
        throw std::logic_error(msg);
    }
};

class Stl {
  public:
    Stl() = delete;

    template <typename T>
    static const bool is_elem_in_vector(const vector<string> &vec, const T &value) {
        auto it = find(vec.cbegin(), vec.cend(), value);
        if (it != vec.cend())
            return true;
        return false;
    }

    template <typename T1, typename T2>
    static const bool is_elem_in_map_key(const map<T1, T2> &map_obj, const T1 &key) {
        for (auto &value : map_obj) {
            if (value.first == key)
                return true;
        }
        return false;
    }
};

class Math {
  public:
    Math() = delete;
    static double Round(double value, int num) {
        return std::round(value * (std::pow(10.0, num))) / std::pow(10.0, num);
    };
};

} // namespace utils
