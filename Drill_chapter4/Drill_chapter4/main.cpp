//
//  main.cpp
//  Drill_chapter4
//
//  Created by Junho Kim on 2022/04/23.
//

#include "../../include/std_lib_facilities.h"

using namespace std;
const vector<string> units{"cm", "m", "in", "ft"};
// conversion factors
constexpr double cm_per_inch{2.54};
constexpr double cm_per_m{100.};
constexpr double in_per_ft{12.};

bool check_inputs(const double length, const string unit){

    if(length < 0){
        cout << "Length should be positive.\n";
        return false;
    }
    
    bool valid_unit{false};
    for(auto unit_: units){
        if(unit_ == unit){
            valid_unit = true;
            break;
        }
    }
    if(!valid_unit){
        cout << "Only cm, m, in, ft are valid units.\n";
        return false;
    }
    
    return true;
}

void convert_to_m(double& length, const string unit){
    if(unit != "m"){
        if(unit == "cm"){
            length = length / cm_per_m;
        }
        if(unit == "in"){
            length = length * cm_per_inch; // inch to cm
            length = length / cm_per_m;
        }
        if(unit == "ft"){
            length = length * in_per_ft;
            length = length * cm_per_inch;
            length = length / cm_per_m;
        }
    }
}


int main(int argc, const char * argv[]) {
    // insert code hejre...
    
    double length{0};
    string unit{"m"};
    int count{0};
    double max{0};
    double min{0};
    double sum{0};
    
    string min_unit{""};
    string max_unit{""};
    double raw_min{0};
    double raw_max{0};

    vector<double> lengths{};
    
    cout<< "Please enter a length followed by a unit (cm, m, in, ft):\n";
    cout << "White space(s) needed between number and unit!\n";
    
    while(cin >> length >> unit){
        // check inputs
        if(check_inputs(length, unit)){
            // convert to m
            double temp_raw_length = length;
            convert_to_m(length, unit);
            if(count == 0){ // first input
                max = length;
                min = length;
                
                min_unit = unit;
                max_unit = unit;
                raw_min = temp_raw_length;
                raw_max = temp_raw_length;
            }
            else{
                if(length < min){
                    min = length;
                    
                    raw_min = temp_raw_length;
                    min_unit = unit;
                    cout << "the smallest so far.\n";
                }
                if(length > max){
                    max = length;
                    
                    raw_max = temp_raw_length;
                    max_unit = unit;
                    cout << "the largest so far.\n";
                }
            }
            lengths.push_back(length);
            sum += length;
            count++;
        }
    }
    
    cout << "Sum : " << sum << " m\n";
    cout << "Number of valid inputs: " << count << "\n";
    cout << "Largest length: " << max << " m (" << raw_max << " " << max_unit << ") \n";
    cout << "Smallest length: " << min << " m (" << raw_min << " " << min_unit << ") \n";
   
    sort(length);
    cout << "Print all the input lengths.\n";
    for(auto length_: lengths){
        cout << length_ << " m\n";
    }
    
    return 0;
}
