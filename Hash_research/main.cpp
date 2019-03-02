#include <iostream>
#include "Hash.h"

using namespace std;




//哈希表输出函数
void hashout(ChainHashTab H,int m)
{
	HLink p, q;
	for (int i = 0; i < m; i++)
	{
		p = H.rcd[i];

		while (p)
		{
			cout << i << "	" << p->data<<endl;
			p = p->next;
		}
	}
	cout << endl;
	cout << "输出结果:" << endl;
	cout << H.count << endl;
	cout << H.size << endl;
}

int main()
{
	ChainHashTab H;
	int m = NUM;

	HKeyType es[] = { 'J', 'B', 'U', 'C', 'N', 'E', 'L', 'N', 'Z', 'W', 'F', 'F', 'D' };

	BuildHashTab(H, 13, es);
	
	hashout(H, H.size);
	return 0;
}