#ifndef GAMESCENE_EARTH_H_INCLUDED
#define GAMESCENE_EARTH_H_INCLUDED

#include "../GameWindow.h"
#include "../Utils.h"
#include "../Global.h"
#include "../shapes/Shape.h"
#include "Scenemanager.h"
#include "Scene.h"
#include "../UI.h"
#include "../Resource.h"

#include "../data/DataCenter.h"
#include "../data/OperationCenter.h"
#include "../data/SoundCenter.h"
#include "../data/ImageCenter.h"
#include "../data/FontCenter.h"

#include "../Player.h"
#include "../Level.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <cstring>  
#include <fstream>
#include <iostream>

#include "../element/Hero.h"
#include "../element/Platform.h"

class Gamescene_earth : public Scene{
    public:
        Gamescene_earth();
        ~Gamescene_earth();

        void init() override;
        bool update() override;
        void draw() override;
        void destroy() override;

        void hero_init();
    private:
        /**
         * @brief States of the game process in game_update.
         * @see Game::game_update()
         */
        enum class STATE {
            PLAYING, // -> PAUSE, END
            PAUSE, // -> LEVEL
            END
        };
        STATE state;
        ALLEGRO_EVENT event;
        ALLEGRO_BITMAP *game_icon;
        ALLEGRO_BITMAP *background_img;
        ALLEGRO_BITMAP *earth_wall;
        ALLEGRO_BITMAP *earth_land;
        ALLEGRO_BITMAP *earth_mud;
        static ALLEGRO_SAMPLE_INSTANCE *background_music;

        bool BGM_played;
};

#endif
