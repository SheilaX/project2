#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<math.h>
#include<list>
#include<stdlib.h>//�����
#include<Windows.h>
#include<mmsystem.h>
#include"��ͷ.h"
using namespace std;
#pragma warning(default: 4996)//�����Ϣ�ı�������
#pragma comment(lib,"Winmm.lib")

#define _CRT_SECURE_NO_WARNINGS
#define	WIN_WIDTH  533 //������
#define WIN_HEIGHT 800 //������

//�����ӵ��ͷɻ�������
class Node
{
public:
	Node(int xx, int yy, int hitt)
	{
		x = xx;
		y = yy;
		hit = hitt;
		//enemy_kind = enemyy;
	}
	int x;
	int y;
	int hit;//�Ѿ����ܵĹ��������Ե��˶���
	//int enemy_kind;//���˵����� 0��ͨ��1boss1��2boss2�� 3boss3��99Ϊ��������Ҫ�����ж���
};

//boss��
class  Boss
{
public:
	Boss(int xx, int yy, int hitt, int enemyy)
	{
		x = xx;
		y = yy;
		hit = hitt;
		enemy_kind = enemyy;
	}
	int x;
	int y;
	int hit;//�Ѿ����ܵĹ��������Ե��˶���
	int enemy_kind;//���˵����� 1boss1��2boss2�� 3boss3��99Ϊ��������Ҫ�����ж���
};

class gift
{
public:
	gift(int xx, int yy, int texistt)
	{
		x = xx;
		y = yy;
		texist = texistt;
	}
	int x;
	int y;
	int texist;//��Ч����
};

Node myPlane(260, 700, 0);			//����λ�ó�ʼ��
list<gift> gift1;							//����1  ��Ҷɡ ��������
list<gift> gift2;							//����2  �����ӵ�
//gift gift3;							//����3
list<Boss> boss1_list;				//boss1�б�
list<Node> boss1_bullet_list;		//boss1�ӵ��б�node�࣬������Ҫ����
list<Boss> boss2_list;				//boss2�б�
list<Node> boss2_bullet_list;		//boss2�ӵ��б�
list<Node> boss2_bullet_list_left;
list<Node> boss2_bullet_list_right;
list<Boss> boss3_list;				//boss3�б�
list<Node> boss3_bullet_list1;		//boss3�ӵ��б�
list<Node> boss3_bullet_list2;
list<Node> boss3_bullet_list3;
list<Node> boss3_bullet_list4;
list<Node> boss3_bullet_list5;
list<Node> firecracker_list;		//�����ӵ��б�
list<Node> spider_list;				//֩���б�
list<Node> spider_web_list;			//֩�����б�

IMAGE im_bk, im_bk0, im_bk2, im_bk3, im_lose, im_win;		//����
IMAGE im_redpacket; //���
IMAGE im_me1, im_me2, im_me3, im_me4;//��ұ���
IMAGE im_firecracker;//�����ӵ�������

IMAGE im_spider, im_spider1, im_spider2, im_spider3, im_spider4, im_spider_web;//֩���֩��������ͨС��
//boss1���ӵ�
IMAGE im_boss1, im_boss1_bullet; 
//boss1��������
IMAGE im_boss1_down1, im_boss1_down2, im_boss1_down3, im_boss1_down4;
//boss2���ӵ�
IMAGE im_boss2, im_boss2_bullet, im_boss2_bullet_left30, im_boss2_bullet_right30;
//boss3���ӵ�
IMAGE im_boss3, im_boss3_bullet;
//����
IMAGE im_giftbox;
//�񵽵���֮��ı���
IMAGE im_gift1_me;//���߶�����Ҫ�Ա�����������޸�

int red_packet = 1;					//�������
int speed_bk = 1;					//�����ƶ��ٶ�
int dy = 0;							//��������ʱ��y�������
bool boss1_exist = 1;				//boss1��ʼ��Ϊ����
bool boss2_exist = 1;
bool boss3_exist = 1;
int boss1_die = 0;					//boss1��������
int spider_hit_to_death = 2;		//��ͨ����������������ӵ���
int get_score_whenkillaspider = 5; //ɱ����ͨ���˼ӷ���
int get_score_whenkillboss1;	   //ɱ��boss1�ӷ���
int roundN = 0;					   //�ؿ�����
int boss1_create_time;			   //boss1����ʱ��
int boss2_create_time;			   //boss2����ʱ��
int boss3_create_time;			   //boss3����ʱ��
int boss3Speed = 2;				   //boss3�ƶ��ٶ�
int sleeptime = 14;				   //ѭ�����ʱ��
int gift1_dis = 0;				   //����һʧЧʱ��
int gift2_dis = 0;				   //���߶�ʧЧʱ��
int mywidth, myheight;             //�ҵ�ͼ��ĳ��Ϳ�����߱仯
bool gift1_exist = 0, gift2_exist = 0;		   //�����������,��ʼΪ��
bool giftbox1 = 0, giftbox2 = 0;               //�����������,��ʼΪ��
DWORD tbossdie1, tbossdie2;			//boss1��������  ����Ϊȫ�ֱ���
DWORD tred1, tred2;					//������Ȼ�����ʱ
DWORD tfire1, tfire2;				//�ӵ����ɼ�ʱ����
DWORD tspider1, tspider2;			//֩������ʱ�����
DWORD tboss11, tboss12;				//boss1�ӵ���ʱ
DWORD tboss21, tboss22;				//boss2�ӵ���ʱ
DWORD tboss31, tboss32;				//boss3�ӵ���ʱ
DWORD tgift11, tgift12;			    //��һ������ʹ��ʱ��


