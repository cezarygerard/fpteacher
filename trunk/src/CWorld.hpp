/**
* @author Czarek Zawadka
* @date 2009.12.06
* @version 0.1_draft
* @brief klasa CWorld reprezentuje ca�y �wiat gry, jest singletonem.
*	
* @todo sprawi� �eby do odrysowania wykorzysta� CVideoSystem 
* @todo przemysle zarzadzanie CEntity -  kto powinien wywolywac konstruktory, 
*	kto powinien dodawac i usuwac CEntity ze swiata gry 
*/

#ifndef	WORLD_H
#define WORLD_H

#include <set>
#include <iostream>
#include <string>
#include "CEntity.hpp"
#include "CSingleton.hpp"

using namespace std; 
 
class CEntity;

class CWorld : public CSingleton<CWorld>
{
	friend CSingleton<CWorld>;

public:

	///odrysowuje wszystkie CEntity
	void draw();	

	///odgrywa d�wi�k we wszystkich CEntity
	void play();			

	///dodaje CEntity do wewn�trznego kontenera, metoda (poki co) wolana przez ka�d� CEntity w konstruktorze
	void addEntity(const CEntity& entity);		

	///usuwa CEntity z wewn�trznego kontenera, wywoluje destruktor CEntity
	void removeEntity(CEntity&);	

private:
	///kontener zawierajacy wszystkie CEntity ze �wiata
	set<CEntity> entities_;
	///konstruktor
	CWorld();
	///destruktor
	~CWorld();

};
#endif
