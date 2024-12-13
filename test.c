#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

//function declarations
bool init();
bool makeWindow();
void end();
void loop();

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init() {
	bool success = SDL_Init(SDL_INIT_VIDEO);
    if( !success ) {
        SDL_Log("Initialization failed! Cuz: %s\n", SDL_GetError());
    }

	return success;
}

bool makeWindow() {
	const int kScreenWidth = 640;
	const int kScreenHeight = 480;

	gWindow = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3!", kScreenWidth, kScreenHeight, 0);
    if( gWindow == NULL) {
        SDL_Log("Window creation failed: %s\n", SDL_GetError());
        return false;
    }

    //get draw surface
    gScreenSurface = SDL_GetWindowSurface( gWindow );
	
	return true;
}

bool loadMedia() {
	char* imagePath = "hello.bmp";
    
	gHelloWorld = SDL_LoadBMP( imagePath );

    if( gHelloWorld == NULL ) {
        SDL_Log( "Unable to load image %s! Cuz: %s\n", imagePath, SDL_GetError() );
        return false;
    }

	return true;
}

void end() {
	//Destroy surface
    SDL_DestroySurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gScreenSurface = NULL;

    SDL_Quit();
}

void loop() {
	//Main game loop
    bool quit = false;
    SDL_Event e;
    SDL_zero( e );  //ensure that we're dealing with zeroed out memory

    while( !quit ) {
        //start by processing events
        while( SDL_PollEvent( &e ) ) {
            if( e.type == SDL_EVENT_QUIT ) {
                quit = true;
            }
        }

        //then, perform updates
        SDL_FillSurfaceRect( gScreenSurface,
                        NULL,
                        SDL_MapSurfaceRGB( gScreenSurface, 0xFF, 0xFF, 0xFF) );

        SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );

        //update the surface
        SDL_UpdateWindowSurface( gWindow );
    }
}

int main(int argc, char **argv) {
	bool success = true;
	
	//initialize
	if( !init() )
		return -1;
	
	//create window
	if( !makeWindow() )
		return -2;

	//Now, load media
	if ( !loadMedia() )
		return -4;
	
	loop();
	
	end();

	return 0;
}
