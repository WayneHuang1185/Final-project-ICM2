#include "Platform.h"
#include "../Resource.h"
#include <fstream>
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include"Hero.h"
#include"Glasses.h"
Platform::Platform(){

}
void Platform::loadmap(const std::string& map, std::map<int,RectangleParams>mode, int window_width, int window_height){
    rectangles.clear();
    textures.clear();
    block_width = window_width / 20.0;
    block_height = window_height / 12.0;    
    DataCenter *DC = DataCenter::get_instance();
    std::ifstream file(map);

    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << map << std::endl;
        return;
    }

    std::string line;

    int row = 0;
    while(std::getline(file, line)){
        for (size_t col = 0; col < line.size(); ++col) {
            if (line[col] >= '1' && line[col] <= '9') { 
                int type = line[col] - '0';
                double x1 = col * block_width;
                double y1 = row * block_height;
                double x2 = x1 + block_width;
                double y2 = y1 + block_height;
                if(mode.find(type)!=mode.end())
                    rectangles.emplace_back(x1,y1,x2,y2,type,mode[type]);
                }
            }
            ++row; 
        }
       
    file.close();
}

void Platform::init(){

}

void Platform::update() {
    DataCenter *DC = DataCenter::get_instance();
    Hero *hero=DC->hero;
    Rectangle h_rect=*dynamic_cast<Rectangle*>(hero->shape.get());
    for (auto& rect : rectangles) {
        if (rect.can_move) {
            switch(rect.move_type){
                case 1:
                    rect.x1 += rect.vx;
                    rect.x2 += rect.vx;    
                    if (rect.x1 <rect.boundary_1 || rect.x2 >rect.boundary_2)                
                        rect.vx = -rect.vx;
                    break; 
                case 2:
                    rect.y1 += rect.vy;
                    rect.y2 += rect.vy;
                    if (rect.y1 <rect.boundary_1 || rect.y2 >rect.boundary_2) 
                        rect.vy = -rect.vy; 
                    break;
                case 3:{
                    bool verticalCheck3 = rect.triger_dir_flip 
                     ? ((rect.vy > 0 && h_rect.y1 < rect.y2) || (rect.vy < 0 && h_rect.y2 > rect.y1))
                     : ((rect.vy > 0 && h_rect.y1 > rect.y2) || (rect.vy < 0 && h_rect.y2 < rect.y1));

                    bool horizontalCheck3 = ((h_rect.x2 > (rect.x1 + block_width / 5) && h_rect.x1 < rect.x1) || 
                        ((h_rect.x1 + block_width / 5) > rect.x2 && h_rect.x2 < rect.x2));
                    if (verticalCheck3 && horizontalCheck3)
                        rect.move_type=5;
                    break;
                }
                case 4:{
                    bool verticalCheck4 = rect.triger_dir_flip 
                     ? ((rect.vx > 0 && h_rect.x1 < rect.x2) || (rect.vx < 0 && h_rect.x2 > rect.x1))
                     : ((rect.vx > 0 && h_rect.x1 > rect.x2) || (rect.vx < 0 && h_rect.x2 < rect.x1));
                    bool horizontalCheck4 = ((h_rect.y2 > (rect.y1 + block_height / 5) && h_rect.y1 < rect.y1) || 
                        ((h_rect.y1 + block_height / 5) > rect.y2 && h_rect.y2 < rect.y2));
                    if (verticalCheck4 && horizontalCheck4)
                        rect.move_type=6;
                    break;
                }
                case 5:
                    rect.y1 += rect.vy;
                    rect.y2 += rect.vy;
                    if(!rect.dir && ((rect.vy>0 && rect.y2>rect.boundary_2) || (rect.vy<0 && rect.y1<rect.boundary_2))){
                        rect.vy = -rect.vy; 
                        rect.dir=true;
                    }
                    else if(rect.dir){
                        if(rect.vy<0 && rect.y1<rect.boundary_1){
                            rect.update_center_y(rect.boundary_1+block_height/2);
                            rect.vy = -rect.vy; 
                            rect.dir=false;
                            rect.move_type=3;
                        }
                        else if(rect.vy>0 && rect.y2>rect.boundary_1){
                            rect.update_center_y(rect.boundary_1-block_height/2);
                            rect.vy = -rect.vy; 
                            rect.dir=false;
                            rect.move_type=3;
                        }
                    }
                    break;
                case 6:
                    rect.x1 += rect.vx;
                    rect.x2 += rect.vx;
                    if(!rect.dir && ((rect.vx>0 && rect.x2>rect.boundary_2) || (rect.vx<0 && rect.x1<rect.boundary_2))){
                        rect.vx = -rect.vx; 
                        rect.dir=true;
                    }
                    else if(rect.dir){
                        if(rect.vx<0 && rect.x1<rect.boundary_1){
                            rect.update_center_x(rect.boundary_1+block_width/2);
                            rect.vx=-rect.vx;
                            rect.dir=false;
                            rect.move_type=4;
                        }
                        else if(rect.vx>0 && rect.x2>rect.boundary_1){
                            rect.update_center_x(rect.boundary_1-block_width/2);
                            rect.vx=-rect.vx;
                            rect.dir=false;
                            rect.move_type=4;
                        }
                    }
                    break;
            }
        }
    }
}


void Platform::draw() {
    DataCenter *DC = DataCenter::get_instance();
    Glasses *glasses=DC->glasses;
    for (const auto& rect : rectangles) {
        ALLEGRO_BITMAP* texture = textures[rect.texture_type];
        if((glasses->glasses_collected ||rect.visible) && texture){
            al_draw_scaled_bitmap(
                texture,
                0, 0, al_get_bitmap_width(texture), al_get_bitmap_height(texture), 
                rect.x1, rect.y1, block_width, block_height, 
                0
            );
        }
        if(debug){
            al_draw_filled_rectangle(
                rect.x1, rect.y1, rect.x2, rect.y2,
                al_map_rgb(100, 100, 255)
            );
        }
    }
}

const std::vector<Rectangle>& Platform::get_platforms() const {
    return rectangles;
}