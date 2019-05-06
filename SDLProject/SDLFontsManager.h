#pragma once

#include "FontsManager.h"
#include <map>

/*
 *
 */
class SDLFontsManager : public FontsManager {
public:
	SDLFontsManager();
	virtual ~SDLFontsManager();

	// supposed to be called before start using the object
	virtual bool init();

	virtual Font* getFont(int tag);
	virtual bool loadFont(int tag, string fileName, int size);
private:
	map<int,Font*> fonts_;
	bool initialized_;
};

