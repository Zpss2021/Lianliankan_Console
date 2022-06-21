#include "Judge.h"

bool toJudge::Judge(int** a, int b[4], int size)/*�ж��Ƿ��ܹ�����*/
{
	if (a[b[0]][b[1]] == a[b[2]][b[3]] && !(b[0] == b[2] && b[1] == b[3]))		//logic:���غϵ�����ͬͼ��
	{
		if ((b[0] == b[2] && abs(b[3] - b[1]) == 1)
			|| (b[1] == b[3] && abs(b[0] - b[2]) == 1))			/*�������*/
			return true;
		if ((b[0] == b[2] && (b[0] == 1 || b[0] == size))
			|| (b[1] == b[3] && (b[1] == size || b[1] == 1)))	/*�����ڱ߽�*/		//hint:�߽�����Ϊ1��6������Ϊ1 2 3 4 5 6��
			return true;

		if (b[0] == b[2])          /*������ͬһ��*/
		{
			int n = b[3] > b[1] ? b[3] : b[1];
			int m = b[3] > b[1] ? b[1] : b[3];	//nΪ�������нϴ��ֵ��mΪ�����н�С�ġ�
			n--;
			while (n > m)	//�����������β鿴�����ڴ��У�����֮���Ƿ��Ϊ�ո�
				if (isEmpty(a[b[0]][n]))
					n--;
				else
					break;
			if (n == m)//�ڴ��У�����֮���Ϊ�ո�
				return true;
		}

		if (b[1] == b[3])        /*������ͬһ��*/
		{
			int n = b[2] > b[0] ? b[2] : b[0];
			int m = b[2] > b[0] ? b[0] : b[2]; //nΪ�������нϴ��ֵ��mΪ�����н�С�ġ�
			n--;
			while (n > m)	//�����������β鿴�����ڴ��У�����֮���Ƿ��Ϊ�ո�
				if (isEmpty(a[n][b[1]]))
					n--;
				else
					break;
			if (n == m)//�ڴ��У�����֮���Ϊ�ո�
				return true;
		}

		if (Two(a, b))			//�����ߵ����
			return true;

		//		if (1)//Ϊ����Ӿֲ�����f,w,e��������if(1),�ŵ㣺ʹ����f,e,w���ڵ�ʱ�価���̡ܶ�
		{						//�����ߵ����
			int f, w, e;
			bool c1[5] = { false }, c2[5] = { false }, c3[2] = { false };
			//���(b[0],b[1]),(b[2],b[3])�ϡ��¡����ҵ����
			c3[0] = Check(a, b[0], b[1], c1);
			c3[1] = Check(a, b[2], b[3], c2);
			if (c3[0] || c3[1])
				return false;	//������ֻҪ��һ�����ܾ���Ϊ�գ�����Ͳ�����ͨ����������������

			for (e = 0; e <= 3; e++)//�Ƚ��������ܵ����
			{
				int r[4];
				memset(r, 0, 4 * sizeof(int));
				memcpy(r, b, 4 * sizeof(int));
				//b�����е�ֵ���ɱ仯�������r�������b�����е�ֵ
				if (c1[e] == c2[e] && c1[e])
				{
					switch (e)
					{
					case 0://�����Ϸ����пո�
						  //���μ��(b[0],b[1])�Ϸ��ĵ��Ƿ�Ϊ�ո�ֱ���߽磩����Ϊ�ո�����õ���(b[2],b[3])
						  //�Ƿ���ͨ����������ͨ
						while (r[0] > 0)
						{
							r[0]--;
							if (!isEmpty(a[r[0]][r[1]]))//ֻҪ��Ϊ�ո����˵��������ͨ
								break;
							if (Two(a, r))
								return true;
						}
						break;
					case 1://�����·����пո�
						  //���μ��(b[0],b[1])�·��ĵ��Ƿ�Ϊ�ո�ֱ���߽磩����Ϊ�ո�����õ���(b[2],b[3])
						  //�Ƿ���ͨ����������ͨ
						while (r[0] < size + 1)			////<--------need to check
						{
							r[0]++;
							if (!isEmpty(a[r[0]][r[1]]))//ֻҪ��Ϊ�ո����˵��������ͨ
								break;
							if (Two(a, r))
								return true;
						}
						break;
					case 2:
						//������߾��пո�
						  //���μ��(b[0],b[1])��ߵĵ��Ƿ�Ϊ�ո�ֱ���߽磩����Ϊ�ո�����õ���(b[2],b[3])
						  //�Ƿ���ͨ����������ͨ
						while (r[1] > 0)
						{
							r[1]--;
							if (!isEmpty(a[r[0]][r[1]]))//ֻҪ��Ϊ�ո����˵��������ͨ
								break;
							if (Two(a, r))
								return true;
						}
						break;
					case 3:
						//�����ұ߾��пո�
						  //���μ��(b[0],b[1])�ұߵĵ��Ƿ�Ϊ�ո�ֱ���߽磩����Ϊ�ո�����õ���(b[2],b[3])
						  //�Ƿ���ͨ����������ͨ
						while (r[1] < size + 2)	////<--------need to check
						{
							r[1] ++;
							if (!isEmpty(a[r[0]][r[1]]))//ֻҪ��Ϊ�ո����˵��������ͨ
								break;
							if (Two(a, r))
								return true;
						}
						break;
					}
				}
			}

			f = b[2] - b[0];//f>0��ʾ(b[2],b[3])��(b[0],b[1])�·���f<0��ʾ(b[2],b[3])��(b[0],b[1])�Ϸ�

			w = b[3] - b[1];//w>0��ʾ(b[2],b[3])��(b[0],b[1])�ҷ���w<0��ʾ(b[2],b[3])��(b[0],b[1])��


			if (f > 0 && w > 0)                        /*(b[2],b[3])��(b[0],b[1])����*/
			{
				if (c2[0] && c1[1]) //(b[2],b[3])���Ϸ�Ϊ�ո�(b[0],b[1])���·�Ϊ�ո�
					if (UpDown(a, b, 1))
						return true;
				if (c2[2] && c1[3])//(b[2],b[3])�����Ϊ�ո�(b[0],b[1])���ұ�Ϊ�ո�
					if (LeftRight(a, b, 1))
						return true;
			}
			if (f < 0 && w>0)                       /*(b[2],b[3])��(b[0],b[1])����*/
			{
				if (c2[1] && c1[0])   //(b[2],b[3])���·�Ϊ�ո�(b[0],b[1])���Ϸ�Ϊ�ո�
					if (UpDown(a, b, 0))
						return true;
				if (c2[2] && c1[3])//(b[2],b[3])�����Ϊ�ո�(b[0],b[1])���ұ�Ϊ�ո�
					if (LeftRight(a, b, 1))
						return true;
			}
			if (f > 0 && w < 0)                     /*(b[2],b[3])��(b[0],b[1])����*/
			{
				if (c2[0] && c1[1])//(b[2],b[3])���Ϸ�Ϊ�ո�(b[0],b[1])���·�Ϊ�ո�
					if (UpDown(a, b, 1))
						return true;
				if (c2[3] && c1[2])//(b[2],b[3])���ұ�Ϊ�ո�(b[0],b[1])�����Ϊ�ո�
					if (LeftRight(a, b, 0))
						return true;
			}
			if (f < 0 && w < 0)                    /*(b[2],b[3])��(b[0],b[1])����*/
			{
				if (c2[1] && c1[0]) //(b[2],b[3])���·�Ϊ�ո�(b[0],b[1])���Ϸ�Ϊ�ո�
				{
					if (UpDown(a, b, 0))
						return true;
				}
				if (c2[3] && c1[2])//(b[2],b[3])���ұ�Ϊ�ո�(b[0],b[1])�����Ϊ�ո�
				{
					if (LeftRight(a, b, 0))
						return true;
				}
			}
		}
	}
	return false;
}

