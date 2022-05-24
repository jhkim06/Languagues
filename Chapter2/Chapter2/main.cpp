//
//  main.cpp
//  Chapter2
//
//  Created by Junho Kim on 2022/04/22.
//

#include "std_lib_facilities.h"

int main() {
    // insert code here...
    std::cout << "Hello, World!\n";
    //keep_window_open();
    
    /*
     The “places” in which we store data are called objects.
     
     */
    // five most frequently used types


    constexpr double pi = 3.14159; // constexpr must be given at compile time
    int n = 0;
    //cin >> n;
    //const int c2 = n+7; // not known at compile time, but do not change after initialization.

    //char a = 'A';
    //cout << a << " " << int(a) << "\n";
    for(char a = 'A'; a <= 'Z'; a++){
        cout << a << " " << int(a) << "\n";
    }

    //simple_error("you're kidding!");
    /*
     간단히 말해서 vector는 sequence of elements that you can access by an index.
     */
    
    vector<string> words;
    string disliked = "Broccoli";
    
    for(string word ; cin >> word; ){
        words.push_back(word);
    }
    
    for(string word : words){
        if(word == disliked){
            cout << "BLEEP" << "\n";
        }
        else{
            cout << word << "\n";
        }
    }
}
