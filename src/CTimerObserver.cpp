#include "CTimerObserver.hpp"

///destruktor powoduje wyrejestrowanie sie z obserwatorow CTimer'a. je�li ju� to zosta�o zrobione 
///to nic z�ego nie powinno sie zdarzyc
CTimerObserver::~CTimerObserver()
{
	std::cout<<"CTimerObserver::~CTimerObserver: niszczenie"<<std::endl; 
	CTimer::getInstance()->removeObserver(*this);
		
}
