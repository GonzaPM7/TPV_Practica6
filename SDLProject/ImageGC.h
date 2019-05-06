#pragma once

#include "GraphicsComponent.h"

/*
 *
 */
class ImageGC: public GraphicsComponent {
public:
	ImageGC();
	ImageGC(Texture* texture);
	ImageGC(Texture* texture, SDL_Rect clip);
	virtual ~ImageGC();
	void setTexture(Texture* texture);
	void setTexture(Texture* texture, SDL_Rect clip);
	virtual void render(Container* c, Uint32 time);
private:
	Texture* texture_;
	SDL_Rect clip_;
};

