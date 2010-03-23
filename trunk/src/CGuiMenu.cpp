/** @file CGuiMenu.cpp
* @author Sebastian Luczak
* @date 2010.03.03
* @version 0.1
 
* @brief klasa CGuiMenu opisuje wysuwane menu wyboru akcji
*	
*/


#include "CGuiMenu.hpp"

using namespace std;
using namespace logging;


//konstruktor 
//@param trzy liczby float
CGuiMenu::CGuiMenu() : slide_(boost::logic::indeterminate), visible_(false), x_(1000.f), y_(200.f)
{
	menuBackground_ = boost::shared_ptr<CStaticObject>( new CStaticObject(x_, y_, 300.f, utils::PATH_GUI+"sliding_menu.png", 0, 0));
	//inicjalizacja obserwatora myszy
	setId();
	CInput::getInstance()->
		addMouseObserver(*this, static_cast<int>(x_), static_cast<int>(x_+100), static_cast<int>(y_), static_cast<int>(y_+371) );
	moveObserver_=true;
	
	//siatka przyciskow --> do wyciagania z pliku konf
	//for(int x = 0; x < 2; x++)
	//	for(int y = 0; y < 4; y++)
	//		Pobierz jaka akcja, koszt i grafika
	//		CGuiMenuButton(52 + ( x * 90 ), y_ + 45 + ( y * 75 ), AKCJA, KOSZT, SPRITENAME);
	
	
	CConstants * cc = CConstants::getInstance();
	AcDesMap::iterator it = cc->actionsDesc_.begin();
	for(int x = 0; x < 2; x++)
		for(int y = 0; y < 4; y++)
		{
			if (it != cc->actionsDesc_.end())
			{
				if(static_cast<bool>((it->second.find("whose"))->second) == CLogic::getInstance()->getIsTeacher())
				{
					string actName = it->first;
					string spriteName;
					int cost = (it->second.find("manaCost"))->second;
					
					if(it->second.find("spriteExist") != it->second.end())
						spriteName = actName;
					else
						spriteName = "teach_chalk.png";
					
					buttons_.push_back(boost::shared_ptr<CGuiMenuButton>(new CGuiMenuButton(52, y_ + 45, cost, spriteName, actName)));
				}
				else
				{
						buttons_.push_back(boost::shared_ptr<CGuiMenuButton>(new CGuiMenuButton(52, y_ + 45, 0, "teach_chalk.png", "NULL")));
				}
				
				it++;
			}
		}
/*
	CConstants * cc = CConstants::getInstance();
	//manaCost_ = cc->actionsDesc_.f
	AcDesMap::iterator it = cc->actionsDesc_.find(ca.name_);
	//cout<<string(typeid(*this).name());
	assert(it != cc->actionsDesc_.end());
	std::map<string,unsigned int> * acMap = &(it->second);

	ca.manaCost_ = (it->second.find("manaCost"))->second;
	ca.manaProfit_ = (it->second.find("manaProfit"))->second;
	ca.pointsProfit_ = (it->second.find("pointsProfit"))->second;
	ca.whose_ =static_cast<bool>((it->second.find("whose"))->second);
*/

//	buttons_.push_back(boost::shared_ptr<CGuiMenuButton>(new CGuiMenuButton(52, y_ + 45, 20, "teach_chalk.png", actName)));
	
	CLog::getInstance()->sss << "CGuiMenu::CGuiMenu: tworzenie zakonczone sukcesem" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

CGuiMenu::~CGuiMenu()
{
	CLog::getInstance()->sss << "CGuiMenu::~CGuiMenu: niszczenie" << endl;
	logs(CLog::getInstance()->sss.str(), INFO);
}

void CGuiMenu::show()
{	
	slide_ = true;
}

void CGuiMenu::hide()
{	
	slide_ = false;
	BOOST_FOREACH( boost::shared_ptr<CGuiMenuButton> button, buttons_ )
	{
		button->hide();
	}
}

const bool CGuiMenu::isVisible() const
{
	return visible_;
}

void CGuiMenu::refresh(CMouseEvent * CMO)
{
	//puste
}

void CGuiMenu::drawIt()
{
	if(slide_)
	{///@todo Przerobic na stale (224, 800.f, 371.f itp)!!!
		visible_ = false;
		if(x_ >= 800.f)
		{
			x_ = x_ - 10.f;
			menuBackground_->updatePosition(x_, y_);
			CInput::getInstance()->removeMouseObserver(*this);
			CInput::getInstance()->addMouseObserver(*this, static_cast<int>(x_), static_cast<int>(x_+234), static_cast<int>(y_), static_cast<int>(y_+371) );
		}
		else
		{
			visible_ = true;
			BOOST_FOREACH( boost::shared_ptr<CGuiMenuButton> button, buttons_ )
			{
				button->show(x_);
			}
		}
	}
	else if(!slide_)
	{
		visible_ = false;
		if(x_ < 1000.f)
		{
			x_ = x_ + 10.f;
			menuBackground_->updatePosition(x_, y_);
			CInput::getInstance()->removeMouseObserver(*this);
			CInput::getInstance()->addMouseObserver(*this, static_cast<int>(x_), static_cast<int>(x_+100), static_cast<int>(y_), static_cast<int>(y_+371) );
		}
	}

	menuBackground_->drawIt();
	
	if(visible_)
	{
		slide_ = boost::logic::indeterminate;
		BOOST_FOREACH( boost::shared_ptr<CGuiMenuButton> button, buttons_ )
		{
			button->drawIt();
		}
	}
}

void CGuiMenu::mouseIsOver(bool over)
{
	if (over) 
		show();
	else  
		hide();
	setMoveIsOver(over);
}

//~~CGuiMenu.cpp
