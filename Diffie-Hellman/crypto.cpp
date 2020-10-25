#include "crypto.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>

Crypto::Crypto()
{
	this->_g = (unsigned)rand()%9+2; 
	this->_p = create_big_integer();
	this->_private = (size_t)rand()%this->_p; // create_big_integer()>>8%this->_p;
	this->_pub_key = pow_mod(this->_g, this->_private, this->_p); 
	this->_pri_key = new char[sizeof(size_t)+1];
	this->_public = new size_t[2];
}

Crypto::Crypto(size_t g, size_t p)
{
	this->_g = g;
	this->_p = p;
	this->_private = (size_t)rand()%this->_p; // create_big_integer()>>8%this->_p;
	this->_pub_key = pow_mod(this->_g, this->_private, this->_p); 
	this->_pri_key = new char[sizeof(size_t)+1];
	this->_public = new size_t[2];
}

void Crypto::init()
{
	srand((unsigned)time(0));
}

size_t *Crypto::get_public()
{
	this->_public[0] = _g;
	this->_public[1] = _p;
	return this->_public;
}

size_t Crypto::get_pub_key()
{
	return this->_pub_key;
}

char *Crypto::get_key(size_t pub_key)
{
	size_t tmp = pow_mod(pub_key, this->_private, this->_p);
	sprintf(this->_pri_key, "%08x", tmp);
	return this->_pri_key;
}

void Crypto::crypto(char *data, size_t size, const char *key)
{
	size_t len = strlen(key);
	for(size_t i=0; i<size; ++i)
	{
		data[i] ^= key[i%len];
	}
}

size_t Crypto::create_big_integer()
{
	return ((size_t)((size_t)rand()<<16)|(size_t)rand());// | (size_t)0x80000000; // 8:1000, 28*0
}

size_t Crypto::pow_mod(size_t n, unsigned int times, size_t mod)
{
	size_t tmp = 1;
	for(unsigned int i=0; i<times; i++)
	{
		tmp = tmp*n%mod;
	}
	return tmp;
}

Crypto::~Crypto()
{
	delete [] this->_public;
	delete [] this->_pri_key;
}
