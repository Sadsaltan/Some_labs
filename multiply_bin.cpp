#include "multiply_bin.h"
#include <intrin.h>

std::bitset<48> Multiply_Mantissa(unsigned int orig_m, unsigned int orig_r)
{


	unsigned int x = 33 - __lzcnt(orig_m);

	unsigned int y = 33 - __lzcnt((orig_r));


	int p_size = x + y + 1;
	std::bitset<65> A(static_cast<unsigned>(orig_m));
	A <<= y + 1; 
	std::bitset<65> S(static_cast<unsigned>(-static_cast<int>(orig_m)));
	S <<= y + 1;
	std::bitset<65> P(static_cast<unsigned>(orig_r));
	P <<= 65 - y;
	P >>= 65 - (y + 1);

	int i = 1;
	while (i <= y)
	{
		if (P[0] != P[1])
		{
			if (P.test(1))
			{
				// P = P + S
				unsigned long long P_conv = P.to_ullong();
				unsigned long long S_conv = S.to_ullong();
				P = std::bitset<65>(P_conv + S_conv);
			}
			else
			{
				// P = P + A
				unsigned long long P_conv = P.to_ullong();
				unsigned long long A_conv = A.to_ullong();
				P = std::bitset<65>(P_conv + A_conv);
			}
		}
		//здвиг
		P >>= 1;
		P[p_size - 1] = P[p_size - 2];
		i++;
	}
	P <<=2;
	return std::bitset<48>(P.to_string().substr(65 - p_size, p_size - 1));

}