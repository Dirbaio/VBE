#include <VBE/system/sdl2/InputImpl.hpp>
#include <VBE/system/sdl2/ScreenImpl.hpp>
#include <VBE/system/Log.hpp>

// static
InputImpl::KeyState InputImpl::keyboardState[Keyboard::KeyCount];
InputImpl::KeyState InputImpl::mouseButtonState[Mouse::ButtonCount];
vec2i InputImpl::mousePos;
vec2i InputImpl::mouseWheel;
bool InputImpl::relativeMouse;

// static
void InputImpl::init() {
	mousePos = vec2i(0, 0);
	mouseWheel = vec2i(0, 0);
	relativeMouse = false;

	for(int i = 0; i < Keyboard::KeyCount; i++)
		keyboardState[i] = Released;
	for(int i = 0; i < Mouse::ButtonCount; i++)
		mouseButtonState[i] = Released;
}

// static
InputImpl::KeyState InputImpl::nextState(InputImpl::KeyState state) {
	switch(state) {
		case JustPressed: return Pressed;
		case JustReleased: return Released;
		default: return state;
	}
}

// static
void InputImpl::update() {
	for(int i = 0; i < Keyboard::KeyCount; i++)
		keyboardState[i] = nextState(keyboardState[i]);
	for(int i = 0; i < Mouse::ButtonCount; i++)
		mouseButtonState[i] = nextState(mouseButtonState[i]);
}

// static
InputImpl::KeyState InputImpl::getKeyState(Keyboard::Key key) {
	return keyboardState[key];
}

// static
InputImpl::KeyState InputImpl::getMouseButtonState(Mouse::Button button) {
	return mouseButtonState[button];
}

void InputImpl::setMousePosition(int x, int y) {
	if(!ScreenImpl::isFocused() || relativeMouse)
		return;

	SDL_WarpMouseInWindow(ScreenImpl::window, x, y);
	mousePos = vec2i(x, y);
}

void InputImpl::setCursorVisible(bool visible) {
	SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}

void InputImpl::setGrab(bool grab) {
	SDL_SetWindowGrab(ScreenImpl::window, (grab ? SDL_TRUE : SDL_FALSE));
}

void InputImpl::setRelativeMouseMode(bool relative) {
	relativeMouse = relative;
	SDL_SetRelativeMouseMode(relative? SDL_TRUE : SDL_FALSE);
}


// static
void InputImpl::processEvent(const SDL_Event& e) {
	switch(e.type) {
		// Keyboard events
		case SDL_KEYDOWN:
			keyboardState[convertSdlKey(e.key.keysym.sym)] = JustPressed;
			break;
		case SDL_KEYUP:
			keyboardState[convertSdlKey(e.key.keysym.sym)] = JustReleased;
			break;

		// Mouse events
		case SDL_MOUSEBUTTONDOWN:
			mouseButtonState[convertSdlButton(e.button.button)] = JustPressed;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButtonState[convertSdlButton(e.button.button)] = JustReleased;
			break;
		case SDL_MOUSEMOTION:
			if(relativeMouse)
				mousePos += vec2i(e.motion.xrel, e.motion.yrel);
			else
				mousePos = vec2i(e.motion.x, e.motion.y);
			break;
		case SDL_MOUSEWHEEL:
			mouseWheel = vec2i(e.wheel.x, e.wheel.y);
			break;
		default:
			break;
	}
}

// static
Mouse::Button InputImpl::convertSdlButton(int button) {
	switch(button) {
		case SDL_BUTTON_LEFT: return Mouse::Left;
		case SDL_BUTTON_MIDDLE: return Mouse::Middle;
		case SDL_BUTTON_RIGHT: return Mouse::Right;
		case SDL_BUTTON_X1: return Mouse::X1;
		case SDL_BUTTON_X2: return Mouse::X2;
		default:
			VBE_ASSERT(false, "Invalid SDL button code");
	}
}

