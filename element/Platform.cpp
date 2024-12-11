#include "Platform.h"
#include "../Resource.h"
#include <fstream>
#include <iostream>
#include <allegro5/allegro_primitives.h>

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
    for (auto& rect : rectangles) {
        if (rect.can_move) {
            rect.x1 += rect.vx;
            rect.x2 += rect.vx;
            rect.y1 += rect.vy;
            rect.y2 += rect.vy;      
            if(rect.move_type == 1){          
                if (rect.x1 < rect.start_x|| rect.x2 > rect.end_x)
                    rect.vx = -rect.vx; 
                if (rect.y1 < rect.start_y|| rect.y2 > rect.end_y)
                    rect.vy = -rect.vy;
            }
            else if (rect.move_type == 2) {
                if (rect.x1 <rect.left_boundary || rect.x2 >rect.right_boundary) {
                    rect.vx = -rect.vx; 
                }
                if (rect.y1 <rect.up_boundary || rect.y2 >rect.down_boundary) {
                    rect.vy = -rect.vy; 
                }
            }
        }
    }
}


void Platform::draw() {
    for (const auto& rect : rectangles) {
        ALLEGRO_BITMAP* texture = textures[rect.texture_type];
        if(rect.visible && texture){
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