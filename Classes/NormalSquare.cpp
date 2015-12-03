#include "NormalSquare.h"

#define PUSH(i,j,I,J,V,T,O)	for(i = 0 ; i < I ; ++i)		\
							{								\
								O.clear();					\
								for(j = 0 ; j < J ; ++j)	\
									O.push_back(T[i][j]);	\
								V.push_back(O);				\
							}

NormalSquare::NormalSquare(int ix,int iy,int kind):
	m_squareKind(kind),
	m_indexX(ix),
	m_indexY(iy),
	m_angle(0)
{

}

void NormalSquare::downOne(std::vector<std::vector<bool>>& v)
{
	-- m_indexY;

	bool temp[8][6] = {false};
	int i,j;
	int I,J;
	std::vector<bool> one;
	
	switch(m_squareKind)
	{
	case SQUARE1:
		{
			temp[1][0] = temp[1][1] = temp[1][2] = temp[2][1] = true;
			I = J = 3;
			break;
		}
	case SQUARE2:
		{
			break;
		}
	case SQUARE3:
		{
			break;
		}
	case SQUARE4:
		{
			break;
		}
	case SQUARE5:
		{
			break;
		}
	case SQUARE6:
		{
			break;
		}
	case SQUARE7:
		{
			break;
		}
	case SQUARE8:
		{
			break;
		}
	case SQUARE9:
		{
			break;
		}
	case SQUARE10:
		{
			break;
		}
	case SQUARE11:
		{
			break;
		}
	case SQUARE12:
		{
			break;
		}
	case SQUARE13:
		{
			break;
		}
	case SQUARE14:
		{
			break;
		}
	case SQUARE15:
		{
			break;
		}
	case SQUARE16:
		{
			break;
		}
	case SQUARE17:
		{
			break;
		}
	}

	PUSH(i,j,3,3,v,temp,one);
}

void NormalSquare::fall()
{

}

void NormalSquare::newSquare( int ix,int iy,int kind )
{
	m_indexX = ix;
	m_indexY = iy;
	m_squareKind = kind;
	m_angle = 0;
}

void NormalSquare::changeAngle()
{
	++ m_angle;
	m_angle %= 4;
}

