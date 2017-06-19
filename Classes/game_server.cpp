
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
//���������													
class game_participant
{
public:
	virtual ~game_participant() {}
	virtual void deliver(const order_message& msg) = 0; // ������Ϸ������������Ϣ  
	void get_name(char*p, int n)   //��¼�����ߵ�ID
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

//��Ϸ����
class game_room
{
public: 
	//�����߼�����Ϸ����
	void join(game_participant_ptr participant) 
	{

		participants_.push_back(participant);
		
	}
	//���������뿪ʱ��ɾ����������Ϣ��
	void leave(game_participant_ptr participant)
	{
		player_num--;
		player_ready--;
		std::vector<game_participant_ptr>::iterator pos_parti = find(participants_.begin(), participants_.end(), participant);
		int position = std::distance(participants_.begin(), pos_parti);
		participants_.erase(participants_.begin() + position);
		
	}

	 
	void deliver(const order_message& msg) // ����������Ϣ  
	{

		recent_msgs_.push_back(msg);
		//�����Ϣ��Ϊ1000����������������ݡ�
		while (recent_msgs_.size() >= max_recent_msgs)
			recent_msgs_.pop_front(); // ����ʱ�������������  

									  // ������Ϣ����ÿ����Ϸ������  
		for (vector<game_participant_ptr>::iterator pos_Parti = participants_.begin(); pos_Parti < participants_.end(); pos_Parti++)
			(*pos_Parti)->deliver(msg);
	}
	void back_deliver(const order_message& msg) //�����Կͻ���id
	{

		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() >= max_recent_msgs)
		recent_msgs_.pop_front();
		vector<game_participant_ptr>::iterator p_end = participants_.end() - 1;
		(*p_end)->deliver(msg);
	}
	

	//��������Ϣ
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
	std::vector<game_participant_ptr> participants_; // ��ǰ��Ϸ������. 
	size_t max_recent_msgs = 1000;// ������Ϣ����1000
	order_message_queue recent_msgs_; // ��Ϣ���У�����������������			
	
};

//----------------------------------------------------

// ����Ϸ�����£�һ��session����һ�������ߣ�����Ҫ��¼�Ų����߶���Ϣ�Ķ�д  
class game_session
	: public game_participant, // �̳� chat_participant
	public boost::enable_shared_from_this<game_session> // ����ʹ��shared_from_this() ���г�Ա����Ҫ�ѵ�ǰ�������Ϊ����������������
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

	// ����ͷ�����ݣ���ȡ����ȣ���ȡ�������� 
	void handle_read_sign(const boost::system::error_code& error)   
	{
		
		read_msg_.get_length();		
		if (!error)
		{
			
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.length_() - 1),// ȡ����ֵ�read_msg_  			
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
		
		if (type == '8')//8Ϊ��¼��־��
		{
			room_.participants_changed(msg.name(), id_list, msg.length_() - 2);//��¼��½����Ϣ
			if (id_list[6] == '3')//��Ա���ܾ���½
			{
				msg.copy_(c_full_player, strlen(c_full_player));
				room_.back_deliver(msg);
			}
			else 
			{
				player_num++;
				msg.get_ip(id_list);
				msg.send_ip();
				room_.back_deliver(msg);						//����ip		
				id_list[6] = id_list[6] + 1;
			}
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.order(), order_message::sign_length),
				boost::bind(
					&game_session::handle_read_sign, shared_from_this(),
					boost::asio::placeholders::error));
		}
		else if (type == '0')//0Ϊ������־�������Ϸ����
		{
			room_.clear();		
		}
		else if (type == '<' || type == '>' || type == '[' || type == ']')//��¼����ѡ����Ϣ��
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
			if (player_ready == player_num&&ifstart==false)//��ȷ���������ڲ�������������Ϸ��ʼ
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
	
	
	//�������ݵ�write_msgs_���Ӷ��е��ʼһ������������Ϣ��buffer  
	void deliver(const order_message& msg)
	{
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().order(),
					write_msgs_.front().length_()), // ���е��ʼһ������������Ϣ��buffer  
				boost::bind(&game_session::handle_write, shared_from_this(),
					boost::asio::placeholders::error));
		}
	}

	// ��write_msgs_������buffer��ʹ�ͻ��˿��Եõ����ݹ��������ֵ��write_msgs_Ϊ��  
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
	order_message read_msg_; // ���buffer����������  
	order_message_queue write_msgs_;// ��д��buffer�����ݶ��У�deque  		
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
	// �����ӵ���ʱ������Ȼ��ȴ��¸����ӵ���  
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
		chat_server_list servers; // server�б�һ��server�൱��һ����Ϸƽ̨��
		tcp::endpoint endpoint(tcp::v4(), 33668);//��ֵĶ˿�33668 hh
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