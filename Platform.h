#ifndef PLATFORM_H
#define PLATFORM_H

#include "Object.h"
#include "shapes/Rectangle.h"
#include <string>
#include <vector>

class Platform : public Object{
    public:
        Platform();

        void loadmap(const std::string& map, int window_width, int window_height);
        void init() ;
        void update() ;
        void draw() override;
        double get_block_width(){
            return block_width;
        }
        double get_block_height(){
            return block_height;
        }
        const std::vector<Rectangle>& get_platforms() const;
    private:
        std::vector<Rectangle> rectangles;
        double block_height;
        double block_width;
};

#endif