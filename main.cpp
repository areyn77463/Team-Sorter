#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

//the next lines of code before the main function
//are prototypes to the functions used in the program
void menu();
void promptToContinue();
int randomInt();
void loadNames(string* names, int size);
void shuffle(int* participants, int size);
void printEvenTeams(int* participants, string* names, int size);
void printUnevenTeams(int* participants, string* names, int size);


int main(){

    randomInt(); //function to allow different random numbers
    int size = 52;  //number of people to shuffle

    int participants[size]; //IDs
    string names[size];     //will hold actual names

    shuffle(participants, size); //function that shuffles the participants

    loadNames(names,size); // function that stores names from text file
                           // into names array
    int action = -1;
    while(action!=0){
        menu(); // outputs the main menu

        reenter:
        cout<<"Select:";
        cin>> action;
        cout<<endl;

        if(action == 1){
            printEvenTeams(participants, names, size); // prints teams with
                                                       // even number of participants
        }

        else if(action == 2){

            printUnevenTeams(participants, names, size); //prompts user to enter
                                                         //amount of participants in teams
        }
        else if(action == 3){

            shuffle(participants, size);

            cout<<"Shuffled"<<endl;
            promptToContinue(); //prompts user to enter a key to continue
        }
        else if(action == 0)
            break;
        else{
            cout<<"Please enter valid Menu item\n";
            goto reenter;
        }
    }
    return 0;
}
void menu()
{
    system("CLS");
    cout<<setw(20)<<"Menu"<<endl;
    cout<<setw(25)<<std::left<<"Even Teams:"<<setw(10)<<"1"<<endl;
    cout<<setw(25)<<std::left<<"Uneven Teams:"<<setw(10)<<"2"<<endl;
    cout<<setw(25)<<std::left<<"Reshuffle:"<<setw(10)<<"3"<<endl;
    cout<<setw(25)<<std::left<<"Exit:"<<setw(10)<<"0"<<endl<<endl;
}
void promptToContinue()
{
    char key;
    cout<<"Press any key to continue:";
    cin>>key;
}
int randomInt()
{
     srand (time(NULL)); //allows different random numbers every time we run
}
void loadNames(string* names, int size)
{
    ifstream myfile ("names.txt");
    if (myfile.is_open()){
        for(int i=0; i<size; i++)
             getline(myfile, names[i]);
    }
}
void shuffle(int* participants ,int size )
{
    int ID_pool[size];  //available IDs
    int unused[size];   //keeps track unused IDs
    int current_size = size;    //keeps track of how much of ID_pool elements we actually use
                                //reset variables
    for(int i=0; i< size; i++){
        ID_pool[i] = i;
        unused[i] = 1;
            }
    current_size = size;

    int temp_index = -1;
    for(int i=0; i<size; i++){
        temp_index = rand() % current_size; // get random index

        participants[i]= ID_pool[temp_index];   //use that random index, to see which card to insert at shuffled[i]
        unused[ID_pool[temp_index]]--; //mark that we used that card

        if(unused[ID_pool[temp_index]] == 0){
            for(int j = temp_index; j < current_size-1; j++)
                ID_pool[j]= ID_pool[j+1];
                current_size--;
                    }
            }
}
void printEvenTeams(int* participants, string* names, int size)
{

    int curr_team = 0;   //each team has 4 members
    for(int i=0; i<size; i++){
        if(i%4==0){
            curr_team++;
            cout<<"====================="<<endl;
            cout<<"Team "<<curr_team<<endl;
                }
        cout<<setw(35)<<names[participants[i]]<<endl; //get a name for the participant's ID
            }
    cout<<"====================="<<endl;

            //the Menu refreshes with action (screen clears)
            //so we need this user input pause, to allow the user to inspect what happened
            //and continue when necessary
    promptToContinue();
}
void printUnevenTeams(int* participants, string* names, int size)
{
    int curr_size = size;
    int team_size = 0;
    int curr_index = 0;
    int curr_team = 0;

    while(curr_index<size-1){
        reEnter:
            cout<<size - curr_index<<" participants remain"<<endl;
            cout<<"Enter next team's size:";
            cin>>team_size;
            cout<<endl;

        if(curr_index+team_size>size || team_size < 1){
            cout<<"Invalid team size"<<endl;
            cout<<size - curr_index<<" participants remain"<<endl;
            goto reEnter;
                }
        else{
            curr_team++;
            cout<<"====================="<<endl;
            cout<<"Team "<<curr_team<<endl;
            for(int i=curr_index; i<curr_index+team_size; i++)
                cout<<setw(35)<<names[participants[i]]<<endl;
                curr_index += team_size;
                cout<<"====================="<<endl;
                }
            }

    promptToContinue();
}