//�����ƶ�����
void IsPressKey()
{
	MOUSEMSG m;
	while (MouseHit())
	{
		m = GetMouseMsg();
		if (gift1_exist)
		{
			mywidth = im_gift1_me.getwidth();
			myheight = im_gift1_me.getheight();
			if (m.uMsg == WM_MOUSEMOVE)
			{
				myPlane.x = m.x - im_gift1_me.getwidth() / 2;
				myPlane.y = m.y;
			}
			if (myPlane.x >= WIN_WIDTH - im_gift1_me.getwidth() / 2)
			{
				myPlane.x = WIN_WIDTH - im_gift1_me.getwidth() / 2;
			}
			if (myPlane.x <= 0)
			{
				myPlane.x = 0;
			}
			if (myPlane.y >= WIN_HEIGHT - im_gift1_me.getheight())
			{
				myPlane.y = WIN_HEIGHT - im_gift1_me.getheight();
			}
			if (myPlane.y <= 0)
			{
				myPlane.y = 0;
			}
		}
		else
		{
			mywidth = im_me1.getwidth();
			myheight = im_me1.getheight();
			if (m.uMsg == WM_MOUSEMOVE)
			{
				myPlane.x = m.x - im_me1.getwidth() / 2;
				myPlane.y = m.y;
			}
			if (myPlane.x >= WIN_WIDTH - im_me1.getwidth() / 2)
			{
				myPlane.x = WIN_WIDTH - im_me1.getwidth() / 2;
			}
			if (myPlane.x <= im_me1.getwidth() / 2)
			{
				myPlane.x = im_me1.getwidth() / 2;
			}
			if (myPlane.y >= WIN_HEIGHT - im_me1.getheight())
			{
				myPlane.y = WIN_HEIGHT - im_me1.getheight();
			}
			if (myPlane.y <= 0)
			{
				myPlane.y = 0;
			}
		}
	}
}

