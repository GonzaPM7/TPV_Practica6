#include "BoundingBoxGC.h"
#include <algorithm>

BoundingBoxGC::BoundingBoxGC() :
		BoundingBoxGC( { COLOR(0xffffffff) }) {
}


BoundingBoxGC::BoundingBoxGC(SDL_Color color) :
		color_(color) {
}

BoundingBoxGC::~BoundingBoxGC() {
}

void BoundingBoxGC::render(Container* c, Uint32 time) {
	SDL_Renderer* renderer = c->getGame()->getRenderer();

	// the rotation angle of the object wrt to
	double angle = c->getRotation();

	// assuming the (0,0) point is the middle of the object, the following are
	// vectors to the corners of its bounding rectangle
	Vector2D lu = Vector2D(-c->getWidth() / 2.0, -c->getHeight() / 2.0);
	Vector2D ru = Vector2D(c->getWidth() / 2.0, -c->getHeight() / 2.0);
	Vector2D rb = Vector2D(c->getWidth() / 2.0, c->getHeight() / 2.0);
	Vector2D lb = Vector2D(-c->getWidth() / 2.0, c->getHeight() / 2.0);

	// rotate the corners, so we get a rotated rectangle
	lu = lu.rotate(angle);
	ru = ru.rotate(angle);
	rb = rb.rotate(angle);
	lb = lb.rotate(angle);

	// the center of the object
	double x = c->getPosition().getX() + c->getWidth() / 2.0;
	double y = c->getPosition().getY() + c->getHeight() / 2.0;

	// draw lines between the corners, after shifting them by (x,y)
	SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
	SDL_RenderDrawLine(renderer, lu.getX() + x, lu.getY() + y, ru.getX() + x, ru.getY() + y);
	SDL_RenderDrawLine(renderer, ru.getX() + x, ru.getY() + y, rb.getX() + x, rb.getY() + y);
	SDL_RenderDrawLine(renderer, rb.getX() + x, rb.getY() + y, lb.getX() + x, lb.getY() + y);
	SDL_RenderDrawLine(renderer, lb.getX() + x, lb.getY() + y, lu.getX() + x, lu.getY() + y);

	// draw center point
	SDL_SetRenderDrawColor(renderer, COLOR(0xff000000));
	SDL_Rect dest = RECT(x-1, y-1, 3, 3);
	SDL_RenderFillRect(renderer, &dest);

	// draw velocity vector
	SDL_SetRenderDrawColor(renderer, COLOR(0x00ff0011));

	Vector2D vel = c->getVelocity();
	double wh = std::min(c->getHeight(), c->getWidth()) / 2.0; // minimum of width an height
	vel = vel * wh/2.0;
	SDL_RenderDrawLine(renderer, x, y, vel.getX() + x, vel.getY() + y);
}
