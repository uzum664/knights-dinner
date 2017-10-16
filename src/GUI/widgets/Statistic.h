#ifndef _Statistic_H
#define _Statistic_H
// -------------------------------------------------------------------------
#include "TreeView.h"

namespace knights
{

	class Statistic : public TreeView
	{
		public:
			Statistic();
			explicit Statistic(TreeView::BaseObjectType* gobject);
			virtual ~Statistic();
			
		protected:
			virtual void init_treeview();

		private:
			void constructor();

			DISALLOW_COPY_AND_ASSIGN(Statistic);
	};

}
#endif
