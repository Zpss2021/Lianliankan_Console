#include "Judge.h"

bool toJudge::Judge(int** a, int b[4], int size)/*判断是否能够消除*/
{
	if (a[b[0]][b[1]] == a[b[2]][b[3]] && !(b[0] == b[2] && b[1] == b[3]))		//logic:不重合的两相同图标
	{
		if ((b[0] == b[2] && abs(b[3] - b[1]) == 1)
			|| (b[1] == b[3] && abs(b[0] - b[2]) == 1))			/*两点紧邻*/
			return true;
		if ((b[0] == b[2] && (b[0] == 1 || b[0] == size))
			|| (b[1] == b[3] && (b[1] == size || b[1] == 1)))	/*两点在边界*/		//hint:边界坐标为1和6（坐标为1 2 3 4 5 6）
			return true;

		if (b[0] == b[2])          /*两点在同一行*/
		{
			int n = b[3] > b[1] ? b[3] : b[1];
			int m = b[3] > b[1] ? b[1] : b[3];	//n为两个数中较大的值，m为两数中较小的。
			n--;
			while (n > m)	//从右往左依次查看，看在此行，两点之间是否均为空格
				if (isEmpty(a[b[0]][n]))
					n--;
				else
					break;
			if (n == m)//在此行，两点之间均为空格。
				return true;
		}

		if (b[1] == b[3])        /*两点在同一列*/
		{
			int n = b[2] > b[0] ? b[2] : b[0];
			int m = b[2] > b[0] ? b[0] : b[2]; //n为两个数中较大的值，m为两数中较小的。
			n--;
			while (n > m)	//从下往上依次查看，看在此列，两点之间是否均为空格
				if (isEmpty(a[n][b[1]]))
					n--;
				else
					break;
			if (n == m)//在此列，两点之间均为空格
				return true;
		}

		if (Two(a, b))			//两条线的情况
			return true;

		//		if (1)//为了添加局部变量f,w,e，所以用if(1),优点：使变量f,e,w存在的时间尽可能短。
		{						//三条线的情况
			int f, w, e;
			bool c1[5] = { false }, c2[5] = { false }, c3[2] = { false };
			//检查(b[0],b[1]),(b[2],b[3])上、下、左、右的情况
			c3[0] = Check(a, b[0], b[1], c1);
			c3[1] = Check(a, b[2], b[3], c2);
			if (c3[0] || c3[1])
				return false;	//两点中只要有一点四周均不为空，两点就不能连通，即：不可消除。

			for (e = 0; e <= 3; e++)//比较两点四周的情况
			{
				int r[4];
				memset(r, 0, 4 * sizeof(int));
				memcpy(r, b, 4 * sizeof(int));
				//b数组中的值不可变化，因此用r数组接收b数组中的值
				if (c1[e] == c2[e] && c1[e])
				{
					switch (e)
					{
					case 0://两点上方均有空格
						  //依次检查(b[0],b[1])上方的点是否为空格（直到边界），若为空格则检查该点与(b[2],b[3])
						  //是否能通过两条线连通
						while (r[0] > 0)
						{
							r[0]--;
							if (!isEmpty(a[r[0]][r[1]]))//只要不为空格就已说明不可连通
								break;
							if (Two(a, r))
								return true;
						}
						break;
					case 1://两点下方均有空格
						  //依次检查(b[0],b[1])下方的点是否为空格（直到边界），若为空格则检查该点与(b[2],b[3])
						  //是否能通过两条线连通
						while (r[0] < size + 1)			////<--------need to check
						{
							r[0]++;
							if (!isEmpty(a[r[0]][r[1]]))//只要不为空格就已说明不可连通
								break;
							if (Two(a, r))
								return true;
						}
						break;
					case 2:
						//两点左边均有空格
						  //依次检查(b[0],b[1])左边的点是否为空格（直到边界），若为空格则检查该点与(b[2],b[3])
						  //是否能通过两条线连通
						while (r[1] > 0)
						{
							r[1]--;
							if (!isEmpty(a[r[0]][r[1]]))//只要不为空格就已说明不可连通
								break;
							if (Two(a, r))
								return true;
						}
						break;
					case 3:
						//两点右边均有空格
						  //依次检查(b[0],b[1])右边的点是否为空格（直到边界），若为空格则检查该点与(b[2],b[3])
						  //是否能通过两条线连通
						while (r[1] < size + 2)	////<--------need to check
						{
							r[1] ++;
							if (!isEmpty(a[r[0]][r[1]]))//只要不为空格就已说明不可连通
								break;
							if (Two(a, r))
								return true;
						}
						break;
					}
				}
			}

			f = b[2] - b[0];//f>0表示(b[2],b[3])在(b[0],b[1])下方，f<0表示(b[2],b[3])在(b[0],b[1])上方

			w = b[3] - b[1];//w>0表示(b[2],b[3])在(b[0],b[1])右方，w<0表示(b[2],b[3])在(b[0],b[1])左方


			if (f > 0 && w > 0)                        /*(b[2],b[3])在(b[0],b[1])右下*/
			{
				if (c2[0] && c1[1]) //(b[2],b[3])的上方为空格，(b[0],b[1])的下方为空格
					if (UpDown(a, b, 1))
						return true;
				if (c2[2] && c1[3])//(b[2],b[3])的左边为空格，(b[0],b[1])的右边为空格
					if (LeftRight(a, b, 1))
						return true;
			}
			if (f < 0 && w>0)                       /*(b[2],b[3])在(b[0],b[1])右上*/
			{
				if (c2[1] && c1[0])   //(b[2],b[3])的下方为空格，(b[0],b[1])的上方为空格
					if (UpDown(a, b, 0))
						return true;
				if (c2[2] && c1[3])//(b[2],b[3])的左边为空格，(b[0],b[1])的右边为空格
					if (LeftRight(a, b, 1))
						return true;
			}
			if (f > 0 && w < 0)                     /*(b[2],b[3])在(b[0],b[1])左下*/
			{
				if (c2[0] && c1[1])//(b[2],b[3])的上方为空格，(b[0],b[1])的下方为空格
					if (UpDown(a, b, 1))
						return true;
				if (c2[3] && c1[2])//(b[2],b[3])的右边为空格，(b[0],b[1])的左边为空格
					if (LeftRight(a, b, 0))
						return true;
			}
			if (f < 0 && w < 0)                    /*(b[2],b[3])在(b[0],b[1])左上*/
			{
				if (c2[1] && c1[0]) //(b[2],b[3])的下方为空格，(b[0],b[1])的上方为空格
				{
					if (UpDown(a, b, 0))
						return true;
				}
				if (c2[3] && c1[2])//(b[2],b[3])的右边为空格，(b[0],b[1])的左边为空格
				{
					if (LeftRight(a, b, 0))
						return true;
				}
			}
		}
	}
	return false;
}

