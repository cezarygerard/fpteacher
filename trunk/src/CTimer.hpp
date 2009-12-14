/**
* @author Czarek Zawadka
* @date 2009.12.12
* @version 0.1_draft
* @brief klasa CTimer pozwala  klasom implementuj�cym interfejs CTimerObserver na dost�p do timera z SDL'a. CTimer to singleton
*	korzystanie z CTimer polega na wywolaniu klasy addObserver i cieszeniu sie z dok�adnego odmierzania czasu, 
*	gdy ju� si� nacieszymy mo�na wywo�a� removeObserver
*	
* @todo dodanie parametru metody addObserver oznaczaj�ce funkcj� wywo�ywan� gdy zostanie odmierzony zadany czas
*/

#ifndef CTIMER_H
#define CTIMER_H

#include <map>
#include "CSingleton.hpp"
#include "CTimerObserver.hpp"
#include  "SDL.h"
using namespace std;

class CTimerObserver;

class CTimer : public CSingleton<CTimer>
{
	friend CSingleton<CTimer>;

public:

	///rejestrowanie obserwatora. Pocz�tek odmierzania czasu jest natychmiasowy
	void addObserver(CTimerObserver& o, int interval);	
	///usuwanie obserwatora
	void removeObserver(const CTimerObserver& o);
	
	//void start(const CTimerObserver& o);
	//void stop(const CTimerObserver& o);

	///wska�nik na t� metod� jest argumentem funkcji SDL_AddTimer(), tutaj realizowane jest powiadamianie obserwator�w
	///@param interval - odmierzany czas
	///@param param - wska�nik na obserwatora dla kt�rego odmierzany jest czas
	static Uint32 timerCallback(Uint32 interval, void* param);

private:

	///Konstruktor domyslny
	CTimer();
	///Destruktor
	~CTimer();
	///kontener przechowuj�cy obserwator�w
	map<int, CTimerObserver *> observers_;
	///klucz do mapy observers_, dodanie obserwatora inkrementuje id_ o jeden dla kolenych obserwatorow
	static int id_;
};

#endif

