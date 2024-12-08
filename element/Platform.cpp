#include "Platform.h"
#include "../Resource.h"
#include <fstream>
#include <iostream>
#include <allegro5/allegro_primitives.h>

Platform::Platform(){

}
void Platform::loadmap(const std::string& map, int window_width, int window_height){
    rectangles.clear();
    
    block_width = window_width / 20.0;
    block_height = window_height / 12.0;    
    
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

                if(type == 9) rectangles.emplace_back(x1, y1, x2, y2, type, true, 1.0, 0.0);
                else rectangles.emplace_back(x1, y1, x2, y2, type);
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
    for (auto& rect : rectangles) {
        if (rect.can_move) {

            rect.x1 += rect.dx;
            rect.x2 += rect.dx;
            rect.y1 += rect.dy;
            rect.y2 += rect.dy;


            if (rect.x1 < DC->window_width / 20 * 10  || rect.x2 > DC->window_width / 20 * 16) {
                rect.dx = -rect.dx; 
            }
        }
    }
}


void Platform::draw() {
    for (const auto& rect : rectangles) {
        ALLEGRO_BITMAP* texture = textures[rect.type];
        if(texture){
            al_draw_scaled_bitmap(
                texture,
                0, 0, al_get_bitmap_width(texture), al_get_bitmap_height(texture), 
                rect.x1, rect.y1, block_width, block_height, 
                0
            );
        }
        else{
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