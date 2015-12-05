#include "InfectMode.h"

Scene* InfectMode::createMode()
{
	auto sce = Scene::create();
	auto mode = InfectMode::create();
	if(sce && mode)
	{
		sce->addChild(mode);
		return sce;
	}
	CC_SAFE_DELETE(mode);
	return nullptr;
}

bool InfectMode::init()
{
	if(!Node::init())
		return false;

	Size size = Director::getInstance()->getWinSize();

	auto BG = Sprite::create("BG.png");
	BG->setPosition(Vec2(size.width / 2,size.height / 2));
	this->addChild(BG);

	addSelectMenu();
	//addScene();

	return true;
}

InfectMode::InfectMode():
	m_modeLevel(1),
	m_squareSize(0),
	m_countSize(0),
	m_scaleSize(1.0f),
	m_level(1),
	m_stepCount(0),
	m_isGameOver(false)
{
	
}


void InfectMode::addSelectMenu()
{
	FileUtils * fu = FileUtils::getInstance();
	auto doc = new tinyxml2::XMLDocument();
	doc->Parse(fu->getStringFromFile("InfectMode/selectMenu.xml").c_str());
	auto root = doc->RootElement();
	auto e = root->FirstChildElement();

	auto c1 = e->FirstChildElement();
	auto c2 = c1->NextSiblingElement();

	int baseX = std::atoi(c1->GetText());
	int baseY = std::atoi(c2->GetText());

	auto node = Node::create();
	for(int i = 0 ; i < 10 ; ++ i)
		for(int j = 0 ; j < 10 ; ++ j)
		{
			auto sp = Sprite::create("InfectMode/noclear.png");
			sp->setPosition(Vec2(baseX + 60 * j,baseY + 60 * i));
			node->addChild(sp);
		}

	this->addChild(node);
}

void InfectMode::addScene()
{
	FileUtils * fu = FileUtils::getInstance();
	auto doc = new tinyxml2::XMLDocument();
	doc->Parse(fu->getStringFromFile("InfectMode/position.xml").c_str());
	auto root = doc->RootElement();
	auto e = root->FirstChildElement();

	auto c1 = e->FirstChildElement();
	auto c2 = c1->NextSiblingElement();

	int baseX = std::atoi(c1->GetText());
	int baseY = std::atoi(c2->GetText());

	auto background = Sprite::create("NormalMode/background.png");
	background->setAnchorPoint(Vec2(0,0));
	background->setPosition(Vec2(m_baseX,m_baseY));
	this->addChild(background);

	const std::string picName[] = { "InfectMode/blue.png","InfectMode/green.png","InfectMode/orange.png",
									"InfectMode/purple.png","InfectMode/red.png","InfectMode/yellow.png"};

	for(int i = 0 ; i < 6 ; ++ i)
	{
		auto sp = Sprite::create(picName[i]);
		sp->setPosition(Vec2(baseX + 110 * i,baseY));
		this->addChild(sp);
	}

	auto blue = MenuItemImage::create("InfectMode/white.png","InfectMode/gray.png",CC_CALLBACK_0(InfectMode::btnBLUECallBack,this));
	blue->setPosition(Vec2(baseX,baseY));
	baseX += 110;

	auto green = MenuItemImage::create("InfectMode/white.png","InfectMode/gray.png",CC_CALLBACK_0(InfectMode::btnGREENCallBack,this));
	green->setPosition(Vec2(baseX,baseY));
	baseX += 110;

	auto orange = MenuItemImage::create("InfectMode/white.png","InfectMode/gray.png",CC_CALLBACK_0(InfectMode::btnORANGECallBack,this));
	orange->setPosition(Vec2(baseX,baseY));
	baseX += 110;

	auto purple = MenuItemImage::create("InfectMode/white.png","InfectMode/gray.png",CC_CALLBACK_0(InfectMode::btnPURPLECallBack,this));
	purple->setPosition(Vec2(baseX,baseY));
	baseX += 110;

	auto red = MenuItemImage::create("InfectMode/white.png","InfectMode/gray.png",CC_CALLBACK_0(InfectMode::btnREDCallBack,this));
	red->setPosition(Vec2(baseX,baseY));
	baseX += 110;

	auto yellow = MenuItemImage::create("InfectMode/white.png","InfectMode/gray.png",CC_CALLBACK_0(InfectMode::btnYELLOWCallBack,this));
	yellow->setPosition(Vec2(baseX,baseY));

	auto menu = Menu::create(blue,green,orange,purple,red,yellow,NULL);
	menu->setPosition(Vec2(0,0));
	this->addChild(menu);

	//模式的选择
	switch(m_modeLevel)
	{
	case 1:
		m_maxStep = 8;
		m_squareSize = 130;
		m_countSize = 4;
		m_scaleSize = 1.2f;
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	}

	//添加步数
	m_step = LabelTTF::create(CCString::createWithFormat("Step : %d /%d\nLevel : %d",m_stepCount,m_maxStep,m_level)->getCString(), "Consolas", 40);
	m_step->setPosition(360, 1180);
	addChild(m_step);

	addTile();
}

