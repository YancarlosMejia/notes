#include "Pasta.h"
#include "Inventory.h"
#include "PastaFactory.h"
#include "PenneFactory.h"
#include "RigatoniFactory.h"
#include "RavioliFactory.h"
#include "Penne.h"
#include "Rigatoni.h"
#include "Ravioli.h"
#include <iostream>

using namespace std;

void inventorySummary (Inventory inventory){
    cout<< "Inventory: " << endl;
	cout<< "-->Total Cash Available: " << inventory.getCash() << endl;
	cout<< "-->Total Dough Available: " << inventory.getDough() << endl;
	cout<< "-->There are currently " << inventory.lookup("penne") << " Penne in the inventory." << endl;
    cout<< "-->There are currently " << inventory.lookup("ravioli") << " Ravioli in the inventory." << endl;
    cout<< "-->There are currently " << inventory.lookup("rigatoni") << " Rigatoni in the inventory." << endl << endl;
}


void askInput(Inventory inventory){
    int choice;
    cin >> choice;
    cout << endl;
    if (choice == 2){
        inventorySummary(inventory);
    }
    else if (choice == 3){
       // exit(1);
    }
}

int main(){

    cout << "|-------------------------------------------------|" << endl;
    cout << "|  ---------------------------------------------- |" << endl;
    cout << "|  |  WELCOME TO THE                            | |" << endl;
    cout << "|  |            PASTA FACTORY!!!                | |" << endl;
    cout << "|  ---------------------------------------------- |" << endl;
    cout << "|-------------------------------------------------|" << endl << endl;

    cout << "Here you can create and purchase a variety of pasta that includes Penne, Rigatoni and Ravioli." << endl;
    cout << "Dough can be purchased at 2 kg for $1. Pasta is sold for the following prices: Box of Penne - $2, Box of Ravioli - $5, Box of Rigatoni - $1. The following demo will ilustrate how this application works." << endl << endl;
    cout << "Any time you are promted, Press 1 to continue the demo. Press 2 to view an updated summary of the inventory. Press 3 to quit the demo." << endl << endl;

    //Create the inventory
    Inventory *inventory1 = new Inventory();
	inventory1->setCash(1000);
	inventory1->buyDough(1000);
    inventorySummary(*inventory1);

    //Creaste 100 Penne Pasta pieces
    PastaFactory *p1 = new PenneFactory();
    Pasta* pasta1 = p1->create(1, *inventory1, 100);
    cout<< "ACTION: 100 Pieces of Penne pasta are made!" << endl;
    cout<< pasta1->getDesc()<< endl << endl;
    askInput(*inventory1);

    //Creaste 100 Ravioli Pasta pieces
    PastaFactory *p2 = new RavioliFactory;
    Pasta* pasta2 = p2->create(2, *inventory1, 50);
    cout<< "ACTION: 50 Pieces of Ravioli pasta are made!" << endl;
    cout<< pasta2->getDesc()<< endl << endl;
    askInput(*inventory1);

    PastaFactory *p3 = new RigatoniFactory;
    Pasta* pasta3 = p3->create(3, *inventory1, 10);
    cout<< "ACTION: 10 Pieces of Rigatoni pasta are made!" << endl;
    cout<<pasta3->getDesc()<< endl << endl;
    askInput(*inventory1);


    PastaFactory *p4 = new PenneFactory;
    Pasta* pasta4 = p4->create(1, *inventory1, 100);
    cout<< "ACTION: 100 Pieces of Penne pasta are made!" << endl;
    cout<< pasta4->getDesc()<<  endl << endl;
    askInput(*inventory1);

    cout<< "ACTION: 50 Pieces of Penne pasta are sold!" << endl;
	inventory1->sellPasta(pasta1,50);
    askInput(*inventory1);

	cout<< "ACTION: 40 Pieces of Ravioli pasta are sold!" << endl;
	inventory1->sellPasta(pasta2,40);
    askInput(*inventory1);

	cout<< "ACTION: 10 Pieces of Rigatoni pasta are sold!" << endl;
	inventory1->sellPasta(pasta3,10);
    askInput(*inventory1);

	cout<< "ATTEMPTED ACTION: 15 Pieces of Ravioli pasta are sold!" << endl;
    inventory1->sellPasta(pasta2,15);
    askInput(*inventory1);

    cout<< "ACTION: Buy 1000 kg of dough" << endl;
	inventory1->buyDough(1000);
    askInput(*inventory1);

	cout<< "ATTEMPTED ACTION: Buy another 1000 kg of dough" << endl;
    inventory1->buyDough(1000);

    cout << endl << "END OF DEMO! WE HOPE YOU LIKED OUR PASTA FACTORY!" << endl << endl;
    cout << "///////////////////////////////////////////////////" << endl;
    inventorySummary(*inventory1);
    cout << "///////////////////////////////////////////////////" << endl;

}
