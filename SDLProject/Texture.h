#pragma once

#include "sdl_includes.h"
#include <string>
#include "Font.h"

using namespace std;

class Texture {
public:
	Texture();
	Texture(SDL_Renderer* renderer, string fileName);
	Texture(SDL_Renderer* renderer, string text, Font& font,
			const SDL_Color color);
	virtual ~Texture();

	int getWidth();
	int getHeight();

	bool isReady();

	bool loadFromImg(SDL_Renderer* renderer, string fileName);
	bool loadFromText(SDL_Renderer* renderer, string texto, Font& font,
			SDL_Color color = { 0, 0, 0, 255 });

	// render the complete texture at position (x,y). We either provide
	// a renderer or use the one used at construction
	void render(int x, int y) const;
	void render(SDL_Renderer* renderer, int x, int y) const;

	// render part of the texture (clip) to a destination rectangle, if no
	// clip provided it renders all texture (scaled to dest). We either provide
	// a renderer or use the one used at construction
	void render(SDL_Rect const& dest, SDL_Rect* clip = nullptr) const;
	void render(SDL_Renderer* renderer, SDL_Rect const& dest, SDL_Rect* clip =
			nullptr) const;

	// render part of the texture (clip) to a destination rectangle with a rotation,
	// if no clip provided it renders all texture (scaled to dest). We either provide
	// a renderer or use the one used at construction
	void render(SDL_Rect const& dest, double angle,
			SDL_Rect* clip = nullptr) const;
	void render(SDL_Renderer* renderer, SDL_Rect const& dest, double angle,
			SDL_Rect* clip = nullptr) const;

	void close();

private:

	SDL_Texture *texture_;
	SDL_Renderer* renderer_;
	int width_;
	int height_;
};
