#pragma once

#include "sdl_includes.h"
#include <string>

using namespace std;

class Font {
public:
	Font();
	Font(string fileName, int size);
	virtual ~Font();

	bool load(string fileName, int size);
	void close();
	SDL_Surface* renderText(string text, SDL_Color color) const;
private:
	TTF_Font *font_;
};
