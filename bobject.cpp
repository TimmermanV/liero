#include "bobject.hpp"

#include "gfx/color.hpp"
#include "game.hpp"
#include "constants.hpp"

void Game::createBObject(fixedvec pos, fixedvec vel)
{
	Common& common = *this->common;

	BObject& obj = *bobjects.newObjectReuse();
	
	obj.color = rand(LC(NumBloodColours)) + LC(FirstBloodColour);
	obj.pos = pos;
	obj.vel = vel;
}

bool BObject::process(Game& game)
{
	Common& common = *game.common;
	
	pos += vel;
	
	auto ipos = ftoi(pos);
	
	if(!game.level.inside(ipos))
	{
		return false;
	}
	else
	{
		PalIdx c = game.level.pixel(ipos);
		Material m = game.level.mat(ipos);
		
		if(m.background())
			vel.y += LC(BObjGravity);

		LTRACE(blod, c, xpos, ipos.x);
		LTRACE(blod, c, ypos, ipos.y);
			
		if((c >= 1 && c <= 2)
		|| (c >= 77 && c <= 79)) // TODO: Read from EXE
		{
			int w = 77 + game.rand(3);
			game.level.setPixel(ipos, w, common);
			common.logDrawPixelOnMap(w, ipos.x, ipos.y);
			return false;
		}
		else if(m.anyDirt())
		{
			int w = 82 + game.rand(3);
			game.level.setPixel(ipos, w, common);
			common.logDrawPixelOnMap(w, ipos.x, ipos.y);
			return false;
		}
		else if(m.rock())
		{
			int w = 85 + game.rand(3);
			game.level.setPixel(ipos, w, common);
			common.logDrawPixelOnMap(w, ipos.x, ipos.y);
			return false;
		}
	}
	
	return true;
}
