#ifndef CRYPTO_H
#define CRYPTO_H
#include <stdlib.h>

/**
* 基于DH的密钥协商加密类 
* 1、请先使用Crypto::init()方法初始化随机种子 
* 2、客户端构造此类，服务端通过客户端生成的 [g,p] 构造 
* 3、客户端通过调用get_public()方法得到一个数组 [g, p] 
* 4、客户端、服务端通过get_pub_key()方法获取公钥 C、S 用于协商 
* 5、客户端、服务端通过get_key(size_t pub_key)方法获取密钥用于加密 
* 6、客户端、服务端可使用crypto(char *data, size_t size, const char *key)方法加解密 
*/
class Crypto
{
	public:
		Crypto();
		Crypto(size_t g, size_t p);
		static void init();
		size_t *get_public();
		size_t get_pub_key();
		char *get_key(size_t pub_key);
		void crypto(char *data, size_t size, const char *key);
		virtual ~Crypto();
		
	protected:
		size_t create_big_integer();
		size_t pow_mod(size_t n, unsigned int times, size_t mod);
		
	private:
		size_t _g, _p;
		size_t *_public;
		size_t _private;
		size_t _pub_key;
		char *_pri_key;
};

#endif
