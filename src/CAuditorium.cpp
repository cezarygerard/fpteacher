/**@file CAuditorium.cpp
* @author Czarek Zawadka
* @date 2010.01.04
* @version 0.1_draft
* 
* @brief klasa CAuditorium przedstawia sale
* 
* klasa CAuditorium przedstawia sale, sklada sie z z pol CField, odpowiedzialna jest za za ladowanie sali na poczatku
*	gry a takze, za dodawanie studentow na sale. Sale mozna serializowac i deserializowac wywolujac metody initFromXml()
*	saveToXml() lub przez archiwa z boost::serializable. Mozna zmienic plik xml opisujacy sale - .\res\XML\CAuditorium.xml
*	klasa jest singletonem 
*
* @todo przemyslec udostpnianie informacji o polach innym klasom
* @todo przemysle wspolprace z CInput
* @todo stworzyc flage bool initiated blokujaca initFromXml() oraz deserializacje gdy wywolany init(bool teacher) i na odwrot
* @todo dodac prawdzanie xml - pol CField powinno byc 40 (COLUMNS * ROWS)
* @todo sprawdzic wycieki (dotyczy tez innych klas ;)
* @todo rozna inicjalizacje grafik dla nauczycieli/studentow
* @todo serializacja/deserializacja parametrow(proporcji) pliku graficznego sali,
*	tak aby calkowita zmiana pliku nie powodowala potrzeby ponownej kompilacji
*/

#include "CAuditorium.hpp"

const float CAuditorium::MARGIN = 0.0143f;
const float CAuditorium::TAB =  0.0119f;
const float CAuditorium::CUT_OFF = 1.0f;

CAuditorium::CAuditorium() 
				: fields_(boost::extents[ROWS][COLUMNS]), teacher_(false)
{
	cout<<"CAuditorium::CAuditorium() tworzenie"<<endl;
}

CAuditorium::~CAuditorium() 
{
	
	cout<<"CAuditorium::~CAuditorium() nieszczenie"<<endl;
}
 
void CAuditorium::initFromXml()
{
	std::ifstream ifs("..\\res\\XML\\CAuditorium.xml");
    boost::archive::xml_iarchive ia(ifs);
	CAuditorium * ca = CAuditorium::getInstance();
	ia>>BOOST_SERIALIZATION_NVP(ca);
	ifs.close();	   
}

void CAuditorium::init(bool teacher)
{
	new CStaticEntity(1.0, 1.0, 0.0, "..\\res\\graphics\\sprites\\auditorium\\audmain01.png");
	new CStaticEntity(9.0, 585.0, 60.0, "..\\res\\graphics\\sprites\\auditorium\\audmid01.png");	
	CStaticEntity * rows[] ={new CStaticEntity(28.0, 471.0, 50.0, "..\\res\\graphics\\sprites\\auditorium\\row1.png"),
							new CStaticEntity(46.0, 366.0, 40.0, "..\\res\\graphics\\sprites\\auditorium\\row2.png"),
							new CStaticEntity(63.0, 269.0, 30.0, "..\\res\\graphics\\sprites\\auditorium\\row3.png"),
							new CStaticEntity(79.0, 179.0, 20.0, "..\\res\\graphics\\sprites\\auditorium\\row4.png"),
							new CStaticEntity(95.0, 96.0, 10.0, "..\\res\\graphics\\sprites\\auditorium\\row5.png")
							};
	teacher_ = teacher;
	float currentX;  
	float currentY; 
	float currentZ;
	float h;
	float w;
	for(int j = 0; j<ROWS; j++)
	{
		h = rows[j]->getHeight() * CUT_OFF ;
		w = (rows[j]->getWidth() - ((COLUMNS - 1) * TAB + 2 * MARGIN) * rows[j]-> getWidth())/COLUMNS;
		currentX = rows[j]->getX() + MARGIN * rows[j]->getWidth();
		currentY = rows[j]->getY();
		currentZ = rows[j]->getZ();

		for (int i = 0; i<COLUMNS;i++)
		{
			boost::shared_ptr<CField> ptr(new CField(currentX, currentY, currentZ, w, h, j,	i));
			fields_[j][i] = ptr;
			currentX += w +  TAB * rows[j]->getWidth();
		}
	}
	
}
void CAuditorium::saveToXml()
{ 
	std::ofstream ofs("..\\res\\XML\\CAuditorium.xml");
	boost::archive::xml_oarchive oa(ofs);
	CAuditorium * ca = CAuditorium::getInstance();
	oa<<BOOST_SERIALIZATION_NVP(ca);
	ofs.close(); 
}

void CAuditorium::loadStaticEntities()
{
	new CStaticEntity(1.0, 1.0, 0.0, "..\\res\\graphics\\sprites\\auditorium\\audmain01.png");
	new CStaticEntity(9.0, 585.0, 60.0, "..\\res\\graphics\\sprites\\auditorium\\audmid01.png");	
	new CStaticEntity(28.0, 471.0, 50.0, "..\\res\\graphics\\sprites\\auditorium\\row1.png");
	new CStaticEntity(46.0, 366.0, 40.0, "..\\res\\graphics\\sprites\\auditorium\\row2.png");
	new CStaticEntity(63.0, 269.0, 30.0, "..\\res\\graphics\\sprites\\auditorium\\row3.png");
	new CStaticEntity(79.0, 179.0, 20.0, "..\\res\\graphics\\sprites\\auditorium\\row4.png");
	new CStaticEntity(95.0, 96.0, 10.0, "..\\res\\graphics\\sprites\\auditorium\\row5.png");
							
}
//
bool CAuditorium::seatNewStudent(int row, int col,string filename, string type)
{

//	boost::shared_ptr<CField> cf(fields_[at.first][at.second]);
	boost::shared_ptr<CField> cf(fields_[row][col]);
	if(cf->isFree_)
	{	
		if(type == "CDynamicEntity")	 
		{
			cf->entPtr_ = EntityPtr(		
			( new CDynamicEntity(cf->x_, cf->y_, cf->z_+0.1f, filename))->selfPtr_);
			cf->isFree_ = false;
			cf->isBusy_ = true;
			return true;
		}
		if(type == "CStaticEntity")	 
		{
			cf->entPtr_ = EntityPtr(		
							( new CStaticEntity(cf->x_, cf->y_, cf->z_+0.1f, filename))->selfPtr_); 
			cf->isFree_ = false;
			cf->isBusy_ = true;
			return true;
		}
	}
	return false;
}

//
bool CAuditorium::seatNewStudent(int row, int col, int type)
{
	switch(type)
	{
		case 0: 
			seatNewStudent(row,col,"..\\res\\graphics\\sprites\\students\\yawn_animset.dat", "CDynamicEntity");
			return true;
		case 1:
			seatNewStudent(row,col,"..\\res\\graphics\\sprites\\students\\boy2.png","CStaticEntity");
			return true;
		default:
			return false;
	
	}
}

