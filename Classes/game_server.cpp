
#include <deque>  
#include <list> 
#include <iostream>   
#include <boost/bind.hpp>  
#include <boost/shared_ptr.hpp>  
#include <boost/enable_shared_from_this.hpp>  
#include <boost/asio.hpp>  
#include <boost/order_message.hpp> 
#include <vector>

using boost::asio::ip::tcp;
using namespace std;


typedef std::deque<order_message> order_message_queue;
char id_list[8] = "player1";
bool ifstart = false;
int player_num = 0;
int player_ready = 0;
int flag = 1;
//-------------------------------------------------------
//聊天参与者													
class game_participant
{
public:
	virtual ~game_participant() {}
	virtual void deliver(const order_message& msg) = 0; // 发送游戏参与者命令消息  
	void get_name(char*p, int n)   //记录参与者的ID
	{
		memcpy(name, p, n);
	}
	char *name_()
	{
		return name;
	}
	void get_ip(char *p)
	{
		memcpy(ip, p, 7);
	}
	char *ip_()
	{
		return ip;
	}
private:
	char name[13] = { 0 };
	char ip[8] = { 0 };
};

typedef boost::shared_ptr<game_participant> game_participant_ptr;

//-----------------------------------------------------------------

//游戏房间
class game_room
{
public: 
	//参与者加入游戏房间
	void join(game_participant_ptr participant) 
	{

		participants_.push_back(participant);
		
	}
	//当参与者离开时，删除参与者信息。
	void leave(game_participant_ptr participant)
	{
		player_num--;
		player_ready--;
		std::vector<game_participant_ptr>::iterator pos_parti = find(participants_.begin(), participants_.end(), participant);
		int position = std::distance(participants_.begin(), pos_parti);
		participants_.erase(participants_.begin() + position);
		
	}

	 
	void deliver(const order_message& msg) // 发送命令消息  
	{

		recent_msgs_.push_back(msg);
		//最大消息数为1000，到达清除多余内容。
		while (recent_msgs_.size() >= max_recent_msgs)
			recent_msgs_.pop_front(); // 将过时命令清出缓冲区  

									  // 将新消息发给每个游戏参与者  
		for (vector<game_participant_ptr>::iterator pos_Parti = participants_.begin(); pos_Parti < participants_.end(); pos_Parti++)
			(*pos_Parti)->deliver(msg);
	}
	void back_deliver(const order_message& msg) //仅回显客户端id
	{

		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() >= max_recent_msgs)
		recent_msgs_.pop_front();
		vector<game_participant_ptr>::iterator p_end = participants_.end() - 1;
		(*p_end)->deliver(msg);
	}
	

	//参与者信息
	void participants_changed(char*name,char*ip, int n)
	{
		vector<game_participant_ptr>::iterator p_end = participants_.end() - 1;
		(*p_end )->get_name(name, n);
		(*p_end)->get_ip(ip);
	}
	
	
	void clear()
	{
		participants_.swap(vector<game_participant_ptr>()); 
		player_num = 0;
		player_ready = 0;
		id_list[6] = 1;
	}
	order_message roleA;
	order_message roleB;
private:
	std::vector<game_participant_ptr> participants_; // 当前游戏参与者. 
	size_t max_recent_msgs = 1000;// 最大的消息数量1000
	order_message_queue recent_msgs_; // 消息队列：方便清除多余的命令			
	
};

//----------------------------------------------------

