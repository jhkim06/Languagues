//
//  main.cpp
//  Chapter5
//
//  Created by Junho Kim on 2022/04/23.
//

#include <iostream>
#include <std_lib_facilities.h>

class Bad_area{};

int area(int length, int width){
    //if(length<=0||width<=0) return -1;
    if(length<=0||width<=0) throw Bad_area();
    return length*width;
}
int framed_area(int length, int width){
    constexpr int frame = 2;
    return area(length-frame, width-frame);
}

void error_test(string s1){
    throw runtime_error(s1);
}
void f(int x, int y , int z){
    
    int area1 = area(x,y);
    if(area1<=0) error("non-positive area.\n");
    int area2 = framed_area(3, z);
    int area3 = framed_area(y, z);
    double ratio = double(area1)/area3;
    
    cout << "area1: " << area1 << "\n";
    cout << "area2: " << area2 << "\n";
    cout << "area3: " << area3 << "\n";
    cout << "ratio: " << ratio << "\n";
}
int main(int argc, const char * argv[]) {
    // insert code here...
  
    int x{0}, y{0}, z{0};
    while(cin >> x >> y >> z)
    {
        try{
            f(x, y, z);
        }
        catch(Bad_area){
            cout << "Oop! bad arguments to area()\n";
        }
    }
    error_test("uncaughted error!");
    
    
    
    return 0;
}
