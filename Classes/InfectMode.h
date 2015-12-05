#ifndef __INFECTMODE_H__
#define __INFECTMODE_H__

/*俄罗斯方块的侵染模式，有六种颜色
 * 2015-12-5 创建
 */

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "InfectTile.h"

USING_NS_CC;

class InfectMode : public Node
{
public :
	CREATE_FUNC(InfectMode);
	InfectMode();
	static Scene* createMode();
	bool init();
private:
	/**添加选择关卡的界面*/
	void addSelectMenu();
	/**添加俄罗斯方块场景*/
	void addScene();
	/**添加方块*/
	void addTile();

	/**六个颜色按钮的回调函数*/
	void btnBLUECallBack();
	void btnGREENCallBack();
	void btnORANGECallBack();
	void btnPURPLECallBack();
	void btnREDCallBack();
	void btnYELLOWCallBack();

	/**检测更新*/
	void checkTouch(InfectTileColor c);

	/**检测游戏结束*/
	bool checkOver();

	/**将方块聚集在一起*/
	void putTileTogether();

	/**重新开始游戏*/
	void restartGame();

	/**碰撞检测更新函数*/
	void myCollionUpdate(float tmd);
	/**刷新目前放快的位置*/
	void refreshSquarePos(int ox,int oy);

	/**显示右半部分*/
	void showPreviewSquare();
	/**满行消去*/
	void removeRow();
private:
	/**方块数组*/
	InfectTile* m_infectTile[10][10];
	/**步数计算*/
	LabelTTF* m_step;
	/**目前正在掉落的块的信息*/
	//NormalSquare m_square;
	/**下一个方块的信息*/
	//NormalSquare m_nextSquare;
private:
	/**难度等级，1-5 分别为easy，normal，legend，hard，utmost，4 6 7 8 10*/
	int m_modeLevel;
	/**方块间的间隔*/
	int m_squareSize;
	/**方块的总*/
	int m_countSize;
	/**完美解可以到达的最大步数*/
	int m_maxStep;
	/**方块的缩放*/
	float m_scaleSize;


	/**关卡的数字*/
	int m_level;

	/**步数计算*/
	int m_stepCount;

	/**游戏是否已经结束*/
	bool m_isGameOver;

	/*方块的基础坐标*/
	int m_baseX;
	int m_baseY;




	/**俄罗斯方块上次的位置*/
	int m_lastIndexX;
	int m_lastIndexY;

	/**上一个俄罗斯方块的位置*/
	std::vector<std::vector<bool>> m_lastPos;
	/**目前的俄罗斯方块的位置*/
	std::vector<std::vector<bool>> m_currPos;
	/**显示下一个的俄罗斯方块的位置*/
	std::vector<std::vector<bool>> m_nextPos;
};

#endif