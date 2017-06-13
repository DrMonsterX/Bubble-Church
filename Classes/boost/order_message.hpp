
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
		: order_size(0),name_size(0)
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
	void copy_(char*content, size_t con_size)
	{
		memcpy(order_, content, con_size);
		order_size = con_size;
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
		order_[13] = { 0 };
		add_sign('1');		
	}
	void down()
	{
		order_[13] = { 0 };
		add_sign('2');
	}
	void left()
	{
		order_[13] = { 0 };
		add_sign('3');
	}
	void right()
	{
		order_[13] = { 0 };
		add_sign('4');
	}
	void create_boom()
	{
		order_[13] = { 0 };
		add_sign('5');
	}
	void start_game()
	{
		order_[13] = { 0 };
		add_sign('6');
	}
	void die()
	{
		order_[13] = { 0 };
		add_sign('7');
	}
	void login()
	{
		order_[13] = { 0 };
		add_sign('8');
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
		order_[0] = (char)(name_size+47);
		order_[1] = c;
		strcat(order_, owner_name);
		get_length();
		
	}
	void get_length()
	{
		order_size = ((int)order_[0]) - 47 + 2;
	}
	void get_order()
	{
		if (order_[1] == '1')
			;//up
		else if (order_[1] == '2')
			;//down
		else if (order_[1] == '3')
			;//left
		else if (order_[1] == '4')
			;//right
		else if (order_[1] == '5')
			;//create_boom
		else if (order_[1] == '6')
			;//start_game
		else if (order_[1] == '7')
			;//die
		else if (order_[1] == '8')
			;//login


	}
private:
	char owner_name[11] = { 0 };
	char order_[13] = { 0 };
	size_t name_size;
	size_t order_size;
	
};

#endif