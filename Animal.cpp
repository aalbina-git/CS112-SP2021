#include <string>
#include <iostream>
#include <ctime>

using namespace std;

class Animal{

private:

    int id;
    string name;
    int cage_num;
    int enclosure_num;


public:
    double weight;
    int weightDate;
    char size;
    int feedHour;
    string food_type;


    Animal(int id, string name, int cage_number, int enclosure_number=0 ){
        if (id>0)
            this->id=id;
        else{
            cout<<"Exception: Invalid animal id."<<endl;
            throw std::exception();
        }

        if (!name.empty())
            this->name=name;
        else{
            cout<<"Exception: Invalid animal name."<<endl;
            throw std::exception();
        }
        if (cage_number >0 && cage_number <=120)
            this->cage_num=cage_number;
        else {
            cout << "Exception: Invalid cage number." << endl;
            throw std::exception();
        }
        if(enclosure_number > 0 && enclosure_number <=25)
            this->enclosure_num=enclosure_number;
        else {
            cout << "Exception: Invalid enclosure number." << endl;
            throw std::exception();
        }
    }

    int getID(){
        return id;
    }

    void changeName(string newName){
        if (!newName.empty())
            name=newName;
    }

    string getName(){return name;}

    void changeEnclosure(int num){
        if(num > 0)
        enclosure_num=num;
    }

    int getEnclosure(){return enclosure_num;}

    void changeCage(int num) {
        if (num > 0)
            cage_num = num;
    }

    int getCage(){return cage_num;}

    bool isHungry(){
        time_t datetime = time(nullptr);
        tm *local_time = localtime(&datetime);
        int curHour = local_time->tm_hour;
        if(curHour < feedHour)
            return true;
        else
            return false;
    }
};

