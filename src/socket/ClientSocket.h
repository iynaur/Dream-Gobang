#pragma once
#include <winsock.h>
#include <windows.h>
#include "../tools/ThreadQueue.h"
#include <string>

using namespace std;

class ClientSocket
{
private:
	SOCKET client_socket_;
	string server_IP_addr_;
	string server_port_;

	static const int max_mission_num_ = 1000;
	static const int max_buf_size_ = 1024;
	static const int connect_time_out_ = 10;

	enum mission_type
	{
		MISSION_RECEIVE,
		MISSION_SEND,
	};
	struct socket_mission
	{
		mission_type mission_ID;
		string send_str;												//仅当ID为MISSION_SEND时有效
	};
	ThreadQueue<socket_mission> mission_queue_;
	volatile bool running_flag_;
	volatile bool stop_flag_;
	char receive_buf_[max_buf_size_];
	HANDLE socket_thread_;

	static bool win_socket_init();
	static DWORD WINAPI on_socket_running(LPVOID data);
protected:
	//回调函数
	virtual void on_init_failed(){}
	virtual void on_socket_create_failed(int WSA_error_code){}
	virtual void on_connect_failed(SOCKET socket, int WSA_error_code){}
	virtual void on_connect_success(SOCKET socket){}
	virtual void on_receive_failed(SOCKET socket, int WSA_error_code){}
	virtual void on_receive_completed(SOCKET socket, char* str, int length){}
	virtual void on_send_failed(SOCKET socket, const char* send_str, int WSA_error_code){}
	virtual void on_send_completed(SOCKET socket){}
	void send_stop_message();																						//该函数用于在回调函数中发送终止消息来终止socket守护线程
public:
	ClientSocket();
	virtual ~ClientSocket();

	void set_server_IP_addr(const char* IP_addr)
	{
		server_IP_addr_ = IP_addr;
	}

	void set_server_port(const char* port)
	{
		server_port_ = port;
	}

	void clean_mission_queue();
	void start();																				//启动socket守护线程
	void stop();																				//停止socket守护线程，请勿在回调函数中使用。回调函数中请使用send_stop_message()函数
	void receive();																			//接收消息
	void send_string(const char* str);									//发送消息

	bool is_run()
	{
		return running_flag_;
	}
};

