#include "Input.h"



void Input::Update(void)
{
	while (SDL_PollEvent(&m_event) != NULL)
	{
		//got an event. Let's Proccess it

		//check for keydown

		if (m_event.type == SDL_KEYDOWN)
		{
			//cache the code of the key we pressed for easier debugging
			SDL_Keycode keyPressed = m_event.key.keysym.sym;

			//update keys

			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				m_keysPressed[KEY_ESCAPE] = true;
				break;
			case SDLK_r:
				m_keysPressed[KEY_R] = true;
				break;
			case SDLK_g:
				m_keysPressed[KEY_G] = true;
				break;
			case SDLK_b:
				m_keysPressed[KEY_B] = true;
				break;
			case SDLK_LEFT:
				m_keysPressed[KEY_LEFT] = true;
				break;
			case SDLK_RIGHT:
				m_keysPressed[KEY_RIGHT] = true;
				break;
			case SDLK_UP:
				m_keysPressed[KEY_UP] = true;
				break;
			case SDLK_DOWN:
				m_keysPressed[KEY_DOWN] = true;
				break;
			case SDLK_RETURN:
				m_keysPressed[KEY_RETURN] = true;
				break;
			}
		}

		//check for key up
		else if (m_event.type == SDL_KEYUP)
		{
			SDL_Keycode keyPressed = m_event.key.keysym.sym;

			switch (keyPressed)
			{
			case SDLK_r:
				m_keysPressed[KEY_R] = false;
				break;
			case SDLK_g:
				m_keysPressed[KEY_G] = false;
				break;
			case SDLK_b:
				m_keysPressed[KEY_B] = false;
				break;
			case SDLK_LEFT:
				m_keysPressed[KEY_LEFT] = false;
				break;
			case SDLK_RIGHT:
				m_keysPressed[KEY_RIGHT] = false;
				break;
			case SDLK_UP:
				m_keysPressed[KEY_UP] = false;
				break;
			case SDLK_DOWN:
				m_keysPressed[KEY_DOWN] = false;
				break;
			case SDLK_RETURN:
				m_keysPressed[KEY_RETURN] = false;
				break;
			}
		}
	}
}

bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	return m_keysPressed[key];
}

Input::Input()
{
}


Input::~Input()
{
}
