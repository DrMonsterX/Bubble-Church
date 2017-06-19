
#pragma warning(disable:4996)  
#ifndef ORDER_MESSAGE_HPP  
#define ORDER_MESSAGE_HPP  

#include <cstdio>  
#include <cstdlib>  
#include <cstring>  
using namespace std;
class order_message {
public:
	enum { max_name_length = 10, max_order_length = 12, sign_length = 1 };
	order_message()
		: order_size(0),name_size(0),ip_size(0)
	{
	}
	void get_name(char *name,size_t size)
	{
		if (size < 13) 
		{
			memcpy(owner_name, name, size);
			name_size = size;
		}
	}
	void get_ip(char *ip)
	{

		memcpy(owner_ip, ip, 7);
		ip_size = 7;
		order_size = 9;
	}
	void copy_(char*content, size_t con_size)
	{
		memset(order_, 0, order_size);
		memcpy(order_, content, con_size);
		order_size = con_size;
	}
	char player_num()
	{
		return order_[8];
	}
	size_t length_()
	{
		return order_size;
	}
	char *order()
	{
		return order_;
	}
	char *body()
	{
		return order_ + sign_length;
	}
	char *name()
	{
		return order_ + sign_length + 1;
	}
	void up()
	{
		memset(order_, 0, order_size);
		add_sign('1');		
	}
	void down()
	{
		memset(order_, 0, order_size);
		add_sign('2');
	}
	void left()
	{
		memset(order_, 0, order_size);
		add_sign('3');
	}
	void right()
	{
		memset(order_, 0, order_size);
		add_sign('4');
	}
	void create_boom()
	{
		memset(order_, 0, order_size);
		add_sign('5');
	}
	void start_game()
	{
		memset(order_, 0, order_size);
		add_sign('6');
	}
	void die()
	{
		memset(order_, 0, order_size);
		add_sign('7');
	}
	void login()
	{
		memset(order_, 0, order_size);
		order_[0] = (char)(name_size + ip_size + 47);
		order_[1] = '8';
		strcat(order_, owner_name);
		get_length();
	}
	void send_ip()
	{

		memset(order_, 0, order_size);
		add_sign('9');
	}
	void roleA()
	{
		memset(order_, 0, order_size);
		add_sign('<');
	}
	void roleB()
	{
		memset(order_, 0, order_size);
		add_sign('>');
	}
	void roleC()
	{
		memset(order_, 0, order_size);
		add_sign('[');
	}
	void roleD()
	{
		memset(order_, 0, order_size);
		add_sign(']');
	}
	void mapA()
	{
		memset(order_, 0, order_size);
		add_sign('a');
	}
	void mapB()
	{
		memset(order_, 0, order_size);
		add_sign('b');
	}
	void mapC()
	{
		memset(order_, 0, order_size);
		add_sign('c');
	}
	void mapD()
	{
		memset(order_, 0, order_size);
		add_sign('d');
	}
	void end_game()
	{
		memset(order_, 0, order_size);
		add_sign('0');
	}
	void stop_move()
	{
		memset(order_, 0, order_size);
		add_sign('(');
	}void stop_boom()
	{
		memset(order_, 0, order_size);
		add_sign(')');
	}
	void add_sign(char c)
	{
		//命令格式为sign+name，通过辨别sign，分析命令的长短和命令的种类
		//第一位为数据长短-3，记录数据的大小
		//第二位为命令的种类 
		//1-up
		//2-down
		//3-left
		//4-right
		//5-create_boom
		//6-start_game
		//7-die
		//8-login
		//9-get_ip
		//<-roleA
		//>-roleB
		//[-roleC
		//]-roleD
		//a-mapA
		//b-mapB
		//c-mapC
		//d-mapD
		//0-end_game
		//(-stop_move
		//)-stop_boom
		order_[0] = (char)(name_size+ ip_size +47);
		order_[1] = c;
		strcat(order_, owner_ip);
		get_length();		
	}
	void get_length()
	{
		order_size = ((int)order_[0]) - 47 + 2;
	}
	char get_order()
	{
		return order_[1];
	}
private:
	char owner_name[11] = { 0 };
	char owner_ip[8] = { 0 };
	char order_[13] = { 0 };
	size_t name_size;
	size_t order_size;
	size_t ip_size;	
};

#endif