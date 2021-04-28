#include "Animal.cpp"
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> split(string, char);
void printAnimals(vector<Animal*>);
int displayMenu();
vector<Animal*> getAnimals(char size, vector<Animal*>);
vector<Animal*> getAnimals(int id,vector<Animal*>);
vector<Animal*> getAnimals(int num, char containment_type,vector<Animal*>);
vector<Animal*> getHungryAnimals(vector<Animal*>);
vector<Animal*> getTBWeighed(int cur_year, vector<Animal*>);
void displayAnimals(vector<Animal*>selected, vector<int>values);

int main(){

    string line;
    int line_count=0, choice;
    vector <Animal*> myZoo;
    ifstream infile;
    string filename = "our_zoo.csv";

    /**
     * Using the delimiter in the getline method to separate by strings
     * instead of a split function.  Little harder to do as you have to
     * handle the \r\n in the file and use eof instead of getline in the
     * while condition.  This quick implementation still misses the last food
     * type for the last animal in the file - I'll fix it when I have time.
     * **/
    infile.open(filename);
    if (infile.is_open()) {
        (getline(infile, line));
        string item;
        vector<string> tmpVec;
        while (!infile.eof()){
            getline(infile, item, ',');
            while((item.find("\r\n") == string::npos and !infile.eof())){
                tmpVec.push_back(item);
                getline(infile,item,',');
            }//inner while
            string last;
            int i = 0;

            // you actually get "grain\r\n346" as the item
            // which is the last element in the line and the
            // the next element of the next line - have to break
            // those up.
            for (i = 0;i<item.find("\r");i++){
                if(infile.eof())
                    break;
                if (item[i] != '\r')
                    last+=item[i];
            }//for
            tmpVec.push_back(last);
            string next_item;
            for(i = (i + 2);i < item.length();i++) {
                if(infile.eof())
                    break;
                else{
                    next_item+=item[i];
                }
            }
//            for(string s:tmpVec){
//                cout<<s<<" ";
//            }
//            cout<<endl;
            Animal *p = new Animal(stoi(tmpVec[0]),
                                   tmpVec[1],
                                   stoi(tmpVec[2]),
                                   stoi(tmpVec[3]));
            p->weight=stod(tmpVec[4]);
            p->weightDate=stoi(tmpVec[5]);
            string s = tmpVec[6];
            p->size=s[0];
            p->feedHour=stoi(tmpVec[7]);
            p->food_type=tmpVec[8];

            myZoo.push_back(p);
            line_count++;
            tmpVec.clear();
            //use that last element to start the vector off for the
            //the next object.  Kind of pita.
            tmpVec.push_back(next_item);
        }
    }
    else{
        cout<<"Couldn't open zoo file."<<endl;
        exit(999);
    }

//    //debug: print out the data using a for range loop
//    cout<<"\nPrint using a for range loop: \n";
//    printAnimals(myZoo);

    do {
        choice = displayMenu();
        switch(choice){
            case 1: {//Display animals by size
                string c_size;
                do {
                    cout << "What size would you like to see (S,M,L): ";
                    getline(cin, c_size);
                }while (c_size!="S" and c_size!="M" and c_size!="L");
                vector<int>elements{1,2,3,4};
                vector<Animal*>selected=getAnimals(c_size[0],myZoo);
                displayAnimals(selected, elements);
                break;
            }
            case 2: {//search for animals by id
                string s_id;
                int id;
                bool good=true;
                do {
                    cout << "What ID would you like to search for?  ";
                    getline(cin, s_id);
                    try{
                        id = stoi(s_id);
                        good=true;
                    }catch (std::exception e){
                        cout<<e.what()<<endl;
                        cout<<"Please enter a valid ID."<<endl<<endl;
                        good=false;
                    }
                }while (!good);
                vector<int>elements{1,2,3,4,5,6,7,8,9};
                vector<Animal*>selected=getAnimals(id,myZoo);
                if(!selected.empty())
                    displayAnimals(selected, elements);
                else
                    cout<<"No animals met the criterion."<<endl;
                break;
            }
            case 3: {//display all animals in an enclosure
                string s_enc;
                int i_enc;
                bool good=true;
                do {
                    cout << "What Enclosure ID would you like to search for?  ";
                    getline(cin, s_enc);
                    try{
                        i_enc = stoi(s_enc);
                        good=true;
                    }catch (std::exception e){
                        cout<<e.what()<<endl;
                        cout<<"Please enter a valid Enclosure Number."<<endl<<endl;
                        good=false;
                    }
                }while (!good);
                vector<int>elements{1,2,3,8};
                vector<Animal*>selected=getAnimals(i_enc,'e',myZoo);
                if(!selected.empty())
                    displayAnimals(selected, elements);
                else
                    cout<<"No animals met the criterion."<<endl;
                break;
            }
            case 4: {//display all animals that need to be fed
                vector<int>elements{1,3,4,8,9};
                vector<Animal*>selected=getHungryAnimals(myZoo);
                if(!selected.empty())
                    displayAnimals(selected, elements);
                else
                    cout<<"No animals met the criterion."<<endl;
                break;
            }
            case 5: {//display all animals that need to be weighed
                string s_cur_year;
                int i_cur_year;
                bool good=true;
                do {
                    cout << "What is the current year (yyyy)?  ";
                    getline(cin, s_cur_year);
                    try{
                        i_cur_year = stoi(s_cur_year);
                        good=true;
                    }catch (std::exception e){
                        cout<<e.what()<<endl;
                        cout<<"Please enter a valid Year (yyyy)."<<endl<<endl;
                        good=false;
                    }
                }while (!good);

                vector<int>elements{1,2,3,4,5,6};
                vector<Animal*>selected= getTBWeighed(i_cur_year,myZoo);
                if(!selected.empty())
                    displayAnimals(selected, elements);
                else
                    cout<<"No animals met the criterion."<<endl;
                break;
            }
            case 6: {//Exit
                break;
            }
            default: {
                break;
            }
        }
    }while(choice!=6);

    return 0;
}

