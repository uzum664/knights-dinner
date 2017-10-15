#ifndef _RoundTable_H
#define _RoundTable_H
// -------------------------------------------------------------------------
#include <gtkmm.h>
#include <map>
#include "gtk_macros.h"

namespace knights
{

	class RoundTable : public Gtk::Fixed
	{
		public:
			RoundTable();
			explicit RoundTable(Gtk::Fixed::BaseObjectType* gobject);
			virtual ~RoundTable();
			
			enum ImageType{
				KNIGHT_WAIT,
				KNIGHT_EAT,
				KNIGHT_TALK,
				FOOD_KNIFE,
				CUTTER_KNIFE
			};
			bool setKnight( const unsigned int& number, const ImageType& type );
			bool setKnife( const unsigned int& number, const ImageType& type );
			void swapKnifes( const unsigned int& number1, const unsigned int& number2 );
			void attachKnife( const unsigned int& knife_number, const unsigned int& knight_number );
			
		protected:
			void moveKnight( const unsigned int& number, const double& pos );
			void moveKnife( const unsigned int& number, const double& pos );
			void getPosition( int& x, int& y, const double& angle );
			virtual void on_size_allocate(Gtk::Allocation& alloc);
			virtual void on_realize();

		private:
			
			void constructor();
			void on_place_number_changed();
			
			ADD_PROPERTY( place_number, unsigned int )
			ADD_PROPERTY( knight_wait_image_path, Glib::RefPtr<Gdk::Pixbuf> )
			ADD_PROPERTY( knight_eat_image_path, Glib::RefPtr<Gdk::Pixbuf> )
			ADD_PROPERTY( knight_talk_image_path, Glib::RefPtr<Gdk::Pixbuf> )
			ADD_PROPERTY( food_knife_image_path, Glib::RefPtr<Gdk::Pixbuf> )
			ADD_PROPERTY( cutter_knife_image_path, Glib::RefPtr<Gdk::Pixbuf> )
			
			struct ImageState
			{
				Gtk::Image* image;
				int x;
				int y;
			};
			typedef std::map<unsigned int, ImageState> Images;
			Images knight_images_;
			Images knife_images_;
			unsigned int table_radius_;
			double angle_step_;

			DISALLOW_COPY_AND_ASSIGN(RoundTable);
	};

}
#endif
