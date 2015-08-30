#pragma once
#include "Settings.h"
#include "widgets/ImageButton.h"
class NetSettingsInterface
{
private:
	Settings* game_settings_;
	static Image* bg_img_;
	static ImageButton* button_save_;
	static ImageButton* button_cancel_;
	static const int edit_button_num_ = 4;
	static ImageButton* button_edit_[edit_button_num_];

	static const int font_size_level_1_ = 30;
	static const int font_size_level_2_ = 23;
	static const int text_margin_ = 20;
	static const int text_indent_ = 50;
	static const int button_margin_ = 15;
	static const int text_x_offset = 25;
	static const int text_y_offset = 7;
public:
	NetSettingsInterface(Settings* setting);
	~NetSettingsInterface();
	void show_interface();
	
	enum ACTION_TYPE
	{
		ACTION_NONE,
		ACTION_SAVE,
		ACTION_CANCEL,
		ACTION_EDIT_USER_NAME,
		ACTION_EDIT_SERVER_PORT,
		ACTION_EDIT_CLIENT_CONNECT_IP,
		ACTION_EDIT_CLIENT_CONNECT_PORT,
	};

	ACTION_TYPE action_judge(int x, int y);
	void on_mouse_move(ACTION_TYPE type);
	void on_mouse_click(ACTION_TYPE type);
};
