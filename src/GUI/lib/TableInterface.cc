#include "TableInterface.h"
#include "Table/Place.h"
#include <iostream>
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
TableInterface* TableInterface::table_interface_ = NULL;
// -------------------------------------------------------------------------
TableInterface::TableInterface( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml ) :
	gui_table_(NULL)
{
	if( !gladexml )
	{
		cerr << "TableInterface(): Wrong glade!" << endl;
		throw;
	}
	gladexml->get_widget("roundtable1", gui_table_);
	if( !gui_table_ )
	{
		cerr << "TableInterface(): No 'roundtable1' in glade!" << endl;
		throw;
	}
	
	Table* table = Table::Instance();
	if( !table )
	{
		cerr << "TableInterface(): No table ???" << endl;
		throw;
	}
	// подключаем отложенную инициализацию
	gui_table_->signal_realize().connect( sigc::mem_fun( this, &TableInterface::init) );
	// цикл алгоритма обновления
	Glib::signal_timeout().connect( sigc::mem_fun( this, &TableInterface::poll ), getPollTimeout() );
}
// -------------------------------------------------------------------------
TableInterface::~TableInterface()
{
}
// -------------------------------------------------------------------------
TableInterface*  TableInterface::Instance( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml )
{
	if( !table_interface_ )
		table_interface_ = new TableInterface(gladexml);
	return table_interface_;
}
// -------------------------------------------------------------------------
void TableInterface::init()
{
	Table* table = Table::Instance();
	if( !table )
		return;
	// формируем массив knife_keys_, т.е. выстраиваем соответствие ножа своему спрайту (Knife* -> RoundTable::ImageKey)
	{
		RoundTable::ImageKey i = 0;
		for(Table::Knifes::iterator it = table->knifes_.begin() ; it != table->knifes_.end(); ++it, ++i )
		{
			if( dynamic_cast<FoodKnife*>(*it) )
			{
				// меняем картинку в соответствии с типом ножа
				gui_table_->setKnife(i, RoundTable::FOOD_KNIFE);
				ostringstream os;
				os << "TableInterface" << "() нож " << i << " для еды" <<  endl;
				cout << os.str();
			}
			else if( dynamic_cast<CutterKnife*>(*it) )
			{
				// меняем картинку в соответствии с типом ножа
				gui_table_->setKnife(i, RoundTable::CUTTER_KNIFE);
				ostringstream os;
				os << "TableInterface" << "() нож " << i << " для нарезки" <<  endl;
				cout << os.str();
			}
			knife_keys_[*it] = i;
		}
	}
}
// -------------------------------------------------------------------------
bool TableInterface::poll()
{
	Table* table = Table::Instance();
	if( !table )
		return true;
	
	// Проверяем и перемещаем ножи
	{
		RoundTable::ImagePosition i = 0;
		for(Table::Knifes::iterator it = table->knifes_.begin() ; it != table->knifes_.end(); ++it, ++i )
		{
			if( !*it )
				continue;
			
			gui_table_->moveKnife( knife_keys_[*it], i );
		}
	}
	// Проверяем и выводим состояние рыцаря
	{
		RoundTable::ImageKey i = 0;
		for( Table::Places::iterator it = table->places_.begin() ; it != table->places_.end(); ++it, ++i )
		{
			if( !*it )
				continue;
			// проверяем занято ли место рыцарем
			Knight* knight = reinterpret_cast<Knight*>((*it)->getOwner());
			if( !knight )
				continue;
			
			switch( knight->getState() )
			{
				case Knight::WAITING:
					gui_table_->setKnight(i, RoundTable::KNIGHT_WAIT);
					break;
				case Knight::EAT:
					gui_table_->setKnight(i, RoundTable::KNIGHT_EAT);
					break;
				case Knight::TALK:
					gui_table_->setKnight(i, RoundTable::KNIGHT_TALK);
					break;
			}
			
			// если ножи взяты в руки, двигаем поближе
			if( knight->hasLeftKnife() )
			{
				gui_table_->attachKnife( knife_keys_[*(*it)->getLeftKnife()], i);
				ostringstream os;
				os << "TableInterface" << "::poll() нож " << knife_keys_[*(*it)->getLeftKnife()] << " на месте" << i << " занят" <<  endl;
				//cout << os.str();
			}
			if( knight->hasRightKnife() )
			{
				gui_table_->attachKnife( knife_keys_[*(*it)->getRightKnife()], i);
				ostringstream os;
				os << "TableInterface" << "::poll() нож " << knife_keys_[*(*it)->getRightKnife()] <<  " на месте" << (i + 1) << " занят" <<  endl;
				//cout << os.str();
			}
		}
	}
	
	// не заканчиваем цикл вызова
	return true;
}
// -------------------------------------------------------------------------