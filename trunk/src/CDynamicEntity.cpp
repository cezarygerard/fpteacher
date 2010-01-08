/** @file CEntity.cpp
* @author Sebastian Luczak
* @date 2009.01.04
* @version 0.1_draft
 
* @brief klasa CDynamicEntity jest klasa elementów posiadajacych animacje, mozliwych do wyswietlenia na ekranie
*	
*/


#include "CDynamicEntity.hpp"

using namespace std;


///konstruktor 
///@param trzy liczby float
CDynamicEntity::CDynamicEntity(float x, float y, float z, const string& filename)
{
	x_=x;
	y_=y;
	z_=z;
	
	//if(&filename != NULL)
	animationHandle_ = CAnimationMgr::getInstance()->getCAnimation(filename);
	cout << "ANIMACJA STWORZONA!!" << endl;
	///Encja sama dodaje sie do CWorld
	CWorld::getInstance()-> addEntity(*this);
	cout<<"CDynamicEntity::CDynamicEntity: tworzenie zakończone sukcesem"<<endl;
}

CDynamicEntity::~CDynamicEntity(void)
{
//	CWorld::getInstance()-> removeEntity(*this);
	cout<<"CDynamicEntity::~CDynamicEntity: niszczenie"<<endl;
}

///woluje metode rysowania
void CDynamicEntity::draw()
{
	CVideoSystem::getInstance()->animateCAnimation(x_,y_,CAnimationMgr::getInstance()->getCAnimationInstance(animationHandle_));
}



//~~CDynamicEntity.cpp
