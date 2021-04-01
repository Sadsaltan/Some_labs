
#include <iostream>
#include <bitset>
#include <cstring>
#include "multiply_bin.h"

int main()
{
    std::cout << "Hello World!\n";
	union
	{
		float first_fpu;
		unsigned int first;
	};
	union
	{
		float second_fpu;
		unsigned int second;
	};
	union
	{
		float result_fpu;
		unsigned int result;
	};
	std::cin >> first_fpu;
	std::cout << "First float:    " << std::bitset<32>(first).to_string() << "\n";
	std::cin >> second_fpu;
	std::cout << "Second float:   " << std::bitset<32>(second).to_string() << "\n";
	result_fpu = first_fpu * second_fpu;
	unsigned int first_mantisa  = (first & 0x7FFFFF) + 0x800000;
	std::cout << "First mantissa: " << std::bitset<32>(first_mantisa).to_string().insert(9,1,'.') << "\n";
	unsigned int second_mantisa = (second & 0x7FFFFF) + 0x800000;
	std::cout << "Second mantiss: " << std::bitset<32>(second_mantisa).to_string().insert(9,1,'.') << "\n";
	unsigned int first_exp = (first & 0x7F800000) >> 23;
	std::cout << "Exp. of first:  " << std::bitset<32>(first_exp).to_string() << "\n";
	unsigned int second_exp = (second & 0x7F800000) >> 23;
	std::cout << "Exp. of second: " << std::bitset<32>(second_exp).to_string() << "\n";
	std::bitset<48> result_mantissa = Multiply_Mantissa(first_mantisa, second_mantisa);
	std::cout << "Mant. multiply: " << result_mantissa.to_string().insert(2, 1, '.') << "\n";
	bool exp_norm = 0;
	if (result_mantissa.test(47)) exp_norm = 1;
	std::cout << "Exp. addition: " << exp_norm << "\n";
	unsigned int result_exp = first_exp + second_exp - 127 + exp_norm;
	std::cout << "Exponent: " << result_exp << "\n";
	bool sign = (first & 0x80000000)^(second & 0x80000000);
	std::cout << "Sign: " << sign << "\n";
	std::cout << "\nResulting float: " << sign << ' ' << std::bitset<8>(result_exp).to_string() << ' ' << result_mantissa.to_string().substr(exp_norm ? 1 : 2, 23);
	std::cout << "\nReference float: " << std::bitset<32>(result).to_string().insert(1,1, ' ').insert(10,1, ' ') +"\n\n";
}
