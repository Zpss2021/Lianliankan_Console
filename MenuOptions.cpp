#include "Menu.h"

options menus = {
	"��ʼ��Ϸ",
	"������Ϸ",
	"���а�",
	"����",
	"��Ϸ����",
	"�˳���Ϸ"
};

options loads;
//ר�Ŷ���һ����������ݵĺ���
//	1."�浵1����",
//	2."�浵2����",
//	3."�浵3����",
//    ������
//	4."�������˵�"
//};

options ranks;
//	ר�Ŷ���һ����������ݵĺ���
// 1.xxx mmm��
//	2.yyy nnn��
//	3.zzz ddd��
//  ������
//	4."�������˵�"

options helps = {
	"����Ϸ����",
	"����ͬ����ͼ���������",
	"��������",
	"WASD�����ƹ�꣬�ո��ѡ��",
	"��Գɹ���ѡ�е���ͼ����ʧ",
	"��������",
	"��R���ţ���P��ͣ��Esc�˳�",
	"���߷ּ��ɡ�",
	"��ʱԽ�٣�����Խ��",
	"               ����by Zpss"
};

options setOptions = {
	"��Ϸ�Ѷȣ�",
	//	"����ģʽ",
	"�������˵�"
};

options* setOpCps;

options diffs = {
	"�򵥣� 6��ͼ��",
	"��ͨ�� 9��ͼ��",
	"���ѣ�12��ͼ��"
};

Menu mainMenu(menus);
//Menu loadMenu(loads);
//Menu rankMenu(ranks);
Menu helpMenu(helps);
Menu diffMenu(diffs);