#ifndef CLIENTHPP
#define CLIENTHPP


#include <cstdlib>  
#include <deque>  
#include <iostream>  
#include <boost/bind.hpp>  
#include <boost/asio.hpp>  
#include <boost/thread.hpp>  
#include <orderMessage.hpp>
#include "OnLinePlay.h"
#include "OnlineHeroSelect.h"
 

using boost::asio::ip::tcp;
using namespace std;
typedef std::deque<orderMessage> orderMessageQueue;

class client
{
public:
	//connect

	friend class OnLinePlay;
	friend class OnlineHeroSelect;
	

	client(boost::asio::io_service& ioService,
		tcp::resolver::iterator endpointIterator)
		: ioService_(ioService),
		socket_(ioService)
	{		
		tcp::endpoint endpoint = *endpointIterator;
		socket_.async_connect(endpoint,
			boost::bind(&client::handleConnect, this,
				boost::asio::placeholders::error, ++endpointIterator));
	}

	void getPSelect(OnlineHeroSelect* p)
	{
		pOnlineHeroSelect = p;
	}

	void getPPlay(OnLinePlay* p)
	{
		pOnLinePlay = p;
	}

	void write(orderMessage msg)
	{

		ioService_.post(boost::bind(&client::doWrite, this, msg));
	}

	void close()
	{

		ioService_.post(boost::bind(&client::doClose, this));
	}

private:

	void handleConnect(const boost::system::error_code& error,
		tcp::resolver::iterator endpointIterator)
	{
		if (!error)
		{
			//succeed conneting ,bind 
			boost::asio::async_read(socket_,
				boost::asio::buffer(readMsg.order(), orderMessage::signLength),  //read the sign
				boost::bind(&client::handleReadSign, this,
					boost::asio::placeholders::error));
		}
		else if (endpointIterator != tcp::resolver::iterator())
		{
			//fail,again
			socket_.close();
			tcp::endpoint endpoint = *endpointIterator;
			socket_.async_connect(endpoint,
				boost::bind(&client::handleConnect, this,
					boost::asio::placeholders::error, ++endpointIterator));
		}
	}

	void handleReadSign(const boost::system::error_code& error)
	{

		readMsg.getLength();
		if (!error)
		{

			boost::asio::async_read(socket_,
				boost::asio::buffer(readMsg.body(), readMsg.length_() - 1),// read the body 			
				boost::bind(&client::handleReadBody, this,
					boost::asio::placeholders::error));
		}
		else
		{
			doClose();
		}
	}
	void handleReadBody(const boost::system::error_code& error)
	{

		
		if (!error)
		{
			char type = readMsg.getOrder();
			if (type == '9')
			{
				if (pOnlineHeroSelect != nullptr)
					pOnlineHeroSelect->progressOrder1(readMsg);
			}
			else
			{
				if (pOnLinePlay != nullptr)
					pOnLinePlay->progressOrder(readMsg);
			}
			boost::asio::async_read(socket_,
				boost::asio::buffer(readMsg.order(), orderMessage::signLength),
				boost::bind(
					&client::handleReadSign, this,
					boost::asio::placeholders::error));
		}
		else
		{
			doClose();   
		}
	}





	void doWrite(orderMessage msg)   
	{

		bool writeInProgress = !writeMsgs.empty();
		writeMsgs.push_back(msg);

		if (!writeInProgress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(writeMsgs.front().order(),
					writeMsgs.front().length_()), // write the msg to buffer
				boost::bind(&client::handleWrite, this,
					boost::asio::placeholders::error));
		}
	}

	void handleWrite(const boost::system::error_code& error) 
	{

		if (!error)
		{

			writeMsgs.pop_front();
			if (!writeMsgs.empty())
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(writeMsgs.front().order(),// Determine if there is excess content
						writeMsgs.front().length_()),
					boost::bind(&client::handleWrite, this,
						boost::asio::placeholders::error));
			}
		}
		else
		{
			doClose();
		}
	}

	void doClose()
	{

		socket_.close();
	}

private:
	boost::asio::io_service& ioService_;
	tcp::socket socket_;
	orderMessage readMsg;  // Store data read from buffer
	orderMessageQueue writeMsgs; // Data queue written to buffer
	OnlineHeroSelect* pOnlineHeroSelect = nullptr;
	OnLinePlay* pOnLinePlay = nullptr;
	
}

#endif // CLIENTHPP
