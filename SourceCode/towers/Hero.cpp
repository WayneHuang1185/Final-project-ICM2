#include<Hero.h>
#include "../data/DataCenter.h"
#include "../data/ImageCenter.h"
#include "../algif5/algif.h"
#include "../shapes/Rectangle.h"

namespace HeroSetting {
	static constexpr char gif_root_path[50] = "../assets/gif/Hero";
    static constexpr char gif_postfix[][10]={
        "left",
        "right",
        "front",
        "back",
    };
}
void HERO::init(){
    for(size_t type=0; type < static_cast<size_t>(Herostate::HEROSTATE_MAX);++type){
        char buffer[50];
        sprintf("buffer","%s/dragonite_%s.gif",
            HeroSetting::gif_root_path,
            
        )
    }


}