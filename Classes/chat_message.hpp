
#pragma warning(disable:4996)  
#ifndef CHAT_MESSAGE_HPP  
#define CHAT_MESSAGE_HPP  

#include <cstdio>  
#include <cstdlib>  
#include <cstring>  

class chat_message
{
public:
	enum { header_length = 3 };
	enum { max_body_length = 512 };

	chat_message()
		: body_length_(0)
	{
	}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	size_t length() const
	{
		return header_length + body_length_;
	}

	const char* body() const
	{
		return data_ + header_length;
	}

	char* body()
	{
		return data_ + header_length;
	}

	size_t body_length() const
	{
		return body_length_;
	}

	void body_length(size_t length)
	{
		body_length_ = length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}
	//chat_message.data_分为两部分，header和body，其中header为头，他代表着这个正文body字符串的长度，如果header过大，将会取消发送。
	//解码得到字符串的长度
	bool decode_header()
	{
		using namespace std;
		char header[header_length + 1] = "";
		strncat(header, data_, header_length);//链接字符串
		body_length_ = atoi(header);//将字符串转化为整形数
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}
	//把字符串的长度写到data_里
	void encode_header()
	{
		using namespace std;
		char header[header_length + 1] = "";
		sprintf(header, "%3d", body_length_);//数据格式化
		memcpy(data_, header, header_length);//拷贝
	}

private:
	char data_[header_length + max_body_length];
	size_t body_length_;
};
#endif