void InfectMode::addTile()
{
	FileUtils * fu = FileUtils::getInstance();
	auto doc = new tinyxml2::XMLDocument();
	doc->Parse(fu->getStringFromFile("InfectMode/level/easy.xml").c_str());
	auto root = doc->RootElement();
	auto e = root->FirstChildElement();

	auto c1 = e->FirstChildElement();
	auto c2 = c1->NextSiblingElement();

	m_baseX = std::atoi(c1->GetText());
	m_baseY = std::atoi(c2->GetText());

	int r = rand() % 2;

	int a[10][10];

	for(e = e->NextSiblingElement();e != NULL;e = e->NextSiblingElement())
	{
		std::string s = "l";
		s +=  CCString::createWithFormat("%d",m_level)->getCString();
		if((std::string)e->Value() == s)
			break;
	}

	if(e != NULL)
	{
		int i = 1;
		auto attr = e->FirstAttribute();
		auto fir = e->FirstChildElement();
		const char* temp = fir->GetText();

		for(int j = 0 ; temp[j] ; ++ j)
			a[0][j] = temp[j] - '0';

		for(fir = fir->NextSiblingElement() ; fir != NULL ; fir = fir->NextSiblingElement())
		{
			const char* t = fir->GetText();
			for(int j = 0 ; t[j] ; ++ j)
				a[i][j] = t[j] - '0';
			++ i;
		}
	}

	for(int i = 0 ; i < m_countSize ; ++ i)
	{
		for(int j = 0 ; j < m_countSize ; ++ j)
		{
			m_infectTile[i][j] = InfectTile::createTile(a[i][j],j,i,m_baseX,m_baseY,m_squareSize);
			m_infectTile[i][j]->setScale(m_scaleSize);
			this->addChild(m_infectTile[i][j]);
		}
	}
}

void InfectMode::btnBLUECallBack()
{
	//log("blue");
	if(m_isGameOver)
	{
		return ;
	}
	checkTouch(BLUE_infect);
}

void InfectMode::btnGREENCallBack()
{
	//log("green");
	if(m_isGameOver)
	{
		return ;
	}
	checkTouch(GREEN_infect);
}

void InfectMode::btnORANGECallBack()
{
	//log("orange");
	if(m_isGameOver)
	{
		return ;
	}
	checkTouch(ORANGE_infect);
}

void InfectMode::btnPURPLECallBack()
{
	//log("purple");
	if(m_isGameOver)
	{
		return ;
	}
	checkTouch(PURPLE_infect);
}

void InfectMode::btnREDCallBack()
{
	//log("red");
	if(m_isGameOver)
	{
		return ;
	}
	checkTouch(RED_infect);
}

void InfectMode::btnYELLOWCallBack()
{
	//log("yellow");
	if(m_isGameOver)
	{
		m_isGameOver = false;
		restartGame();
		return ;
	}
	checkTouch(YELLOW_infect);
}

