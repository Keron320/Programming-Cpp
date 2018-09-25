#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){

vector<string> game;
string choice;
string change;
int unlist = 0;

vector<string>::const_iterator iter;
cout<<"Welcome to your favorite game list!"<<endl;
while(choice != "exit"){
cout<<"Your current favourite games are: "<<endl;

sort(game.begin(),game.end());
for (iter = game.begin(); iter != game.end();++iter){
    cout<<*iter<<endl;
}
cout<<"What would you like to do next,add or remove games? (add/remove)"<<endl;
cin >> choice;
if (choice == "add"){
    cout<<"Insert name of the game: "<<endl;
    string favouriteGame;
    cin>>ws; // std::ws absorbs whitespace stuff
    getline(cin,favouriteGame);
    game.insert(game.begin(),favouriteGame);
}
else if (choice == "remove"){
    cout<<"By number or name?"<<endl;
    cin >> choice;
    if(choice == "name"){
        string name;
        cout<<"Enter the name of the game: "<<endl;
        cin>>ws;
        getline(cin,name);
        iter = find(game.begin(),game.end(),name);
        if ( iter != game.end()){
            cout<<name<<" found and removed from the list"<<endl;
            game.erase(remove(game.begin(),game.end(),name),game.end());
        }
    }
    else if ( choice == "number"){
        cin>>unlist;
        cout<<"Enter number from: "<<endl;
        game.erase(game.begin()+(unlist-1));
    }




}


}
return 0;

}
