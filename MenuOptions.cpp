#include "Menu.h"

options menus = {
	"ð��ģʽ",
	"�޾�ģʽ",
	"���а�",
	"����",
	"��Ϸ����",
	"�˳���Ϸ"
};

//options loads;

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
	"��R���ţ���Esc�˳�",
	"���߷ּ��ɡ�",
	"��ʱԽ�٣�����Խ��",
	"               ����by Zpss"
};

options setOptions = {
	"��Ϸ�Ѷȣ�",
	//	"��Ϸ��Ч",
	"�������˵�"
};

options* setOpCps;

options diffs = {
	"�򵥣� 6��ͼ��",
	"��ͨ�� 9��ͼ��",
	"���ѣ�12��ͼ��"
};

options pauses = {
	"��Ч��",
	"������Ϸ",
	"�浵",
	"�����沢�˳�"
};

Menu mainMenu(menus);
//Menu loadMenu(loads);
//Menu rankMenu(ranks);
Menu helpMenu(helps);
Menu diffMenu(diffs);
Menu pausMenu(pauses);