void InfectMode::checkTouch( InfectTileColor c )
{
	if(m_infectTile[0][0]->getTileColor() == c)
		return ;

	std::deque<InfectTile* > Tdeque;
	InfectTileColor baseColor = m_infectTile[0][0]->getTileColor();
	m_infectTile[0][0]->setInQueue(true);
	Tdeque.push_back(m_infectTile[0][0]);

	InfectTile* top;
	int x;
	int y;
	//添加进队列
	while(!Tdeque.empty())
	{
		top = Tdeque.front();
		Tdeque.pop_front();
		x = top->getIndexX();
		y = top->getIndexY();
		//左
		if(x - 1 >= 0 && m_infectTile[y][x - 1]->getTileColor() == baseColor && !m_infectTile[y][x - 1]->getInQueue())
		{
			m_infectTile[y][x - 1]->setInQueue(true);
			Tdeque.push_back(m_infectTile[y][x - 1]);
		}
		//右
		if(x + 1 < m_countSize && m_infectTile[y][x + 1]->getTileColor() == baseColor && !m_infectTile[y][x + 1]->getInQueue())
		{
			m_infectTile[y][x + 1]->setInQueue(true);
			Tdeque.push_back(m_infectTile[y][x + 1]);
		}
		//上
		if(y + 1 < m_countSize && m_infectTile[y + 1][x]->getTileColor() == baseColor && !m_infectTile[y + 1][x]->getInQueue())
		{
			m_infectTile[y + 1][x]->setInQueue(true);
			Tdeque.push_back(m_infectTile[y + 1][x]);
		}
		//下
		if(y - 1 >= 0 && m_infectTile[y - 1][x]->getTileColor() == baseColor && !m_infectTile[y - 1][x]->getInQueue())
		{
			m_infectTile[y - 1][x]->setInQueue(true);
			Tdeque.push_back(m_infectTile[y - 1][x]);
		}
	}
	for(int i = 0 ; i < m_countSize ; ++ i)
		for(int j = 0 ; j < m_countSize ; ++ j)
		{
			if(m_infectTile[i][j]->getInQueue())
			{
				m_infectTile[i][j]->setDelayCount(i + j);
				m_infectTile[i][j]->setTileColor(c);
			}
			m_infectTile[i][j]->setInQueue(false);
		}

	++ m_stepCount;

	m_step->setString(CCString::createWithFormat("Step : %d / %d\nLevel : %d",m_stepCount,m_maxStep,m_level)->getCString());

	if(checkOver())
	{
		putTileTogether();
		m_isGameOver = true;
	}
}

bool InfectMode::checkOver()
{
	InfectTileColor c = m_infectTile[0][0]->getTileColor();
	for(int i = 0 ; i < m_countSize ; ++ i)
		for(int j = 0 ; j < m_countSize ; ++ j)
		{
			if(m_infectTile[i][j]->getTileColor() != c)
			{
				return false;
			}
		}
	return true;
}

void InfectMode::restartGame()
{
	for(int i = 0 ; i < m_countSize ; ++ i)
	{
		for(int j = 0 ; j < m_countSize ; ++ j)
		{
			m_infectTile[i][j]->setPosition(Vec2(m_baseX + j * m_squareSize,m_baseY + i * m_squareSize));
		}
	}

	++ m_level;
	if(m_level == 101)
		return ;

	FileUtils * fu = FileUtils::getInstance();
	auto doc = new tinyxml2::XMLDocument();
	doc->Parse(fu->getStringFromFile("InfectMode/level/easy.xml").c_str());
	auto root = doc->RootElement();
	auto e = root->FirstChildElement();

	auto c1 = e->FirstChildElement();
	auto c2 = c1->NextSiblingElement();

	m_baseX = std::atoi(c1->GetText());
	m_baseY = std::atoi(c2->GetText());

	int r = rand() % 2;

	int a[10][10];

	for(e = e->NextSiblingElement();e != NULL;e = e->NextSiblingElement())
	{
		std::string s = "l";
		s += CCString::createWithFormat("%d",m_level)->getCString();
		if((std::string)e->Value() == s)
			break;
	}

	if(e != NULL)
	{
		int ans = 2;
		if(m_stepCount <= m_maxStep)
			ans = 1;

		int i = 1;
		auto attr = e->FirstAttribute();
		auto fir = e->FirstChildElement();
		const char* temp = fir->GetText();

		for(int j = 0 ; temp[j] ; ++ j)
			a[0][j] = temp[j] - '0';

		for(fir = fir->NextSiblingElement() ; fir != NULL ; fir = fir->NextSiblingElement())
		{
			const char* t = fir->GetText();
			for(int j = 0 ; t[j] ; ++ j)
				a[i][j] = t[j] - '0';
			++ i;
		}
	}

	for(int i = 0 ; i < m_countSize ; ++ i)
	{
		for(int j = 0 ; j < m_countSize ; ++ j)
		{
			m_infectTile[i][j]->setTileColor((InfectTileColor)a[i][j]);
		}
	}

	m_stepCount = 0;
	m_step->setString(CCString::createWithFormat("Step : %d / %d\nLevel : %d",m_stepCount,m_maxStep,m_level)->getCString());
}

void InfectMode::putTileTogether()
{
	for(int i = 0 ; i < m_countSize ; ++ i)
	{
		for(int j = 0 ; j < m_countSize ; ++ j)
		{
			m_infectTile[i][j]->runAction(Sequence::create(DelayTime::create(0.8f),MoveTo::create(0.5f,Vec2(360,640)),NULL));
		}
	}
}