vector<string> split(string s, char delimiter){
    vector<string> strVector;
    string tmp;
    for (int i=0;i<s.size();i++){
        if ((s[i] != delimiter) and (i != s.size()-1))
            tmp += s[i];
        else{
            if (i ==  s.size()-1)//since the very last char may not be followed by whitespace
                if (s[i] != '\r')
                    tmp += s[i];
            strVector.push_back(tmp);
            tmp="";//reset tmp for the next loop
        }
    }
    return strVector;
}

void printAnimals(vector<Animal*> myZoo){

    //print out the data using a for range loop

    for(Animal *p: myZoo){
        cout << "ID: " << p->getID() << endl
             << "\tName: "<<p->getName() << endl
             << "\tCage Number: " <<p->getCage() <<endl
             << "\tEnclosure Number: "<<p->getEnclosure() << endl
             << "\tWeight: "<<p->weight << endl
             << "\tWeight Date: "<<p->weightDate << endl
             << "\tSize: "<<p->size << endl
             << "\tFeeding Hour:"<<p->feedHour << endl
             << "\tFood Type: "<<p->food_type << endl;
        string hungry = p->isHungry() ? "Hungry!" : "Not Hungry.";
        cout<< "\tAt 1000 today, is hungry?: "<<hungry<<endl;
    }
}

int displayMenu(){
    //Display the menu for the Zoo Management Systemc
    string choice;
    bool good=true;
    int option;
    do {
        cout << setw(10) << "Zoo Management System" << endl
             << "\t1. Display animals by Size" << endl
             << "\t2. Search for animal by ID" << endl
             << "\t3. Display all animals in an enclosure" << endl
             << "\t4. Display animals that need to be fed" << endl
             << "\t5. Display animals who need to be weighed" << endl
             << "\t6. Exit" << endl
             << setw(10) << "Enter option: ";

        getline(cin, choice);
        try {
            option=stoi(choice);
            if(option > 0 and option <= 6)
                good = true;
            else {
                good = false;
                throw std::exception();
            }
        }
        catch (std::exception e) {
//            cout<<e.what()<< endl;
            cout<<"Please enter a valid choice."<<endl<<endl;
            good = false;
        }

    }while(!good);

    return option;
}

vector<Animal*> getAnimals(char size, vector<Animal*>animal){
    vector<Animal*> selected;
    for (Animal* p: animal){
        if(p->size==size)
            selected.push_back(p);
    }
    return selected;
}
vector<Animal*> getAnimals(int id,vector<Animal*>animal){
    vector<Animal*> selected;
    for (Animal* p: animal){
        if(p->getID()==id)
            selected.push_back(p);
    }
    return selected;
}
vector<Animal*> getAnimals(int num, char containment_type,vector<Animal*>animal){
    vector<Animal*> selected;
    //containment type c is cage
    if (containment_type == 'c'){
        for (Animal* p: animal){
            if(p->getCage()==num)
                selected.push_back(p);
        }
    }

    //containment type e is enclosure
    if (containment_type == 'e'){
        for (Animal* p: animal){
            if(p->getEnclosure()==num)
                selected.push_back(p);
        }
    }

    return selected;
}
vector<Animal*> getHungryAnimals(vector<Animal*>animal){
    vector<Animal*> selected;
    for (Animal* p: animal){
        if(p->isHungry())
            selected.push_back(p);
    }
    return selected;
}
vector<Animal*> getTBWeighed(int cur_year, vector<Animal*>animal){
    vector<Animal*> selected;
    for (Animal* p: animal){
        if(p->weightDate < cur_year)
            selected.push_back(p);
    }
    return selected;
}
void displayAnimals(vector<Animal*>selected, vector<int>values){

    for(Animal* p: selected){
        for(int val: values){
            if(val==1)
                cout << "ID: " << p->getID() << endl;
            if(val==2)
                cout << "\tName: " <<p->getName() <<endl;
            if (val==3)
                cout << "\tCage Number: " <<p->getCage() <<endl;
            if (val==4)
                cout<< "\tEnclosure Number: "<<p->getEnclosure() << endl;
            if (val==5)
                cout<< "\tWeight: "<<p->weight << endl;
            if (val==6)
                cout << "\tWeight Date: "<<p->weightDate << endl;
            if (val==7)
                cout<< "\tSize: "<<p->size << endl;
            if (val==8)
                cout<< "\tFeeding Hour:"<<p->feedHour << endl;
            if (val==9)
                cout << "\tFood Type: "<<p->food_type << endl;
        }
    }
}