// 在游戏房间下，一个session就是一个参与者，他主要记录着参与者对信息的读写  
class game_session
	: public game_participant, // 继承 chat_participant
	public boost::enable_shared_from_this<game_session> // 可以使用shared_from_this() 其中成员函数要把当前类对象作为参数传给其他函数
{
public:
	game_session(boost::asio::io_service& io_service, game_room& room)
		: socket_(io_service),
		room_(room)
	{

	}

	tcp::socket& socket()
	{

		return socket_;
	}

	void start()  
	{
		
		room_.join(shared_from_this());
		
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.order(), order_message::sign_length),
			boost::bind(&game_session::handle_read_sign, shared_from_this(),
				boost::asio::placeholders::error));
	}

	// 处理头部内容，获取命令长度，读取正文内容 
	void handle_read_sign(const boost::system::error_code& error)   
	{
		
		read_msg_.get_length();		
		if (!error)
		{
			
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.length_() - 1),// 取命令部分到read_msg_  			
				boost::bind(&game_session::handle_read_body, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else
		{
			room_.leave(shared_from_this()); 
		}
	}

	void handle_read_body(const boost::system::error_code& error)  
	{
		
		cout << read_msg_.order() << endl;
		if (!error)
		{
			
			process_msg_(read_msg_);                                
		}
		else
		{
			room_.leave(shared_from_this()); 
		}
	}

	void process_msg_(order_message& msg)
	{
		char type = msg.get_order();
		
		if (type == '8')//8为登录标志。
		{
			room_.participants_changed(msg.name(), id_list, msg.length_() - 2);//记录登陆者信息
			if (id_list[6] == '3')//满员，拒绝登陆
			{
				msg.copy_(c_full_player, strlen(c_full_player));
				room_.back_deliver(msg);
			}
			else 
			{
				player_num++;
				msg.get_ip(id_list);
				msg.send_ip();
				room_.back_deliver(msg);						//回显ip		
				id_list[6] = id_list[6] + 1;
			}
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.order(), order_message::sign_length),
				boost::bind(
					&game_session::handle_read_sign, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else if (type == '0')//0为结束标志，清除游戏房间
		{
			room_.clear();		
		}
		else if (type == '<' || type == '>' || type == '[' || type == ']')//记录人物选择信息。
		{
			if (*(msg.order()) == '/')
			{
				*(msg.order()) = '6';
				msg.get_length();
			}
			player_ready++;
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
			if (player_ready == player_num&&ifstart==false)//当确定人数等于参与者人数，游戏开始
			{				
				room_.deliver(room_.roleA);
				room_.deliver(room_.roleB);
				game_start.copy_(c_game_start, strlen(c_game_start));
				room_.deliver(game_start);
				ifstart = true;
			}
			
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.order(), order_message::sign_length),
				boost::bind(
					&game_session::handle_read_sign, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else {
			room_.deliver(read_msg_);
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.order(), order_message::sign_length),
				boost::bind(
					&game_session::handle_read_sign, shared_from_this(),
					boost::asio::placeholders::error));
		}
	}
	
	
	//存入数据到write_msgs_，从队列的最开始一条发送命令信息到buffer  
	void deliver(const order_message& msg)
	{
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().order(),
					write_msgs_.front().length_()), // 队列的最开始一条发送命令消息到buffer  
				boost::bind(&game_session::handle_write, shared_from_this(),
					boost::asio::placeholders::error));
		}
	}

	// 把write_msgs_数据送buffer，使客户端可以得到，递归调用自身值到write_msgs_为空  
	void handle_write(const boost::system::error_code& error)
	{

		if (!error)
		{
			
			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().order(),
						write_msgs_.front().length_()),
					boost::bind(&game_session::handle_write, shared_from_this(),
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
	game_room& room_;
	order_message read_msg_; // 存从buffer读出的数据  
	order_message_queue write_msgs_;// 欲写入buffer的数据队列，deque  		
	order_message game_start;
	char c_full_player[7] = "3ffull";
	char c_game_start[7] = "3ggame";
	
};

typedef boost::shared_ptr<game_session> game_session_ptr;


//----------------------------------------------------------------------  

class game_server
{
public:
	game_server(boost::asio::io_service& io_service,
		const tcp::endpoint& endpoint)
		: io_service_(io_service),
		acceptor_(io_service, endpoint)
	{
		game_session_ptr new_session(new game_session(io_service_, room_));
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&game_server::handle_accept, this, new_session,
				boost::asio::placeholders::error));
	}
	// 有连接到来时触发，然后等待下个连接到来  
	void handle_accept(game_session_ptr session, const boost::system::error_code& error)
	{

		if (!error)
		{
			
			session->start();
			game_session_ptr new_session(new game_session(io_service_, room_));
			acceptor_.async_accept(new_session->socket(),
				boost::bind(&game_server::handle_accept, this, new_session,
					boost::asio::placeholders::error));
		}
	}

private:
	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
	game_room room_;
};

//-----------------------------------------------------------------

typedef boost::shared_ptr<game_server> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;

int main(int argc, char* argv[])
{

	try
	{
		boost::asio::io_service io_service;
		chat_server_list servers; // server列表：一个server相当于一个游戏平台。
		tcp::endpoint endpoint(tcp::v4(), 33668);//奇怪的端口33668 hh
		chat_server_ptr server(new game_server(io_service, endpoint));
		servers.push_back(server);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}