/** @file CAudioSystem.cpp
* @author Rafal Malinowski
* @date 2009.12.18
* @version 0.1_draft
* @brief klasa CAudioSystem bedzie odpowiedzialna za odtwarzanie wszystkich dzwiekow i muzyki
*	
*		
*/

#include "CAudioSystem.hpp"
using namespace std;

///Konstruktor Domyslny
CAudioSystem::CAudioSystem()
{
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	int audio_channels = 2;
	int audio_buffers = 512;


  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    cout <<"Unable to open audio!\n" << endl << endl;
	cout << Mix_GetError() << endl << endl;
	 }
}

///Destruktor Domyslny
CAudioSystem::~CAudioSystem()
{
	musics_.clear();
	sounds_.clear();
}

/// Metoda dodajaca muzyke do zbioru "musics_"
/// @param music referencja do muzyki ktora ma zostac dodana do zbioru "musics_"
void CAudioSystem::addMusic(const CMusic & music)
{
	//Jezeli muzyka juz istnieje
	//to kolejna nie zostanie dodana do CAudioSystem
	if(musics_.find(music) == musics_.end())
		{
		musics_.insert(music);
		cout << "	CAudioSystem::addMusics: dodano muzyke do CAudioSystem" << endl;
		}
	else 
		cout<<"		CAudioSystem::addMusics: muzyka juz istnieje \n";
}

/// Metoda dodajaca dzwiek do zbioru "sounds_"
/// @param sound referencja do dzwieku ktory ma zostac dodany do zbioru "sounds_"
void CAudioSystem::addSound(const CSound & sound)
{
	//Jezeli muzyka juz istnieje
	//to kolejna nie zostanie dodana do CAudioSystem
	if(sounds_.find(sound) == sounds_.end())
		{
		sounds_.insert(sound);
		cout << "	CAudioSystem::addSounds: dodano dzwiek do CAudioSystem" << endl;
		}
	else 
		cout<<"		CAudioSystem::addSounds: dzwiek juz istnieje \n";
}

/// Metoda sluzaca do wlaczenia muzyki
/// @param nickname nazwa muzyki jaka ma byc puszczona
void CAudioSystem::play_music(string nickname)
{
	cout << "wcisnieto play_music();" << endl;
	set<CMusic>::iterator it; 
  for ( it=musics_.begin() ; it != musics_.end(); it++ ) 
  {
	  if(it->GetNickname() == nickname) 
	  {
		  it->Play(); 
		  cout << "znaleziono muzyke" << endl;
	  }
  }
}

/// Metoda sluzaca do wstrzymania muzyki
/// @param nickname nazwa muzyki jaka ma byc wstrzymana
void CAudioSystem::pause_music(string nickname)
{
	cout << "wcisnieto pause_music();" << endl;
	set<CMusic>::iterator it; 
  for ( it=musics_.begin() ; it != musics_.end(); it++ ) 
  {
	  if(it->GetNickname() == nickname) 
	  {
		  it->Pause(); 
		  cout << "znaleziono muzyke" << endl;
	  }
  }
}

/// Metoda sluzaca do zatrzymania muzyki
/// @param nickname nazwa muzyki jaka ma byc zatrzymana
void CAudioSystem::stop_music(string nickname)
{
	cout << "wcisnieto stop_music();" << endl;
	set<CMusic>::iterator it; 
  for ( it=musics_.begin() ; it != musics_.end(); it++ ) 
  {
	  if(it->GetNickname() == nickname) 
	  {
		  it->Stop(); 
		  cout << "znaleziono muzyke" << endl;
	  }
  }
}

/// Metoda sluzaca do wlaczenia dzwieku
/// @param nickname nazwa dzwieku jaki ma byc puszczony
void CAudioSystem::play_sound(string nickname)
{
	cout << "wcisnieto play_sound();" << endl;
	set<CSound>::iterator it; 
  for ( it=sounds_.begin() ; it != sounds_.end(); it++ ) 
  {
	  if(it->GetNickname() == nickname) 
	  {
		  it->Play(); 
		  cout << "znaleziono dzwiek" << endl;
	  }
  }
}

/// Metoda sluzaca do ustawienia pozycji z ktorej ma byc odgrywany dzwiek (3D)
/// @param nickname nazwa dzwieku ktorego pozycja ma byc ustalona
/// @param polozenie kat z ktorego bedzie slychac dzwiek (0 - przed nami, 90 - z prawej, 180 - z tylu, 270 - z lewej)
void CAudioSystem::set_sound_position(string nickname, Sint16 polozenie)
{
	cout << "wcisnieto zmiane polozenia dla dzwieku " << nickname << endl;
	set<CSound>::iterator it; 
  for ( it=sounds_.begin() ; it != sounds_.end(); it++ ) 
  {
	  if(it->GetNickname() == nickname) 
	  {
		  it->SetAngle(polozenie); 
		  cout << "zmieniono polozenie dzwieku" << endl;
	  }
  }
}