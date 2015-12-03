#ifndef __NORMALTILE_H__
#define __NORMALTILE_H__

/*����˹����ĵ�ͼ��ʾ����7����ɫ
 * 2015-12-2 ����
 */

#include "cocos2d.h"

USING_NS_CC;

enum TileColor
{
	BLACK,
	BLUE,
	GREEN,
	ORANGE,
	PURPLE,
	RED
};

class NormalTile : public Sprite
{
public :
	CREATE_FUNC(NormalTile);
	static NormalTile* createTile(TileColor c,Vec2 p);
	bool init();
	/**���õ�ͼ�鲻�ɼ�*/
	void setUNVisiable();
	/**���õ�ͼ����ɫ�Ϳɼ�*/
	void setTileVisible(TileColor c);
	/**�õ��Ƿ�ɼ�*/
	bool getTileVisible() const {return m_isVisible;}
private:
	/**��ʼ����ͼ��*/
	void initTile();
private:
	/**����˹�����ͼ�����ɫ*/
	TileColor m_tileColor;
private:
	/**��ͼ���Ƿ���ʾ����*/
	bool m_isVisible;

};

#endif