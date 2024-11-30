#include "Platform.h"
#include <fstream>
#include <iostream>
#include <allegro5/allegro_primitives.h>

Platform::Platform(){}
void Platform::loadmap(const std::string& map, int window_width, int window_height){
    block_width = window_width / 20.0;
    block_height = window_height / 9.0;    
    
    std::ifstream file("./assets/map.txt");

    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << map << std::endl;
        return;
    }

    std::string line;

    int row = 0;
    while(std::getline(file, line)){
        for (size_t col = 0; col < line.size(); ++col) {
            if (line[col] == '1') { 
                double x1 = col * block_width;
                double y1 = row * block_height;
                double x2 = x1 + block_width;
                double y2 = y1 + block_height;
                rectangles.emplace_back(x1, y1, x2, y2);
            }
        }
        ++row; 
    }

    file.close();
}

void Platform::init(){

}

void Platform::update(){

}

void Platform::draw() {
    for (const auto& rect : rectangles) {
        al_draw_filled_rectangle(
            rect.x1, rect.y1, rect.x2, rect.y2,
            al_map_rgb(100, 100, 255) 
        );
    }
}

const std::vector<Rectangle>& Platform::get_platforms() const {
    return rectangles;
}