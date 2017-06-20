#ifndef ORDERMESSAGEHPP  
#define ORDERMESSAGEHPP  

#include <cstdio>  
#include <cstdlib>  
#include <cstring>  
using namespace std;
class orderMessage {
public:
	enum { maxNameLength = 10, maxOrderLength = 12, signLength = 1 };
	orderMessage()
		: orderSize(0),nameSize(0),idSize(0)
	{
	}
	void getName(char *name,size_t size)
	{
		if (size < 13) 
		{
			memcpy(ownerName, name, size);
			nameSize = size;
		}
	}
	void getId(char *id)
	{

		memcpy(ownerId, id, 7);
		idSize = 7;
		orderSize = 9;
	}
	void copy_(char*content, size_t conSize)
	{
		memset(order_, 0, orderSize);
		memcpy(order_, content, conSize);
		orderSize = conSize;
	}
	char playerNum()
	{
		return order_[8];
	}
	size_t length_()
	{
		return orderSize;
	}
	char *order()
	{
		return order_;
	}
	char *body()
	{
		return order_ + signLength;
	}
	char *name()
	{
		return order_ + signLength + 1;
	}
	void up()
	{
		memset(order_, 0, orderSize);
		addSign('1');		
	}
	void down()
	{
		memset(order_, 0, orderSize);
		addSign('2');
	}
	void left()
	{
		memset(order_, 0, orderSize);
		addSign('3');
	}
	void right()
	{
		memset(order_, 0, orderSize);
		addSign('4');
	}
	void createBoom()
	{
		memset(order_, 0, orderSize);
		addSign('5');
	}
	void startGame()
	{
		memset(order_, 0, orderSize);
		addSign('6');
	}
	void die()
	{
		memset(order_, 0, orderSize);
		addSign('7');
	}
	void login()
	{
		memset(order_, 0, orderSize);
		order_[0] = (char)(nameSize + idSize + 47);
		order_[1] = '8';
		strcat(order_, ownerName);
		getLength();
	}
	void sendId()
	{

		memset(order_, 0, orderSize);
		addSign('9');
	}
	void roleA()
	{
		memset(order_, 0, orderSize);
		addSign('<');
	}
	void roleB()
	{
		memset(order_, 0, orderSize);
		addSign('>');
	}
	void roleC()
	{
		memset(order_, 0, orderSize);
		addSign('[');
	}
	void roleD()
	{
		memset(order_, 0, orderSize);
		addSign(']');
	}
	void endGame()
	{
		memset(order_, 0, orderSize);
		addSign('0');
	}
	void stopMove()
	{
		memset(order_, 0, orderSize);
		addSign('(');
	}void stopBoom()
	{
		memset(order_, 0, orderSize);
		addSign(')');
	}
	void addSign(char c)
	{
		//the form of order is 'sign+name'£¬By identifying the sign, analyze the length of command and the type of command.
		//The first is data length -3, and the size of the data is recorded
		//The second is the type of order
		//1-up
		//2-down
		//3-left
		//4-right
		//5-createBoom
		//6-startGame
		//7-die
		//8-login
		//9-getId
		//<-roleA
		//>-roleB
		//[-roleC
		//]-roleD
		//0-endGame
		//(-stopMove
		//)-stopBoom
		//g-gameStart
		order_[0] = (char)(nameSize+ idSize +47);
		order_[1] = c;
		strcat(order_, ownerId);
		getLength();		
	}
	void getLength()
	{
		orderSize = ((int)order_[0]) - 47 + 2;
	}
	char getOrder()
	{
		return order_[1];
	}
private:
	char ownerName[11] = { 0 };
	char ownerId[8] = { 0 };
	char order_[13] = { 0 };
	size_t nameSize;
	size_t orderSize;
	size_t idSize;	
};

#endif
