#include <iostream>
#include <stdlib.h> 
#include <set>
#include <time.h>
using namespace std;

int board[9]={0};
set<int> notOccupied;
int defBoardValue[9]={8,3,4,1,5,9,6,7,2};

int getRandom(){
    auto r = rand()%notOccupied.size(); 
    auto it = notOccupied.begin();
    while(r--) it++;
    return *it;
}

void showBoard(){
    cout<<"Board: "<<endl;
    for(size_t i=1;i<=9;i+=3){
        cout<<" ("<<i<<")"<<": "<<board[i-1]<<\
              " ("<<i+1<<")"<<": "<<board[i]<<\
              " ("<<i+2<<")"<<": "<<board[i+1];
        cout<<"\n";
    }
}

void setMove(int move,int val){
    if(notOccupied.find(move)!=notOccupied.end()){
        board[move-1]=val;
        notOccupied.erase(move);
    }else{
        cout<<"INVALID MOVE";
        exit(0);
    }
}

int getWinPos(int val,int cond){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            for (int k = 0; k < 9; k++){
                if (i != j && i != k && j != k){
                    if(board[i]==val&&board[j]==val&&board[k]==cond){
                        if((defBoardValue[i]+defBoardValue[j]+defBoardValue[k])==15){
                            return (k);
                        }
                    }
                }
            }
        }
    }
    return -1;
}

void checkPlayerWin(){
    if(getWinPos(1,1)>0){
        showBoard();
        cout<<"Player won";
        exit(0);
    }
}

void botAssign(){
    int move=getWinPos(1,0);
    if(move==-1){
        setMove(getRandom(),2);
    }else{
        setMove(move+1,2);
    }
    showBoard();
}

void checkBotWin(){
    int move=getWinPos(2,0);
    if(move>=0){
        setMove(move+1,2);
        cout<<"Bot won"<<endl;
        showBoard();
        exit(0);
    }else{
        botAssign();
    }
}

void getHumanMove(){
    int move;
    cout<<"Enter your move :";
    cin>>move;
    setMove(move,1);
}

int main(){

    for( int i = 1; i != 10; ++i ) notOccupied.insert(i);
    srand(time(0));

    showBoard();
    getHumanMove();
    setMove(getRandom(),2);
    showBoard();
    getHumanMove();
    botAssign();
    for(int i=0;i!=2;i++){ 
        getHumanMove();
        checkPlayerWin();
        checkBotWin();
    }
    getHumanMove();
    checkPlayerWin();
    cout<<"Draw"<<endl;
    showBoard();
}