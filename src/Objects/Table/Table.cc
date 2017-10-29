#include "Table.h"
#include "Knife.h"
#include "Place.h"
#include "Configuration.h"
#include <iomanip>
#include <cstdlib>
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
Table* Table::inst = NULL;
//---------------------------------------------------------------------------------------
Table* Table::Instance( const int& num )
{
	// вызов Instance с параметром num происходит из Алгоритма (см Dinner.h)
	// поэтому принудительно пересоздаем
	if( inst )
		inst->Destroy();
	if( inst == NULL )
		inst = new Table(num);
	return inst;
}
//---------------------------------------------------------------------------------------
Table* Table::Instance()
{
	if( inst == NULL )
		inst = new Table(0);
	return inst;
}
//---------------------------------------------------------------------------------------
void Table::Destroy()
{
	if(inst)
		delete inst;
	inst = NULL;
}
//---------------------------------------------------------------------------------------
Table::Table( const int& num )
{
	for( int i = 0; i < num; ++i)
	{
		Place* place = new Place(this);
		place->num_ = (i + 1);
		// если было пусто за столом, то сразу добавляем 2 ножа
		if( places_.empty() )
		{
			// в списке 1ый нож = левый нож у 1ого рыцаря
			place->left_knife_ = addKnife("food");
			place->right_knife_ = addKnife("cutter");
		}
		else
		{
			Place* first = places_.front();
			Place* last = places_.back();
			// если было одно место, 3ий нож пока не нужен
			if( last != first )
				last->right_knife_ = addOtherKnife( last->left_knife_ );
			place->right_knife_ = first->left_knife_;
			place->left_knife_ = last->right_knife_;
		}
		places_.push_back(place);
	}
}
//---------------------------------------------------------------------------------------
Table::~Table()
{
	for( Knifes::iterator it = knifes_.begin() ; it != knifes_.end(); ++it )
		if( *it )
			delete *it;
	for( Places::iterator it = places_.begin() ; it != places_.end(); ++it )
		if( *it )
			delete *it;
}
//---------------------------------------------------------------------------------------
Place* Table::findFreePlace() const
{
	for( Places::const_iterator it = places_.begin() ; it != places_.end(); ++it )
		if( *it && !(*it)->isBusy() )
			return *it;
	return NULL;
}
//---------------------------------------------------------------------------------------
Table::Knifes::iterator Table::addKnife( const std::string& type )
{
	Knife* knife;
	if( type == "cutter" )
		knife = new CutterKnife();
	else if( type == "food" )
		knife = new FoodKnife();
	if( knife )
		knifes_.push_back(knife);
	for( Knifes::iterator it = knifes_.begin() ; it != knifes_.end(); ++it )
		if( *it == knife )
			return it;
	return knifes_.end();
}
//---------------------------------------------------------------------------------------
Table::Knifes::iterator Table::addOtherKnife( const Knifes::iterator it )
{
	if( dynamic_cast<CutterKnife*>(*it) )
		return addKnife("food");
	if( dynamic_cast<FoodKnife*>(*it) )
		return addKnife("cutter");
	return knifes_.end();
}
//---------------------------------------------------------------------------------------
bool Table::take( Table::Knifes::iterator it )
{
	if( it == knifes_.end() || !*it )
		return false;
	return (*it)->take();
}
//---------------------------------------------------------------------------------------
bool Table::put( Table::Knifes::iterator it )
{
	if( it == knifes_.end() || !*it )
		return false;
	return (*it)->put();
}
//---------------------------------------------------------------------------------------
bool Table::swapKnifes( Table::Knifes::iterator left, Table::Knifes::iterator right )
{
	Knife* right_knife = *right;
	*right = *left;
	*left = right_knife;
	return true;
}
//---------------------------------------------------------------------------------------
const std::string Table::textDraw() const
{
	// рисуем стол в текстовом виде (т.е. построчно вниз сразу сначала и с конца)
	std::ostringstream os;
	int size = knifes_.size();
	int max = size / 2;
	bool odd = size % 2;
	int k = 3;
	 // отступы что бы создать эффект круга
	int lspace = ( max - ( odd ? 0 : 1 ) ) * k;
	int cspace = 0;
	
	Table::Knifes::const_iterator kit = knifes_.begin();
	Table::Knifes::const_reverse_iterator rkit = knifes_.rbegin();
	Table::Places::const_iterator pit = places_.begin();
	Table::Places::const_reverse_iterator rpit = places_.rbegin();
	
	for( int i = 0; i < max ; ++i, ++pit, ++kit, ++rkit, ++rpit )
	{
		// рисуем левую часть стола
		os << std::setw(lspace) << "";
		os << std::setw(6) << *kit;
		os << std::setw(cspace) << "";
		os << std::setw(6) << (*rpit)->num_ << endl;
		
		// правим отступы на половине стола
		if( (lspace - k) < 0 )
		{
			// правим отступы для четного кол-ва мест 
			if( !odd )
			{
				lspace = lspace - k;
				cspace = cspace + 2*k;
			}
			k = abs(k) * (-1);
		}
		lspace = lspace - k;
		cspace = cspace + 2*k;
		
		// рисуем правую часть стола
		os << std::setw(lspace) << "";
		os << std::setw(6) << (*pit)->num_;
		os << std::setw(cspace) << "";
		os << std::setw(6) << *rkit << endl;
		
		// правим отступы на половине стола
		if( (lspace - k) < 0 )
		{
			// правим отступы для четного кол-ва мест 
			if( !odd )
			{
				lspace = lspace - k;
				cspace = cspace + 2*k;
			}
			k = abs(k) * (-1);
		}
		lspace = lspace - k;
		cspace = cspace + 2*k;
	}
	// если нечетное кол-во элементов, дорисовываем последнюю строку
	if( odd )
	{
		os << std::setw(lspace) << "";
		os << std::setw(6) << *kit;
		os << std::setw(cspace) << "";
		os << std::setw(6) << (*rpit)->num_ << endl;
	}
	return os.str();
}
//---------------------------------------------------------------------------------------
std::ostream& knights::operator<<(std::ostream& os, Table& table)
{
	return os << table.textDraw();
}
//---------------------------------------------------------------------------------------
std::ostream& knights::operator<<(std::ostream& os, Table* table)
{
	if( table )
		return os << *table;
	return os << "";
}
//---------------------------------------------------------------------------------------