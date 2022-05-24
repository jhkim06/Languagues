//
//  main.cpp
//  Drill_Project13
//
//  Created by Junho Kim on 2022/05/20.
//

#include "Simple_window.h"
#include "Graph.h"
//#include "std_lib_facilities.h"

using namespace Graph_lib;

int main()
try{

    Point t1 {100,100};
    Simple_window win {t1,1000,800,"Canvas"};
    
    Lines grid;
    int x_size = win.x_max();
    int y_size = win.y_max();
    int x_grid = 100;
    int y_grid = 100;
    
    const int x_grid_max = 800;
    
    for (int x=x_grid; x<=x_grid_max; x+=x_grid)
        grid.add(Point{x,800}, Point{x,0});
    for (int y=y_grid; y<y_size; y+=y_grid)
        grid.add(Point{0,y}, Point{800,y});
    
    win.attach(grid);
   
    Vector_ref<Rectangle> rects;
    for (int i=0; i<x_grid_max/x_grid; i++){
        rects.push_back(new Rectangle{Point{i*100,i*100},100,100});
        rects[rects.size()-1].set_fill_color(Color::red);
        rects[rects.size()-1].set_color(Color::invisible);
        win.attach(rects[rects.size()-1]);
    }
    
    int current_xi=0, current_yi=0;
    Image pic{Point{current_xi*100,current_yi*100}, "/Users/jhkim/Learning/C++/Stroustrup/Drill_Project13/Drill_Project13/picture.jpg"};
    pic.set_mask(Point{0,0},100,100);
    win.attach(pic);
    
    for (int yi=current_yi; yi<(y_size/y_grid); yi++){ // current_yi가 7인 경우에도 xi에 대한 loop를 실행하야하므로 (y_size/y_grid)에서 1을 빼지 않았다. 
        for (int xi=current_xi; xi<(x_grid_max/x_grid)-1; xi++){
            if (xi!=yi) win.wait_for_button();
            pic.move(100,0);
        }
        if (yi==(y_size/y_grid)-1) break;
        win.wait_for_button();
        pic.move(-700,100); // move to the first colum in the next row
        current_xi=0;
    }
    
    win.wait_for_button();
}
catch(exception& e){
    return 1;
}
catch(...){
    return 2;
}
