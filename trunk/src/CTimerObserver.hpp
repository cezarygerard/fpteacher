/**
* @author Czarek Zawadka
* @date 2009.12.12
* @version 0.1_draft
* @brief klasa CTimerObserver to interfejs dla klas korzystających z CTimer
*	
*	
*/

#ifndef CTIMER_OBSERVER_H
#define CTIMER_OBSERVER_H

#include "CTimer.hpp"
#include "SDL.h"
#include <iostream>

class CTimerObserver{
	///potrzebme aby CTimer mogl sie dobierać do prywatnych skladowych tej klasy
	friend class CTimer;				

//protected:
protected:
	/// jedyna metoda jaką powinna implementować kalsa dziedziczaca po tym interfejsie	
	virtual void refresh()=0;
	virtual ~CTimerObserver();

private:
	mutable SDL_TimerID timerId_;
	mutable int id_;

};
#endif