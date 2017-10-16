#include <iostream>
#include "Journal.h"
#include "Configuration.h"
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
#define INIT_ROUNDTABLE_PROPERTIES() \

// -------------------------------------------------------------------------
void Journal::constructor()
{
	cout << "Journal::constructor()" << endl;
	columns_ = &journal_columns_;
}
// -------------------------------------------------------------------------
Journal::Journal() :
	Glib::ObjectBase("journal")
	//,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
Journal::Journal( TreeView::BaseObjectType* gobject ) :
	TreeView(gobject)
	//,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
Journal::~Journal()
{
}
//-----------------------------------------------------------------------------------------------------
void Journal::init_treeview()
{
	if(tree_model_ref_)
		return;
	TreeView::init_treeview();
}
// -------------------------------------------------------------------------
