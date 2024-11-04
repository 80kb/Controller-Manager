#include "MainState.hpp"
#include "Palette.hpp"
#include <assert.h>
#include <string>

#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

cmMainState::cmMainState( void ) : state( "Controller Manager" ) {
	quit = false;
	menu = new cmMenu( this );

	RegisterControllers();
}

cmMainState::~cmMainState( void ) {
	delete menu;
	for ( size_t i = 0; i < controllers.size(); i++ ) {
		SDL_GameControllerClose( controllers[i] );
	}
}

void cmMainState::MainLoop( void ) {
	while ( !quit ) {
		EventLoop();
		Update();
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
		case SDL_WINDOWEVENT:
			HandleWindowEvent();
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			ControllerButtonDown();
			break;
		case SDL_CONTROLLERDEVICEADDED:
			RegisterControllers();
			break;
	}
}

void cmMainState::HandleWindowEvent( void ) {
	switch ( event.window.event ) {
		case SDL_WINDOWEVENT_RESIZED:
			WindowResized();
			break;
	}
}

void cmMainState::Update( void ) {
	menu->Update();
}

void cmMainState::Render( void ) {
	SDL_SetRenderDrawColor( state.get_renderer(), CM_BACKGROUND_COLOR );
	SDL_RenderClear( state.get_renderer() );

	menu->Render();

	SDL_RenderPresent( state.get_renderer() );
}

void cmMainState::ControllerButtonDown( void ) {
	for ( size_t i = 0; i < controllers.size(); i++ ) {
		bool triggerL = SDL_GameControllerGetButton( controllers[i], SDL_CONTROLLER_BUTTON_LEFTSHOULDER );
		bool triggerR = SDL_GameControllerGetButton( controllers[i], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER );

		if ( triggerL && triggerR && !PlayerRegistered( controllers[i] ) ) {
			RegisterPlayer( controllers[i] );
			printf( "Controller registererd: %p\n", controllers[i] );
		}
	}
}

bool cmMainState::PlayerRegistered( SDL_GameController* controller ) {
	for ( size_t i = 0; i < players.size(); i++ ) {
		if ( controller == players[i] ) {
			return true;
		}
	}
	return false;
}

void cmMainState::RegisterPlayer( SDL_GameController* controller ) {
	if ( players.size() >= CM_MAX_PLAYERS ) {
		return;
	}

	players.push_back( controller );
}

SDL_Renderer* cmMainState::GetRenderer( void ) const {
	return state.get_renderer();
}

SDL_Window* cmMainState::GetWindow( void ) const {
	return state.get_window();
}

void cmMainState::WindowResized( void ) {
	menu->UpdateOffset();
}

int cmMainState::PlayerCount( void ) const {
	return (int)players.size();
}

SDL_GameController* cmMainState::GetPlayer( const int index ) const {
	assert( index >= 0 );
	assert( index < CM_MAX_PLAYERS );

	return players[ index ];
}

void cmMainState::RegisterControllers( void ) {
	int controllerCount = SDL_NumJoysticks();
	for ( int i = 0; i < controllerCount; i++ ) {
		if ( !SDL_IsGameController( i ) ) {
			continue;
		}

		SDL_GameController* controller = SDL_GameControllerOpen( i );
		if ( controller ) {
			controllers.push_back( controller );
			printf( "Successfully detected controller: %s\n", SDL_GameControllerName( controller ) );
		} else {
			printf( "Failed to open SDL_GameController %d\n", i );
		}
	}
}

std::string cmMainState::GetExePath( void ) const {
#ifdef __linux__
	char buffer[1024];
	ssize_t len;

	len = readlink( "/proc/self/exe", buffer, sizeof(buffer) - 1 );
	if ( len != -1 ) {
		buffer[len] = '\0';
	} else {
		printf("Failed reading exe path\n");
	}
	std::string path(buffer);
	path = path.substr(0, path.find_last_of("/\\"));
#elif _WIN32
	wchar_t buffer[MAX_PATH];
	GetModuleFileNameW( NULL, buffer, MAX_PATH );

	int len = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, NULL, 0, NULL, NULL);
	char* char_path = new char[len + 1];
	WideCharToMultiByte(CP_UTF8, 0, buffer, -1, char_path, len, NULL, NULL);
	char_path[len] = '\0';

	std::string path(char_path);
	path = path.substr(0, path.find_last_of("/\\"));
	delete[] char_path;
#endif

	return path;
}