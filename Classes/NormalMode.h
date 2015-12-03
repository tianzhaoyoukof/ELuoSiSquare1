#ifndef __NORMALMODE_H__
#define __NORMALMODE_H__

/*����˹����ľ���ģʽ��������ģʽ��
  1.��׼ģʽ
  2.���ģʽ
  3.����ģʽ
 * 2015-12-2 ����
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
	/**��Ӷ���˹���鱳��*/
	void addBackGround();

	/**�� ��ť������*/
	void btnUPCallBack();
	/**�� ��ť������*/
	void btnDOWNCallBack();
	/**�� ��ť������*/
	void btnLEFTCallBack();
	/**�� ��ť������*/
	void btnRIGHTCallBack();
	/**�仯 ��ť������*/
	void btnCHANGECallBack();

	/**���º���*/
	void myUpdate(float tmd);
	/**ˢ��Ŀǰ�ſ��λ��*/
	void refreshSquarePos(int ox,int oy);

	/**�����ײ*/
	bool isCollion();
private:
	/**��ߵķ����������*/
	NormalTile* m_leftTile[20][10];
	/**�ұߵķ�����ʾ����*/
	NormalTile* m_rightTile[8][6];
	/**Ŀǰ���ڵ���Ŀ����Ϣ*/
	NormalSquare m_square;
private:
	/*����˹���鱳���Ļ�������*/
	int m_baseX;
	int m_baseY;

	/**����˹�����ϴε�λ��*/
	int m_lastIndexX;
	int m_lastIndexY;

	/**��һ������˹�����λ��*/
	std::vector<std::vector<bool>> m_lastPos;
	/**Ŀǰ�Ķ���˹�����λ��*/
	std::vector<std::vector<bool>> m_currPos;
};

#endif