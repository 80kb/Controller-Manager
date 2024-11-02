#include "Menu.hpp"
#include "../MainState.hpp"
#include "../Palette.hpp"

cmMenu::cmMenu( cmMainState* mainState ) {
	this->mainState = mainState;
	headerLabel	= new uiLabel( mainState );

	headerLabel->SetText( "Press L and R at the same time" );
	headerLabel->SetSize( CM_HEADER_WIDTH );
	
	/* controller labels */
	for ( int i = 0; i < CM_BOX_COUNT; i++ ) {
		labels.push_back( new uiLabel( mainState ) );
		labels[i]->SetText( " " );
		labels[i]->SetSize( CM_BOX_SIZE - 10 );
	}

	UpdateOffset();
}

cmMenu::~cmMenu( void ) {
	delete headerLabel;
	for ( int i = 0; i < CM_BOX_COUNT; i++ ) {
		delete labels[i];
	}
}

void cmMenu::Update( void ) {
	for( int i = 0; i < mainState->PlayerCount(); i++ ) {
		labels[i]->SetText( SDL_GameControllerName( mainState->GetPlayer( i ) ) );
		labels[i]->SetSize( CM_BOX_SIZE - 20 );
	}
}

void cmMenu::Render( void ) {
	SDL_SetRenderDrawColor( mainState->GetRenderer(), CM_PRIMARY_COLOR );
	headerLabel->Render();
	for ( int i = 0; i < CM_BOX_COUNT; i++ ) {
		SDL_RenderDrawRect( mainState->GetRenderer(), &boxes[i] );
		labels[i]->Render();
	}
}

void cmMenu::UpdateOffset( void ) {
	int fullW = (CM_BOX_COUNT * CM_BOX_SIZE) + ((CM_BOX_COUNT - 1) * CM_BOX_PADDING);
	int windowW, windowH;
	SDL_GetWindowSize( mainState->GetWindow(), &windowW, &windowH );

	this->offsetX 	= (windowW / 2) - (fullW / 2);
	this->offsetY	= (windowH / 2) - (CM_BOX_SIZE / 2);

	headerLabel->SetPosition(
		(windowW / 2) - (CM_HEADER_WIDTH / 2),
		offsetY - 150
	);

	for ( int i = 0; i < CM_BOX_COUNT; i++ ) {
		boxes[i].h = CM_BOX_SIZE;
		boxes[i].w = CM_BOX_SIZE;
		boxes[i].x = offsetX + (CM_BOX_SIZE * i) + (CM_BOX_PADDING * i);
		boxes[i].y = offsetY;

		labels[i]->SetPosition(
			boxes[i].x + 10,
			boxes[i].y + (CM_BOX_SIZE / 2)
		);
	}
}
