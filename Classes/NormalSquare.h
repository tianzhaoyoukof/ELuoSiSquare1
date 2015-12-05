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
	/**向左移动*/
	void leftOne(std::vector<std::vector<bool>>& v);
	/**向右移动*/
	void rightOne(std::vector<std::vector<bool>>& v);
	/**直接降落*/
	void fall();
	/**改变翻转*/
	void changeAngle(std::vector<std::vector<bool>>& v);
	void changeAngle(std::vector<std::vector<bool>>& v,std::vector<std::vector<bool>>& v1);
	/**得到索引的位置*/
	int getIndexX() const {return m_indexX;}
	int getIndexY() const {return m_indexY;}
	/**得到种类*/
	int getSquareKind() const {return m_squareKind;}

	/**是否已经到底了*/
	bool isTouchBottom();

	/**展示预览的窗口*/
	void showPreView(std::vector<std::vector<bool>>& v);
private:
	/**各种方块及角度的操作*/
	void allSquareKindChange(bool b[8][6],int & I,int& J,int kind);
	/**方块是否能翻转*/
	bool canFlipSquare(std::vector<std::vector<bool>>& t);
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