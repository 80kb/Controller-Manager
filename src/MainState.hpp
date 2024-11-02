#pragma once

#include <SDL2/SDL.h>
#include "sdl/sdl_boiler.hpp"

class cmMainState {
	SDL_Event 	event;
	SDL_State 	state;
	bool		quit;

	void EventLoop( void );
	void HandleEvent( void );
	void Render( void );

public:
	cmMainState( void );

	void MainLoop( void );
};