//����ͱ�����ײ
void box_me_collision()
{
	list<gift>::iterator pDj = gift1.begin();
	bool flag = false;
	while (pDj != gift1.end())
	{
		if ((*pDj).x >= myPlane.x - im_giftbox.getwidth() && (*pDj).x <= myPlane.x + mywidth &&
			(*pDj).y >= myPlane.y - im_giftbox.getheight() && (*pDj).y <= myPlane.y + myheight)
		{

			gift1.erase(pDj++);
			mciSendString(_T("close getbox"), NULL, 0, NULL);
			mciSendString(_T("open getbox.mp3 alias getbox"), NULL, 0, NULL);
			mciSendString(_T("play getbox"), NULL, 0, NULL);
			flag = false;
			gift1_exist = 1;
			//tgift12 = GetTickCount();
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}

	pDj = gift2.begin();
	flag = false;
	while (pDj != gift2.end())
	{
		if ((*pDj).x >= myPlane.x - im_giftbox.getwidth() && (*pDj).x <= myPlane.x + mywidth &&
			(*pDj).y >= myPlane.y - im_giftbox.getheight() && (*pDj).y <= myPlane.y + myheight)
		{

			gift2.erase(pDj++);
			mciSendString(_T("close getbox"), NULL, 0, NULL);
			mciSendString(_T("open getbox.mp3 alias getbox"), NULL, 0, NULL);
			mciSendString(_T("play getbox"), NULL, 0, NULL);
			flag = false;
			gift2_exist = 1;
			//tgift12 = GetTickCount();
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}
}

//��ͨ�����ӵ��ͱ�����ײ��redpacket--,֩������ʧ lose
void spider_web_and_me_collision()
{
	list<Node>::iterator pDj = spider_web_list.begin();
	bool flag = false;
	while (pDj!=spider_web_list.end())
	{
		if ((*pDj).x >= myPlane.x - im_spider_web.getwidth() && (*pDj).x <= myPlane.x + mywidth &&
			(*pDj).y >= myPlane.y - im_spider_web.getheight() && (*pDj).y <= myPlane.y + myheight)
		{
			
			spider_web_list.erase(pDj++);
			
			if (gift1_exist == 0)
			{
				red_packet--;
				mciSendString(_T("close losemusic"), NULL, 0, NULL);//lose score
			    mciSendString(_T("open lose.mp3 alias losemusic"), NULL, 0, NULL);
			    mciSendString(_T("play losemusic"), NULL, 0, NULL);
			}
			flag = false;
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}
}

//boss1�ӵ��ͱ�����ײ��� --lose
void boss1_bullet_and_me_collision()
{
	list<Node>::iterator pDj = boss1_bullet_list.begin();
	bool flag = false;
	while (pDj != boss1_bullet_list.end())
	{
		if ((*pDj).x >= myPlane.x - im_boss1_bullet.getwidth() + 2 && (*pDj).x <= myPlane.x + 45 &&
			(*pDj).y >= myPlane.y - im_boss1_bullet.getheight() + 2 && (*pDj).y <= myPlane.y + 45)
		{
			boss1_bullet_list.erase(pDj++);
			mciSendString(_T("close losemusic"), NULL, 0, NULL);
			mciSendString(_T("open lose.mp3 alias losemusic"), NULL, 0, NULL);
			mciSendString(_T("play losemusic"), NULL, 0, NULL);
			red_packet -= 5;
			flag = false;
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}
}

//֩��ͱ�����ײ��redpacket-- normal
void spider_and_me_collision()
{
	list<Node>::iterator spi = spider_list.begin();
	bool flag1 = false;
	while (spi!=spider_list.end())
	{
			if ((*spi).x >= myPlane.x - 32 && (*spi).x <= myPlane.x + 45 &&
				(*spi).y >= myPlane.y - 32 && (*spi).y <= myPlane.y + 45)//ײ����
			{
				spider_list.erase(spi++);
				
				if (gift1_exist == 0)
				{
					red_packet--;
					mciSendString(_T("close losemusic"), NULL, 0, NULL);
					mciSendString(_T("open lose.mp3 alias losemusic"), NULL, 0, NULL);
					mciSendString(_T("play losemusic"), NULL, 0, NULL);
				}
				flag1 = false;
				break;
			}
			else
			{
				++spi;
			}
		if (flag1)
		{
			break;
		}
	}
}

//boss1�ͱ����ӵ���ײ bossdie
void boss1_mybullet_collision()
{
		list<Boss>::iterator spi = boss1_list.begin();

		while (spi != boss1_list.end())//��������
		{
			bool flag = false;
			list<Node>::iterator firec = firecracker_list.begin();
			while (firec != firecracker_list.end())//����ˮ��
			{
				if ((*firec).x >= (*spi).x - im_firecracker.getwidth() + 2 && (*firec).x <= (*spi).x + im_boss1.getwidth() - 2 &&
					(*firec).y <= (*spi).y + im_boss1.getheight() + 2 && (*firec).y >= (*spi).y - im_firecracker.getheight() + 2)
				{
					firecracker_list.erase(firec++);
					(*spi).hit++;
					break;
				}
				else
				{
					++firec;
				}
			}// end firec
			if ((*spi).hit == 30)
			{
				red_packet += get_score_whenkillboss1;
				giftbox1 = 1;//��һ����������
				gift1.push_back(gift((*spi).x + im_boss1.getwidth() / 2 - im_giftbox.getwidth() / 2, (*spi).y, 0));//����gift1
				boss1_list.erase(spi);
				mciSendString(_T("close bossmusic"), NULL, 0, NULL);
				mciSendString(_T("open bossdie.mp3 alias bossmusic"), NULL, 0, NULL);
				mciSendString(_T("play bossmusic"), NULL, 0, NULL);
				flag = true;
			}
			if (flag)
			{
				break;
			}
			++spi;
	}
}

//��ͨ���˺ͱ����ӵ���ײ����֮��redpacket++,֩����ӵ�����ʧ normal
void spider_and_firecracker_collision()
{
	list<Node>::iterator spi = spider_list.begin();
	
	while (spi != spider_list.end())//��������
	{
		//if ((*spi).enemy_kind == 0)//��ͨ֩��
		//{
		bool flag = false;
		list<Node>::iterator firec = firecracker_list.begin();
		while (firec != firecracker_list.end())//����ˮ��
		{
			if ((*firec).x >= (*spi).x - im_firecracker.getwidth() + 2 && (*firec).x <= (*spi).x + 32 &&
				(*firec).y <= (*spi).y + im_spider.getheight() + 2 && (*firec).y >= (*spi).y - im_firecracker.getheight() + 2)
			{
				firecracker_list.erase(firec++);
				(*spi).hit++;
				break;
			}
			else
			{
				++firec;
			}
		}// end firec
		if ((*spi).hit >= spider_hit_to_death)
		{
			spider_list.erase(spi);
			mciSendString(_T("close nmusic"), NULL, 0, NULL);
			mciSendString(_T("open normal.mp3 alias nmusic"), NULL, 0, NULL);
			mciSendString(_T("play nmusic"), NULL, 0, NULL);
			red_packet += get_score_whenkillaspider;
			flag = true;
		}
		if (flag)
		{
			break;
		}
		++spi;
	}
}

//boss2�뱾���ӵ���ײ bossdie
void boss2_mybullet_collision()
{
	list<Boss>::iterator spi1 = boss2_list.begin();

	while (spi1 != boss2_list.end())//��������
	{
		bool flag = false;
		list<Node>::iterator firec = firecracker_list.begin();
		while (firec != firecracker_list.end())//����ˮ��
		{
			if ((*firec).x >= (*spi1).x - im_firecracker.getwidth() + 2 && (*firec).x <= (*spi1).x + im_boss2.getwidth() - 2 &&
				(*firec).y <= (*spi1).y + im_boss2.getheight() + 2 && (*firec).y >= (*spi1).y - im_firecracker.getheight() + 2)
			{
				firecracker_list.erase(firec++);
				(*spi1).hit++;
				break;
			}
			else
			{
				++firec;
			}
		}// end firec
		if ((*spi1).hit == 15)
		{
			red_packet += 10;
			giftbox2 = 1;//��2����������
			gift2.push_back(gift((*spi1).x + im_boss2.getwidth()/2 - im_giftbox.getwidth()/2, (*spi1).y, 0));//����gift2
			boss2_list.erase(spi1);
			mciSendString(_T("close bossmusic"), NULL, 0, NULL);
			mciSendString(_T("open bossdie.mp3 alias bossmusic"), NULL, 0, NULL);
			mciSendString(_T("play bossmusic"), NULL, 0, NULL);
			flag = true;
		}
		if (flag)
		{
			break;
		}
		++spi1;
	}
}

//boss2�ӵ�(�м�)�뱾����ײ lose
void boss2bullet_me_collision()
{
	list<Node>::iterator pDj = boss2_bullet_list.begin();
	bool flag = false;
	while (pDj != boss2_bullet_list.end())
	{
		if ((*pDj).x >= myPlane.x - im_boss1_bullet.getwidth() + 2 && (*pDj).x <= myPlane.x + 45 &&
			(*pDj).y >= myPlane.y - im_boss1_bullet.getheight() + 2 && (*pDj).y <= myPlane.y + 45)
		{
			boss2_bullet_list.erase(pDj++);
			
			if (gift1_exist == 0)
			{
				red_packet -= 5;
				mciSendString(_T("close losemusic"), NULL, 0, NULL);//lose score
				mciSendString(_T("open lose.mp3 alias losemusic"), NULL, 0, NULL);
				mciSendString(_T("play losemusic"), NULL, 0, NULL);
			}
			//red_packet -= 5;
			flag = false;
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}
}

//boss2�ӵ�(left)�뱾����ײ lose
void boss2bulletleft_me_collision()
{
	list<Node>::iterator pDj = boss2_bullet_list_left.begin();
	bool flag = false;
	while (pDj != boss2_bullet_list_left.end())
	{
		if ((*pDj).x >= myPlane.x - im_boss1_bullet.getwidth() + 2 && (*pDj).x <= myPlane.x + 45 &&
			(*pDj).y >= myPlane.y - im_boss1_bullet.getheight() + 2 && (*pDj).y <= myPlane.y + 45)
		{
			boss2_bullet_list_left.erase(pDj++);
			
			if (gift1_exist == 0)
			{
				red_packet -= 5;
				mciSendString(_T("close losemusic"), NULL, 0, NULL);//lose score
				mciSendString(_T("open lose.mp3 alias losemusic"), NULL, 0, NULL);
				mciSendString(_T("play losemusic"), NULL, 0, NULL);
			}
			
			flag = false;
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}
}

//boss2�ӵ�(right)�뱾����ײ lose
void boss2bulletright_me_collision()
{
	list<Node>::iterator pDj = boss2_bullet_list_right.begin();
	bool flag = false;
	while (pDj != boss2_bullet_list_right.end())
	{
		if ((*pDj).x >= myPlane.x - im_boss1_bullet.getwidth() + 2 && (*pDj).x <= myPlane.x + 45 &&
			(*pDj).y >= myPlane.y - im_boss1_bullet.getheight() + 2 && (*pDj).y <= myPlane.y + 45)
		{
			boss2_bullet_list_right.erase(pDj++);
			
			if (gift1_exist == 0)
			{
				red_packet -= 5;
				mciSendString(_T("close losemusic"), NULL, 0, NULL);//lose score
				mciSendString(_T("open lose.mp3 alias losemusic"), NULL, 0, NULL);
				mciSendString(_T("play losemusic"), NULL, 0, NULL);
			}
			flag = false;
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}
}

//boss3�ͱ����ӵ���ײ bossdie
void boss3_mybullet_collision()
{
	list<Boss>::iterator spi1 = boss3_list.begin();

	while (spi1 != boss3_list.end())//��������
	{
		bool flag = false;
		list<Node>::iterator firec = firecracker_list.begin();
		while (firec != firecracker_list.end())//����ˮ��
		{
			if ((*firec).x >= (*spi1).x - im_firecracker.getwidth() + 2 && (*firec).x <= (*spi1).x + im_boss3.getwidth() - 2 &&
				(*firec).y <= (*spi1).y + im_boss3.getheight() + 2 && (*firec).y >= (*spi1).y - im_firecracker.getheight() + 2)
			{
				firecracker_list.erase(firec++);
				(*spi1).hit++;
				break;
			}
			else
			{
				++firec;
			}
		}// end firec
		if ((*spi1).hit == 20)
		{
	    	red_packet += 10;
			boss3_list.erase(spi1);
			giftbox1 = 1;//���ɱ���
			mciSendString(_T("close bossmusic"), NULL, 0, NULL);
			mciSendString(_T("open bossdie.mp3 alias bossmusic"), NULL, 0, NULL);
			mciSendString(_T("play bossmusic"), NULL, 0, NULL);
			flag = true;
		}
		if (flag)
		{
			break;
		}
		++spi1;
	}
}

//boss3�ӵ��ͱ�����ײ1 lose
void boss3bullet1_me_collision()
{
	list<Node>::iterator pDj = boss3_bullet_list1.begin();
	bool flag = false;
	while (pDj != boss3_bullet_list1.end())
	{
		if ((*pDj).x >= myPlane.x - im_boss3_bullet.getwidth() + 2 && (*pDj).x <= myPlane.x + 45 &&
			(*pDj).y >= myPlane.y - im_boss3_bullet.getheight() + 2 && (*pDj).y <= myPlane.y + 45)
		{
			boss3_bullet_list1.erase(pDj++);
			
			if (gift1_exist == 0)
			{
				red_packet -= 1;
				mciSendString(_T("close losemusic"), NULL, 0, NULL);
				mciSendString(_T("open lose.mp3 alias losemusic"), NULL, 0, NULL);
				mciSendString(_T("play losemusic"), NULL, 0, NULL);
			}
			flag = false;
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}
}

//boss3�ӵ��ͱ�����ײ2 lose
void boss3bullet2_me_collision()
{
	list<Node>::iterator pDj = boss3_bullet_list2.begin();
	bool flag = false;
	while (pDj != boss3_bullet_list2.end())
	{
		if ((*pDj).x >= myPlane.x - im_boss3_bullet.getwidth() + 2 && (*pDj).x <= myPlane.x + 45 &&
			(*pDj).y >= myPlane.y - im_boss3_bullet.getheight() + 2 && (*pDj).y <= myPlane.y + 45)
		{
			boss3_bullet_list2.erase(pDj++);
			
			if (gift1_exist == 0)
			{
				red_packet -= 1;
				mciSendString(_T("close losemusic"), NULL, 0, NULL);
				mciSendString(_T("open lose.mp3 alias losemusic"), NULL, 0, NULL);
				mciSendString(_T("play losemusic"), NULL, 0, NULL);
			}
			flag = false;
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}
}

//boss3�ӵ��ͱ�����ײ3
void boss3bullet3_me_collision()
{
	list<Node>::iterator pDj = boss3_bullet_list3.begin();
	bool flag = false;
	while (pDj != boss3_bullet_list3.end())
	{
		if ((*pDj).x >= myPlane.x - im_boss3_bullet.getwidth() + 2 && (*pDj).x <= myPlane.x + 45 &&
			(*pDj).y >= myPlane.y - im_boss3_bullet.getheight() + 2 && (*pDj).y <= myPlane.y + 45)
		{
			boss3_bullet_list3.erase(pDj++);
			
			if (gift1_exist == 0)
			{
				red_packet -= 1;
				mciSendString(_T("close losemusic"), NULL, 0, NULL);
				mciSendString(_T("open lose.mp3 alias losemusic"), NULL, 0, NULL);
				mciSendString(_T("play losemusic"), NULL, 0, NULL);
			}
			flag = false;
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}
}

//boss3�ӵ��ͱ�����ײ4
void boss3bullet4_me_collision()
{
	list<Node>::iterator pDj = boss3_bullet_list4.begin();
	bool flag = false;
	while (pDj != boss3_bullet_list4.end())
	{
		if ((*pDj).x >= myPlane.x - im_boss3_bullet.getwidth() + 2 && (*pDj).x <= myPlane.x + 45 &&
			(*pDj).y >= myPlane.y - im_boss3_bullet.getheight() + 2 && (*pDj).y <= myPlane.y + 45)
		{
			boss3_bullet_list4.erase(pDj++);
			
			if (gift1_exist == 0)
			{
				red_packet -= 1;
				mciSendString(_T("close losemusic"), NULL, 0, NULL);
				mciSendString(_T("open lose.mp3 alias losemusic"), NULL, 0, NULL);
				mciSendString(_T("play losemusic"), NULL, 0, NULL);
			}
			flag = false;
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}
}

//boss3�ӵ��ͱ�����ײ5
void boss3bullet5_me_collision()
{
	list<Node>::iterator pDj = boss3_bullet_list5.begin();
	bool flag = false;
	while (pDj != boss3_bullet_list5.end())
	{
		if ((*pDj).x >= myPlane.x - im_boss3_bullet.getwidth() + 2 && (*pDj).x <= myPlane.x + 45 &&
			(*pDj).y >= myPlane.y - im_boss3_bullet.getheight() + 2 && (*pDj).y <= myPlane.y + 45)
		{
			boss3_bullet_list5.erase(pDj++);
			
			if (gift1_exist == 0)
			{
				red_packet -= 1;
				mciSendString(_T("close losemusic"), NULL, 0, NULL);
				mciSendString(_T("open lose.mp3 alias losemusic"), NULL, 0, NULL);
				mciSendString(_T("play losemusic"), NULL, 0, NULL);
			}
			flag = false;
			break;
		}
		else
		{
			++pDj;
		}
		if (flag) break;
	}
}

 // ����ɳ���Ļ���ӵ�
void free()
{
	list<Node>::iterator pDj = spider_web_list.begin();//��ʼ��֩����
	
	while (pDj != spider_web_list.end())
	{//֩����
		if ((*pDj).y >= WIN_HEIGHT /*|| (*pDj).y < 0*/)
		{
			spider_web_list.erase(pDj++);
		}
		else
			pDj++;
	}
	pDj = spider_list.begin();
	while (pDj != spider_list.end())
	{//֩��
		if ((*pDj).y >= WIN_HEIGHT /*|| (*pDj).y < 0*/)
		{
			spider_list.erase(pDj++);
		}
		else
			pDj++;
	}
	pDj = firecracker_list.begin();
	while (pDj != firecracker_list.end())
	{//����
		if (/*(*pDj).y > WIN_HEIGHT || */(*pDj).y < 0)
		{
			firecracker_list.erase(pDj++);
		}
		else
			pDj++;
	}

	pDj = boss2_bullet_list.begin();
	while (pDj != boss2_bullet_list.end())
	{//����
		if ((*pDj).y > WIN_HEIGHT || (*pDj).x < 0 || (*pDj).x > WIN_WIDTH)
		{
			boss2_bullet_list.erase(pDj++);
		}
		else
			pDj++;
	}

	pDj = boss2_bullet_list_left.begin();
	while (pDj != boss2_bullet_list_left.end())
	{//����
		if ((*pDj).y > WIN_HEIGHT || (*pDj).x < 0 || (*pDj).x > WIN_WIDTH)
		{
			boss2_bullet_list_left.erase(pDj++);
		}
		else
			pDj++;
	}

	pDj = boss2_bullet_list_right.begin();
	while (pDj != boss2_bullet_list_right.end())
	{//����
		if ((*pDj).y > WIN_HEIGHT || (*pDj).x < 0 || (*pDj).x > WIN_WIDTH)
		{
			boss2_bullet_list_right.erase(pDj++);
		}
		else
			pDj++;
	}
	//boss3�ӵ����
	pDj = boss3_bullet_list1.begin();
	while (pDj != boss3_bullet_list1.end())
	{//����
		if ((*pDj).y > WIN_HEIGHT || (*pDj).x < 0 || (*pDj).x > WIN_WIDTH)
		{
			boss3_bullet_list1.erase(pDj++);
		}
		else
			pDj++;
	}

	pDj = boss3_bullet_list2.begin();
	while (pDj != boss3_bullet_list2.end())
	{//����
		if ((*pDj).y > WIN_HEIGHT || (*pDj).x < 0 || (*pDj).x > WIN_WIDTH)
		{
			boss3_bullet_list2.erase(pDj++);
		}
		else
			pDj++;
	}

	pDj = boss3_bullet_list3.begin();
	while (pDj != boss3_bullet_list3.end())
	{//����
		if ((*pDj).y > WIN_HEIGHT || (*pDj).x < 0 || (*pDj).x > WIN_WIDTH)
		{
			boss3_bullet_list3.erase(pDj++);
		}
		else
			pDj++;
	}

	pDj = boss3_bullet_list4.begin();
	while (pDj != boss3_bullet_list4.end())
	{//����
		if ((*pDj).y > WIN_HEIGHT || (*pDj).x < 0 || (*pDj).x > WIN_WIDTH)
		{
			boss3_bullet_list4.erase(pDj++);
		}
		else
			pDj++;
	}

	pDj = boss3_bullet_list5.begin();
	while (pDj != boss3_bullet_list5.end())
	{//����
		if ((*pDj).y > WIN_HEIGHT || (*pDj).x < 0 || (*pDj).x > WIN_WIDTH)
		{
			boss3_bullet_list5.erase(pDj++);
		}
		else
			pDj++;
	}

}

//��ʼ������
void init()
{
	//����ͼ��
	loadimage(&im_bk, _T("bk.png"));					   //���� 533*800
	loadimage(&im_bk0, _T("bk0.png"));					   //��һ�ر���
	loadimage(&im_bk2, _T("bk2.png"));					   //�ڶ��ر���
	loadimage(&im_bk3, _T("bk3.png"));					   //�����ر���
	loadimage(&im_redpacket, _T("redpacket.png"));			//��� 38*47
	loadimage(&im_lose, _T("LOSE.png"));
	loadimage(&im_win, _T("WIN.png"));
	//��������
	loadimage(&im_me1, _T("smile_face.png"));				// 47*47
	//�����ӵ�
	loadimage(&im_firecracker, _T("firecracker.png"));		// 11*28
	//֩���֩��������ͨ��
	loadimage(&im_spider, _T("spider.png"));				// 34*34
	loadimage(&im_spider1, _T("spider1.png"));
	loadimage(&im_spider2, _T("spider2.png"));
	loadimage(&im_spider3, _T("spider3.png"));
	loadimage(&im_spider4, _T("spider4.png"));
	loadimage(&im_spider_web, _T("spider_web.png"));		// 20*20
	//boss1 + boss1_bullet
	loadimage(&im_boss1, _T("hat_man_boss1.png"));			// 66*70
	loadimage(&im_boss1_bullet, _T("hat_man_bullet.png"));	// 49*48
	//boss1 die
	loadimage(&im_boss1_down1, _T("white_flag_boss1_1"));	// 55*53
	loadimage(&im_boss1_down2, _T("white_flag_boss1_2"));
	loadimage(&im_boss1_down3, _T("white_flag_boss1_3"));
	loadimage(&im_boss1_down4, _T("white_flag_boss1_4"));
	//boss2 + boss2_bullet
	loadimage(&im_boss2, _T("lion_face_boss2.png"));			// 70*70
	loadimage(&im_boss2_bullet, _T("boss2_bullet.png"));	    // 26*31
	loadimage(&im_boss2_bullet_left30, _T("boss2_bullet_left30.png"));//25*28
	loadimage(&im_boss2_bullet_right30, _T("boss2_bullet_right30.png"));//25*28
	//boss3 + boss3_bullet
	loadimage(&im_boss3, _T("boss3.png"));						//70*70
	loadimage(&im_boss3_bullet, _T("boss3_bullet.png"));		//22*24
	//gift
	loadimage(&im_giftbox, _T("giftbox.png"));	
	//gift1_me
	loadimage(&im_gift1_me, _T("gift1_me.png"));

	tred1 = GetTickCount();
	tspider1 = GetTickCount();
	tfire1 = GetTickCount();
	tboss11 = GetTickCount();
	tbossdie1 = GetTickCount();
	tboss21 = GetTickCount();
	tgift11 = GetTickCount();
	//tboss11 = GetTickCount();
	
}

//���߼�����ͼ��
void create_roles()
{
	//���ɱ����ӵ�
	tfire2 = GetTickCount();
	if (tfire2 - tfire1 >= 300)
	{
		if (gift2_exist)
		{
			firecracker_list.push_back(Node(myPlane.x, myPlane.y - 28, 0));//�����ɵ��ӵ��ͱ���λ���й�
			firecracker_list.push_back(Node(myPlane.x + im_me1.getwidth() - im_firecracker.getwidth(), myPlane.y - 28, 0));//�����ɵ��ӵ��ͱ���λ���й�
		}
		else
		{
			firecracker_list.push_back(Node(myPlane.x + 18, myPlane.y - 28, 0));//�����ɵ��ӵ��ͱ���λ���й�
		}
		tfire1 = tfire2;
	}

	//�������֩�룬һ��һ��
	tspider2 = GetTickCount();
	if (tspider2 - tspider1 >= 1000)
	{
		spider_list.push_back(Node(rand() % (WIN_WIDTH - 34), 0, 0));//���֩��λ��
		list<Node>::iterator pDj = spider_list.begin();//����֩���ÿ��֩����1/3�ĸ��ʷ���֩����
		while (pDj != spider_list.end()) {
			if (rand() % 3 == 0) {
				spider_web_list.push_back(Node((*pDj).x + 8, (*pDj).y + 35, 0));
			}
			++pDj;
		}
		tspider1 = tspider2;
	}

	//����boss1
	if (red_packet >= boss1_create_time && boss1_exist)
	{
		boss1_list.push_back(Boss(300, 0, 0, 1));//boss1��ʼλ�ã�����Ϊ1
		boss1_exist = 0;
	}

	//����boss1�ӵ�
	list<Boss>::iterator pDj = boss1_list.begin();//��boss1�����ӵ�
	tboss12 = GetTickCount();
	if (tboss12 - tboss11 >= 5000)
	{
		while (pDj != boss1_list.end())
		{
			boss1_bullet_list.push_back(Node((*pDj).x + 8, (*pDj).y + 70, 0));
			tboss11 = tboss12;
			++pDj;
		}
	}
	

	//����boss2,ǰ�����ڵڶ��ػ������
	if (roundN == 2 || roundN == 3)
	{
		if (red_packet >= boss2_create_time && boss2_exist)
		{
			boss2_list.push_back(Boss(180, 0, 0, 2));//boss2��ʼλ�ã�����Ϊ2
			boss2_exist = 0;
		}
	}

	//����boss2�ӵ�,ǰ�����ڵڶ��ػ������
	if (roundN == 2 || roundN == 3)
	{
		list<Boss>::iterator b2 = boss2_list.begin();//��boss2�����ӵ�
		tboss22 = GetTickCount();
		if (tboss22 - tboss21 >= 1000)
		{
			while (b2 != boss2_list.end())
			{
				boss2_bullet_list.push_back(Node((*b2).x + 22, (*b2).y + 70, 0));
				boss2_bullet_list_left.push_back(Node((*b2).x - 35, (*b2).y + 70, 0));
				boss2_bullet_list_right.push_back(Node((*b2).x + 95, (*b2).y + 70, 0));
				tboss21 = tboss22;
				++b2;
			}
		}
	}

	//����boss3,ǰ�����ڵ�����
	if (roundN == 3)
	{
		if (red_packet >= boss3_create_time && boss3_exist)
		{
			boss3_list.push_back(Boss(276, 0, 0, 2));//boss2��ʼλ�ã�����Ϊ2
			boss3_exist = 0;
		}
	}

	//����boss3�ӵ�,ǰ�����ڵ�����
	if (roundN == 3)
	{
		list<Boss>::iterator b3 = boss3_list.begin();//��boss2�����ӵ�
		tboss32 = GetTickCount();
		if (tboss32 - tboss31 >= 900)
		{
			while (b3 != boss3_list.end())
			{
				boss3_bullet_list1.push_back(Node((*b3).x - 68,  (*b3).y + 70, 0));
				boss3_bullet_list2.push_back(Node((*b3).x - 22,  (*b3).y + 70, 0));
				boss3_bullet_list3.push_back(Node((*b3).x + 24,  (*b3).y + 70, 0));
				boss3_bullet_list4.push_back(Node((*b3).x + 70,  (*b3).y + 70, 0));
				boss3_bullet_list5.push_back(Node((*b3).x + 116, (*b3).y + 70, 0));
				tboss31 = tboss32;
				++b3;
			}
		}
	}

}//end creat_roles

//��ͼ
void draw_roles()
{
	if (red_packet >=  85)
	{
		gift1_exist = 0;
	}

	//������
	IsPressKey();
	if (gift1_exist)
	{
		putimagePng(myPlane.x, myPlane.y, &im_gift1_me);
		//tgift11 = tgift12;
	}
	else
	{
		putimagePng(myPlane.x, myPlane.y, &im_me1);
		//gift1_exist = 0;
	}
	

	//�������ӵ�
	for (auto &p : firecracker_list)
	{
		putimagePng(p.x, p.y, &im_firecracker);
		p.y -= speed_bk + 1;
	}
	//��ײ���
	spider_and_me_collision();//���˺ͱ���
	spider_and_firecracker_collision();//���˺ͱ����ӵ�
	boss1_bullet_and_me_collision();//boss1�ӵ�����
	spider_web_and_me_collision();//�����͵����ӵ�
	boss1_mybullet_collision();//boss1���ҵ��ӵ���ײ
	boss2_mybullet_collision();//boss2���ҵ��ӵ���ײ
	boss2bullet_me_collision();//boss2�ӵ�������ײ
	boss2bulletleft_me_collision();
	boss2bulletright_me_collision();
	boss3_mybullet_collision();
	boss3bullet1_me_collision();
	boss3bullet2_me_collision();
	boss3bullet3_me_collision();
	boss3bullet4_me_collision();
	boss3bullet5_me_collision();
	box_me_collision();
	//����ͨ����
	for (auto &p : spider_list)
	{
			if (p.hit == 0)
				putimagePng(p.x, p.y, &im_spider);
			if (p.hit == 1)
				putimagePng(p.x, p.y, &im_spider1);
			if (p.hit == 2)
				putimagePng(p.x, p.y, &im_spider2);
			if (p.hit == 3)
				putimagePng(p.x, p.y, &im_spider3);
			if (p.hit == 4)
				putimagePng(p.x, p.y, &im_spider4);
		
			p.y += 2;
	}//end for

	//��boss1
	for (auto &p : boss1_list)
	{
		if (p.hit == 29)//��������
		{
			
				if (boss1_die == 0)
				{
					putimagePng(p.x, p.y, &im_boss1);
					boss1_die = 1;
					continue;
				}
				else if (boss1_die == 1)
				{
					putimagePng(p.x, p.y, &im_boss1_down1);
					boss1_die = 2;
					continue;
				}
				else if (boss1_die == 2)
				{
					putimagePng(p.x, p.y, &im_boss1_down2);
					boss1_die = 3;
					continue;
				}
				else if (boss1_die == 3)
				{
					putimagePng(p.x, p.y, &im_boss1_down3);
					boss1_die = 4;
					continue;
				}
				else if (boss1_die == 4)
				{
					putimagePng(p.x, p.y, &im_boss1_down4);
					boss1_die = 5;
				}
			
		}
		else if (p.hit < 30 /*&& red_packet >= 10*/)//������
		{
			putimagePng(p.x, p.y, &im_boss1);
		}
		//p.y += 2; boss1����
	}
	//������
	if (giftbox1)
	{
		for (auto& p : gift1)
		{
			putimagePng(p.x, p.y, &im_giftbox);
			p.y += 3;
		}
	}

	//��boss2
	for (auto &p : boss2_list)
	{
		putimagePng(p.x, p.y, &im_boss2);
	}

	if (giftbox2)
	{
		for (auto& p : gift2)
		{
			putimagePng(p.x, p.y, &im_giftbox);
			p.y += 3;
		}
	}

	//��boss3
	for (auto &p : boss3_list)
	{
		putimagePng(p.x, p.y, &im_boss3);
		if (p.x >= WIN_WIDTH - im_boss3.getwidth())
		{
			p.x = WIN_WIDTH - im_boss3.getwidth();
			boss3Speed = -boss3Speed;
		}
		if (p.x <= 180)
		{
			p.x = 180;
			boss3Speed = -boss3Speed;
		}
		p.x += boss3Speed + 1;//������
	}

	//��֩����
	for (auto &p : spider_web_list)
	{
		putimagePng(p.x, p.y, &im_spider_web);
		p.y += 3;
	}

	//��boss1�ӵ�,boss1�ӵ�ֻ������boss1���ŵ�ʱ��
	list<Boss>::iterator bo = boss1_list.begin();
	while (bo!=boss1_list.end())
	{
		if ((*bo).hit < 21)
		{
			for (auto &p : boss1_bullet_list)
			{
				putimagePng(p.x, p.y, &im_boss1_bullet);
				//boss1���ӵ���׷�ٵ�
				if (myPlane.x >= p.x)
					p.x += 1;
				if (myPlane.x < p.x)
					p.x -= 1;
				if (myPlane.y >= p.y)
					p.y += 1;
				if (myPlane.y < p.y)
					p.y -= 1;
			}
		}
		++bo;
	}

	//��boss2�ӵ�
	list<Boss>::iterator bo11 = boss2_list.begin();
	while (bo11 != boss2_list.end())
	{
		if ((*bo11).hit < 21)
		{
			for (auto &p1 : boss2_bullet_list_left)
			{
				putimagePng(p1.x, p1.y, &im_boss2_bullet_left30);
				p1.x -= 3;
				p1.y += 3;
			}
			for (auto &p2 : boss2_bullet_list_right)
			{
				putimagePng(p2.x, p2.y, &im_boss2_bullet_right30);
				p2.x += 3;
				p2.y += 3;
			}
			for (auto &p : boss2_bullet_list)
			{
				putimagePng(p.x, p.y, &im_boss2_bullet);
				p.y += 3;
			}
		}
		++bo11;
	}

	//��boss3�ӵ�1
	list<Boss>::iterator bo3 = boss3_list.begin();
	while (bo3 != boss3_list.end())
	{
		if ((*bo3).hit < 21)
		{
			for (auto &p : boss3_bullet_list1)
			{
				putimagePng(p.x, p.y, &im_boss3_bullet);
				p.x -= 3;
				p.y += 3;
			}
			for (auto &p1 : boss3_bullet_list2)
			{
				putimagePng(p1.x, p1.y, &im_boss3_bullet);
				p1.x -= 2;
				p1.y += 3;
			}
			for (auto &p2 : boss3_bullet_list3)
			{
				putimagePng(p2.x, p2.y, &im_boss3_bullet);
				//p2.x += 3;
				p2.y += 3;
			}
			for (auto &p3 : boss3_bullet_list4)
			{
				putimagePng(p3.x, p3.y, &im_boss3_bullet);
				p3.x += 2;
				p3.y += 3;
			}
			for (auto &p4 : boss3_bullet_list5)
			{
				putimagePng(p4.x, p4.y, &im_boss3_bullet);
				p4.x += 3;
				p4.y += 3;
			}
		}
		++bo3;
	}

	
	//�����������
	setlinecolor(WHITE);
	rectangle(41, 15, 142, 35);
	setfillcolor(WHITE);
	fillrectangle(42, 16, 42 + red_packet, 34);

	//д������Ȱٷֱ�
	TCHAR s[20];
	settextstyle(28, 0, _T("Arial"));
	_stprintf_s(s, _T("%d"), red_packet);
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	outtextxy(150, 11, s);

	//��������־
	if (red_packet <= 0)
	{
		putimagePng(WIN_WIDTH / 2 - im_lose.getwidth() / 2, WIN_HEIGHT / 2 - im_lose.getheight() / 2, &im_lose);
		/*TCHAR s[20];
		settextstyle(100, 0, _T("Arial"));
		_stprintf_s(s, _T("ʧ�ܣ�"));
		settextcolor(RGB(0, 0, 0));
		setbkmode(TRANSPARENT);
		outtextxy(250, 300, s);*/
		//break;
	}
	if (red_packet >= 100)
	{
		/*TCHAR s[20];
		settextstyle(100, 0, _T("Arial"));
		_stprintf_s(s, _T("�ɹ���"));
		settextcolor(RGB(0, 0, 0));
		setbkmode(TRANSPARENT);
		outtextxy(250, 300, s);*/
		putimagePng(WIN_WIDTH / 2 - im_win.getwidth() / 2, WIN_HEIGHT / 2 - im_win.getheight() / 2, &im_win);
		//break;
	}
}

void round1()
{
	//Sleep(2000);
	//init();
	mciSendString(_T("close r1music"), NULL, 0, NULL);
	mciSendString(_T("open R1.mp3 alias r1music"), NULL, 0, NULL);
	//�򿪱�������
	mciSendString(_T("play r1music repeat"), NULL, 0, NULL);
	// ѭ������
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	Sleep(2000);

	srand((unsigned int)time(NULL));//�������

	BeginBatchDraw();
	while (1)
	{
		
		cleardevice();
		
		//������ͼ
		putimage(0, 0, 600, dy, &im_bk, 0, WIN_HEIGHT - dy, SRCCOPY);
		putimage(0, dy, 600, WIN_HEIGHT - dy, &im_bk, 0, 0, SRCCOPY);
		dy += speed_bk;
		if (dy >= WIN_HEIGHT) dy = speed_bk;
		putimagePng(2, 2, &im_redpacket);//���
		create_roles();//���ɸ�����ɫ
		draw_roles();//����������ɫ
		
		FlushBatchDraw();
		if (red_packet <= 0 || red_packet >= 100)
		{
			break;
		}
		Sleep(sleeptime);
		free();
	}
	mciSendString(_T("close r1music"), NULL, 0, NULL);

	getchar();
	//return 0;
}

void round2()
{
	//Sleep(2000);
	mciSendString(_T("close r1music"), NULL, 0, NULL);
	mciSendString(_T("open R2.mp3 alias r2music"), NULL, 0, NULL);
	//�򿪱�������
	mciSendString(_T("play r2music repeat"), NULL, 0, NULL);
	// ѭ������
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	Sleep(2000);
	srand((unsigned int)time(NULL));//�������

	BeginBatchDraw();
	while (1)
	{

		cleardevice();

		//������ͼ
		putimage(0, 0, 600, dy, &im_bk2, 0, WIN_HEIGHT - dy, SRCCOPY);
		putimage(0, dy, 600, WIN_HEIGHT - dy, &im_bk2, 0, 0, SRCCOPY);
		dy += speed_bk;
		if (dy >= WIN_HEIGHT) dy = speed_bk;
		putimagePng(2, 2, &im_redpacket);//���
		create_roles();//���ɸ�����ɫ
		draw_roles();//����������ɫ

		FlushBatchDraw();
		if (red_packet <= 0 || red_packet >= 100)
		{
			break;
		}
		Sleep(sleeptime);
		free();
	}
	mciSendString(_T("close r2music"), NULL, 0, NULL);

	getchar();
}

void round3()
{
	//Sleep(2000);
	mciSendString(_T("close r1music"), NULL, 0, NULL);
	mciSendString(_T("close r2music"), NULL, 0, NULL);
	mciSendString(_T("open R3.mp3 alias r3music"), NULL, 0, NULL);
	//�򿪱�������
	mciSendString(_T("play r3music repeat"), NULL, 0, NULL);
	// ѭ������
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	Sleep(2000);
	srand((unsigned int)time(NULL));//�������

	BeginBatchDraw();
	while (1)
	{

		cleardevice();

		//������ͼ
		putimage(0, 0, 600, dy, &im_bk3, 0, WIN_HEIGHT - dy, SRCCOPY);
		putimage(0, dy, 600, WIN_HEIGHT - dy, &im_bk3, 0, 0, SRCCOPY);
		dy += speed_bk;
		if (dy >= WIN_HEIGHT) dy = speed_bk;
		putimagePng(2, 2, &im_redpacket);//���
		create_roles();//���ɸ�����ɫ
		draw_roles();//����������ɫ

		FlushBatchDraw();
		if (red_packet <= 0 || red_packet >= 100)
		{
			break;
		}
		Sleep(sleeptime);
		free();
	}
	mciSendString(_T("close r3music"), NULL, 0, NULL);
	getchar();
}

ExMessage mess;
int main()
{
	init();
	initgraph(WIN_WIDTH, WIN_HEIGHT, SHOWCONSOLE);
	loadimage(&im_bk0, _T("bk1.png"));

	while (1)
	{
		mess = getmessage(EM_MOUSE);
		putimagePng(0, 0, &im_bk0);
		
			if (GetAsyncKeyState(VK_LBUTTON))
			{
				if (mess.x > 156 && mess.x < 360)
				{
					if (mess.y > 307 && mess.y < 364)
					{//��һ��
						roundN = 1;
						spider_hit_to_death = 2;
						get_score_whenkillaspider = 4;
						boss1_create_time = 40;
						get_score_whenkillboss1 = 10;
						gift1_dis = 90;
						round1();
						//continue;
					}

					else if (mess.y > 459 && mess.y < 516)
					{//�ڶ���
						roundN = 2;
						spider_hit_to_death = 3;
						get_score_whenkillaspider = 3;
						get_score_whenkillboss1 = 8;
						boss1_create_time = 30;
						boss2_create_time = 70;
						gift1_dis = 80;
						gift2_dis = 99;
						round2();
						
					}
					else if (mess.y > 611 && mess.y < 668)
					{//������
						roundN = 3;
						spider_hit_to_death = 5;
						get_score_whenkillaspider = 3;
						boss1_create_time = 20;
						boss2_create_time = 50;
						boss3_create_time = 75;
						gift1_dis = 60;
						gift2_dis = 89;
						round3();
						
					}
				}
			}
		
		
	}
	return 0;
}