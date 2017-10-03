#include "Place.h"
#include "Knife.h"
#include "Configuration.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
Place::Place( Table* table ) :
	table_(table)
	,busy_(false)
	,num_(0)
{
}
//---------------------------------------------------------------------------------------
Place::Place()
{
	throw Exception( "Place(): попытка создать место без привязки к столу" );
}
//---------------------------------------------------------------------------------------
Place::~Place()
{
}
//---------------------------------------------------------------------------------------
Table::Knifes::iterator Place::getLeftKnife() const
{
	return left_knife_;
}
//---------------------------------------------------------------------------------------
Table::Knifes::iterator Place::getRightKnife() const
{
	return right_knife_;
}
//---------------------------------------------------------------------------------------
bool Place::swapKnifes()
{
	return table_->swapKnifes( left_knife_ , right_knife_ );
}
//---------------------------------------------------------------------------------------
bool Place::isKnifesDifferent()  const
{
	if( dynamic_cast<CutterKnife*>(*right_knife_) && dynamic_cast<CutterKnife*>(*left_knife_) )
		 return false;
	if( dynamic_cast<FoodKnife*>(*right_knife_) && dynamic_cast<FoodKnife*>(*left_knife_) )
		 return false;
	return true;
}
//---------------------------------------------------------------------------------------
std::ostream& knights::operator<<(std::ostream& os, Place& place)
{
	//return os << *place.left_knife_<< "(" << std::hex << (int)*place.left_knife_ << ")" << "-" << place.num_ << "-" << *place.right_knife_ << "(" << std::hex << (int)*place.right_knife_ << ")";
	return os << place.num_;
}
//---------------------------------------------------------------------------------------
std::ostream& knights::operator<<(std::ostream& os, Place* place)
{
	if( place )
		return os << *place;
	return os << "";
}
//---------------------------------------------------------------------------------------