#include "SDLFontsManager.h"

SDLFontsManager::SDLFontsManager() :
		initialized_(false) {
}

SDLFontsManager::~SDLFontsManager() {
	if ( !initialized_ )
		return;

	// free all sound effect chucks
	for (const auto &font : fonts_) {
		if (font.second != nullptr)
			delete font.second;
	}

	TTF_Quit();
}

bool SDLFontsManager::init() {
	if (initialized_)
		return false;

	TTF_Init();

	initialized_ = true;

	return true;
}

Font* SDLFontsManager::getFont(int tag) {
	return fonts_[tag];
}

bool SDLFontsManager::loadFont(int tag, string fileName, int size) {
	if (!initialized_)
		return false;

	Font* font = new Font();
	if (font->load(fileName, size)) {
		Font* curr = fonts_[tag];
		if (curr != nullptr)
			delete curr;
		fonts_[tag] = font;
		return true;
	} else {
		delete font;
		return false;
	}
}
