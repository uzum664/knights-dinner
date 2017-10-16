#include <iostream>
#include "Statistic.h"
#include "Configuration.h"
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
#define INIT_ROUNDTABLE_PROPERTIES() \

// -------------------------------------------------------------------------
void Statistic::constructor()
{
	cout << "Statistic::constructor()" << endl;
}
// -------------------------------------------------------------------------
Statistic::Statistic() :
	Glib::ObjectBase("statistic")
	//,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
Statistic::Statistic( TreeView::BaseObjectType* gobject ) :
	TreeView(gobject)
	//,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
Statistic::~Statistic()
{
}
// -------------------------------------------------------------------------
void Statistic::init_treeview()
{
	if(tree_model_ref_)
		return;
	TreeView::init_treeview();
}
// -------------------------------------------------------------------------
