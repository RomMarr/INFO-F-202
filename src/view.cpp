#include "view.hpp"
#include "controller.hpp"

#include <iostream>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_draw.H>

void LoadingScreen::Draw() {
    Fl_PNG_Image myimage = Fl_PNG_Image("loading.png");
    Fl_Box mypicturebox = Fl_Box(50, 50, 50, 50);
    mypicturebox.box(Fl_Boxtype::FL_FLAT_BOX);
    mypicturebox.color(fl_rgb_color(255, 0, 0));
    // mypicturebox.image(myimage);
    mypicturebox.redraw();

    // ->image(Fl_Shared_Image::get("/home/tim/Sources/Frontends/mac-attal/ico_attal-server.png"));

    
    // Fl_Box        box(Fl_Boxtype::FL_FLAT_BOX,0,0,500,500,"hello");     
    // Fl_JPEG_Image  png("loading.jpg");      
    // box.image(png);       

    // CE QUI MARCH
    // std::string teststring = "hello world";
    // fl_draw(teststring.c_str(), 50,50);  

    Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");
    box->box(FL_UP_BOX);
    box->labelfont(FL_BOLD+FL_ITALIC);
    box->labelsize(36);
    box->labeltype(FL_SHADOW_LABEL);   
    box->redraw();              

    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, 200, 200, 50, 50, fl_rgb_color(255, 0, 0));
}

MainWindow::MainWindow(): Fl_Window(500, 500, 500, 500, "Sokoban") {
    Fl::add_timeout(1.0/refreshPerSecond, timer_CB, this);
    // resizable(this);
}

void MainWindow::set_controller(shared_ptr<Controller> new_controller) {
    controller = new_controller;
}

void MainWindow::draw_board() {
    for (size_t y = 0; y < (*board).get_height(); y++) {
        for (size_t x = 0; x < (*board).get_width(); x++) {
            shared_ptr<Player> player_here = (*board).get_player_on_pos(make_tuple(x, y));
            shared_ptr<Block> box_here = (*board).get_box_on_pos(make_tuple(x, y));

            if (player_here) {
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, 50 * x, 50 * y, 50, 50, fl_rgb_color(0, 0, 255));
            } else if (box_here) {
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, 50 * x, 50 * y, 50, 50, (*box_here).getColor());
            } else {
                shared_ptr<Block> cell = (*board).get_block(make_tuple(x, y));
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, 50 * x, 50 * y, 50, 50, (*cell).getColor());
            }
        }
    }
}

void MainWindow::draw_menu() {
    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, 50, 50, 50, 50, fl_rgb_color(255, 128, 0));
}

void MainWindow::draw() {
    Fl_Window::draw();
    
    switch (current_screen) {
        case loading_screen: LoadingScreen::Draw(); break;
        case menu_screen: draw_menu(); break;
        case board_screen: draw_board(); break;
    
        default: break;
    }
}

int MainWindow::handle(int event) {
    // Doit pas être ici à terme, je voulais juste test, mais c'est cette fonction qui est call à chaque keyevent (souris ou clavier)
    if (event == FL_KEYDOWN) {
        //key_handler(Fl::event_key());
       
        controller->key_handler(Fl::event_key());
        
    }
}

void MainWindow::set_board(shared_ptr<Board> new_board) {
    board = new_board;
}

void MainWindow::display_menu() {
    current_screen = menu_screen;
}

void MainWindow::display_board() {
    if (board) {
        // current_screen = board_screen;
    }
}

void MainWindow::timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow*>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0/refreshPerSecond, timer_CB, userdata);
}