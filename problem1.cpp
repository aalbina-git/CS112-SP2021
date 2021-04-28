#include <iostream>
#include "Animal.cpp"

using namespace std;

int main(){

    Animal Lion1(1,"African Lion", 25, 5);
    Animal Lion2(2,"African Lion", 26, 5);
    Animal Lion3(3,"African Lion", 27, 5);
    Animal Lion4(4,"African Lion", 28, 5);

    cout<<Lion1.getID() << " " << Lion1.getName() << Lion1.getCage() << endl;
    cout<<Lion2.getID() <<  " " << Lion1.getName() << Lion1.getCage() << endl;
    cout<<Lion3.getID() << " " <<Lion1.getName() << Lion1.getCage() << endl;
    cout<<Lion4.getID() << " " <<Lion1.getName() << Lion1.getCage() << endl;

    return 0;
}

