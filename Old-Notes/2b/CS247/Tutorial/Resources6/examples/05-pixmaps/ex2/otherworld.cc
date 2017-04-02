#include "otherworld.h"

// Sets the horizontal box to have homogeneous spacing (all elements are of the same size), and to put 10 pixels
// between each widget. Initializes the pixel buffer for the null place holder card, and the 10 of spades.
// Puts a frame in the window, and lays out the widgets horizontally. Four widgets are images, the fifth is a button
// with an image in it.
//
// Since widgets cannot be shared, must use pixel buffers to share images.
OtherWorld::OtherWorld() : hbox( true, 10 ) {
    nextCard = 0;
    nextSuit = (Suits) 0;
    nextFace = (Faces) 0;
		
	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf     = deck.getCardImage( TEN, SPADE );
	
	// Sets the border width of the window.
	set_border_width( 10 );
		
	// Set the look of the frame.
	frame.set_label( "Cards:" );
	frame.set_label_align( Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP );
	frame.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
	
	// Add the frame to the window. Windows can only hold one widget, same for frames.
	add( frame );
	
	// Add the horizontal box for laying out the images to the frame.
	frame.add( hbox );
	
	// Initialize 4 empty cards and place them in the box.
	for (int i = 0; i < 5; i++ ) {
		card[i] = new Gtk::Image( nullCardPixbuf );
		hbox.add( *card[i] );
	} // for
	
	// Initialize the 5th card and place the image into the button.
//	card[4] = new Gtk::Image( cardPixbuf );	
	button.set_image( *card[4] );	

    // Attach event listener to button
    button.signal_clicked().connect(sigc::mem_fun( *this, &OtherWorld::onButtonClicked));
			
	// Add the button to the box.
	hbox.add( button );
	
	// The final step is to display this newly created widget.
	show_all();
} // OtherWorld::OtherWorld

OtherWorld::~OtherWorld() {
	for (int i = 0; i < 5; i++ ) delete card[i];
} // OtherWorld::~OtherWorld()

void OtherWorld::onButtonClicked()
{
    card[nextCard]->set(deck.getCardImage(nextFace, nextSuit));

    nextCard = (nextCard+1) % 4;
    if( (nextFace+1) == 6)
    {
        nextFace = (Faces) 0;
        nextSuit = (Suits) ((nextSuit + 1) % 4);
    }
    else
    {
        nextFace = (Faces) (nextFace+1);
    }
}
