/*

g++ -std=c++11 -I/Users/junhokim/Programming/c++/stroustrup/include -L/Users/junhokim/Programming/c++/stroustrup/include -lbookgui -lstdc++ -lfltk -lfltk_images -lfltk_jpeg -framework Cocoa hello_graphic_world.cpp

*/

#include<iostream>
#include"Simple_window.h"
#include"Graph.h"

int main()
{    
    std::cout << "Hello Graphic World! \n"; 


    using namespace Graph_lib;
    Point tl{100, 100};

    Simple_window win{tl, 600,400,"Canvas"};
    
    Polygon poly;
    
    poly.add(Point{300, 200});
    poly.add(Point{350, 100});
    poly.add(Point{400, 200});
    
    poly.set_color(Color::red);

    win.attach(poly);
    win.wait_for_button();
}
