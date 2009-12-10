/**
* @author Sebastian �uczak
* @date 2009.12.08
* @version 0.1_draft
* @brief naglowek dolaczajacy pozostale pliki naglowkowe
*	
*		
*/

#ifndef GLOBALS_H
#define GLOBALS_H
#include <iostream>
#include <string>
#include <cassert>

// naglowki boost
//#include <boost/smart_ptr.hpp>

// naglowki SDL
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//naglowki OpenGL
#include <windows.h>
#include <GL/gl.h>	
#include <GL/glu.h>	
//naglowki klas aplikacji
#include "CSingleton.hpp"
#include "CInput.hpp"
#include "CEngine.hpp"
//#include "CEntity.hpp"
#include "COGLWindow.hpp"

//naglowki dodatkowe
#include "keys.hpp"
using namespace std;
#endif