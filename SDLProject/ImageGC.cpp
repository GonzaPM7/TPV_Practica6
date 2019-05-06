#include "ImageGC.h"

ImageGC::ImageGC() :
		texture_(nullptr), clip_() {
}

ImageGC::ImageGC(Texture* texture) :
		ImageGC(texture, { 0, 0, texture->getWidth(), texture->getHeight() }) {
}

ImageGC::ImageGC(Texture* texture, SDL_Rect clip) :
		texture_(texture), clip_(clip) {
}

ImageGC::~ImageGC() {
}

void ImageGC::render(Container* c, Uint32 time) {
	SDL_Rect dest = RECT(c->getPosition().getX(), c->getPosition().getY(),
			c->getWidth(), c->getHeight());
	texture_->render(dest, c->getRotation(), &clip_);
}

void ImageGC::setTexture(Texture* texture) {
	texture_ = texture;
	clip_ = {0, 0, texture->getWidth(), texture->getHeight()};
}

void ImageGC::setTexture(Texture* texture, SDL_Rect clip) {
	texture_ = texture;
	clip_ = clip;
}
