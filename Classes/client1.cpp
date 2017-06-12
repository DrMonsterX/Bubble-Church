#include "afx.h"  
#include <cstdlib>  
#include <deque>  
#include <iostream>  
#include <boost/bind.hpp>  
#include <boost/asio.hpp>  
#include <boost/thread.hpp>  
#include <boost/chat_message.hpp>


using boost::asio::ip::tcp;
using namespace std;
typedef std::deque<chat_message> chat_message_queue;

class chat_client
{
public:
	//链接
	chat_client(boost::asio::io_service& io_service,   
		tcp::resolver::iterator endpoint_iterator)
		: io_service_(io_service),
		socket_(io_service)
	{

		tcp::endpoint endpoint = *endpoint_iterator;
		socket_.async_connect(endpoint,
			boost::bind(&chat_client::handle_connect, this, 
				boost::asio::placeholders::error, ++endpoint_iterator));
	}

	void write(const chat_message& msg) // 5  
	{

		io_service_.post(boost::bind(&chat_client::do_write, this, msg));
	}

	void close()
	{

		io_service_.post(boost::bind(&chat_client::do_close, this));
	}

private:

	void handle_connect(const boost::system::error_code& error, // 2  
		tcp::resolver::iterator endpoint_iterator)
	{

		if (!error)
		{
			//链接成功，绑定。
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), chat_message::header_length),  //读取头部。
				boost::bind(&chat_client::handle_read_header, this, // 3  
					boost::asio::placeholders::error));
		}
		else if (endpoint_iterator != tcp::resolver::iterator())
		{
			//失败，重新链接
			socket_.close();
			tcp::endpoint endpoint = *endpoint_iterator;
			socket_.async_connect(endpoint,
				boost::bind(&chat_client::handle_connect, this, // 2  
					boost::asio::placeholders::error, ++endpoint_iterator));
		}
	}

	void handle_read_header(const boost::system::error_code& error) // 3  
	{

		if (!error && read_msg_.decode_header())
		{
			
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()), //读取正文。  
				boost::bind(&chat_client::handle_read_body, this, // 4  
					boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void handle_read_body(const boost::system::error_code& error) // 4  
	{

		if (!error)
		{
			
			std::cout.write(read_msg_.body(), read_msg_.body_length()); // 输出正文内容  
			std::cout << "\n";
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), chat_message::header_length),
				boost::bind(&chat_client::handle_read_header, this,   
					boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}

	void do_write(chat_message msg) // 6  
	{

		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()), // 把发言内容写入buffer  
				boost::bind(&chat_client::handle_write, this,   
					boost::asio::placeholders::error));
		}
	}

	void handle_write(const boost::system::error_code& error) // 7  
	{

		if (!error)
		{
			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().data(),//判断是否还有多余的内容
						write_msgs_.front().length()),
					boost::bind(&chat_client::handle_write, this,   
						boost::asio::placeholders::error));
			}
		}
		else
		{
			do_close();
		}
	}

	void do_close()
	{

		socket_.close();
	}

private:
	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	chat_message read_msg_;  // 存从buffer读出的数据  
	chat_message_queue write_msgs_; // 写入buffer的数据队列 
};

int _tmain(int argc, _TCHAR* argv[])
{
	
	try
	{
		//输入个人ID
		std::cout << "请输入你的姓名：";
		char name[chat_message::max_body_length + 1] = { 0 };
		std::cin.getline(name, chat_message::max_body_length + 1);
		char login[11] = " login OK!", login_msg[513] = { 0 };
		strcpy(login_msg, name);
		strncat(login_msg, login, strlen(login) + 1);
		//连接
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query("127.0.0.1", "1000"); 
		tcp::resolver::iterator iterator = resolver.resolve(query);
		chat_client c(io_service, iterator);  
		boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));  

		//发送个人信息
		chat_message msg;
		msg.body_length(strlen(login_msg));
		memcpy(msg.body(), login_msg, msg.body_length());  			
		msg.encode_header();
		c.write(msg);
		name[strlen(name)] = ':';
		//开启个人聊天。
		char line[chat_message::max_body_length + 1];
		while (std::cin.getline(line, chat_message::max_body_length + 1))
		{
			char massage[chat_message::max_body_length + 1] = { 0 };
			strcpy(massage, name);
			strncat(massage, line, strlen(line) + 1);
			chat_message msg;
			msg.body_length(strlen(massage));
			memcpy(msg.body(), massage, msg.body_length());// line to msg  			
			msg.encode_header();
			c.write(msg);
		}

		c.close();
		t.join(); // 执行线程  
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}











