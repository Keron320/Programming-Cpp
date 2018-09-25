#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){

vector<string> game;
string choice;
string change;
string favouriteGame;
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
    cin>>favouriteGame;
    game.insert(game.begin(),favouriteGame);

}
else if (choice == "remove"){
    cin>>unlist;
    game.erase(game.begin()+(unlist-1));

}

}



return 0;

}
