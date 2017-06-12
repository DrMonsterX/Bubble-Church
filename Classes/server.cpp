
#include "afx.h"  
#include <deque>  
#include <list> 
#include <iostream>   
#include <boost/bind.hpp>  
#include <boost/shared_ptr.hpp>  
#include <boost/enable_shared_from_this.hpp>  
#include <boost/asio.hpp>  
#include <boost/chat_message.hpp> 
#include <vector>

using boost::asio::ip::tcp;
using namespace std;


typedef std::deque<chat_message> chat_message_queue;
													 
//���������													
class chat_participant   
{
public:
	virtual ~chat_participant() {}
	virtual void deliver(const chat_message& msg) = 0; // ����  
	void get_name(char*p, int n)   //��¼�����ߵ�ID
	{
		memcpy(name, p, n);				
	}
	char *name_()
	{
		return name;
	}
private:
	char name[chat_message::max_body_length] = { 0 };
};

typedef boost::shared_ptr<chat_participant> chat_participant_ptr;



//������
class chat_room   
{
public:
	//�����߼���������
	void join(chat_participant_ptr participant) // 6  
	{

		participants_.push_back(participant);

		// ���������ڻ������Ϣ���͸��¼���ĳ�Ա
		for (chat_message_queue::iterator pos_msgs = recent_msgs_.begin(); pos_msgs < recent_msgs_.end(); pos_msgs++)
			participant->deliver(*pos_msgs);    
	}
	//���������뿪ʱ��ɾ����������Ϣ�������·��Ͳ�����������
	void leave(chat_participant_ptr participant)
	{
		char leave[50] = {0};
		std::vector<chat_participant_ptr>::iterator pos_parti = find(participants_.begin(), participants_.end(), participant);
		strcpy(leave, (*pos_parti)->name_());
		strcat(leave, leave_order);		
		leave_msg.body_length(strlen(leave));
		memcpy(leave_msg.body(), leave, leave_msg.body_length());
		leave_msg.encode_header();
		for (vector<chat_participant_ptr>::iterator pos_Parti = participants_.begin(); pos_Parti < participants_.end() ; pos_Parti++)				
			if (pos_Parti != pos_parti)
			{
				(*pos_Parti)->deliver(leave_msg);
			}
		int position = std::distance(participants_.begin(), pos_parti);
		participants_.erase(participants_.begin() + position);
		name_list_changed();
	}

	// ����msg������������  
	void deliver(const chat_message& msg) // 11 ����  
	{

		recent_msgs_.push_back(msg);
		//�����Ϣ��Ϊ20����������������ݡ�
		while (recent_msgs_.size() >= max_recent_msgs)
			recent_msgs_.pop_front(); // ����ʱ�������������  

	     // ������Ϣ����ÿ�������ҳ�Ա  
		for (vector<chat_participant_ptr>::iterator pos_Parti = participants_.begin(); pos_Parti < participants_.end(); pos_Parti++)
			(*pos_Parti)->deliver(msg);  
	}
	void participants_changed(char*p, int n)
	{
		vector<chat_participant_ptr>::iterator p_end = participants_.end() - 1;
		(*p_end)->get_name(p, n);
	}
	//����������Ա�����������͵�ÿ�����������С�
	void name_list_changed()
	{
		char name_list[50] = { 0 };
		strcpy(name_list, name_list_copy);
		for (vector<chat_participant_ptr>::iterator pos_Parti = participants_.begin(); pos_Parti < participants_.end(); pos_Parti++)
		{
			strcat(name_list, (*pos_Parti)->name_());
			strcat(name_list, " ");
		}		
		cout << name_list << "\n";
		name_list_msg.body_length(strlen(name_list));
		memcpy(name_list_msg.body(), name_list, name_list_msg.body_length());// line to msg  			
		name_list_msg.encode_header();		
		for (vector<chat_participant_ptr>::iterator pos_Parti = participants_.begin(); pos_Parti < participants_.end(); pos_Parti++)
			(*pos_Parti)->deliver(name_list_msg);
	}

private:
	std::vector<chat_participant_ptr> participants_; // ��ǰ�����ҵ�n��������. 
	size_t max_recent_msgs = 20;// ������Ϣ����20
	chat_message_queue recent_msgs_; // ��Ϣ���У�����������Ƚ�����Ϣ
	char name_list_copy[50] = "����������Ա�У�";
	chat_message name_list_msg;	
	chat_message leave_msg;
	char leave_order[9] = " leaves!";
};



