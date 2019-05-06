#pragma once

#include "Font.h"
#include "Texture.h"
#include <string>

using namespace std;

/*
 *
 */
class TexturesManager {
public:
	TexturesManager();
	virtual ~TexturesManager();

	// supposed to be called before start using the object
	virtual bool init() = 0;

	virtual Texture* getTexture(int tag) = 0;
	virtual bool loadFromImg(int tag, SDL_Renderer* renderer, string fileName) = 0;
	virtual bool loadFromText(int tag, SDL_Renderer* renderer, string texto, Font& font, SDL_Color color = { 0, 0, 0, 255 }) = 0;
};
