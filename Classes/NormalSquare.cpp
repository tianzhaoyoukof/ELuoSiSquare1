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
	m_angle(1)
{

}

void NormalSquare::downOne(std::vector<std::vector<bool>>& v)
{
	-- m_indexY;

	bool temp[8][6] = {false};
	int i,j;
	int I,J;
	std::vector<bool> one;

	allSquareKindChange(temp,I,J,0);

	PUSH(i,j,I,J,v,temp,one);
}

void NormalSquare::fall()
{

}

void NormalSquare::newSquare( int ix,int iy,int kind )
{
	m_indexX = ix;
	m_indexY = iy;
	m_squareKind = kind;
	m_angle = 1;
}

void NormalSquare::changeAngle( std::vector<std::vector<bool>>& v )
{
	++ m_angle;
	if(m_angle == 5)
		m_angle -= 4;

	bool temp[8][6] = {false};
	int i,j;
	int I,J;
	std::vector<bool> one;

	allSquareKindChange(temp,I,J,3);

	PUSH(i,j,I,J,v,temp,one);
}

void NormalSquare::leftOne( std::vector<std::vector<bool>>& v )
{
	bool temp[8][6] = {false};
	int i,j;
	int I,J;
	std::vector<bool> one;

	allSquareKindChange(temp,I,J,1);


	PUSH(i,j,I,J,v,temp,one);
}

void NormalSquare::rightOne( std::vector<std::vector<bool>>& v )
{
	bool temp[8][6] = {false};
	int i,j;
	int I,J;
	std::vector<bool> one;

	allSquareKindChange(temp,I,J,2);


	PUSH(i,j,I,J,v,temp,one);
}

void NormalSquare::allSquareKindChange( bool b[8][6] ,int & I,int & J,int kind)
{
	//kind :  0����   1����   2����  3����
	switch(m_squareKind)
	{
	case SQUARE1:
		{
			switch(m_angle)
			{
			case 1:
				b[1][0] = b[1][1] = b[1][2] = b[2][1] = true;

				if(kind == 1)
				{
					if(m_indexX > 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				else if(kind == 3)
				{
					if(m_indexX == 8)
						-- m_indexX;
				}
				break;
			case 2:
				b[0][1] = b[1][1] = b[1][2] = b[2][1] = true;
				if(kind == 1)
				{
					if(m_indexX >= 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				break;
			case 3:
				b[1][0] = b[1][1] = b[1][2] = b[0][1] = true;
				if(kind == 1)
				{
					if(m_indexX > 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				else if(kind == 3)
				{
					if(m_indexX == -1)
						++ m_indexX;
				}
				break;
			case 4:
				b[0][1] = b[1][1] = b[2][1] = b[1][0] = true;
				if(kind == 1)
				{
					if(m_indexX > 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 8)
						++ m_indexX;
				}
				break;
			}
			I = J = 3;
			break;
		}
	case SQUARE2:
		{
			switch(m_angle)
			{
			case 1:case 3:
				b[2][0] = b[2][1] = b[1][1] = b[1][2] = true;
				if(kind == 1)
				{
					if(m_indexX > 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				else if(kind == 3)
				{
					if(m_indexX == -1)
						++ m_indexX;
				}
				break;
			case 2:case 4:
				b[0][1] = b[1][1] = b[1][2] = b[2][2] = true;
				if(kind == 1)
				{
					if(m_indexX >= 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				break;
			}
			I = J = 3;
			break;
		}
	case SQUARE3:
		{
			switch(m_angle)
			{
			case 1:case 3:
				b[1][0] = b[1][1] = b[2][1] = b[2][2] = true;
				if(kind == 1)
				{
					if(m_indexX > 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				else if(kind == 3)
				{
					if(m_indexX == 8)
						-- m_indexX;
				}
				break;
			case 2:case 4:
				b[0][1] = b[1][0] = b[1][1] = b[2][0] = true;
				if(kind == 1)
				{
					if(m_indexX > 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 8)
						++ m_indexX;
				}
				break;
			}
			I = J = 3;
			break;
		}
	case SQUARE4:
		{
			switch(m_angle)
			{
			case 1:
				b[1][1] = b[1][2] = b[1][3] = b[2][1] = true;

				if(kind == 1)
				{
					if(m_indexX >= 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 6)
						++ m_indexX;
				}
				else if(kind == 3)
				{
					if(m_indexX == 7)
						-- m_indexX;
				}
				break;
			case 2:
				b[1][1] = b[1][2] = b[2][2] = b[3][2] = true;
				if(kind == 1)
				{
					if(m_indexX >= 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				break;
			case 3:
				b[1][2] = b[2][0] = b[2][1] = b[2][2] = true;
				if(kind == 1)
				{
					if(m_indexX > 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				else if(kind == 3)
				{
					if(m_indexX == -1)
						++ m_indexX;
				}
				break;
			case 4:
				b[0][1] = b[1][1] = b[2][1] = b[2][2] = true;
				if(kind == 1)
				{
					if(m_indexX > 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				break;
			}
			I = J = 4;
			break;
		}
	case SQUARE5:
		{
			switch(m_angle)
			{
			case 1:
				b[1][0] = b[1][1] = b[1][2] = b[2][2] = true;

				if(kind == 1)
				{
					if(m_indexX > 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				else if(kind == 3)
				{
					if(m_indexX == -1)
						++ m_indexX;
				}
				break;
			case 2:
				b[0][2] = b[1][2] = b[2][1] = b[2][2] = true;
				if(kind == 1)
				{
					if(m_indexX >= 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				break;
			case 3:
				b[1][1] = b[2][1] = b[2][2] = b[2][3] = true;
				if(kind == 1)
				{
					if(m_indexX >= 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 6)
						++ m_indexX;
				}
				else if(kind == 3)
				{
					if(m_indexX == 7)
						-- m_indexX;
				}
				break;
			case 4:
				b[1][1] = b[1][2] = b[2][1] = b[3][1] = true;
				if(kind == 1)
				{
					if(m_indexX > 0)
						-- m_indexX;
				}
				else if(kind == 2)
				{
					if(m_indexX < 7)
						++ m_indexX;
				}
				break;
			}
			I = J = 4;
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
}

bool NormalSquare::isTouchBottom()
{
	switch(m_squareKind)
	{
	case SQUARE1:
		{
			switch(m_angle)
			{
			case 1:
				if(m_indexY < 0)
					return true;
				break;
			case 2:case 3:case 4:
				if(m_indexY < 1)
					return true;
				break;
			}
			break;
		}
	case SQUARE2:case SQUARE3:
		{
			switch(m_angle)
			{
			case 1:case 3:
				if(m_indexY < 0)
					return true;
				break;
			case 2:case 4:
				if(m_indexY < 1)
					return true;
				break;
			}
			break;
		}
	case SQUARE4:
		{
			switch(m_angle)
			{
			case 1:case 2:case 3:
				if(m_indexY < 0)
					return true;
				break;
			case 4:
				if(m_indexY < 1)
					return true;
				break;
			}
			break;
		}
	case SQUARE5:
		{
			switch(m_angle)
			{
			case 1:case 3:case 4:
				if(m_indexY < 0)
					return true;
				break;
			case 2:
				if(m_indexY < 1)
					return true;
				break;
			}
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
	return false;
}

void NormalSquare::newSquare( int ix,int iy,int kind )
{
	bool temp[8][6] = {false};
	int i,j;
	int I,J;

void NormalSquare::changeAngle()
{
	++ m_angle;
	m_angle %= 4;
}

