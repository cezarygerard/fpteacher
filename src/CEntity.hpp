/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* @brief klasa CEntity jest blas� bazow� dla element�w, kt�re mozna wy�wietli� na ekranie
*	
* @todo zrobi� z tej klasy klas� abstrakcyj�
* @todo sprawi� �eby do odrysowania wykorzysta� CVideoSystem 
* 
*/
#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "CSprite.hpp"
#include "CWorld.hpp"

using namespace std;
 
class CSprite;

class CEntity
{
public:

//	CEntity();
	///konstruktor
	CEntity(float x, float y,	float z, const string& filename);
	virtual ~CEntity();
	virtual void draw();
	float getX() const;
	float getY() const;
	float getZ() const;
	float getHeight() const;
	float getWidth() const;
//	bool operator<(const CEntity& e2 ) const;///potrzebny, aby w CWorld mozna by�o uzywa� std::set


protected:
	///wskaznik shared_ptr na CSprite odpowiadajacy danej CEntity
	boost::shared_ptr<CSprite> sprite_;
	///wspolrzedna x'owa - os X przebiega z lewej do prawej
	float x_;
	///wspolrzedna y'owa - os Y przebiega z gory na dol
	float y_;
	///pseudo-wspolrzedna oznaczajaca bufor Z
	float z_;
//	float width_;
//	float height_;
	
};

///potrzebny, aby w CWorld mozna by�o uzywa� std::set
bool operator<(const CEntity& e1, const CEntity& e2 );


#endif