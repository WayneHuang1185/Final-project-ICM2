#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

#include <string>
#include <map>
#include "../Object.h"



// fixed settings
enum class Herostate {
	LEFT,
    RIGHT,
    FRONT,
    BACK,
    HEROSTATE_MAX
};

/**
 * @brief The class of a monster (enemies).
 * @details Monster inherits Object and takes Rectangle as its hit box.
 */
class HERO : public Object
{
public:
	void init();
    void update();
    void draw();
private:
	Herostate state=Herostate::FRONT;
    double speed=5;
	std::map<Herostate,std::string>gitPath;
};
#endif