// static
Keyboard::Key InputImpl::convertSdlKey(int key) {
	switch(key) {
		case SDLK_0: return Keyboard::Num0;
		case SDLK_1: return Keyboard::Num1;
		case SDLK_2: return Keyboard::Num2;
		case SDLK_3: return Keyboard::Num3;
		case SDLK_4: return Keyboard::Num4;
		case SDLK_5: return Keyboard::Num5;
		case SDLK_6: return Keyboard::Num6;
		case SDLK_7: return Keyboard::Num7;
		case SDLK_8: return Keyboard::Num8;
		case SDLK_9: return Keyboard::Num9;
		case SDLK_a: return Keyboard::A;
		case SDLK_AC_BACK: return Keyboard::AC_BACK;
		case SDLK_AC_BOOKMARKS: return Keyboard::AC_BOOKMARKS;
		case SDLK_AC_FORWARD: return Keyboard::AC_FORWARD;
		case SDLK_AC_HOME: return Keyboard::AC_HOME;
		case SDLK_AC_REFRESH: return Keyboard::AC_REFRESH;
		case SDLK_AC_SEARCH: return Keyboard::AC_SEARCH;
		case SDLK_AC_STOP: return Keyboard::AC_STOP;
		case SDLK_AGAIN: return Keyboard::Again;
		case SDLK_ALTERASE: return Keyboard::AltErase;
		case SDLK_QUOTE: return Keyboard::Quote;
		case SDLK_APPLICATION: return Keyboard::Application;
		case SDLK_AUDIOMUTE: return Keyboard::AudioMute;
		case SDLK_AUDIONEXT: return Keyboard::AudioNext;
		case SDLK_AUDIOPLAY: return Keyboard::AudioPlay;
		case SDLK_AUDIOPREV: return Keyboard::AudioPrev;
		case SDLK_AUDIOSTOP: return Keyboard::AuidoStop;
		case SDLK_b: return Keyboard::B;
		case SDLK_BACKSLASH: return Keyboard::Backslash;
		case SDLK_BACKSPACE: return Keyboard::Backspace;
		case SDLK_BRIGHTNESSDOWN: return Keyboard::BrightnessDown;
		case SDLK_BRIGHTNESSUP: return Keyboard::BrightnessUp;
		case SDLK_c: return Keyboard::C;
		case SDLK_CALCULATOR: return Keyboard::Calculator;
		case SDLK_CANCEL: return Keyboard::Cancel;
		case SDLK_CAPSLOCK: return Keyboard::Capslock;
		case SDLK_CLEAR: return Keyboard::Clear;
		case SDLK_CLEARAGAIN: return Keyboard::ClearAgain;
		case SDLK_COMMA: return Keyboard::Comma;
		case SDLK_COMPUTER: return Keyboard::Computer;
		case SDLK_COPY: return Keyboard::Copy;
		case SDLK_CRSEL: return Keyboard::CrSel;
		case SDLK_CURRENCYSUBUNIT: return Keyboard::CurrencySubUnit;
		case SDLK_CURRENCYUNIT: return Keyboard::CurrencyUnit;
		case SDLK_CUT: return Keyboard::Cut;
		case SDLK_d: return Keyboard::D;
		case SDLK_DECIMALSEPARATOR: return Keyboard::DecimalSeparator;
		case SDLK_DELETE: return Keyboard::Delete;
		case SDLK_DISPLAYSWITCH: return Keyboard::DisplaySwitch;
		case SDLK_DOWN: return Keyboard::Down;
		case SDLK_e: return Keyboard::E;
		case SDLK_EJECT: return Keyboard::Eject;
		case SDLK_END: return Keyboard::End;
		case SDLK_EQUALS: return Keyboard::Equals;
		case SDLK_ESCAPE: return Keyboard::Escape;
		case SDLK_EXECUTE: return Keyboard::Execute;
		case SDLK_EXSEL: return Keyboard::Exsel;
		case SDLK_f: return Keyboard::F;
		case SDLK_F1: return Keyboard::F1;
		case SDLK_F10: return Keyboard::F10;
		case SDLK_F11: return Keyboard::F11;
		case SDLK_F12: return Keyboard::F12;
		case SDLK_F13: return Keyboard::F13;
		case SDLK_F14: return Keyboard::F14;
		case SDLK_F15: return Keyboard::F15;
		case SDLK_F16: return Keyboard::F16;
		case SDLK_F17: return Keyboard::F17;
		case SDLK_F18: return Keyboard::F18;
		case SDLK_F19: return Keyboard::F19;
		case SDLK_F2: return Keyboard::F2;
		case SDLK_F20: return Keyboard::F20;
		case SDLK_F21: return Keyboard::F21;
		case SDLK_F22: return Keyboard::F22;
		case SDLK_F23: return Keyboard::F23;
		case SDLK_F24: return Keyboard::F24;
		case SDLK_F3: return Keyboard::F3;
		case SDLK_F4: return Keyboard::F4;
		case SDLK_F5: return Keyboard::F5;
		case SDLK_F6: return Keyboard::F6;
		case SDLK_F7: return Keyboard::F7;
		case SDLK_F8: return Keyboard::F8;
		case SDLK_F9: return Keyboard::F9;
		case SDLK_FIND: return Keyboard::Find;
		case SDLK_g: return Keyboard::G;
		case SDLK_BACKQUOTE: return Keyboard::BackQuote;
		case SDLK_h: return Keyboard::H;
		case SDLK_HELP: return Keyboard::Help;
		case SDLK_HOME: return Keyboard::Home;
		case SDLK_i: return Keyboard::I;
		case SDLK_INSERT: return Keyboard::Insert;
		case SDLK_j: return Keyboard::J;
		case SDLK_k: return Keyboard::K;
		case SDLK_KBDILLUMDOWN: return Keyboard::KBDIllumDown;
		case SDLK_KBDILLUMTOGGLE: return Keyboard::KBDIllumToggle;
		case SDLK_KBDILLUMUP: return Keyboard::KBDIllumUp;
		case SDLK_KP_0: return Keyboard::Keypad0;
		case SDLK_KP_00: return Keyboard::Keypad00;
		case SDLK_KP_000: return Keyboard::Keypad000;
		case SDLK_KP_1: return Keyboard::Keypad1;
		case SDLK_KP_2: return Keyboard::Keypad2;
		case SDLK_KP_3: return Keyboard::Keypad3;
		case SDLK_KP_4: return Keyboard::Keypad4;
		case SDLK_KP_5: return Keyboard::Keypad5;
		case SDLK_KP_6: return Keyboard::Keypad6;
		case SDLK_KP_7: return Keyboard::Keypad7;
		case SDLK_KP_8: return Keyboard::Keypad8;
		case SDLK_KP_9: return Keyboard::Keypad9;
		case SDLK_KP_A: return Keyboard::KeypadA;
		case SDLK_KP_AMPERSAND: return Keyboard::KeypadAmpersand;
		case SDLK_KP_AT: return Keyboard::KeypadAt;
		case SDLK_KP_B: return Keyboard::KeypadB;
		case SDLK_KP_BACKSPACE: return Keyboard::KeypadBackspace;
		case SDLK_KP_BINARY: return Keyboard::KeypadBinary;
		case SDLK_KP_C: return Keyboard::KeypadC;
		case SDLK_KP_CLEAR: return Keyboard::KeypadClear;
		case SDLK_KP_CLEARENTRY: return Keyboard::KeypadClearEntry;
		case SDLK_KP_COLON: return Keyboard::KeypadColon;
		case SDLK_KP_COMMA: return Keyboard::KeypadComma;
		case SDLK_KP_D: return Keyboard::KeypadD;
		case SDLK_KP_DBLAMPERSAND: return Keyboard::KeypadDoubleAmpersand;
		case SDLK_KP_DBLVERTICALBAR: return Keyboard::KeypadDoubleVerticalBar;
		case SDLK_KP_DECIMAL: return Keyboard::KeypadDecimal;
		case SDLK_KP_DIVIDE: return Keyboard::KeypadDivide;
		case SDLK_KP_E: return Keyboard::KeypadE;
		case SDLK_KP_ENTER: return Keyboard::KeypadEnter;
		case SDLK_KP_EQUALS: return Keyboard::KeypadEquals;
		case SDLK_KP_EQUALSAS400: return Keyboard::KeypadEqualsAS400;
		case SDLK_KP_EXCLAM: return Keyboard::KeypadExclamation;
		case SDLK_KP_F: return Keyboard::KeypadF;
		case SDLK_KP_GREATER: return Keyboard::KeypadGreater;
		case SDLK_KP_HASH: return Keyboard::KeypadHash;
		case SDLK_KP_HEXADECIMAL: return Keyboard::KeypadHexadecimal;
		case SDLK_KP_LEFTBRACE: return Keyboard::KeypadLBrace;
		case SDLK_KP_LEFTPAREN: return Keyboard::KeypadLParenthesis;
		case SDLK_KP_LESS: return Keyboard::KeypadLess;
		case SDLK_KP_MEMADD: return Keyboard::KeypadMemAdd;
		case SDLK_KP_MEMCLEAR: return Keyboard::KeypadMemClear;
		case SDLK_KP_MEMDIVIDE: return Keyboard::KeypadMemDivide;
		case SDLK_KP_MEMMULTIPLY: return Keyboard::KeypadMemMultiply;
		case SDLK_KP_MEMRECALL: return Keyboard::KeypadMemRecall;
		case SDLK_KP_MEMSTORE: return Keyboard::KeypadMemStore;
		case SDLK_KP_MEMSUBTRACT: return Keyboard::KeypadMemSubstract;
		case SDLK_KP_MINUS: return Keyboard::KeypadMinus;
		case SDLK_KP_MULTIPLY: return Keyboard::KeypadMultiply;
		case SDLK_KP_OCTAL: return Keyboard::KeypadOctal;
		case SDLK_KP_PERCENT: return Keyboard::KeypadPercent;
		case SDLK_KP_PERIOD: return Keyboard::KeypadPeriod;
		case SDLK_KP_PLUS: return Keyboard::KeypadPlus;
		case SDLK_KP_PLUSMINUS: return Keyboard::KeypadPlusMinus;
		case SDLK_KP_POWER: return Keyboard::KeypadPower;
		case SDLK_KP_RIGHTBRACE: return Keyboard::KeypadRBrace;
		case SDLK_KP_RIGHTPAREN: return Keyboard::KeypadRParenthesis;
		case SDLK_KP_SPACE: return Keyboard::KeypadSpace;
		case SDLK_KP_TAB: return Keyboard::KeypadTab;
		case SDLK_KP_VERTICALBAR: return Keyboard::KeypadVerticalBar;
		case SDLK_KP_XOR: return Keyboard::KeypadXor;
		case SDLK_l: return Keyboard::L;
		case SDLK_LALT: return Keyboard::LAlt;
		case SDLK_LCTRL: return Keyboard::LControl;
		case SDLK_LEFT: return Keyboard::Left;
		case SDLK_LEFTBRACKET: return Keyboard::LBracket;
		case SDLK_LGUI: return Keyboard::LGUI;
		case SDLK_LSHIFT: return Keyboard::LShift;
		case SDLK_m: return Keyboard::M;
		case SDLK_MAIL: return Keyboard::Mail;
		case SDLK_MEDIASELECT: return Keyboard::MediaSelect;
		case SDLK_MENU: return Keyboard::Menu;
		case SDLK_MINUS: return Keyboard::Minus;
		case SDLK_MODE: return Keyboard::Mode;
		case SDLK_MUTE: return Keyboard::Mute;
		case SDLK_n: return Keyboard::N;
		case SDLK_NUMLOCKCLEAR: return Keyboard::NumLockClear;
		case SDLK_o: return Keyboard::O;
		case SDLK_OPER: return Keyboard::Oper;
		case SDLK_OUT: return Keyboard::Out;
		case SDLK_p: return Keyboard::P;
		case SDLK_PAGEDOWN: return Keyboard::PageDown;
		case SDLK_PAGEUP: return Keyboard::PageUp;
		case SDLK_PASTE: return Keyboard::Paste;
		case SDLK_PAUSE: return Keyboard::Pause;
		case SDLK_PERIOD: return Keyboard::Period;
		case SDLK_POWER: return Keyboard::Power;
		case SDLK_PRINTSCREEN: return Keyboard::PrintScren;
		case SDLK_PRIOR: return Keyboard::Prior;
		case SDLK_q: return Keyboard::Q;
		case SDLK_r: return Keyboard::R;
		case SDLK_RALT: return Keyboard::RAlt;
		case SDLK_RCTRL: return Keyboard::RControl;
		case SDLK_RETURN: return Keyboard::Return;
		case SDLK_RETURN2: return Keyboard::Return2;
		case SDLK_RGUI: return Keyboard::RGUI;
		case SDLK_RIGHT: return Keyboard::Right;
		case SDLK_RIGHTBRACKET: return Keyboard::RBracket;
		case SDLK_RSHIFT: return Keyboard::RShift;
		case SDLK_s: return Keyboard::S;
		case SDLK_SCROLLLOCK: return Keyboard::ScrollLock;
		case SDLK_SELECT: return Keyboard::Select;
		case SDLK_SEMICOLON: return Keyboard::Semicolont;
		case SDLK_SEPARATOR: return Keyboard::Separator;
		case SDLK_SLASH: return Keyboard::Slash;
		case SDLK_SLEEP: return Keyboard::Sleep;
		case SDLK_SPACE: return Keyboard::Space;
		case SDLK_STOP: return Keyboard::Stop;
		case SDLK_SYSREQ: return Keyboard::Sysreq;
		case SDLK_t: return Keyboard::T;
		case SDLK_TAB: return Keyboard::Tab;
		case SDLK_THOUSANDSSEPARATOR: return Keyboard::ThousandsSeparator;
		case SDLK_u: return Keyboard::U;
		case SDLK_UNDO: return Keyboard::Undo;
		case SDLK_UNKNOWN: return Keyboard::Unknown;
		case SDLK_UP: return Keyboard::UP;
		case SDLK_v: return Keyboard::V;
		case SDLK_VOLUMEDOWN: return Keyboard::VolumeDown;
		case SDLK_VOLUMEUP: return Keyboard::VolumeUp;
		case SDLK_w: return Keyboard::W;
		case SDLK_WWW: return Keyboard::WWW;
		case SDLK_x: return Keyboard::X;
		case SDLK_y: return Keyboard::Y;
		case SDLK_z: return Keyboard::Z;
		case SDLK_AMPERSAND: return Keyboard::Ampersand;
		case SDLK_ASTERISK: return Keyboard::Asterisk;
		case SDLK_AT: return Keyboard::At;
		case SDLK_CARET: return Keyboard::Caret;
		case SDLK_COLON: return Keyboard::Colon;
		case SDLK_DOLLAR: return Keyboard::Dollar;
		case SDLK_EXCLAIM: return Keyboard::Exclamation;
		case SDLK_GREATER: return Keyboard::Greater;
		case SDLK_HASH: return Keyboard::Hash;
		case SDLK_LEFTPAREN: return Keyboard::LParenthesis;
		case SDLK_LESS: return Keyboard::Less;
		case SDLK_PERCENT: return Keyboard::Percent;
		case SDLK_PLUS: return Keyboard::Plus;
		case SDLK_QUESTION: return Keyboard::Question;
		case SDLK_QUOTEDBL: return Keyboard::DoubleQuote;
		case SDLK_RIGHTPAREN: return Keyboard::RParenthesis;
		case SDLK_UNDERSCORE: return Keyboard::Underscore;
		default:
			VBE_ASSERT(false, "Invalid SDL button code");
	}
}

