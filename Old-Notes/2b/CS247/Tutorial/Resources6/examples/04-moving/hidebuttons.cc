#include "hidebuttons.h"
#include <iostream>
#include <gtkmm/stock.h>

HideButtons::HideButtons() : table(10, 10, true) {
	for (int i = 0; i < 100; i++) {
		buttons[i].set_label("Ha");
	}
        
	// Sets the border width of the window.
	set_border_width( 0 );
	set_default_size(500, 500);
    
	add( table );
	
	for (int i = 0; i < 100; i++) {
      buttons[i].signal_clicked().connect(
                sigc::mem_fun( *this, &HideButtons::onButtonClicked ));
      buttons[i].signal_enter().connect(
                sigc::mem_fun( *this, &HideButtons::onButtonEnter ));
      table.attach(buttons[i], i % 10, (i % 10) + 1, i / 10, (i / 10) + 1);
	}
	
	buttons[0].show();
	index = 0;
	
	table.show();
}

HideButtons::~HideButtons() {}

void HideButtons::onButtonClicked() {
	std::cout << "You got me!" << std::endl;
}

void HideButtons::onButtonEnter() {
	buttons[index].hide();
	index = (index + 1) % 100;
	buttons[index].show();
}
