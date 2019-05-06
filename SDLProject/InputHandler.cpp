#include "InputHandler.h"
#include <iostream>

unique_ptr<InputHandler> InputHandler::instance_ ;

InputHandler::InputHandler() :
		keystates_(nullptr), mousePosition_() {

	for (int i = 0; i < 3; i++) {
		mouseButtonStates_.push_back(false);
	}

}

InputHandler::~InputHandler() {
}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
	return (keystates_ != nullptr && keystates_[key] == 1);
}

bool InputHandler::isKeyDown(SDL_Keycode key) const {
	return isKeyDown(SDL_GetScancodeFromKey(key));
}

bool InputHandler::anyKeyDown() const {
	return keystates_ != nullptr;
}

bool InputHandler::getMouseButtonState(int buttonNumber) const {
	return mouseButtonStates_[buttonNumber];
}

const Vector2D& InputHandler::getMousePosition() const {
	return mousePosition_;
}

void InputHandler::reset() {
	mouseButtonStates_[LEFT] = false;
	mouseButtonStates_[RIGHT] = false;
	mouseButtonStates_[MIDDLE] = false;
	keystates_ = nullptr;
}

void InputHandler::update() {
	SDL_Event event;

	reset();

	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_KEYDOWN:
			onKeyDown();
			break;

		case SDL_KEYUP:
			onKeyUp();
			break;

		default:
			break;
		}

	}

}

void InputHandler::onKeyDown() {
	keystates_ = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp() {
	keystates_ = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseMove(SDL_Event &event) {
	mousePosition_.setX(event.motion.x);
	mousePosition_.setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event &event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		mouseButtonStates_[LEFT] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE) {
		mouseButtonStates_[MIDDLE] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT) {
		mouseButtonStates_[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event &event) {
	if (event.button.button == SDL_BUTTON_LEFT) {
		mouseButtonStates_[LEFT] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE) {
		mouseButtonStates_[MIDDLE] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT) {
		mouseButtonStates_[RIGHT] = false;
	}
}

