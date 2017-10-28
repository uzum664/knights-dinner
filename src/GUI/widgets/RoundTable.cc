#include <iostream>
#include <gdkmm.h>
#include <math.h>
#include <librsvg/rsvg.h>
#include "RoundTable.h"
#include "Configuration.h"
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
#define INIT_ROUNDTABLE_PROPERTIES() \
	place_number(*this, "place-number", 5) \
	,knight_wait_image_path(*this, "knight-wait-image-path", Glib::RefPtr<Gdk::Pixbuf>()) \
	,knight_eat_image_path(*this, "knight-eat-image-path", Glib::RefPtr<Gdk::Pixbuf>()) \
	,knight_talk_image_path(*this, "knight-talk-image-path", Glib::RefPtr<Gdk::Pixbuf>()) \
	,food_knife_image_path(*this, "food-knife-image-path", Glib::RefPtr<Gdk::Pixbuf>()) \
	,cutter_knife_image_path(*this, "cutter-knife-image-path", Glib::RefPtr<Gdk::Pixbuf>()) \
	,table_radius_(50)
// -------------------------------------------------------------------------
void RoundTable::constructor()
{
	cout << "RoundTable::constructor()" << endl;
	connect_property_changed("place-number", sigc::mem_fun( *this, &RoundTable::on_place_number_changed ));
	on_place_number_changed();
}
// -------------------------------------------------------------------------
RoundTable::RoundTable() :
	Glib::ObjectBase("roundtable")
	,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
RoundTable::RoundTable( Gtk::Fixed::BaseObjectType* gobject ) :
	Gtk::Fixed(gobject)
	,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
