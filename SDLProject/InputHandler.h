#pragma once

#include <iostream>
#include <vector>

#include "sdl_includes.h"
#include "Vector2D.h"

class InputHandler {
public:

	enum mouse_buttons {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};

	static InputHandler* instance() {
		if (instance_ == 0) {
			instance_.reset( new InputHandler() );
		}

		return instance_.get();
	}

	// update the input handler
	void update();

	// keyboard events
	bool isKeyDown(SDL_Scancode key) const;
	bool isKeyDown(SDL_Keycode key) const;
	bool anyKeyDown() const;

	// mouse events
	bool getMouseButtonState(int buttonNumber) const;
	const Vector2D& getMousePosition() const;
	bool isMouseMoved() const;

	// delete copy constructor and assignemnt operator
	InputHandler(const InputHandler&) = delete;
	InputHandler& operator=(const InputHandler&) = delete;

	~InputHandler();

private:
	InputHandler();

	// private functions to handle different event types

	void reset();

	// handle keyboard events
	void onKeyDown();
	void onKeyUp();

	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// member variables

	// keyboard specific
	const Uint8* keystates_;

	// mouse specific
	std::vector<bool> mouseButtonStates_;
	Vector2D mousePosition_;

	// singleton
	static unique_ptr<InputHandler> instance_;
};

