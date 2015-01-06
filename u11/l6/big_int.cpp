#include "big_int.h"

bool operator==(const big_int &li, const big_int &ri)
{
	bool ret_val = false;

	if ((li.rep->is_positive == ri.rep->is_positive) &&
		(li.rep->last_rank == ri.rep->last_rank))
	{
		// int res = ::memcmp(li.rep->digits, ri.rep->digits,
		// 					sizeof(int) * li.rep->last_rank);
		// if (0 == res)
		// {
		// 	ret_val = true;
		// }
		int i = li.rep->last_rank;
		while ((i >= 0) && 
			   (li.rep->digits[i] == ri.rep->digits[i]))
		{
			--i;
		}
		if (i == 0)
		{
			ret_val = true;
		}
	}

	return ret_val;
}