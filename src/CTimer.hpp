/**
* @author Czarek Zawadka
* @date 2009.12.12
* @version 0.1_draft
* @brief klasa CTimer pozwala  klasom implementuj�cym interfejs CTimerObserver na dost�p do timera z SDL'a. CTimer to singleton
*	
* @page korzystanie 
*	Korzystanie z CTimer polega na wywolaniu klasy addObserver i cieszeniu sie z dok�adnego odmierzania czasu, 
*	gdy ju� si� nacieszymy mo�na wywo�a� removeObserver. 
*
* @page dzialanie 
*	Dzia�anie klasy CTimer polega na obudowaniu SDL'a. Wykorzystywana jest metoda SDL_AddTimer(Uint32 interval, SDL_NewTimerCallback callback, void* param),
*	kt�ra za�atwia wszystko. Parametry tej funkcji to: interval - odmierzany czas, callback - funkcja kt�ra ma 
*	zosta� wywo�ana po odliczeniu do ko�ca, param - argument z kt�rym ma by� wywolana funkcja callback. 
*	W CTimer zosta�a zdefiniowana funkcja timerCallback, ktora jest uzywana jako callback. Parametremi s�: interval(wymagane przez SDL) 
*	oraz  wska�nik na *	zainteresowanego CTimerObserver'a.
*
* @todo dodanie parametru metody addObserver oznaczaj�ce funkcj� wywo�ywan� gdy zostanie odmierzony zadany czas
* @todo wzbogacenie klasy o mozliwosc pauzowania timera
* @todo wzbogaci klasy CTimer oraz CTimerObserver tak, aby jedna instancja CTimerObserver mogla obserwowac
*	kilka roznych zegarow
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

	///wska�nik na t� metod� jest argumentem funkcji SDL_AddTimer(), tutaj realizowane jest 
	///powiadamianie obserwator�w @ref dzialanie
	
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