bool toJudge::Check(int** a, int x, int y, bool c[5])/*返回某点上下左右的情况*/
{
	//false 表示不为空格，true 表示为空格，
	//c[0],c[1],c[2],c[3]分别表示某点上下左右的情况
	c[0] = isEmpty(a[x - 1][y]);//(x,y)上一格为空

	c[1] = isEmpty(a[x + 1][y]);//(x,y)下一格为空

	c[2] = isEmpty(a[x][y - 1]);//(x,y)左一格为空

	c[3] = isEmpty(a[x][y + 1]);//(x,y)右一格为空

	c[4] = '\0';
	return !c[0] && !c[1] && !c[2] && !c[3];
}

bool toJudge::Two(int** a, int b[4]) /*两条线*/
{
	int m, n, c, d; //(c,d)为可动检验点坐标

	n = b[2] - b[0];          /*行间距*/
	m = b[3] - b[1];         /*列间距*/
	d = b[2];
	c = b[3] - m;//b[1]
	while (c != b[3])// 验证是否存在水平通道(b[2],b[3])到(b[2],b[1])。
	{
		if (isEmpty(a[d][c]))
			c += (m / abs(m));
		else
			break;
	}
	if (c == b[3])//存在水平通道
	{
		c = b[3] - m;
		while (d != b[0])//验证是否存在竖直通道(b[2],b[1])到(b[0],b[1])。
		{
			if (isEmpty(a[d][c]))
				d -= (n / abs(n));
			else
				break;
		}
		if (d == b[0])//存在竖直通道。
			return true;
	}
	c = b[3];
	d = b[2] - n;
	while (d != b[2])//验证是否存在竖直通道(b[2],b[3])到(b[0],b[3])。
	{
		if (isEmpty(a[d][c]))
			d += (n / abs(n));
		else
			break;
	}
	if (d == b[2])//存在竖直通道
	{
		d = b[2] - n;
		while (c != b[1])// 验证是否存在水平通道(b[0],b[3])到(b[0],b[1])。
		{
			if (isEmpty(a[d][c]))
				c -= (m / abs(m));
			else
				break;
		}
		if (c == b[1])
			return true;
	}
	return false;
}

