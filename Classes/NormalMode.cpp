#include "NormalMode.h"
#include "time.h"

Scene* NormalMode::createMode()
{
	auto sce = Scene::create();
	auto mode = NormalMode::create();
	if(sce && mode)
	{
		sce->addChild(mode);
		return sce;
	}
	CC_SAFE_DELETE(mode);
	return nullptr;
}

bool NormalMode::init()
{
	if(!Node::init())
		return false;

	Size size = Director::getInstance()->getWinSize();

	auto BG = Sprite::create("BG.png");
	BG->setPosition(Vec2(size.width / 2,size.height / 2));
	this->addChild(BG);

	addBackGround();

	/*添加左边的地图块*/
	for(int i = 0 ; i < 20 ; ++ i)
		for(int j = 0 ; j < 10 ; ++ j)
		{
			m_leftTile[i][j] = NormalTile::createTile(BLACK,Vec2(m_baseX + j * 36 , m_baseY + i * 36));
			this->addChild(m_leftTile[i][j]);
			m_leftTile[i][j]->setUNVisiable();
		}

	/*添加右边的地图块*/
	for(int i = 0 ; i < 8 ; ++ i)
		for(int j = 0 ; j < 6 ; ++ j)
		{
			m_rightTile[i][j] = NormalTile::createTile(BLACK,Vec2(m_baseX + (j + 11) * 36 , m_baseY + (i + 6) * 36));
			this->addChild(m_rightTile[i][j]);
			m_rightTile[i][j]->setUNVisiable();
		}

	this->schedule(schedule_selector(NormalMode::myUpdate),0.6f);

	return true;
}

NormalMode::NormalMode():
	m_baseX(0),
	m_baseY(0),
	m_square(4,19,7),
	m_nextSquare(7,13,4)
{
	int x = rand() % 2 + 1;
	m_nextSquare.newSquare(1,1,x);
}

void NormalMode::addBackGround()
{
	FileUtils * fu = FileUtils::getInstance();
	auto doc = new tinyxml2::XMLDocument();
	doc->Parse(fu->getStringFromFile("NormalMode/position.xml").c_str());
	auto root = doc->RootElement();
	auto e = root->FirstChildElement();

	auto c1 = e->FirstChildElement();
	auto c2 = c1->NextSiblingElement();

	m_baseX = std::atoi(c1->GetText());
	m_baseY = std::atoi(c2->GetText());

	auto background = Sprite::create("NormalMode/background.png");
	background->setAnchorPoint(Vec2(0,0));
	background->setPosition(Vec2(m_baseX,m_baseY));
	this->addChild(background);

	m_baseX += 34;
	m_baseY += 34;

	auto BtnUp = MenuItemImage::create("NormalMode/small_Btn_0.png","NormalMode/small_Btn_1.png",CC_CALLBACK_0(NormalMode::btnUPCallBack,this));
	e = e->NextSiblingElement();
	BtnUp->setPosition(Vec2(std::atoi(e->FirstChildElement()->GetText()),std::atoi(e->LastChildElement()->GetText())));
	
	auto BtnDown = MenuItemImage::create("NormalMode/small_Btn_0.png","NormalMode/small_Btn_1.png",CC_CALLBACK_0(NormalMode::btnDOWNCallBack,this));
	e = e->NextSiblingElement();
	BtnDown->setPosition(Vec2(std::atoi(e->FirstChildElement()->GetText()),std::atoi(e->LastChildElement()->GetText())));
	
	auto BtnLeft = MenuItemImage::create("NormalMode/small_Btn_0.png","NormalMode/small_Btn_1.png",CC_CALLBACK_0(NormalMode::btnLEFTCallBack,this));
	e = e->NextSiblingElement();
	BtnLeft->setPosition(Vec2(std::atoi(e->FirstChildElement()->GetText()),std::atoi(e->LastChildElement()->GetText())));
	
	auto BtnRight = MenuItemImage::create("NormalMode/small_Btn_0.png","NormalMode/small_Btn_1.png",CC_CALLBACK_0(NormalMode::btnRIGHTCallBack,this));
	e = e->NextSiblingElement();
	BtnRight->setPosition(Vec2(std::atoi(e->FirstChildElement()->GetText()),std::atoi(e->LastChildElement()->GetText())));
	
	auto BtnChange = MenuItemImage::create("NormalMode/big_Btn_0.png","NormalMode/big_Btn_1.png",CC_CALLBACK_0(NormalMode::btnCHANGECallBack,this));
	e = e->NextSiblingElement();
	BtnChange->setPosition(Vec2(std::atoi(e->FirstChildElement()->GetText()),std::atoi(e->LastChildElement()->GetText())));
	
	auto menu = Menu::create(BtnUp,BtnDown,BtnLeft,BtnRight,BtnChange,NULL);
	menu->setPosition(Vec2(0,0));
	this->addChild(menu);
}

