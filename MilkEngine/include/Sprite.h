#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "Quad.h"



class Sprite
{
public:
	Sprite();
	~Sprite();
	
	Quad quad;

	void Draw();
private:
};


#endif  //_SPRITE_H_
