//
//  main.cpp
//  Chapter12
//
//  Created by Junho Kim on 2022/05/15.
//
#include "Simple_window.h"
#include "Graph.h"
//#include "std_lib_facilities.h"

using namespace Graph_lib;

int main()
try{

    Point t1 {100,100};
    Simple_window win {t1,600,400,"Canvas"};
    
    int x_size=win.x_max();
    int y_size=win.y_max();
    int x_grid=80;
    int y_grid=40;
    
    Lines grid;
    
    grid.set_color(Color::red);
    
    for (int x=x_grid; x<x_size; x+=x_grid)
        grid.add(Point{x,0},Point{x,y_size});
    for (int y=y_grid; y<y_size; y+=y_grid)
        grid.add(Point{0,y},Point{x_size,y});
    
    win.attach(grid);
    
    Marked_polyline mpl {"1234"};
    mpl.add(Point{100,100});
    mpl.add(Point{150,200});
    mpl.add(Point{250,250});
    mpl.add(Point{300,200});
    
    win.attach(mpl);
    win.wait_for_button();
}
catch(exception& e){
    return 1;
}
catch(...){
    return 2;
}