void NormalMode::btnUPCallBack()
{
	log("up");
}

void NormalMode::btnDOWNCallBack()
{
	log("down");
	myUpdate(0.1f);
}

void NormalMode::btnLEFTCallBack()
{
	log("left");
	m_currPos.clear();
	m_square.leftOne(m_currPos);

	//左边界检测
	bool flag = false;
	int ox = m_square.getIndexX();
	int oy = m_square.getIndexY();

	int n = m_currPos.size();
	int m = 0;
	if(n)
		m = m_currPos[0].size();

	for(int i = 0 ; i < n ; ++ i)
	{
		for(int j = 0 ; j < m ; ++ j)
		{
			if(m_lastIndexX + j < 0 || m_lastIndexX + j >= 10 || m_lastIndexY + i < 0)
				continue;
			if(m_currPos[i][j] == true)
			{
				if(m_leftTile[m_lastIndexY + i][m_lastIndexX + j - 1]->getTileVisible())
				{
					flag = true;
					if(m_lastIndexX + j != 0)
						m_square.rightOne(m_lastPos);
				}
				break;
			}
		}
	}
	if(!flag)
	{
		refreshSquarePos(ox,oy);
		m_lastIndexX = ox;
		m_lastIndexY = oy;
	}
}

void NormalMode::btnRIGHTCallBack()
{
	log("right");
	m_currPos.clear();
	m_square.rightOne(m_currPos);
	
	//右边界检测
	bool flag = false;
	int ox = m_square.getIndexX();
	int oy = m_square.getIndexY();

	int n = m_currPos.size();
	int m = 0;
	if(n)
		m = m_currPos[0].size();

	for(int i = 0 ; i < n ; ++ i)
	{
		for(int j = m - 1 ; j >= 0 ; -- j)
		{
			if(m_lastIndexX + j < 0 || m_lastIndexX + j >= 10 || m_lastIndexY + i < 0)
				continue;
			if(m_currPos[i][j] == true)
			{
				if(m_leftTile[m_lastIndexY + i][m_lastIndexX + j + 1]->getTileVisible())
				{
					flag = true;
					if(m_lastIndexX + j != 9)
						m_square.leftOne(m_lastPos);
				}
				break;
			}
		}
		if(flag)
			break;
	}

	if(!flag)
	{
		refreshSquarePos(ox,oy);
		m_lastIndexX = ox;
		m_lastIndexY = oy;
	}
}

void NormalMode::btnCHANGECallBack()
{
	log("change");

	m_currPos.clear();
	m_square.changeAngle(m_currPos);

	int n = m_currPos.size();
	int m = 0;
	if(n)
		m = m_currPos[0].size();

	//首先要检测变换的位置是否有方块
	std::vector<std::vector<bool>> temp;
	std::vector<bool> t;
	
	int ox = m_square.getIndexX();
	int oy = m_square.getIndexY();

	for(int i = 0 ; i < n ; ++ i)
	{
		t.clear();
		for(int j = 0 ; j < m ; ++ j)
		{
			if(ox + j < 0 || ox + j >= 10 || oy + i < 0 || oy + i >= 20)
				t.push_back(false);
			else if(m_leftTile[oy + i][ox + j]->getTileVisible())
				t.push_back(true);
			else
				t.push_back(false);
		}
		temp.push_back(t);
	}

	m_currPos.clear();
	m_square.changeAngle(m_currPos,temp);

	ox = m_square.getIndexX();
	oy = m_square.getIndexY();

	refreshSquarePos(ox,oy);
	m_lastIndexX = ox;
	m_lastIndexY = oy;
}

