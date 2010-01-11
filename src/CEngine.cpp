/** @file CEngine.cpp
* @author Rafal Malinowski
* @date 2009.12.07
* @version 0.1_draft
* @brief klasa CEngine odpowiada za poprawne dzialanie silnika gry
*	
*		
*/

/// @FESTER -> Zmienilem CEntity na Static i Dynamic

#include "CEngine.hpp"

using namespace std;

///konstruktor domyslny
CEngine::CEngine()
{
	refresh_flag = false;
	// Ziarno dla funkcji pseudolosowej
	srand( static_cast<int>( SDL_GetTicks() ) );
	cout << "CEngine::CEngine(): konstruktor domyslny" << endl;
}


///destruktor
CEngine::~CEngine()
{
	cout << "CEngine::~CEngine(): niszczenie" << endl;
}

///metoda w ktorej odpalany jest sdl, oraz uruchamiane sa konstruktory wielu klas (COGLWindow, CInput itd...)
bool CEngine::init()
{
	//Odpala SDLa
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
		cout << "CEngine::init(): nie udalo sie uruchomic SDLa" << endl;
        return false;
    }
	//odpalenia singletonu inputa
	CInput* Input = CInput::getInstance();
	//odpalenia singletonu CWorld
	CWorld* CWorld = CWorld::getInstance();

	//odpalenia singletonu COGLa
	COGLWindow* COGLWindow = COGLWindow::getInstance();
	COGLWindow::getInstance()->createDisplay();

	//odpalenie singletonu CVideoSystem
	CVideoSystem* CVideoSystem = CVideoSystem::getInstance();
	
	//
	CStaticEntity* splash = new CStaticEntity(0,0,0,"..\\res\\graphics\\sprites\\auditorium\\teacher\\main.png");
	CWorld::getInstance()->draw();
	COGLWindow::getInstance()->update();
	//odpalenie singletonu CAudioSystem
	CAudioSystem* CAudioSystem = CAudioSystem::getInstance();

	//odpalenie singletonu manager'a sprite'ow
	CSpriteMgr* SpriteMgr = CSpriteMgr::getInstance();

	//odpalenie singletonu manager'a animacji
	CAnimationMgr * CAnimationMgr = CAnimationMgr::getInstance();
 
	//odpalenie singletonu timer'a
	CTimer* timer = CTimer::getInstance();
	CTimer::getInstance()->addObserver(*this, 1000/utils::FPS);

	//odpalenie singletonu CAuditorium
	CAuditorium::getInstance()->initFromXml();

	// odpalenie singletonu GUI
	CGui::getInstance()->initGui();
	//CAuditorium::getInstance()->init(true);
	//CAuditorium::getInstance()->seatNewStudent(4,1, 0);


	return true;
}

///metoda posiadajaca glowna petle programu
void CEngine::start()
{
	CMusic* muza1 = new CMusic("muzyka1", "..\\res\\music\\Track01.mp3");
	//CMusic* muza2 = new CMusic("muzyka2", "..\\res\\music\\Track02.mp3");
	//CMusic* muza3 = new CMusic("muzyka3", "..\\res\\music\\Track03.mp3");
	CSound* dzwiek = new CSound(1, "dzwiek1", "..\\res\\sounds\\Comic_Msg.wav");
	CSound* dzwiek2 = new CSound(2, "ziomek", "..\\res\\sounds\\siemasz_ziomek.wav");
	CSound* dzwiek3 = new CSound(3, "dzien_dobry", "..\\res\\sounds\\dzien_dobry.wav");
	bool quit=false;
	mouse_quit_flag_=false;
	refresh_flag=true;
	refresh_enable=false;
	int time;
	int time1;
	while(!quit)
	{
		if(mouse_quit_flag_) quit=true;
		time = CTimer::getInstance()->getTime();
		CInput::getInstance()->update();
		CWorld::getInstance()->draw();
		COGLWindow::getInstance()->update();
		CNetwork::getInstance()-> handleNetwork();
		if(CInput::getInstance()->getKeyState(KEY_q) == true) quit=true;
		//if(CInput::getInstance()->getKeyState(KEY_m) == true) CAudioSystem::getInstance()->play_music("muzyka1");
		//if(CInput::getInstance()->getKeyState(KEY_n) == true) CAudioSystem::getInstance()->pause_music("muzyka1");
		//if(CInput::getInstance()->getKeyState(KEY_b) == true) CAudioSystem::getInstance()->stop_music("muzyka1");
		if(CInput::getInstance()->getKeyState(KEY_s) == true) CAudioSystem::getInstance()->play_sound("dzwiek1");
		//if(CInput::getInstance()->getKeyState(KEY_d) == true) CAudioSystem::getInstance()->play_sound("ziomek");
		if(CInput::getInstance()->getKeyState(KEY_z) == true) CAudioSystem::getInstance()->set_sound_position("dzwiek1", 270, 128);
		if(CInput::getInstance()->getKeyState(KEY_x) == true) CAudioSystem::getInstance()->set_sound_position("dzwiek1", 0, 0);
		if(CInput::getInstance()->getKeyState(KEY_c) == true) CAudioSystem::getInstance()->set_sound_position("dzwiek1", 90, 220);
		//if(CInput::getInstance()->getKeyState(KEY_1) == true) CAuditorium::getInstance()->seatNewStudent((CTimer::getInstance()->getTime())%5,(CTimer::getInstance()->getTime())%8,(CTimer::getInstance()->getTime())%8);	
	//	if(CInput::getInstance()->getKeyState(KEY_2) == true) CNetwork::getInstance()-> handleNetwork();
		refresh_enable=false;
		
		
		
		
		time1 = CTimer::getInstance()->getTime()-time;
		if(time1<1000/utils::FPS)
			CTimer::getInstance()->delay((1000/utils::FPS) - time1);
		
		//SDL_Delay(1000/utils::FPS);
	}

}

///metoda odpowiedzialna za zamykanie SDLa oraz ewentualne aktywowanie destruktorow roznych klas
void CEngine::end()
{
	refresh_flag=false;
	//niszczy GUI
	CGui::destroyInstance();
	//niszczy singleton inputa
	CInput::destroyInstance();
	// niszczy CAuditoirum
	CAuditorium::destroyInstance();
	//niszczy singleton CWorld
	CWorld::destroyInstance();
	//niszczy singleton CAudioSystem
	CAudioSystem::destroyInstance();
	//niszczy singleton managera zasobow
	CAnimationMgr::destroyInstance();
	//niszczy singleton managera zasobow
	CSpriteMgr::destroyInstance();
	//niszczy system wyswietlania
	CVideoSystem::destroyInstance();
	//zamyka okno
	COGLWindow::getInstance()->closeDisplay();
	//niszczy singleton COGLa
	COGLWindow::destroyInstance();
	//niszczy Timer
	CTimer::destroyInstance();
	//zamyka SDLa
	SDL_Quit(); 

}

/// metoda dziedziczona po obserwatorze CTimerObserver, decydujaca w ktorym momencie ma nastapic refresh aplikacji
void CEngine::refresh()
{
	if(refresh_flag)
	{
		refresh_enable=true;
	}

}

void CEngine::setMouseQuitFlag(bool quit)
{
	mouse_quit_flag_=quit;
}

//~~CEngine.cpp