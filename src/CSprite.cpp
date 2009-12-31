/** @file CSprite.cpp
* @author Sebastian �uczak
* @date 2009.12.08
* @version 0.2_draft
* @brief Klasa sprite'a przydzielonego do Entity
* @todo Wydzielic loader plikow graficznych i zminimalizowac CSprite 
*/

#include "CSprite.hpp"

///Konstruktor z pliku o podanej sciezce
CSprite::CSprite(string filename) : 
    sSprite(new SDL_Surface),
    sAlpha(255)
{
	cout << "Konstruktor CSprite z pliku" << endl;
   openFile(filename);
}

/// Metoda otwierajaca plik graficzny.
/// Wywoluje metode przydzielajaca teksture i komplet parametrow CSprite
/// @param filename sciezka do pliku graficznego
void CSprite::openFile(string filename)
{
	boost::shared_ptr<SDL_Surface> image = utils::LoadImage( filename.c_str() );
	attachSprite(image);
}
/// Metoda przydzielajaca CSprite teksture i parametry na bazie powierzchni odczytanej z pliku
/// @param surface sprytny wskaznik na powierzchnie SDL
void CSprite::attachSprite(boost::shared_ptr<SDL_Surface> surface)
{
	utils::TexDims tex_dims;
	//na wszelki wypadek wyzeruj wszelkie parametry tekstury i sprite'a
	releaseSprite();		
	try{
	if (!surface.get())
		throw utils::BadFileError("CSprite::attachSprite(): Bledny parametr surface!");
	}
	catch (utils::BadFileError& x) {
		cerr << "BadFileError: " << x.what() << endl;
		throw;
	}

	//przypisz wartosci do pol CSprite
	sWidth = static_cast<float>(surface->w);
	sHeight = static_cast<float>(surface->h);
	
	//przetworz SDL_Surface na teksture OGL
	sTexID = utils::SurfaceToTexture(surface, tex_dims);
	//nadaj wymiary teksturze na podstawie wartosci z funckji SurfaceToTexture
	sTexDims = tex_dims;
	//ostatecznie przypisz sama powierzchnie do pola sSprite
	sSprite = surface;
}

///przeladowuje powierzchnie SDL
void CSprite::reloadSprite()
{
    //na wypadek potrzeby przeladowania sprite'a w oknie OGL
	boost::shared_ptr<SDL_Surface> toReload( 
						new SDL_Surface,
						boost::bind(&utils::SafeFreeSurface, _1)); 
	toReload = sSprite;	

    attachSprite(toReload);
}

/// Metoda zerujaca ustawienia sprite'a
void CSprite::releaseSprite()
{
	//przywr�� stan Sprite'a
	if(glIsTexture(sTexID))
		glDeleteTextures(1,&sTexID);
	sTexDims.texMaxX = sTexDims.texMaxY = sTexDims.texMinX = sTexDims.texMinY = 0.f;
	sTexID = 0;
	sWidth = sHeight = 0;
}
/// @return true jesli tekstura zaladowana do OGL
bool CSprite::isLoaded() const
{
	return glIsTexture(sTexID) == GL_TRUE;
}

/// @return powierzchnia SDL CSprite
boost::shared_ptr<SDL_Surface> CSprite::getSprite() const
{
	return sSprite;
}

/// @return szerokosc sprite'a (float)
float CSprite::getSpriteWidth() const
{
	return static_cast<float>(sWidth);
}

/// @return wysokosc sprite'a (float)
float CSprite::getSpriteHeight() const
{
	return static_cast<float>(sHeight);
}

/// @return alpha sprite'a (int)
int CSprite::getSpriteAlpha() const
{
	return static_cast<int>(sAlpha);
}

/// @return ID Textury OGL (unsigned int)
unsigned int CSprite::getTexID() const
{
	return sTexID;
}

/// @return znormalizowane wymiary tekstury (utils::TexDims)
utils::TexDims CSprite::getTexDimensions() const
{ 
	return sTexDims;
}

//~~CSprite.cpp