// �������һ����£�һ��session����һ�������ߣ�����Ҫ��¼�Ų����߶���Ϣ�Ķ�д  
class chat_session
	: public chat_participant, // �̳� chat_participant
	public boost::enable_shared_from_this<chat_session> // ����ʹ��shared_from_this() ���г�Ա����Ҫ�ѵ�ǰ�������Ϊ����������������
{
public:
	chat_session(boost::asio::io_service& io_service, chat_room& room) 
		: socket_(io_service),
		room_(room)
	{

	}

	tcp::socket& socket()  
	{

		return socket_;
	}

	void start() // 5  
	{

		room_.join(shared_from_this());    										 
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::header_length), // �ȶ�ȡͷ�����ݣ����ж������Ƿ���� 
			boost::bind(
				&chat_session::handle_read_header, shared_from_this(),  
				boost::asio::placeholders::error));
	}

	// ����ͷ�����ݣ���ȡ�������� 
	void handle_read_header(const boost::system::error_code& error) // 9  
	{

		if (!error && read_msg_.decode_header())
		{
			boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),// ȡbuffer�ı����ֵ�read_msg_  
				boost::bind(&chat_session::handle_read_body, shared_from_this(),   
					boost::asio::placeholders::error));
		}
		else
		{
			room_.leave(shared_from_this()); // 14  
		}
	}

	//�����������ݣ��ж��Ƿ����µĲ����ߵ�½��
	void handle_read_body(const boost::system::error_code& error)  
	{
		char* p_login = strstr(read_msg_.body(), login);
		int distan = p_login - read_msg_.body() - 1;
		if (p_login)
		{
			room_.participants_changed(read_msg_.body(), distan);			
			if (!error)
			{
				room_.deliver(read_msg_); // 11  
				boost::asio::async_read(socket_,
					boost::asio::buffer(read_msg_.data(), chat_message::header_length),
					boost::bind(&chat_session::handle_read_header, shared_from_this(),// ѭ����ȡ
						boost::asio::placeholders::error));
			}
			else
			{
				room_.leave(shared_from_this());
			}
			room_.name_list_changed();
		}
		else
		{
			if (!error)
			{
				room_.deliver(read_msg_); // 11  
				boost::asio::async_read(socket_,
					boost::asio::buffer(read_msg_.data(), chat_message::header_length),
					boost::bind(&chat_session::handle_read_header, shared_from_this(),// ѭ����ȡ
						boost::asio::placeholders::error));
			}
			else
			{
				room_.leave(shared_from_this());
			}
		}
	}

	//�������ݵ�write_msgs_���Ͷ��е��ʼһ�����Ե�buffer  
	void deliver(const chat_message& msg) 
	{		
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg); 
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()), // ���е��ʼһ�����Ե�buffer  
				boost::bind(&chat_session::handle_write, shared_from_this(),
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
					boost::asio::buffer(write_msgs_.front().data(),  
						write_msgs_.front().length()),
					boost::bind(&chat_session::handle_write, shared_from_this(),
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
	chat_room& room_;
	chat_message read_msg_; // ���buffer����������  
	chat_message_queue write_msgs_;// ��д��buffer�����ݶ��У�deque  	
	char login[10] = "login OK!";
	
};

typedef boost::shared_ptr<chat_session> chat_session_ptr;

//----------------------------------------------------------------------  

class chat_server
{
public:
	chat_server(boost::asio::io_service& io_service,   
		const tcp::endpoint& endpoint)
		: io_service_(io_service),
		acceptor_(io_service, endpoint)
	{

		chat_session_ptr new_session(new chat_session(io_service_, room_));   
		acceptor_.async_accept(new_session->socket(), 
			boost::bind(&chat_server::handle_accept, this, new_session,
				boost::asio::placeholders::error));
	}
	// �����ӵ���ʱ������Ȼ��ȴ��¸����ӵ���  
	void handle_accept(chat_session_ptr session, const boost::system::error_code& error)
	{

		if (!error)
		{
			session->start();    
			chat_session_ptr new_session(new chat_session(io_service_, room_));   
			acceptor_.async_accept(new_session->socket(),   
				boost::bind(&chat_server::handle_accept, this, new_session,
					boost::asio::placeholders::error));
		}
	}

private:
	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
	chat_room room_;
};

typedef boost::shared_ptr<chat_server> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;

//----------------------------------------------------------------------  

int _tmain(int argc, _TCHAR* argv[])
{
	
	try
	{
		boost::asio::io_service io_service;
		chat_server_list servers; // server�б�һ��server�൱��һ������ƽ̨  
		tcp::endpoint endpoint(tcp::v4(), 1000);/*boost::asio::ip::address_v4::from_string("127.0.0.1")*/
		chat_server_ptr server(new chat_server(io_service, endpoint)); 
		servers.push_back(server);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}