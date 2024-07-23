//杭州电子科技大学-2200

#include<iostream>
using namespace std;
int main()
{
	int n;
	while (cin >> n)
	{
		int sum = 0;
		int TempSum = 1;
		int i = 1;
		for (i = 2; i <= n; i++)//抽取人数
		{
			TempSum = 1;//一定要记得重新初始化
			for (int j = 1; j <= i; j++)//计算C（n，i）
			{
				TempSum *= (n - j + 1) ;
				TempSum /= j;
			}
			sum += TempSum * (i - 1);
		}
		
		cout << sum << endl;
	}
}