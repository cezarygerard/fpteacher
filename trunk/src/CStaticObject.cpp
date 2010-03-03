/** @file CStaticObject.cpp
* @author Sebastian Luczak
* @date 2010.03.03
* @version 0.6
 
* @brief klasa CStaticObject jest klasa elementow mozliwych do wyswietlenia na ekranie, nie bedacych encja
*	
*/


#include "CStaticObject.hpp"

using namespace std;


//konstruktor 
//@param trzy liczby float
CStaticObject::CStaticObject(float x, float y, float z, const string& filename, int position, int distance): x_(x), y_(y), z_(z)
{
	spriteHandle_ = CSpriteMgr::getInstance()->getCSprite(filename);
	
	cout<<"CStaticObject::CStaticObject: tworzenie zakończone sukcesem"<<endl;
}

CStaticObject::~CStaticObject()
{
	cout<<"CStaticObject::~CStaticObject: niszczenie"<<endl;
}

//woluje metode rysowania
bool CStaticObject::drawIt()
{
	CVideoSystem::getInstance()->drawCSprite(x_,y_,CSpriteMgr::getInstance()->getCSpritePtr(spriteHandle_));
	return true;
}

void CStaticObject::updatePosition(const float x, const float y, const float z)
{	
	x_ = x;
	y_ = y;
	if( z != 905382.f)
		z_ = z;
}

//~~CStaticObject.cpp
