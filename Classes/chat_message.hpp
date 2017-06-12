
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
	//chat_message.data_��Ϊ�����֣�header��body������headerΪͷ�����������������body�ַ����ĳ��ȣ����header���󣬽���ȡ�����͡�
	//����õ��ַ����ĳ���
	bool decode_header()
	{
		using namespace std;
		char header[header_length + 1] = "";
		strncat(header, data_, header_length);//�����ַ���
		body_length_ = atoi(header);//���ַ���ת��Ϊ������
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}
	//���ַ����ĳ���д��data_��
	void encode_header()
	{
		using namespace std;
		char header[header_length + 1] = "";
		sprintf(header, "%3d", body_length_);//���ݸ�ʽ��
		memcpy(data_, header, header_length);//����
	}

private:
	char data_[header_length + max_body_length];
	size_t body_length_;
};
#endif