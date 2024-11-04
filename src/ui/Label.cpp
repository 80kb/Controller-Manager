#include "Label.hpp"
#include "../MainState.hpp"
#include "../Palette.hpp"
#include <string.h>

uiLabel::uiLabel( cmMainState* mainState ) {
	std::string exePath = mainState->GetExePath();
	exePath += "/ttf/arial.ttf";

	this->mainState = mainState;
	font		= TTF_OpenFont( exePath.c_str(), 128 );
	color		= { CM_PRIMARY_COLOR };

	SetText( "Label" );
}

uiLabel::~uiLabel( void ) {
	SDL_DestroyTexture( texture );
}

void uiLabel::Render( void ) {
	SDL_RenderCopy( mainState->GetRenderer(), texture, NULL, &rect );
}

void uiLabel::SetText( const char* text ) {
	this->text = text;
	SDL_Surface* surface = TTF_RenderText_Solid( font, text, color );
	texture = SDL_CreateTextureFromSurface( mainState->GetRenderer(), surface );
	SDL_FreeSurface( surface );
	TTF_SizeText( font, text, &rect.w, &rect.h );
}

void uiLabel::SetSize( const int w ) {
	int textW, textH;
	TTF_SizeText( font, text, &textW, &textH );

	rect.w = w;
	rect.h = (textH * w) / textW;
}

void uiLabel::SetPosition( const int x, const int y ) {
	rect.x = x;
	rect.y = y;
}
