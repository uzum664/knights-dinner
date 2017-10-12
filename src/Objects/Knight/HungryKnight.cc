#include "HungryKnight.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
HungryKnight::HungryKnight( const std::string& name, const int& hunger, const double& power ) :
	Knight(name)
	,hunger_power_( (power > 0) ? power : 0.01)
{
	hunger_ = hunger;
}
//---------------------------------------------------------------------------------------
HungryKnight::~HungryKnight()
{
}
//---------------------------------------------------------------------------------------
void HungryKnight::tellStory()
{
	Knight::tellStory();
	hunger_++; 
}
//---------------------------------------------------------------------------------------
void HungryKnight::eat()
{
	int hunger = hunger_;
	Knight::eat();
	hunger_ = hunger - (1 / hunger_power_);
}
//---------------------------------------------------------------------------------------