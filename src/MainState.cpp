#include "MainState.hpp"

cmMainState::cmMainState( void ) : state( "Controller Manager" ) {
	quit = false;
}

void cmMainState::MainLoop( void ) {
	while ( !quit ) {
		EventLoop();
		Render();
	}
}

void cmMainState::EventLoop( void ) {
	while ( SDL_PollEvent( &event ) ) {
		HandleEvent();
	}
}

void cmMainState::HandleEvent( void ) {
	switch ( event.type ) {
		case SDL_QUIT:
			quit = true;
			break;
	}
}

void cmMainState::Render( void ) {
	SDL_SetRenderDrawColor( state.get_renderer(), 255, 0, 0, 255 );
	SDL_RenderClear( state.get_renderer() );

	SDL_RenderPresent( state.get_renderer() );
}
