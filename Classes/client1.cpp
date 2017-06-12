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
	//����
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
			//���ӳɹ����󶨡�
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), chat_message::header_length),  //��ȡͷ����
				boost::bind(&chat_client::handle_read_header, this, // 3  
					boost::asio::placeholders::error));
		}
		else if (endpoint_iterator != tcp::resolver::iterator())
		{
			//ʧ�ܣ���������
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
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()), //��ȡ���ġ�  
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
			
			std::cout.write(read_msg_.body(), read_msg_.body_length()); // �����������  
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
					write_msgs_.front().length()), // �ѷ�������д��buffer  
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
					boost::asio::buffer(write_msgs_.front().data(),//�ж��Ƿ��ж��������
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
	chat_message read_msg_;  // ���buffer����������  
	chat_message_queue write_msgs_; // д��buffer�����ݶ��� 
};

int _tmain(int argc, _TCHAR* argv[])
{
	
	try
	{
		//�������ID
		std::cout << "���������������";
		char name[chat_message::max_body_length + 1] = { 0 };
		std::cin.getline(name, chat_message::max_body_length + 1);
		char login[11] = " login OK!", login_msg[513] = { 0 };
		strcpy(login_msg, name);
		strncat(login_msg, login, strlen(login) + 1);
		//����
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query("127.0.0.1", "1000"); 
		tcp::resolver::iterator iterator = resolver.resolve(query);
		chat_client c(io_service, iterator);  
		boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));  

		//���͸�����Ϣ
		chat_message msg;
		msg.body_length(strlen(login_msg));
		memcpy(msg.body(), login_msg, msg.body_length());  			
		msg.encode_header();
		c.write(msg);
		name[strlen(name)] = ':';
		//�����������졣
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
		t.join(); // ִ���߳�  
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}











