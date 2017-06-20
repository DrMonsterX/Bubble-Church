#include <deque>  
#include <list> 
#include <iostream>   
#include <boost/bind.hpp>  
#include <boost/shared_ptr.hpp>  
#include <boost/enable_shared_from_this.hpp>  
#include <boost/asio.hpp>  
#include <orderMessage.hpp> 
#include <vector>


using boost::asio::ip::tcp;
using namespace std;


typedef std::deque<orderMessage> orderMessageQueue;
char idList[8] = "player1";
bool ifStart = false;
int playerNum = 0;
int playerReady = 0;
int flag = 1;


//-------------------------------------------------------
//Chat participant												
class gameParticipant
{
public:
	virtual ~gameParticipant() {}
	virtual void deliver(const orderMessage& msg) = 0; // Send game participant command message  
	void getName(char*p, int n)   //Record participant's ID
	{
		memcpy(name, p, n);
	}
	char *name_()
	{
		return name;
	}
	void getId(char *p)
	{
		memcpy(id, p, 7);
	}
	char *id_()
	{
		return id;
	}
private:
	char name[13] = { 0 };
	char id[8] = { 0 };
};

typedef boost::shared_ptr<gameParticipant> gameParticipantPtr;

//-----------------------------------------------------------------

//Game room
class gameRoom
{
public: 
	//Participants join the game room
	void join(gameParticipantPtr participant) 
	{

		participants_.push_back(participant);
		
	}
	//When participants leave, delete participant information.
	void leave(gameParticipantPtr participant)
	{
		playerNum--;
		playerReady--;
		std::vector<gameParticipantPtr>::iterator posParti = find(participants_.begin(), participants_.end(), participant);
		int position = std::distance(participants_.begin(), posParti);
		participants_.erase(participants_.begin() + position);
		
	}

	// Send command message 
	void deliver(const orderMessage& msg)
	{

		recentMsg.push_back(msg);
		//The maximum number of messages is 1000 to get rid of excess content.
		while (recentMsg.size() >= maxRecentMsgs)
			recentMsg.pop_front(); // Clear the buffer from the out of date command

									  // Send new messages to each game player  
		for (vector<gameParticipantPtr>::iterator posParti = participants_.begin(); posParti < participants_.end(); posParti++)
			(*posParti)->deliver(msg);
	}
	void backDeliver(const orderMessage& msg) //Only return the client ID 
	{

		recentMsg.push_back(msg);
		while (recentMsg.size() >= maxRecentMsgs)
		recentMsg.pop_front();
		vector<gameParticipantPtr>::iterator pEnd = participants_.end() - 1;
		(*pEnd)->deliver(msg);
	}
	

	//Participant information
	void participantsChanged(char*name,char*id, int n)
	{
		vector<gameParticipantPtr>::iterator pEnd = participants_.end() - 1;
		(*pEnd )->getName(name, n);
		(*pEnd)->getId(id);
	}
	
	
	void clear()
	{
		participants_.swap(vector<gameParticipantPtr>()); 
		playerNum = 0;
		playerReady = 0;
		idList[6] = 1;
		flag=1;
	}
	orderMessage roleA;
	orderMessage roleB;
private:
	std::vector<gameParticipantPtr> participants_; // Current game player
	size_t maxRecentMsgs = 1000;// The maximum number of messages is 1000
	orderMessageQueue recentMsg; // Message queuing: convenient to clear superfluous commands			
	
};

//----------------------------------------------------

