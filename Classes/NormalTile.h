#ifndef __NORMALTILE_H__
#define __NORMALTILE_H__

/*俄罗斯方块的地图显示，有7种颜色
 * 2015-12-2 创建
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
	/**设置地图块不可见*/
	void setUNVisiable();
	/**设置地图块颜色和可见*/
	void setTileVisible(TileColor c);
	/**得到是否可见*/
	bool getTileVisible() const {return m_isVisible;}
private:
	/**初始化地图块*/
	void initTile();
private:
	/**俄罗斯方块地图块的颜色*/
	TileColor m_tileColor;
private:
	/**地图块是否被显示出来*/
	bool m_isVisible;

};

#endif