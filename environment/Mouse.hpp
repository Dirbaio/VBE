#ifndef MOUSE_HPP
#define MOUSE_HPP
#include "tools.hpp"

class Mouse
{
	public:
		Mouse();

		enum Button {
			Left,
			Middle,
			Right,
			X1,
			X2,
			_BUTTON_SIZE
		};

		bool isButtonPressed(Button b) const {return !buttonsHeldOld[b] && buttonsHeld[b];}
		bool isButtonReleased(Button b) const {return buttonsHeldOld[b] && !buttonsHeld[b];}
		bool isButtonHeld(Button b) const {return buttonsHeld[b];}

		vec2i getMousePos() const {return mousePos;}
		vec2i getMouseDisplacement() const {return mousePos-mousePosOld;}

	private:
		friend class Environment;

		void processEvent(const SDL_Event& e);
		void update();

		Button sdlButtonToButton(int button);

		bool buttonsHeld[_BUTTON_SIZE];
		bool buttonsHeldOld[_BUTTON_SIZE];

		vec2i mousePos;
		vec2i mousePosOld;
};

#endif // MOUSE_HPP