void NormalMode::myUpdate( float tmd )
{
	log("update");
	/*游戏暂停的话,直接返回*/

	/*显示预览窗口*/
	showPreviewSquare();

	/*碰撞检测*/
	if(isCollion())
	{
		//检测满行消去
		removeRow();
		int ox = rand() % 7 + 1;
		m_lastPos.clear();
		m_square.newSquare(3,19,m_nextSquare.getSquareKind());
		m_square.newSquare(3,19,7);
		m_nextSquare.newSquare(1,1,ox);
		m_isCollisionTakePlace = false;
		return ;
	}

	/*目前正在运动的方块进行位置更新*/
	m_currPos.clear();
	m_square.downOne(m_currPos);
	int ox = m_square.getIndexX();
	int oy = m_square.getIndexY();
	refreshSquarePos(ox,oy);
	m_lastIndexX = ox;
	m_lastIndexY = oy;

	/*检查是否被叠加，游戏是否结束*/


	/*检查行数是否可以消灭*/

}

void NormalMode::refreshSquarePos( int ox , int oy)
{
	//function 形式：1：上，2：下 3：左 4：右
	int n = m_lastPos.size();
	int m;
	if(n != 0)
		m = m_lastPos[0].size();
			
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < m ; ++j)
		{
			if(m_lastIndexY + i < 0 || m_lastIndexY + i >= 20 || m_lastIndexX + j < 0 || m_lastIndexX + j >= 10) 
				continue;
			if(m_lastPos[i][j] == true)
				m_leftTile[m_lastIndexY + i][m_lastIndexX + j]->setUNVisiable();
		}


	n = m_currPos.size();
	if(n != 0)
		m = m_currPos[0].size();
	for(int i = 0 ; i < n ; ++ i)
	{
		for(int j = 0 ; j < m ; ++j)
		{
			if(oy + i < 0 || oy + i >= 20 || ox + j < 0 || ox + j >=10)
				continue;
			if(m_currPos[i][j] == true)
				m_leftTile[oy + i][ox + j]->setTileVisible(BLACK);
		}
	}

	m_lastPos.clear();
	m_lastPos = m_currPos;
}

bool NormalMode::isCollion()
{
	int n = m_lastPos.size();
	int m = 0;
	if(n != 0)
		m = m_lastPos[0].size();

	for(int j = 0 ; j < m ; ++ j)
	{
		for(int i = 0 ; i < n ; ++ i)
		{
			if(m_lastIndexX + j < 0 || m_lastIndexX + j >= 10 || m_lastIndexY + i < 0)
				continue;
			if(m_square.isTouchBottom())
				return true;
			if(m_lastPos[i][j] == true && m_lastIndexY + i != 0)
			{
				if(m_leftTile[m_lastIndexY + i - 1][m_lastIndexX + j]->getTileVisible())
					return true;
				break;
			}
		}
	}
	return false;
}

void NormalMode::showPreviewSquare()
{
	m_nextPos.clear();
	m_nextSquare.showPreView(m_nextPos);
	int n = m_nextPos.size();
	int m = 0;
	if(n)
		m = m_nextPos[0].size();
	int ox = m_nextSquare.getIndexX();
	int oy = m_nextSquare.getIndexY();
	for(int i = 0 ; i < 8 ; ++ i)
		for(int j = 0 ; j < 6 ; ++ j)
		{
			m_rightTile[i][j]->setUNVisiable();
		}
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < m ; ++ j)
		{
			if(m_nextPos[i][j] == true)
				m_rightTile[oy + i][ox + j]->setTileVisible(BLACK);
		}
}

void NormalMode::myCollionUpdate( float tmd )
{
	if(isCollion())
	{
		m_isCollisionTakePlace = true;
	}
	else
	{
		m_isCollisionTakePlace = false;
	}
}

void NormalMode::removeRow()
{
	bool flag = false;
	for(int i = 0 ; i < 20 ; ++ i)
	{
		flag = true;
		for(int j = 0 ; j < 10 ; ++ j)
			if(!m_leftTile[i][j]->getTileVisible())
			{
				flag = false;
				break;
			}
		if(flag)
		{
			for(int j = 0 ; j < 10 ; ++ j)
			{
				m_leftTile[i][j]->setTileVisible(BLACK);
			}
			for(int k = i  ; k < 19 ; ++ k)
			{
				for(int j = 0 ; j < 10 ; ++ j)
				{
					if(m_leftTile[k + 1][j]->getTileVisible())
						m_leftTile[k][j]->setTileVisible(BLACK);
					else
						m_leftTile[k][j]->setUNVisiable();
				}
			}
			-- i;
		}
	}
}
