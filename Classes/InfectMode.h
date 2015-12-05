#ifndef __INFECTMODE_H__
#define __INFECTMODE_H__

/*����˹�������Ⱦģʽ����������ɫ
 * 2015-12-5 ����
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
	/**���ѡ��ؿ��Ľ���*/
	void addSelectMenu();
	/**��Ӷ���˹���鳡��*/
	void addScene();
	/**��ӷ���*/
	void addTile();

	/**������ɫ��ť�Ļص�����*/
	void btnBLUECallBack();
	void btnGREENCallBack();
	void btnORANGECallBack();
	void btnPURPLECallBack();
	void btnREDCallBack();
	void btnYELLOWCallBack();

	/**������*/
	void checkTouch(InfectTileColor c);

	/**�����Ϸ����*/
	bool checkOver();

	/**������ۼ���һ��*/
	void putTileTogether();

	/**���¿�ʼ��Ϸ*/
	void restartGame();

	/**��ײ�����º���*/
	void myCollionUpdate(float tmd);
	/**ˢ��Ŀǰ�ſ��λ��*/
	void refreshSquarePos(int ox,int oy);

	/**��ʾ�Ұ벿��*/
	void showPreviewSquare();
	/**������ȥ*/
	void removeRow();
private:
	/**��������*/
	InfectTile* m_infectTile[10][10];
	/**��������*/
	LabelTTF* m_step;
	/**Ŀǰ���ڵ���Ŀ����Ϣ*/
	//NormalSquare m_square;
	/**��һ���������Ϣ*/
	//NormalSquare m_nextSquare;
private:
	/**�Ѷȵȼ���1-5 �ֱ�Ϊeasy��normal��legend��hard��utmost��4 6 7 8 10*/
	int m_modeLevel;
	/**�����ļ��*/
	int m_squareSize;
	/**�������*/
	int m_countSize;
	/**��������Ե���������*/
	int m_maxStep;
	/**���������*/
	float m_scaleSize;


	/**�ؿ�������*/
	int m_level;

	/**��������*/
	int m_stepCount;

	/**��Ϸ�Ƿ��Ѿ�����*/
	bool m_isGameOver;

	/*����Ļ�������*/
	int m_baseX;
	int m_baseY;




	/**����˹�����ϴε�λ��*/
	int m_lastIndexX;
	int m_lastIndexY;

	/**��һ������˹�����λ��*/
	std::vector<std::vector<bool>> m_lastPos;
	/**Ŀǰ�Ķ���˹�����λ��*/
	std::vector<std::vector<bool>> m_currPos;
	/**��ʾ��һ���Ķ���˹�����λ��*/
	std::vector<std::vector<bool>> m_nextPos;
};

#endif