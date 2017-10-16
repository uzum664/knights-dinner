#ifndef _Journal_H
#define _Journal_H
// -------------------------------------------------------------------------
#include "TreeView.h"

namespace knights
{

	class Journal : public TreeView
	{
		public:
			Journal();
			explicit Journal(TreeView::BaseObjectType* gobject);
			virtual ~Journal();
			
		protected:
			virtual void init_treeview();

		private:
			void constructor();

			DISALLOW_COPY_AND_ASSIGN(Journal);
	};

}
#endif
