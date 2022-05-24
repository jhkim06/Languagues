//
//  main.cpp
//  GUITest
//
//  Created by Junho Kim on 2022/04/22.
//

#include <iostream>
#include "Simple_window.h"
#include "Graph.h"

int main(int argc, const char * argv[]) {
   
    using namespace Graph_lib;
    
    Point t1{500, 100};
    Simple_window win{t1, 600, 400, "Canvas"};
    
    Polygon poly;

    poly.add(Point{300, 200});
    poly.add(Point{350, 100});
    poly.add(Point{400, 200});

    poly.set_color(Color::red);

    win.attach(poly);
    win.wait_for_button();
}
