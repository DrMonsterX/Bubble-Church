#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <cstdlib>  
#include <deque>  
#include <iostream>  
#include <boost/bind.hpp>  
#include <boost/asio.hpp>  
#include <boost/thread.hpp>  
#include <boost/order_message.hpp>
#include "OnLinePlay.h"
#include "OnlineHeroSelect.h"

using boost::asio::ip::tcp;
using namespace std;
typedef std::deque<order_message> order_message_queue;

class client
{
public:
	//����

	friend class OnLinePlay;
	friend class OnlineHeroSelect;
	

	client(boost::asio::io_service& io_service,
		tcp::resolver::iterator endpoint_iterator)
		: io_service_(io_service),
		socket_(io_service)
	{		
		tcp::endpoint endpoint = *endpoint_iterator;
		socket_.async_connect(endpoint,
			boost::bind(&client::handle_connect, this,
				boost::asio::placeholders::error, ++endpoint_iterator));
	}

	void getPSelect(OnlineHeroSelect* p)
	{
		pOnlineHeroSelect = p;
	}

	void getPPlay(OnLinePlay* p)
	{
		pOnLinePlay = p;
	}

	void write(order_message msg)
	{

		io_service_.post(boost::bind(&client::do_write, this, msg));
	}

	void close()
	{

		io_service_.post(boost::bind(&client::do_close, this));
	}

private:

	void handle_connect(const boost::system::error_code& error,
		tcp::resolver::iterator endpoint_iterator)
	{
		ifsuccess = true;
		if (!error)
		{
			//���ӳɹ����󶨡�
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.order(), order_message::sign_length),  //��ȡͷ����
				boost::bind(&client::handle_read_sign, this,
					boost::asio::placeholders::error));
		}
		else if (endpoint_iterator != tcp::resolver::iterator())
		{
			//ʧ�ܣ���������
			socket_.close();
			tcp::endpoint endpoint = *endpoint_iterator;
			socket_.async_connect(endpoint,
				boost::bind(&client::handle_connect, this,
					boost::asio::placeholders::error, ++endpoint_iterator));
		}
	}

	void handle_read_sign(const boost::system::error_code& error)
	{

		read_msg_.get_length();
		if (!error)
		{

			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.length_() - 1),// ȡbuffer�ı����ֵ�read_msg_  			
				boost::bind(&client::handle_read_body, this,
					boost::asio::placeholders::error));
		}
		else
		{
			do_close();
		}
	}
	void handle_read_body(const boost::system::error_code& error)
	{

		
		if (!error)
		{
			char type = read_msg_.get_order();
			if (type == '9')
			{
				if (pOnlineHeroSelect != nullptr)
					pOnlineHeroSelect->progress_order1(read_msg_);
			}
			else
			{
				if (pOnLinePlay != nullptr)
					pOnLinePlay->progress_order(read_msg_);
			}
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.order(), order_message::sign_length),
				boost::bind(
					&client::handle_read_sign, this,
					boost::asio::placeholders::error));
		}
		else
		{
			do_close();   
		}
	}





	void do_write(order_message msg)   
	{

		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);

		if (!write_in_progress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().order(),
					write_msgs_.front().length_()), // �ѷ�������д��buffer  
				boost::bind(&client::handle_write, this,
					boost::asio::placeholders::error));
		}
	}

	void handle_write(const boost::system::error_code& error) 
	{

		if (!error)
		{

			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().order(),//�ж��Ƿ��ж��������
						write_msgs_.front().length_()),
					boost::bind(&client::handle_write, this,
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
	order_message read_msg_;  // ���buffer����������  
	order_message_queue write_msgs_; // д��buffer�����ݶ��� 
	OnlineHeroSelect* pOnlineHeroSelect = nullptr;
	OnLinePlay* pOnLinePlay = nullptr;
	bool ifsuccess = false;
}

#endif // CLIENT_HPP