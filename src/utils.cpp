#include "constants.h"
#include "utils.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

template <typename T>
void print(T &object) {
    cout << "Unknown Type!!!" << endl;
}

template <typename T>
void print(map<string, T> &object) {
    cout << "Map:{";
    for (auto elem : object) {
        cout << "'" << elem.first << "'"
             << ":" << elem.second << ", ";
    }
    cout << "}" << endl;
}

template <typename T>
void print(const map<string, T> &object) {
    cout << "const ";
    print(const_cast<map<string, T> &>(object));
}

template <typename T>
void print(vector<T> &object) {
    cout << "Vector:{";
    for (auto elem : object) {
        cout << elem << ',';
    }
    cout << "}" << endl;
}

template <typename T>
void print(const vector<T> &object) {
    cout << "const ";
    print(const_cast<vector<T> &>(object));
}

void print(sys::EVENT &event_type) {
    if (event_type == sys::EVENT::Market_updated) {
        cout << "Market_updated" << endl;
    } else if (event_type == sys::EVENT::Data_cleaned) {
        cout << "Data_cleaned" << endl;
    } else if (event_type == sys::EVENT::Signal_generated) {
        cout << "Signal_generated" << endl;
    } else if (event_type == sys::EVENT::Submit_order) {
        cout << "Submit_order" << endl;
    } else if (event_type == sys::EVENT::Record_result) {
        cout << "Record_result" << endl;
    }
};
