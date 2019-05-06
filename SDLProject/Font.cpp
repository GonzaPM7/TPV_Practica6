#include "Font.h"

#include <iostream>

using namespace std;

Font::Font() :
		font_(nullptr) {
}

Font::Font(string fileName, int size) {
		load(fileName, size);
}

Font::~Font() {
	close();
}

bool Font::load(string fileName, int size) {
	font_ = TTF_OpenFont(fileName.c_str(), size);
	if ( font_ == nullptr ) {
		cout << "Couldn't load font: " << fileName << endl;
	}
	return font_ != nullptr;
}

void Font::close() {
	if (font_) {
		TTF_CloseFont(font_);
		font_ = nullptr;
	}
}

SDL_Surface* Font::renderText(string text, SDL_Color color) const {
	if ( font_ ) {
		return TTF_RenderText_Solid(font_, text.c_str(), color);
	} else {
		return nullptr;
	}
}
