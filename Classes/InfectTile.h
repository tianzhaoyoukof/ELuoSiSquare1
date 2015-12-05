#ifndef __INFECTTILE_H__
#define __INFECTTILE_H__

/*��Ⱦģʽ�ľ�����ʾ����7����ɫ
 * 2015-12-5 ����
 */

#include "cocos2d.h"

USING_NS_CC;

enum InfectTileColor
{
	BLUE_infect = 0,
	GREEN_infect = 1,
	ORANGE_infect = 2,
	PURPLE_infect = 3,
	RED_infect = 4,
	YELLOW_infect = 5,
	BLACK_infect = 6
};

class InfectTile : public Sprite
{
public :
	CREATE_FUNC(InfectTile);
	InfectTile();
	static InfectTile* createTile(int c,int ix,int iy,int bX,int bY,int size);
	bool init();
	/**���õ�ͼ���Ƿ񱻼������*/
	void setInQueue(bool b) {m_isInQueue = b;}
	/**�õ���ͼ���Ƿ񱻼������*/
	bool getInQueue() const { return m_isInQueue;}

	/**�õ���ɫ*/
	InfectTileColor getTileColor() const {return m_tileColor;}
	/**������ɫ*/
	void setTileColor(InfectTileColor c);

	/**�����ӳټ�����*/
	void setDelayCount(int coun) {m_delayCount = coun;}

	/**�õ�����*/
	int getIndexX() const {return m_indexX;}
	int getIndexY() const {return m_indexY;}

private:
	/**��ʼ����*/
	void initTile();
private:
	/**����˹�����ͼ�����ɫ*/
	InfectTileColor m_tileColor;



private:
	/**��ͼ���Ƿ񱻼������*/
	bool m_isInQueue;

	/**�ӳټ�����*/
	int m_delayCount;

	/**����*/
	int m_indexX;
	int m_indexY;
};

#endif