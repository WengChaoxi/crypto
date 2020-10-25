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
	Crypto::init(); // 初始化随机种子 
	
	// 模拟协商 
	Crypto client;  // A 
	size_t *g_p = client.get_public(); // 生成 (g, p) 
	size_t X = client.get_pub_key();   // 计算 X 
	
	Crypto server(g_p[0], g_p[1]);     // B, 接收 (g, p)  
	size_t Y = server.get_pub_key();   // 计算 Y 
	char *K2 = server.get_key(X);      // B 计算会话密钥 
	char *K1 = client.get_key(Y);      // A 通过 B 发的 Y 计算出会话密钥 
	cout << "K1: " << K1 << "\nK2: " << K2 << endl << endl;
	if(strcmp(K1, K2))
	{
		cout<< "会话密钥生成错误" << endl;
		return 0; 
	}
	
	// 模拟会话 
	char data[11] = "helloworld";     // 明文 
	
	cout << "A加密: " << endl; 
	client.crypto(data, 10, K1);       // 使用密钥加密 
	print(data, 10);
	cout << "==========" << endl;
	
	cout << "B解密: " << endl; 
	server.crypto(data, 10, K2);       // 使用密钥解密 
	print(data, 10);
	cout << "==========" << endl;	
	return 0;
}