bool toJudge::UpDown(int** a, int b[4], int g)
{
	int r[4], i = 0;
	memset(r, 0, 4 * sizeof(int));
	memcpy(r, b, 4 * sizeof(int));
	//g=1表示(b[2],b[3])在(b[0],b[1])的下方，g=0表示(b[2],b[3])在(b[0],b[1])的上方
	if (g == 1)
	{
		//依次检查(b[2],b[3])上边的点是否为空格（直到(b[0],b[3])下方紧邻点），若为空格则检查该点与(b[0],b[1])
	   //是否能通过两条线连通
		r[0]++;
		while (r[2] >= r[0])
		{
			r[2] -= 1;
			if (Two(a, r))
				return true;
		}
	}
	else
	{
		//依次检查(b[2],b[3])下边的点是否为空格（直到(b[0],b[3])上方紧邻点），若为空格则检查该点与(b[0],b[1])
	   //是否能通过两条线连通
		r[0]--;
		while (r[2] <= r[0])
		{
			r[2] += 1;
			if (Two(a, r))
				return true;
		}
	}
	return false;
}

bool toJudge::LeftRight(int** a, int b[4], int g)
{
	int r[4], i = 0;
	memset(r, 0, 4 * sizeof(int));
	memcpy(r, b, 4 * sizeof(int));
	//g=1表示(b[2],b[3])在(b[0],b[1])的右方，g=0表示(b[2],b[3])在(b[0],b[1])的左方
	if (g == 1)
	{
		//依次检查(b[2],b[3])左边的点是否为空格（直到(b[2],b[1]右边紧邻的点），若为空格则检查该点与(b[0],b[1])
		//是否能通过两条线连通
		r[1]++;
		while (r[3] >= r[1])
		{
			r[3]--;
			if (Two(a, r))
				return true;
		}
	}
	else
	{
		//依次检查(b[2],b[3])右边的点是否为空格（直到(b[2],b[1]左边紧邻的点），若为空格则检查该点与(b[0],b[1])
		//是否能通过两条线连通
		r[1]--;
		while (r[3] <= r[1])
		{
			r[3] ++;
			if (Two(a, r))
				return true;
		}
	}
	return false;
}

bool Judge(vector<vector<int>>& _Map, COORD _M, COORD _N) {
	int coords[4] = { _M.X + 1, _M.Y + 1, _N.X + 1, _N.Y + 1 },
		size = int(_Map.size() + 2), i, j;
	for (arr = new int* [size], i = 0; i < size; i++) {
		arr[i] = new int[size];
		for (j = 0; j < size; j++)
			arr[i][j] = -1;
	}
	for (i = 1; i < size - 1; i++)
		for (j = 1; j < size - 1; j++)
			arr[i][j] = _Map[size_t(j) - 1][size_t(i)- 1];

	//for (i = 0; i < size; i++) {
	//	for (j = 0; j < size; j++)
	//		cout << Map::toMark(arr[i][j], false);
	//	cout << endl;
	//}
	//	

	bool ret = toJudge::Judge(arr, coords, int(_Map.size()));
	for (i = 0; i < size; i++)
		delete[] arr[i];
	delete[] arr;
	return ret;
}