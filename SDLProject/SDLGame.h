#pragma once

#include "sdl_includes.h"
#include <string>
#include <vector>

#include "Observer.h"
#include "Resources.h"
#include "SDLTexturesManager.h"
#include "SDLAudioManager.h"
#include "SDLFontsManager.h"
#include "ServiceLocator.h"
#include "SRandBasedGenerator.h"

using namespace std;

class SDLGame {
public:

public:
	SDLGame(string windowTitle_, int width, int height);
	virtual ~SDLGame();

	SDL_Window* getWindow() const; // returns a pointer to the SDL window
	SDL_Renderer* getRenderer() const; // returns a pointer to the SDL renderer
	int getWindowWidth() const; // returns the window width
	int getWindowHeight() const; // returns the window height
	const ServiceLocator* getServiceLocator() const; // returns a pointer to the resources

	void addObserver(Observer* o);
	void send(const void* senderObj, const msg::Message& msg);

	// abstract methods to be implemented by subclasses
	virtual void start() = 0; // start the game
	virtual void stop() = 0;  // stop the game

private:
	void initSDL(); // initialize SDL (ttf, mixer, image, create window and renderer, etc)
	void closeSDL(); // close all SDL resources
	void initResources(); // initialize the SDLResources object with the data at the top of this file
	void closeResources(); // close the  SDLResources object (frees all memory)

protected:
	ServiceLocator services_;
	SDLFontsManager fonts_;
	SDLTexturesManager textures_;
	SDLAudioManager audio_;
	SRandBasedGenerator random_;

	SDL_Window* window_; // the window
	SDL_Renderer* renderer_;  // the renderer

	string windowTitle_; // window title
	int width_; // window width
	int height_; // window height

	vector<Observer*> observers_;

};