bool toJudge::Check(int** a, int x, int y, bool c[5])/*����ĳ���������ҵ����*/
{
	//false ��ʾ��Ϊ�ո�true ��ʾΪ�ո�
	//c[0],c[1],c[2],c[3]�ֱ��ʾĳ���������ҵ����
	c[0] = isEmpty(a[x - 1][y]);//(x,y)��һ��Ϊ��

	c[1] = isEmpty(a[x + 1][y]);//(x,y)��һ��Ϊ��

	c[2] = isEmpty(a[x][y - 1]);//(x,y)��һ��Ϊ��

	c[3] = isEmpty(a[x][y + 1]);//(x,y)��һ��Ϊ��

	c[4] = '\0';
	return !c[0] && !c[1] && !c[2] && !c[3];
}

bool toJudge::Two(int** a, int b[4]) /*������*/
{
	int m, n, c, d; //(c,d)Ϊ�ɶ����������

	n = b[2] - b[0];          /*�м��*/
	m = b[3] - b[1];         /*�м��*/
	d = b[2];
	c = b[3] - m;//b[1]
	while (c != b[3])// ��֤�Ƿ����ˮƽͨ��(b[2],b[3])��(b[2],b[1])��
	{
		if (isEmpty(a[d][c]))
			c += (m / abs(m));
		else
			break;
	}
	if (c == b[3])//����ˮƽͨ��
	{
		c = b[3] - m;
		while (d != b[0])//��֤�Ƿ������ֱͨ��(b[2],b[1])��(b[0],b[1])��
		{
			if (isEmpty(a[d][c]))
				d -= (n / abs(n));
			else
				break;
		}
		if (d == b[0])//������ֱͨ����
			return true;
	}
	c = b[3];
	d = b[2] - n;
	while (d != b[2])//��֤�Ƿ������ֱͨ��(b[2],b[3])��(b[0],b[3])��
	{
		if (isEmpty(a[d][c]))
			d += (n / abs(n));
		else
			break;
	}
	if (d == b[2])//������ֱͨ��
	{
		d = b[2] - n;
		while (c != b[1])// ��֤�Ƿ����ˮƽͨ��(b[0],b[3])��(b[0],b[1])��
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
	//g=1��ʾ(b[2],b[3])��(b[0],b[1])���·���g=0��ʾ(b[2],b[3])��(b[0],b[1])���Ϸ�
	if (g == 1)
	{
		//���μ��(b[2],b[3])�ϱߵĵ��Ƿ�Ϊ�ո�ֱ��(b[0],b[3])�·����ڵ㣩����Ϊ�ո�����õ���(b[0],b[1])
	   //�Ƿ���ͨ����������ͨ
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
		//���μ��(b[2],b[3])�±ߵĵ��Ƿ�Ϊ�ո�ֱ��(b[0],b[3])�Ϸ����ڵ㣩����Ϊ�ո�����õ���(b[0],b[1])
	   //�Ƿ���ͨ����������ͨ
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
	//g=1��ʾ(b[2],b[3])��(b[0],b[1])���ҷ���g=0��ʾ(b[2],b[3])��(b[0],b[1])����
	if (g == 1)
	{
		//���μ��(b[2],b[3])��ߵĵ��Ƿ�Ϊ�ո�ֱ��(b[2],b[1]�ұ߽��ڵĵ㣩����Ϊ�ո�����õ���(b[0],b[1])
		//�Ƿ���ͨ����������ͨ
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
		//���μ��(b[2],b[3])�ұߵĵ��Ƿ�Ϊ�ո�ֱ��(b[2],b[1]��߽��ڵĵ㣩����Ϊ�ո�����õ���(b[0],b[1])
		//�Ƿ���ͨ����������ͨ
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