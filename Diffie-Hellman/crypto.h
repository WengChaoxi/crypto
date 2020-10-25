#ifndef CRYPTO_H
#define CRYPTO_H
#include <stdlib.h>

/**
* ����DH����ԿЭ�̼����� 
* 1������ʹ��Crypto::init()������ʼ��������� 
* 2���ͻ��˹�����࣬�����ͨ���ͻ������ɵ� [g,p] ���� 
* 3���ͻ���ͨ������get_public()�����õ�һ������ [g, p] 
* 4���ͻ��ˡ������ͨ��get_pub_key()������ȡ��Կ C��S ����Э�� 
* 5���ͻ��ˡ������ͨ��get_key(size_t pub_key)������ȡ��Կ���ڼ��� 
* 6���ͻ��ˡ�����˿�ʹ��crypto(char *data, size_t size, const char *key)�����ӽ��� 
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
