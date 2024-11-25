#include "Hero.h"
#include "data/DataCenter.h"
#include "data/GIFCenter.h"
#include "algif5/algif.h"
#include <allegro5/allegro_primitives.h>
#include "shapes/Rectangle.h"
#include "Platform.h"

namespace HeroSetting {
	static constexpr char gif_root_path[50] = "./assets/gif/Hero";
	static constexpr char gif_postfix[][10] = {
		"left", "right", "front", "back"
	};
}

void Hero::init(){
    for(size_t type = 0 ; type < static_cast<size_t>(HeroState::HEROSTATE_MAX) ; type++){
        char buffer[50];
        sprintf(buffer, "%s/dragonite_%s.gif",
                HeroSetting::gif_root_path,
                HeroSetting::gif_postfix[static_cast<int>(type)]);
        gifpath[static_cast<HeroState>(type)] = std::string(buffer);
    }
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifpath[state]);
    DataCenter *DC = DataCenter::get_instance();
    shape.reset(
        new Rectangle(
            DC->window_width/2,
            DC->window_height/2,
            DC->window_width/2 + gif->width,
            DC->window_height/2 + gif->height
        )
    );
}

void Hero::update() {
    DataCenter* DC = DataCenter::get_instance();
    Platform* platforms = DC->platforms;

    Rectangle* rect = dynamic_cast<Rectangle*>(shape.get());
    if (!rect) return;

    // 跳跃逻辑
    if (DC->key_state[ALLEGRO_KEY_W] && !is_jumping) {
        v_speed = jump_speed;
        is_jumping = true;
    }

    // 水平移动
    if (DC->key_state[ALLEGRO_KEY_A]) {
        rect->update_center_x(rect->center_x() - speed);
        state = HeroState::LEFT;
    } else if (DC->key_state[ALLEGRO_KEY_D]) {
        rect->update_center_x(rect->center_x() + speed);
        state = HeroState::RIGHT;
    }

    // 应用重力
    rect->update_center_y(rect->center_y() + v_speed);
    v_speed += gravity;

    // 碰撞检测：检查是否站在平台上
    bool on_platform = false;
    for (const auto& platform : platforms->get_platforms()) {
        if (rect->y2 >= platform.y1 && rect->y1 < platform.y1 && // 确保从上方接触平台
            rect->x2 > platform.x1 && rect->x1 < platform.x2 &&  // 确保水平范围重叠
            v_speed >= 0) { // 仅检测向下移动
            rect->update_center_y(platform.y1 - (rect->y2 - rect->y1) / 2); // 调整到平台顶部
            v_speed = 0;  // 停止垂直移动
            is_jumping = false;  // 停止跳跃状态
            on_platform = true;
            break;
        }
    }

    // 如果不在平台上，则继续下落
    if (!on_platform && rect->y2 < DC->window_height) {
        is_jumping = true; // 开始自由落体
    } else if (rect->y2 >= DC->window_height) {
        // 限制角色在窗口底部
        rect->update_center_y(DC->window_height - (rect->y2 - rect->y1) / 2);
        v_speed = 0;
        is_jumping = false;
    }
}

void Hero::draw(){
    GIFCenter *GIFC = GIFCenter::get_instance();
    ALGIF_ANIMATION *gif = GIFC->get(gifpath[state]);
    algif_draw_gif(gif, shape->center_x() - gif->width/2, shape->center_y() - gif->height/2, 0);    
    
    Rectangle* rect = dynamic_cast<Rectangle*>(shape.get()); 
    if (rect) {
        al_draw_rectangle(
            rect->x1, rect->y1, rect->x2, rect->y2,
            al_map_rgb(255, 0, 0), 
            2.0 
        );
    }
}