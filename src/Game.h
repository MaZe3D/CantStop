#pragma once
#include "mysdl/Window.h"
#include "mysdl/Events.h"
#include "ux/Menu.h"
#include "ux/GameRoundDrawer.h"
#include "logic/GameRound.h"

class Game : WindowClosedEvent, KeyPressedEvent {
public:
	Game(const std::shared_ptr<Window>& window);
	void run();

private:
	const std::shared_ptr<const Font> m_font1;
	const std::shared_ptr<const Font> m_font2;

	Menu m_menu;
	GameRoundDrawer m_gameRoundDrawer;

	bool m_shouldQuit = false;

	void onWindowClosed() override;
	void onKeyPressed(const SDL_Keysym& key) override;
};
