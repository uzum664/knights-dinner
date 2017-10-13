#ifndef _GLOBAL_MACROS_H
#define _GLOBAL_MACROS_H

/* A macro to disallow the copy constructor and operator= functions.
 * This should be used in the private: declarations for a class.
 * For more info see http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
private: \
	TypeName(const TypeName&);               \
	TypeName& operator=(const TypeName&)


/* Macro for Gtk properties definition in classes */
#define ADD_PROPERTY(name, type) \
protected: \
	Glib::Property<type> name; \
public: \
	void set_ ## name(type value) {name.set_value(value);} \
	type get_ ## name() {return name.get_value();} \
  Glib::PropertyProxy<type> proxy_ ## name(){return name.get_proxy();}

#define ADD_TRANSPROPERTY(name, type) \
protected: \
	TransProperty<type> name; \
public: \
	void set_ ## name(type value) {name.set_value(value);} \
	type get_ ## name() {return name.get_value();}

#endif

//   Glib::PropertyProxy_ReadOnly<type> property_ ## name(){return Glib::PropertyProxy_ReadOnly<type>(this,"name");} const
