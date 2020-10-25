#include <iostream>
#include <string.h>
#include "crypto.h"
using namespace std;

void print(char *data, int size)
{
	cout << ""; 
	for(int i=0; i<size; i++)
	{
		cout << data[i];
	}
	cout << endl;
}

int main(int argc, char** argv) 
{
	Crypto::init(); // ��ʼ��������� 
	
	// ģ��Э�� 
	Crypto client;  // A 
	size_t *g_p = client.get_public(); // ���� (g, p) 
	size_t X = client.get_pub_key();   // ���� X 
	
	Crypto server(g_p[0], g_p[1]);     // B, ���� (g, p)  
	size_t Y = server.get_pub_key();   // ���� Y 
	char *K2 = server.get_key(X);      // B ����Ự��Կ 
	char *K1 = client.get_key(Y);      // A ͨ�� B ���� Y ������Ự��Կ 
	cout << "K1: " << K1 << "\nK2: " << K2 << endl << endl;
	if(strcmp(K1, K2))
	{
		cout<< "�Ự��Կ���ɴ���" << endl;
		return 0; 
	}
	
	// ģ��Ự 
	char data[11] = "helloworld";     // ���� 
	
	cout << "A����: " << endl; 
	client.crypto(data, 10, K1);       // ʹ����Կ���� 
	print(data, 10);
	cout << "==========" << endl;
	
	cout << "B����: " << endl; 
	server.crypto(data, 10, K2);       // ʹ����Կ���� 
	print(data, 10);
	cout << "==========" << endl;	
	return 0;
}
