#include <stdio.h>
#include <string.h>
int main(void)
{
	int t, i = 1, n, arr[100001] = { 0, }, len, front = 1, rear, rnum = 0, iferror = 0, num = 0;
	char ft[100002];
	scanf("%d", &t);
	while (t--)
	{
		rnum = 0; iferror = 0; front = 1, i = 1;
		scanf("%s", ft);
		len = strlen(ft);
		scanf("%d", &n);
		getchar();
		while (1)
		{
			int ch = getchar();
			if (ch == '[')
				continue;
			else if (0 <= ch - '0'&&ch - '0' <= 9)
				num = num * 10 + ch - '0';
			else if (ch == ',' || ch == ']')
			{
				arr[i] = num;
				num = 0;
				i++;
			}
			if (ch == ']')
				break;
		}
		rear = n;
		for (i = 0; i < len&&iferror != 1; i++)
		{
			switch (ft[i])
			{
			case'R':
				rnum++;
				break;
			case'D':
				if (rnum % 2 == 1)
				{
					rear--;
					if (rear + 1 < front)
					{
						printf("error\n");
						iferror = 1;
					}
					break;
				}
				else
				{
					front++;
					if (front > rear + 1)
					{
						printf("error\n");
						iferror = 1;
					}
					break;
				}
			}
		}
		if (iferror)
			continue;
		if (n == 0)
		{
			printf("[]\n");
			continue;
		}
		printf("[");
		if (rnum % 2 == 1)
		{
			for (i = rear; i >= front + 1; i--)
				printf("%d,", arr[i]);
			if (front <= rear)
				printf("%d", arr[front]);
		}
		else
		{
			for (i = front; i <= rear - 1; i++)
				printf("%d,", arr[i]);
			if (front <= rear)
				printf("%d", arr[rear]);
		}
		printf("]\n");
	}
	return 0;
}