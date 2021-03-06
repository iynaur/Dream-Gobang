#pragma once
#include <windows.h>
#include "graphics.h"
#include <string>

class Dialog
{
protected:
	int width_;
	int height_;
	std::string title_;
	HWND dialog_handle_;
	HDC dialog_dc_;
	PIMAGE dialog_image_;
	volatile bool exit_flag_;
	bool init_flag_;

	std::string font_family_;
	int font_size_;

	static bool register_flag_;
	static WNDCLASSEX window_class_;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static const int button_width_ = 110;
	static const int button_height_ = 35;
	static const int button_margin_ = 8;
	static const int button_area_height_ = button_height_ + button_margin_ * 2;

	virtual void on_dialog_init(){}
	virtual void on_create_message(){}
	virtual bool on_dialog_close(){ return false; }
	virtual bool on_key_press(unsigned int key_value){ return false; }
public:
	Dialog(int width, int height);
	virtual ~Dialog();
	void show();

	void set_font(LPCSTR font_family, int size);

	void set_title(const char* title)
	{
		title_ = title;
	}
};

