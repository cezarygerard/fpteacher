/**\file
* @author Sebastian luczak
* @date 2009.12.08
* @version 0.2_draft
* @class CVideoSystem CVideoSystem.hpp
* @brief Klasa jest odpowiedzialna za wyswietlanie w oparciu o OpenGL i operacje przeksztalcen sprite'ow
*	
*/

#ifndef	CVIDEOSYSTEM_H
#define CVIDEOSYSTEM_H

#include <iostream>
#include <string>
#include <cassert>

//naglowki OpenGL
#if defined(_WIN32) 
#include <windows.h> 
#endif
#include <GL/gl.h>	
#include <GL/glu.h>	

//naglowki klas aplikacji
#include "CSingleton.hpp"
#include "COGLWindow.hpp"
#include "CSprite.hpp"
#include "CInput.hpp"
#include "utils.hpp"

using namespace std;

class CSprite;

class CVideoSystem : public CSingleton<CVideoSystem>
{
	friend class CSingleton<CVideoSystem>;
	
public:
	///Metoda wiazaca teksture sprite'a z OGL
	/// @param sprite sprite do doczepienia
	void bindTexture(const CSprite& sprite) const;

	///FESTER
	void drawCSprite(const float x,const float y, const CSprite* sprite ) const;

	void hideCursor();

	void drawMouseCursor();

	/// Zamienia bufory obrazu (aktualizuje wyswietlany obraz)
	void update();

private:
	///Konstruktor domyslny
	CVideoSystem();
	///Destruktor
	~CVideoSystem();
};

#endif

//~~CVideoSystem.hpp
