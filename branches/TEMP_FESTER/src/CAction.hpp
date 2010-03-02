/**\file
* @author Czarek Zawadka
* @date 2010.02.28
* @version 0.6
* @class CAction CAction.hpp 
* @brief Klasa bazowa dla wszystkich akcji wykonywanych przez gracza
*
* @todo zamienic asercje na sprytne testy z boosta
* @ todo przemyslec co powinno byc public
*/
#ifndef CACTION_HPP
#define CACTION_HPP

#include <string>
//#include "CLogic.hpp"
//#include "CConstants.hpp"
#include <cassert>

class CLogic;

using namespace std;

class CAction
{
	friend class CLogic;

public:

	CAction();
	
	CAction(string s);

protected:

	virtual bool performAction() = 0;
	
	//virtual CAction * create() = 0;
	
	//zrobic  z tego const??
	string name_;

	unsigned int manaCost_;
	
	unsigned int manaProfit_;

	unsigned int pointsProfit_;

	//czyja to jest akcja, 1 -teacher, 0-studenci
	bool whose_;

};
#endif