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
			
			int getMoveTimeout() { return 200; } // время на перемещение виджетов, 1 итерация, мс
			int getMoveSteps() { return 5; } // кол-во итераций перемещения виджетов за 1 дейтсвие
			
			typedef unsigned int ImageKey;
			typedef unsigned int ImagePosition;
			enum ImageType
			{
				KNIGHT_WAIT,
				KNIGHT_EAT,
				KNIGHT_TALK,
				FOOD_KNIFE,
				CUTTER_KNIFE
			};
			bool setKnight( const ImageKey& number, const ImageType& type );
			bool setKnife( const ImageKey& number, const ImageType& type );
			void moveKnife( const ImageKey& number, const ImagePosition& pos );
			void attachKnife( const ImageKey& knife_number, const ImageKey& knight_number );
			
		protected:
			void putKnight( const ImageKey& number, const ImagePosition& pos );
			void putKnife( const ImageKey& number, const ImagePosition& pos );
			void getPosition( int& x, int& y, const double& angle );
			
			struct ImageState
			{
				Gtk::Image* image;
				int x;
				int y;
				int curx;
				int cury;
				int step;
				int stepx;
				int stepy;
				sigc::connection conn;
				ImagePosition pos;
			};
			
			bool kineticMove( ImageState& knife );
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
			
			typedef std::map<ImageKey, ImageState> Images;
			Images knight_images_;
			Images knife_images_;
			unsigned int table_radius_;
			double angle_step_;
			int timeout;

			DISALLOW_COPY_AND_ASSIGN(RoundTable);
	};

}
#endif
