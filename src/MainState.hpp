#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "sdl/sdl_boiler.hpp"
#include "ui/Menu.hpp"
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#define CM_MAX_PLAYERS 4

class cmMainState {
	SDL_Event 	event;
	SDL_State 	state;
	bool		quit;
	cmMenu*		menu;

	std::vector<SDL_GameController*> controllers;
	std::vector<SDL_GameController*> players;

	void RegisterControllers( void );
	bool PlayerRegistered( SDL_GameController* controller );
	void RegisterPlayer( SDL_GameController* controller );

	void EventLoop( void );
	void HandleEvent( void );
	void HandleWindowEvent( void );
	void Update( void );
	void Render( void );

	void ControllerButtonDown( void );
	void WindowResized( void );

public:
	cmMainState( void );
	~cmMainState( void );

	void 			MainLoop( void );
	SDL_Renderer* 		GetRenderer( void ) const;
	SDL_Window*		GetWindow( void ) const;
	int			PlayerCount( void ) const;
	SDL_GameController* 	GetPlayer( const int index ) const;
	std::string		GetExePath( void ) const;
};

