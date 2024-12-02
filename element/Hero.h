#ifndef Hero_H_INCLUDED
#define Hero_H_INCLUDED
#include "Object.h"
#include "../data/DataCenter.h"
#include "Platform.h"

enum class HeroState{
    RUN,STOP,JUMP,MAX_STATE,DASH
};
enum class HeroDir{
    LEFT,RIGHT,MAX_DIR,UP,DOWN
};
enum class CollisionType{ 
    None, Top, Bottom, Left, Right 
};
namespace OnTheGround{
    constexpr double MAX_SPEED=10;
    constexpr double ACC_DURATION=0.516;
    constexpr double ACCELERATION=(MAX_SPEED/ACC_DURATION)/DataSetting::FPS;
    constexpr double DEC_DURATION=0.16;
    constexpr double DECELERATION=(MAX_SPEED/DEC_DURATION)/DataSetting::FPS;
    constexpr double TUR_DURATION=0.016;
    constexpr double TURN_ACCELERATION=(MAX_SPEED/TUR_DURATION)/DataSetting::FPS;
}
namespace InTheAir{
    constexpr double MAX_SPEED=10;
    constexpr double ACC_DURATION=0.257;
    constexpr double ACCELERATION=(MAX_SPEED/ACC_DURATION)/DataSetting::FPS;
    constexpr double DEC_DURATION=0.457;
    constexpr double DECELERATION=(MAX_SPEED/DEC_DURATION)/DataSetting::FPS;
    constexpr double TUR_DURATION=0.157;
    constexpr double TURN_ACCELERATION=(MAX_SPEED/TUR_DURATION)/DataSetting::FPS;
}
class Hero : public Object
{
public:
    void init();
    void update();
    void draw();
    CollisionType detectCollision(const Rectangle& platform);
private:
	double x_speed,y_speed;
    HeroState state;
    HeroDir dir; 
    double max_jump_height;
    double max_jump_speed;
    double max_hold_time;
    double hold_timer;
    bool jump_redy;
    bool hold;
    bool on_platform;
    int jump_timer;
    int jump_cooldown;
    const double down_gravity=0.6;
    const double up_gravity=0.3;
    int jump_count = 0;
    int hold_count=0;
    int max_jump_limit = 2;
    int max_hold_limit=1;
    bool debug=true;
    std::map<std::pair<HeroState,HeroDir>,std::string>gifpath; //exclude jump
    std::map<std::pair<HeroDir,std::string>,std::string>gifjump;
};

#endif