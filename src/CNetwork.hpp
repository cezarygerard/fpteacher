/**
* @author Czarek Zawadka
* @date 2009.12.29
* @version 0.1_draft
* 
* @brief CNetwork to wstepna klasa odpowiedzialna za komunikacje sieciowa
*
* @todo przemyslec i zaimplementowac protokol komunikacji sieciowej - jakie obiekty, kiedy i jak przesylac przez siec.
* @todo wywolac handleNetwork() z silnika z zaimplementowanych schedulerem
* @todo zlikwidowac imlementacje CTimerObserver - sluzy tylko do celow demonstracyjnych
* @todo podzielic CNetwork tak, aby dzialalo w niezale�nych w�tkach
*/

#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <sstream>
#include <string>

#include "SDL_net.h"
#include "CSingleton.hpp"
#include "CTimerObserver.hpp"

class CNetwork : public CSingleton<CNetwork>, public CTimerObserver 
{
	friend CSingleton<CNetwork>;

public:
	
	int initNetwork(std::string peerIP, int port = 2010);
	void handleNetwork();
	virtual void refresh(int interval, SDL_TimerID timerIds);

private:

	CNetwork();
	~CNetwork();

	//czesc serwerowa:
	TCPsocket sd_, csd_; /* Socket descriptor, Client socket descriptor */
	IPaddress ip_, *remoteIP_;
//	int quit_, quit2_;
//	char buffer_[1024];
	SDLNet_SocketSet sockSet_;
	
	
	//czesc kliencka
//	IPaddress ipC_;		/* Server address */
//	TCPsocket sdC_;		/* Socket descriptor */
//	char bufferC_[1024];

	bool isClient;
};

#endif