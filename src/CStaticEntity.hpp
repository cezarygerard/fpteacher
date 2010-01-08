/**
* @author Sebastian Luczak
* @date 2009.01.04
* @version 0.1_draft
* 
* @brief klasa CStaticEntity jest klasa elementow statycznych, ktore mozna wyswietlac
*	
*/
#ifndef CSTATICENTITY_H
#define CSTATICENTITY_H

#include <string>
#include "CEntity.hpp"
#include "CWorld.hpp"
#include "CVideoSystem.hpp"
#include "CSpriteMgr.hpp"

using namespace std;
 

class CStaticEntity : public CEntity
{
public:

	///konstruktor 
	///@param trzy liczby float
	CStaticEntity(float x, float y,	float z, const string& filename);
	///destruktor
	virtual ~CStaticEntity();
	///wyrysowanie (spite'a) do bufora
	virtual void draw();
	///wysokosci (spite'a)
	float getHeight() const;
	///szerokosc (spite'a)
	float getWidth() const;


protected:
	///uchwyt do sprite'a
	HCSprite spriteHandle_;

};


#endif
