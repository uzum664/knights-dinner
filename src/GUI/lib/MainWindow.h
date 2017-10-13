#ifndef _MainWindow_H_
#define _MainWindow_H_
// ------------------------------------------------------------------------------
#include <gtkmm.h>
// ------------------------------------------------------------------------------
namespace knights
{
	class MainWindow;
	extern MainWindow* gwindow;

	class MainWindow
	{
		public:
			static MainWindow* Instance(std::string gladedir, std::string guifile, std::string svgdir);
			Gtk::Window* w;
			
		protected:
			MainWindow(std::string gladedir, std::string guifile, std::string svgdir);
			MainWindow();
			~MainWindow();
			virtual void on_show();

		private:
			void draw_splash(const double& perc);

			double progress;
			Gtk::Window splash;
			Gtk::Alignment alignment;
			Gtk::ProgressBar bar;
	};
}
// ------------------------------------------------------------------------------
#endif // _MainWindow_H_
// ------------------------------------------------------------------------------