RoundTable::~RoundTable()
{
	for( Images::iterator it = knight_images_.begin(); it != knight_images_.end(); ++it )
		if( it->second.image )
			delete it->second.image;
	for( Images::iterator it = knife_images_.begin(); it != knife_images_.end(); ++it )
		if( it->second.image )
			delete it->second.image;
}
// -------------------------------------------------------------------------
void RoundTable::on_place_number_changed()
{
	// расчитываем минимальный шаг вокруг стола
	// при этом рыцари сидят друг от друга на 4 * angle_step_
	angle_step_ = 2 * M_PI / ( get_place_number() * 4 );
	
	int size = knight_images_.size();
	for( Images::iterator it = knight_images_.begin(); it != knight_images_.end(); ++it )
		if( it->second.image )
			delete it->second.image;
	for( Images::iterator it = knife_images_.begin(); it != knife_images_.end(); ++it )
		if( it->second.image )
			delete it->second.image;
	knight_images_.clear();
	knife_images_.clear();
	for( int i = 0; i < get_place_number(); ++i )
	{
		knight_images_[i].image = new Gtk::Image( get_knight_wait_image_path() );
		knife_images_[i].image = new Gtk::Image( get_food_knife_image_path() );
		put(*knight_images_[i].image, 0, 0);
		put(*knife_images_[i].image, 0, 0);
		moveKnight( i, i );
		moveKnife( i, i );
		knight_images_[i].image->show();
		knife_images_[i].image->show();
		knight_images_[i].label = new Gtk::Label();
		put(*knight_images_[i].label, 0, 0);
		knight_images_[i].label->hide();
	}
}
// -------------------------------------------------------------------------
void RoundTable::on_size_allocate(Gtk::Allocation& alloc)
{
	Gtk::Fixed::on_size_allocate(alloc);
	int width = alloc.get_width();
	int height = alloc.get_height();
	
	if( width > height )
		table_radius_ = height - 18;
	else
		table_radius_ = width - 18;
	//cout << "RoundTable::on_size_allocate()" << " table_radius_=" << table_radius_ << endl;
}
//-----------------------------------------------------------------------------------------------------
void RoundTable::on_realize()
{
	Gtk::Fixed::on_realize();
	cout << "RoundTable::on_realize()" << endl;
	for( int i = 0; i < get_place_number(); ++i )
	{
		setKnight( i, KNIGHT_WAIT );
		setKnife( i, FOOD_KNIFE );
		moveKnight( i, i );
		moveKnife( i, i );
	}
}
// -------------------------------------------------------------------------
bool RoundTable::setKnightName( const ImageKey& number, const std::string& name )
{
	if( number >= get_place_number() )
		return false;
	if( !knight_images_[number].label )
		return false;
	knight_images_[number].label->set_text( name );
	// после присвоения имени сдвигаем Рыцаря
	// так как в нем расчитываются новые координаты Имени с учетом высоты и длины label
	moveKnight(number, number);
	knight_images_[number].label->show();
	return true;
}
// -------------------------------------------------------------------------
bool RoundTable::setKnight( const ImageKey& number, const ImageType& type )
{
	if( number >= get_place_number() )
		return false;
	switch( type )
	{
		case KNIGHT_WAIT:
			knight_images_[number].image->set( get_knight_wait_image_path() );
			break;
		case KNIGHT_EAT:
			knight_images_[number].image->set( get_knight_eat_image_path() );
			break;
		case KNIGHT_TALK:
			knight_images_[number].image->set( get_knight_talk_image_path() );
			break;
		default:
			return false;
	}
	return true;
}
// -------------------------------------------------------------------------
bool RoundTable::setKnife( const ImageKey& number, const ImageType& type )
{
	if( number >= get_place_number() )
		return false;
	switch( type )
	{
		case FOOD_KNIFE:
			knife_images_[number].image->set( get_food_knife_image_path() );
			break;
		case CUTTER_KNIFE:
			knife_images_[number].image->set( get_cutter_knife_image_path() );
			break;
		default:
			return false;
	}
	return true;
}
// -------------------------------------------------------------------------
void RoundTable::moveKnight( const ImageKey& number, const ImagePosition& pos )
{
	getPosition( knight_images_[number].x, knight_images_[number].y, angle_step_ * 4 * pos );
	move( *knight_images_[number].image, knight_images_[number].x, knight_images_[number].y );
	// Имя выводим выше и посередине
	if( knight_images_[number].label )
	{
		int x = knight_images_[number].x - knight_images_[number].label->get_width() / 2;
		int y = knight_images_[number].y - knight_images_[number].label->get_height() - 3; // на 3 пикселя выше спрайта
		move( *knight_images_[number].label, x, y );
	}
}
// -------------------------------------------------------------------------
void RoundTable::moveKnife( const ImageKey& number, const ImagePosition& pos )
{
	getPosition( knight_images_[number].x, knight_images_[number].y, angle_step_ * 4 * pos - angle_step_ * 2 );
	move( *knife_images_[number].image, knight_images_[number].x, knight_images_[number].y );
	
	if( knife_images_[number].pos != pos )
	{
		ostringstream os;
		os << "RoundTable" << "::moveKnife() нож " << number << " передали на место " << pos <<  endl;
		cout << os.str();
	}
	
	knife_images_[number].pos = pos;
}
// -------------------------------------------------------------------------
void RoundTable::getPosition( int& x, int& y, const double& angle )
{
	x = table_radius_ + table_radius_ * cos(angle + M_PI / 2);
	y = table_radius_ - table_radius_ * sin(angle + M_PI / 2);
}
// -------------------------------------------------------------------------
void RoundTable::attachKnife( const ImageKey& knife_number, const ImageKey& knight_number )
{
	double knife_angle = angle_step_ * 4 * knife_images_[knife_number].pos  - angle_step_ * 2;
	double knight_angle = angle_step_ * 4 * knight_number;
	
	if( ( knight_angle - knife_angle ) > M_PI )
		knife_angle -= angle_step_;
	else if( knight_angle > knife_angle )
		knife_angle += angle_step_;
	else
		knife_angle -= angle_step_;
	
	int x,y;
	getPosition( x, y, knife_angle );
	move( *knife_images_[knife_number].image, x, y );
}
// -------------------------------------------------------------------------
