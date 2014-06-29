#include "BigInt128.h"

BigInt::BigInt(char *str)
{
	bits = bitset<MAX_BITS>(str);
	size = 0;
	for (size_t i = 0; i < strlen(str); i++){
		if (bits.test(i))
			size = i;
	}
	size++;
}
BigInt::BigInt(unsigned long long num)
{
	bits = bitset<MAX_BITS>(num);
	size = 0;
	for (size_t i = 0; i < MAX_BITS; i++){
		if (bits.test(i))
			size = i;
	}
	size++;
}

BigInt&
BigInt::operator+=(const BigInt& r_num)
{
	unsigned short carry = 0;
	unsigned short cur_l_bit, cur_r_bit;
	for (size_t i = 0; i <= MAX(this->size, r_num.size); i++){
		if (this->bits.test(i))
			cur_l_bit = 1;
		else
			cur_l_bit = 0;
		if (r_num.bits.test(i))
			cur_r_bit = 1;
		else
			cur_r_bit = 0;
		/*figure the sum of the current bit*/
		if ((cur_l_bit + cur_r_bit + carry) % 2)
			this->bits.set(i);
		else
			this->bits.reset(i);
		/*figure carry*/
		if (cur_l_bit + cur_r_bit + carry > 1)
			carry = 1;
		else
			carry = 0;
	}
	return *this;
}
BigInt&
BigInt::operator-=(const BigInt& r_num)
{
	bitset<MAX_BITS> reverse(r_num.bits);
	reverse.flip();
	unsigned short carry = 1;
	unsigned short cur_l_bit, cur_re_bit;
	for (size_t i = 0; i < MAX_BITS; i++){
		if (this->bits.test(i))
			cur_l_bit = 1;
		else
			cur_l_bit = 0;
		if (reverse.test(i))
			cur_re_bit = 1;
		else
			cur_re_bit = 0;
		/*figure the sum of the current bit*/
		if ((cur_l_bit + cur_re_bit + carry) % 2)
			this->bits.set(i);
		else
			this->bits.reset(i);
		/*figure carry*/
		if (cur_l_bit + cur_re_bit + carry > 1)
			carry = 1;
		else
			carry = 0;
	}
	return *this;
}
BigInt& 
BigInt::operator<<= (size_t offset)
{
	this->bits <<= offset;
	return *this;
}
BigInt&
BigInt::operator*=(const BigInt& r_num)
{
	BigInt l_num(*this);
	/*clear*/
	this->bits.reset();
	for (size_t i = 0; i < r_num.size; i++){
		if (r_num.bits.test(i)){
			BigInt tmp = l_num << i;
			(*this) += tmp;
		}
	}
	return *this;
}
BigInt operator+(const BigInt& l_num, const BigInt& r_num)
{
	BigInt ret(l_num);//local var
	ret += r_num; 
	return ret;//copy ret to return value
}
BigInt operator-(const BigInt& l_num, const BigInt& r_num)
{
	BigInt ret(l_num);
	ret -= r_num;
	return ret;
}
BigInt operator*(const BigInt& l_num, const BigInt& r_num)
{
	BigInt ret(l_num);
	ret *= r_num;
	return ret;
}
BigInt operator<<(BigInt& num, size_t offset)
{
	BigInt ret(num);
	ret <<= offset;
	return ret;
}
ostream& operator<<(ostream& out, const BigInt& num)
{
	out << num.bits;
	return out;
}
int main(int argc, char** argv)
{
	BigInt a1(2LL);
	BigInt a2("00000010");
	BigInt a3 = a1 * a2;
	cout << a3 << endl;
	system("pause");
	return 0;
}