// In the game room, a session is a participant who records the participants' reading and writing of information
class gameSession
	: public gameParticipant, // inherit gameParticipant
	public boost::enable_shared_from_this<gameSession> //  use shared_from_this (), where the member function passes the current class object as a parameter to another function
{
public:
	gameSession(boost::asio::io_service& ioService, gameRoom& room)
		: socket_(ioService),
		room_(room)
	{
;
	}

	tcp::socket& socket()
	{

		return socket_;
	}

	void start()  
	{
		
		room_.join(shared_from_this());
		
		boost::asio::async_read(socket_,
			boost::asio::buffer(readMsg.order(), orderMessage::signLength),
			boost::bind(&gameSession::handleReadSign, shared_from_this(),
				boost::asio::placeholders::error));
	}

	// Handles header content, gets command length, reads text content 
	void handleReadSign(const boost::system::error_code& error)   
	{
		
		readMsg.getLength();		
		if (!error)
		{
			
			boost::asio::async_read(socket_,
				boost::asio::buffer(readMsg.body(), readMsg.length_() - 1),// Take the command section to readMsg
				boost::bind(&gameSession::handleReadBody, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else
		{
			room_.leave(shared_from_this()); 
		}
	}

	void handleReadBody(const boost::system::error_code& error)  
	{				
		if (!error)
		{
			
			processMsg(readMsg);                                
		}
		else
		{
			room_.leave(shared_from_this()); 
		}
	}

	void processMsg(orderMessage& msg)
	{
		char type = msg.getOrder();
		
		if (type == '8')//8 is the login flag.
		{
			room_.participantsChanged(msg.name(), idList, msg.length_() - 2);//Log login information
			if (idList[6] == '3')//Full ,refuse login
			{
				msg.copy_(cFullPlayer, strlen(cFullPlayer));
				room_.backDeliver(msg);
			}
			else 
			{
				playerNum++;
				msg.getId(idList);
				msg.sendId();
				room_.backDeliver(msg);						//return id		
				idList[6] = idList[6] + 1;
			}
			boost::asio::async_read(socket_,
				boost::asio::buffer(readMsg.order(), orderMessage::signLength),
				boost::bind(
					&gameSession::handleReadSign, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else if (type == '0')//0 is the end flag, clear gameRoom
		{
			room_.clear();		
		}
		else if (type == '<' || type == '>' || type == '[' || type == ']')//Record character selection information.
		{
			if (*(msg.order()) == '/')
			{
				*(msg.order()) = '6';
				msg.getLength();
			}
			playerReady++;
			if (flag == 1)
			{
				room_.roleA.copy_(msg.order(), msg.length_());
				flag++;
			}
			else if(flag == 2)
			{
				room_.roleB.copy_(msg.order(), msg.length_());
				flag++;
			}
			if (playerReady == playerNum&&ifStart==false)//When the number of players is equal to the number of participants, the game begins
			{				
				room_.deliver(room_.roleA);
				room_.deliver(room_.roleB);
				gameStart.copy_(cGameStart, strlen(cGameStart));
				room_.deliver(gameStart);
				ifStart = true;
			}
			
			boost::asio::async_read(socket_,
				boost::asio::buffer(readMsg.order(), orderMessage::signLength),
				boost::bind(
					&gameSession::handleReadSign, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else {
			room_.deliver(readMsg);
			boost::asio::async_read(socket_,
				boost::asio::buffer(readMsg.order(), orderMessage::signLength),
				boost::bind(
					&gameSession::handleReadSign, shared_from_this(),
					boost::asio::placeholders::error));
		}
	}
	
	
	//Save data to writeMsgs and send command information from the beginning of the queue to buffer 
	void deliver(const orderMessage& msg)
	{
		bool writeInProgress = !writeMsgs.empty();
		writeMsgs.push_back(msg);
		
		if (!writeInProgress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(writeMsgs.front().order(),
					writeMsgs.front().length_()), // From the start of the queue, send a command message to buffer
				boost::bind(&gameSession::handleWrite, shared_from_this(),
					boost::asio::placeholders::error));
		}
	}

	// Send writeMsgs data to buffer so that clients can get recursive calls to their own values to writeMsgs empty
	void handleWrite(const boost::system::error_code& error)
	{

		if (!error)
		{
			
			writeMsgs.pop_front();
			if (!writeMsgs.empty())
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(writeMsgs.front().order(),
						writeMsgs.front().length_()),
					boost::bind(&gameSession::handleWrite, shared_from_this(),
						boost::asio::placeholders::error));
			}
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}
	
	
private:
	tcp::socket socket_;
	gameRoom& room_;
	orderMessage readMsg; // Store data read from buffer
	orderMessageQueue writeMsgs;// To write to the buffer data queue  deque	
	orderMessage gameStart;
	char cFullPlayer[7] = "3ffull";
	char cGameStart[7] = "3ggame";
	
};

typedef boost::shared_ptr<gameSession> gameSessionPtr;


//----------------------------------------------------------------------  

class gameServer
{
public:
	gameServer(boost::asio::io_service& ioService,
		const tcp::endpoint& endpoint)
		: ioService_(ioService),
		acceptor_(ioService, endpoint)
	{
		gameSessionPtr newSession(new gameSession(ioService_, room_));
		acceptor_.async_accept(newSession->socket(),
			boost::bind(&gameServer::handleAccept, this, newSession,
				boost::asio::placeholders::error));
	}
	//Triggered when the connection arrives, and then wait for the next connection to arrive
	void handleAccept(gameSessionPtr session, const boost::system::error_code& error)
	{

		if (!error)
		{
			
			session->start();
			gameSessionPtr newSession(new gameSession(ioService_, room_));
			acceptor_.async_accept(newSession->socket(),
				boost::bind(&gameServer::handleAccept, this, newSession,
					boost::asio::placeholders::error));
		}
	}

private:
	boost::asio::io_service& ioService_;
	tcp::acceptor acceptor_;
	gameRoom room_;
};

//-----------------------------------------------------------------

typedef boost::shared_ptr<gameServer> chatServerPtr;
typedef std::list<chatServerPtr> chatServerList;

int main(int argc, char* argv[])
{

	try
	{
		boost::asio::io_service ioService;
		chatServerList servers; // Server list: a server is equivalent to a game platform.
		tcp::endpoint endpoint(tcp::v4(), 33668);//a strange endpoint 33668 hh
		chatServerPtr server(new gameServer(ioService, endpoint));
		servers.push_back(server);
		ioService.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}