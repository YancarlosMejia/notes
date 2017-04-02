/*
 * Ch. 3 of "Programming with gtkmm", pp. 11-14
 *
 * Displays a labelled button in a window. When the button is clicked, the text "Hello World" is printed
 * to standard output.
 */

#include "helloworld.h"
#include <iostream>
#include <gtkmm/stock.h>

// Creates a new button with the label "Hello World".
HelloWorld::HelloWorld() : m_label("Hello!"), m_label2("Goodbye!"), 
m_button( "Hello World" ), m_button2(Gtk::Stock::OK) {
        
	// Sets the border width of the window.
	set_border_width( 30 );
    
	add( m_hbox );
	
	// When the button receives the "clicked" signal, it will call 
    // the onButtonClicked() method defined below.
	m_button.signal_clicked().connect(sigc::bind(
                sigc::mem_fun( *this, &HelloWorld::onButtonClicked ), 
                "Howdy Mother Goose!" ));
	m_button2.signal_clicked().connect(sigc::bind(
                sigc::mem_fun( *this, &HelloWorld::onButtonClicked ), 
                "OK!" ));
	
	
    // Add the vertical boxes to the horizontal box
    m_hbox.pack_start(m_vbox);
    m_hbox.pack_end(m_vbox2);

    
    m_vbox.pack_end(m_button);
    m_vbox.pack_end(m_label);

    m_vbox2.pack_start(m_label2);
    m_vbox2.pack_start(m_button2);

    //show_all();

    m_button.show();
    m_label.show();
    m_vbox.show();

    m_button2.show();
    m_label2.show();
    m_vbox2.show();

    m_hbox.show();
} // HelloWorld::HelloWorld

HelloWorld::~HelloWorld() {}

void HelloWorld::onButtonClicked(std::string output) {
	std::cout << output << std::endl;
} // HelloWorld::onButtonClicked
