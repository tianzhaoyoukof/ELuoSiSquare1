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
	/**ֱ�ӽ���*/
	void fall();
	/**�ı䷭ת*/
	void changeAngle();
	/**�õ�������λ��*/
	int getIndexX() const {return m_indexX;}
	int getIndexY() const {return m_indexY;}
private:
	
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