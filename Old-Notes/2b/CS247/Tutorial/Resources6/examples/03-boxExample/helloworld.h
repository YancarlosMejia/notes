/*
 * Ch. 3 of "Programming with gtkmm", pp. 11-14
 *
 * Displays a labelled button in a window. When the button is clicked, the text "Hello World" is printed
 * to standard output.
 */

#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H
#include <string>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>

class HelloWorld : public Gtk::Window {
public:
	HelloWorld();
	virtual ~HelloWorld();
	
protected:
	// Signal handlers:
	virtual void onButtonClicked(std::string output);
	
	// Member widgets:
	Gtk::Label m_label;
	Gtk::Label m_label2;

	Gtk::Button m_button;
	Gtk::Button m_button2;

	Gtk::HBox m_hbox;
	Gtk::VBox m_vbox;
	Gtk::VBox m_vbox2;
}; // HelloWorld

#endif
