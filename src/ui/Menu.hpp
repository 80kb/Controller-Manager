#pragma once

#include <SDL2/SDL.h>
#include "Label.hpp"
#include <vector>

class cmMainState;

#define CM_BOX_COUNT 4
#define CM_BOX_SIZE 300
#define CM_BOX_PADDING 50
#define CM_HEADER_WIDTH 1000

class cmMenu {
	cmMainState* 		mainState;
	SDL_Rect 		boxes[CM_BOX_COUNT];	
	std::vector<uiLabel*> 	labels;	
	uiLabel*		headerLabel;
	int 			offsetX, offsetY;

public:
	cmMenu( cmMainState* mainState );
	~cmMenu( void );

	void Update( void );
	void Render( void );
	void UpdateOffset( void );
};
