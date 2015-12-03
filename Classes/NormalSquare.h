#ifndef __NORMALSQUARE_H__
#define __NORMALSQUARE_H__

/*俄罗斯方块的方块，有17种方块，只负责计算
 * 2015-12-2 创建
 */

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "SquareKind.h"

USING_NS_CC;

class NormalSquare
{
public :
	NormalSquare(int ix = 1,int iy = 1,int kind = 1);
	/**重新生成新方块*/
	void newSquare(int ix,int iy,int kind);
	/**下降一格*/
	void downOne(std::vector<std::vector<bool>>& v);
	/**直接降落*/
	void fall();
	/**改变翻转*/
	void changeAngle();
	/**得到索引的位置*/
	int getIndexX() const {return m_indexX;}
	int getIndexY() const {return m_indexY;}
private:
	
private:
	/**目前的方块类型*/
	int m_squareKind;
	/**方块右下角的索引*/
	int m_indexX;
	int m_indexY;
	/**方块的方位*/
	int m_angle;
};

#endif