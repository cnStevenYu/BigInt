#include <bitset>
#include <iostream>
#define MAX_BITS 8
#define MAX(a, b) ((a)>(b)?(a): (b))
using namespace std;
class BigInt{
	friend ostream& operator<<(ostream&, const BigInt&);
public:
	BigInt();
	BigInt(char *);	
	BigInt(unsigned long long);
	BigInt& operator<<= (size_t offset);
	BigInt& operator+=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	BigInt& operator/=(const BigInt&);
	
private:
	size_t size;
	bitset<MAX_BITS> bits;
};
BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator<<(BigInt&, size_t offset);