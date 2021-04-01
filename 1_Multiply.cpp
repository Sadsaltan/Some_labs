

#include <iostream>
#include <bitset>
#include <intrin.h>

int main()
{
    std::cout << "Hello World!\n";
	int orig_m, orig_r;
	std::cout << "Please enter first number\n";
	std::cin >> orig_m;
	std::cout << "Please enter second number\n";
	std::cin >> orig_r;

	unsigned int x = 33 - __lzcnt(static_cast<unsigned>(orig_m));
	if (x == 33) x = 33 - __lzcnt(static_cast<unsigned>(-orig_m));
	std::cout << "First number lenth: " << x << "\n";
	unsigned int y = 33 - __lzcnt(static_cast<unsigned>(orig_r));
	if (y == 33) y = 33 - __lzcnt(static_cast<unsigned>(-orig_r));
	std::cout << "Second number lenth: " << y << "\n";

	int p_size = x + y + 1;
	std::bitset<65> A(static_cast<unsigned>(orig_m));
	A <<= y + 1;
	std::cout << "A: " << A.to_string().substr(65 - p_size)<< '\n';
	std::bitset<65> S(static_cast<unsigned>(-orig_m));
	S <<= y + 1;
	std::cout << "S: " << S.to_string().substr(65 - p_size) << '\n';
	std::bitset<65> P(static_cast<unsigned>(orig_r));
	P <<= 65 - y;
	P >>= 65 - (y + 1);
	std::cout << "P: " << P.to_string().substr(65 - p_size) << '\n';
	
	int i = 1; 
	while (i <= y)
	{
		std::cout << "Step: " << i << '\n';
		if (P[0] != P[1])
		{
			if (P.test(1))
			{
				// P = P + S
				std::cout << "Combination 10\n";
				std::cout << "	P: " << P.to_string().substr(65 - p_size) << "\n";
				std::cout << "	S: " << S.to_string().substr(65 - p_size) << '\n';
				unsigned long long P_conv = P.to_ullong();
				unsigned long long S_conv = S.to_ullong();
				P = std::bitset<65> (P_conv+ S_conv);
			}
			else
			{
				// P = P + A
				std::cout << "Combination 01\n";
				std::cout << "	P: " << P.to_string().substr(65 - p_size) << "\n";
				std::cout << "	A: " << A.to_string().substr(65 - p_size) << '\n';
				unsigned long long P_conv = P.to_ullong();
				unsigned long long A_conv = A.to_ullong();
				P = std::bitset<65> (P_conv + A_conv);
			}
			std::cout << "	P: " << P.to_string().substr(65 - p_size) << " (result)\n";
		}
		//здвиг
		P >>= 1;
		P[p_size - 1] = P[p_size - 2];
		std::cout << "	P(shifted): " << P.to_string().substr(65 - p_size) << '\n';
		i++;
	}
	std::cout << "\n\nResult in binary: " << P.to_string().substr(65 - p_size, p_size - 1) << '\n';
	if (p_size < 20)
	{
		int Result = 0;
		if (P.test(p_size - 1)) Result = (int)stoul(P.to_string().substr(65 - p_size, p_size - 1).insert(0, 33 - p_size, '1'), 0, 2);
		else Result = stoi(P.to_string().substr(65 - p_size, p_size - 1), 0, 2);
		std::cout << "Result in decimal: " << Result << '\n';
	}



	return 0;
}
