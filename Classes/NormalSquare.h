#ifndef __NORMALSQUARE_H__
#define __NORMALSQUARE_H__

/*����˹����ķ��飬��17�ַ��飬ֻ�������
 * 2015-12-2 ����
 */

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "SquareKind.h"

USING_NS_CC;

class NormalSquare
{
public :
	NormalSquare(int ix = 1,int iy = 1,int kind = 1);
	/**���������·���*/
	void newSquare(int ix,int iy,int kind);
	/**�½�һ��*/
	void downOne(std::vector<std::vector<bool>>& v);
	/**�����ƶ�*/
	void leftOne(std::vector<std::vector<bool>>& v);
	/**�����ƶ�*/
	void rightOne(std::vector<std::vector<bool>>& v);
	/**ֱ�ӽ���*/
	void fall();
	/**�ı䷭ת*/
	void changeAngle(std::vector<std::vector<bool>>& v);
	void changeAngle(std::vector<std::vector<bool>>& v,std::vector<std::vector<bool>>& v1);
	/**�õ�������λ��*/
	int getIndexX() const {return m_indexX;}
	int getIndexY() const {return m_indexY;}
	/**�õ�����*/
	int getSquareKind() const {return m_squareKind;}

	/**�Ƿ��Ѿ�������*/
	bool isTouchBottom();

	/**չʾԤ���Ĵ���*/
	void showPreView(std::vector<std::vector<bool>>& v);
private:
	/**���ַ��鼰�ǶȵĲ���*/
	void allSquareKindChange(bool b[8][6],int & I,int& J,int kind);
	/**�����Ƿ��ܷ�ת*/
	bool canFlipSquare(std::vector<std::vector<bool>>& t);
private:
	/**Ŀǰ�ķ�������*/
	int m_squareKind;
	/**�������½ǵ�����*/
	int m_indexX;
	int m_indexY;
	/**����ķ�λ*/
	int m_angle;
};

#endif