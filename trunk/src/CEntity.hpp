/**
* @brief klasa CEntity jest abstrakcyjna blas� bazow� dla element�w, kt�re mozna wy�wietli� na ekranie
*
*
*/

#include <iostream>
#include <string>
using namespace std;
 

class CEntity
{
public:
	void draw(void);
	virtual ~CEntity(void); 


private:
//	CSprite sprite_;

};