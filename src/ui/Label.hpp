#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class cmMainState;

class uiLabel {
	cmMainState*	mainState;
	SDL_Texture* 	texture;
	TTF_Font*	font;
	SDL_Color	color;
	SDL_Rect	rect;
	const char*	text;

public:
	uiLabel( cmMainState* mainState );
	~uiLabel( void );

	void Render( void );
	void SetText( const char* text );
	void SetSize( const int w );
	void SetPosition( const int x, const int y );
};
