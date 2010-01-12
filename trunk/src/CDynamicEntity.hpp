/**\file
* @author Sebastian Luczak
* @date 2009.01.04
* @version 0.6
* @class CDynamicEntity CDynamicEntity.hpp
* @brief klasa CDynamicEntity jest klasa elementow posiadajacych animacje, mozliwych do wyswietlenia na ekranie
*	
*/
#ifndef CDYNAMICENTITY_H
#define CDYNAMICENTITY_H

#include <string>
#include <list>

#include "CEntity.hpp"
#include "CWorld.hpp"
#include "CAnimator.hpp"

using namespace std;
 
class CDynamicEntity : public CEntity
{
public:

	///konstruktor 
	///@param filename sciezka do ladowanego pliku
	///@param x wspolzedna x
	///@param y wspolzedna y
	///@param z wspolzedna z
	CDynamicEntity(float x, float y, float z, const string& filename);

	///destruktor
	virtual ~CDynamicEntity();

	///wyrysowanie (sprite'a z animacji) do bufora
	virtual void draw();


protected:
	///instancja animatora
	CAnimator animator_;
};


#endif

//~~CDynamicEntity.hpp
