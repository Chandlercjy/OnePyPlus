#pragma once
#include "constants.h"
#include <iostream>

using std::cout;
using std::endl;

template <typename T>
void print_map(const T &map_object) {
    cout << "Map{ ";
    for (auto elem : map_object) {
        cout << "'" << elem.first << "'"
             << ":" << elem.second << ", ";
    }
    cout << " }" << endl;
}

void print_type(EVENT event_type) {
    if (event_type == EVENT::Market_updated) {
        cout << "Market_updated" << endl;
    } else if (event_type == EVENT::Data_cleaned) {
        cout << "Data_cleaned" << endl;
    } else if (event_type == EVENT::Signal_generated) {
        cout << "Signal_generated" << endl;
    } else if (event_type == EVENT::Submit_order) {
        cout << "Submit_order" << endl;
    } else if (event_type == EVENT::Record_result) {
        cout << "Record_result" << endl;
    }
};
