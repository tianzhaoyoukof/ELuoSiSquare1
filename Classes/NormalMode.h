#ifndef __NORMALMODE_H__
#define __NORMALMODE_H__

/*俄罗斯方块的经典模式，有三种模式：
  1.标准模式
  2.大块模式
  3.杂乱模式
 * 2015-12-2 创建
 */

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "NormalTile.h"
#include "NormalSquare.h"

USING_NS_CC;

class NormalMode : public Node
{
public :
	CREATE_FUNC(NormalMode);
	NormalMode();
	static Scene* createMode();
	bool init();
private:
	/**添加俄罗斯方块背景*/
	void addBackGround();

	/**上 按钮被按下*/
	void btnUPCallBack();
	/**下 按钮被按下*/
	void btnDOWNCallBack();
	/**左 按钮被按下*/
	void btnLEFTCallBack();
	/**右 按钮被按下*/
	void btnRIGHTCallBack();
	/**变化 按钮被按下*/
	void btnCHANGECallBack();

	/**更新函数*/
	void myUpdate(float tmd);
	/**刷新目前放快的位置*/
	void refreshSquarePos(int ox,int oy);

	/**检测碰撞*/
	bool isCollion();
private:
	/**左边的方块操作背景*/
	NormalTile* m_leftTile[20][10];
	/**右边的方块显示背景*/
	NormalTile* m_rightTile[8][6];
	/**目前正在掉落的块的信息*/
	NormalSquare m_square;
private:
	/*俄罗斯方块背景的基础坐标*/
	int m_baseX;
	int m_baseY;

	/**俄罗斯方块上次的位置*/
	int m_lastIndexX;
	int m_lastIndexY;

	/**上一个俄罗斯方块的位置*/
	std::vector<std::vector<bool>> m_lastPos;
	/**目前的俄罗斯方块的位置*/
	std::vector<std::vector<bool>> m_currPos;
};

#endif