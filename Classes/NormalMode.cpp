#include "NormalMode.h"

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

	this->schedule(schedule_selector(NormalMode::myUpdate),0.5f);

	return true;
}

NormalMode::NormalMode():
	m_baseX(0),
	m_baseY(0),
	m_square(7,13,1)
{

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
}

void NormalMode::btnLEFTCallBack()
{
	log("left");
}

void NormalMode::btnRIGHTCallBack()
{
	log("right");
}

void NormalMode::btnCHANGECallBack()
{
	log("change");
}

void NormalMode::myUpdate( float tmd )
{
	log("update");
	/*游戏暂停的话,直接返回*/

	/*碰撞检测*/
	if(isCollion())
		return ;

	/*目前正在运动的方块进行位置更新*/
	m_square.downOne(m_currPos);
	int ox = m_square.getIndexX();
	int oy = m_square.getIndexY();
	refreshSquarePos(ox,oy);
	m_currPos.clear();
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
			if(m_currPos[i][j] == true)
				m_leftTile[oy + i][ox + j]->setTileVisible(BLACK);
			else if(oy + i >= 0)
				m_leftTile[oy + i][ox + j]->setUNVisiable();
		}
	}

	m_lastPos.clear();
	m_lastPos = m_currPos;
}

bool NormalMode::isCollion()
{
	int n = m_lastPos.size();
	int m;
	if(n != 0)
		m = m_lastPos[0].size();
	for(int i = 0 ; i < n ; ++ i)
		for(int j = 0 ; j < m ; ++j)
		{
			if(m_lastPos[i][j] == true)
			{
				if(m_lastIndexY + i <= 0)
					return true;
				log("%d,%d",m_lastIndexY + i,m_lastIndexX + j);
			}
			
		}
	return false;
}
