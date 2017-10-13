#ifndef _PLUGINS_H
#define _PLUGINS_H

template<class Type>
extern Type* uwrap(GObject* object, bool take_copy=false)
{
  return dynamic_cast<Type*> (Glib::wrap_auto((GObject*)(object), take_copy));
}

template<class Type> extern Glib::ObjectBase* Obj_Wrap_New(GObject* o)
{
	return manage(new Type(( typename Type::BaseObjectType* )(o)));
}

template<class Type> extern GType Obj_Get_Type()
{
static GType gtype = 0;
	if (!gtype) {
		Type* dummy = new Type();
		gtype = G_OBJECT_TYPE(dummy->gobj());
		delete( dummy );
		Glib::wrap_register(gtype, &Obj_Wrap_New<Type>);
	}
	return gtype;
}
/* Функция, которая меняет порядок инициализации, вызывая Wrap_New перед выставлением свойств виджета. Без этого свойства виджета,
   определенные в классе, не выставляются значениями из glade файла.
*/
template<class Type> static void custom_set_property_callback(GObject * object, unsigned int property_id, const GValue * value, GParamSpec * param_spec)
{
	if( !Glib::ObjectBase::_get_current_wrapper(object) )
		Obj_Wrap_New<Type>(object);
        Glib::ObjectBase *const wrapper = Glib::ObjectBase::_get_current_wrapper(object);
        if (!wrapper)
                return;
        Type *renderer = dynamic_cast<Type *>(wrapper);
        if (!renderer)
                return;
	Glib::custom_set_property_callback(object,property_id,value,param_spec);
}

#endif
