#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 100000

void PrintFull(vector<vector<string>> line, int index){
    for(string str:line[index]){
        cout<<str<<endl;
    }
}
void PrintDate(vector<vector<string>> line, int index){
    for(string str:line[index]){
        str = str.substr(str.find(" ")+1,str.length());
        cout<<str<<endl;
    }
}
void PrintShort(vector<vector<string>> line, int index){
    int count=0;
    for(string str:line[index]){
        for(int i=0; i<str.size(); i++){
            if(count<20) cout<<str[i];
            count++;
        }
    }
    if(count>20) cout<<"..."<<endl;
    else cout<<endl;
}
void SaveDate(vector<vector<string>>& Date, string& dd, string command, int& count){
    count++;
    dd = command.substr(command.find(" "), command.find("/"));
    Date[count].push_back(dd);

}
int CompareLength(vector<vector<string>> line, int count){
    int cnt=0,temp=0; int index;
    for(int i=0; i<=count; i++){
        temp=line[i].size();
        if(temp>cnt){
            index=i;
            cnt=temp;
        }
    }
    return index;
}
int CompareAdj(vector<vector<string>> line, int count){

    ifstream  myfile("positive-words.txt");
    string word;
    int temp=0; int in; int index;

    while(getline(myfile,word,'\n')){
        for(int i=0; i<=count; i++){
            int cnt=0;
            for(string j: line[i]){
                if((in = j.find(word, 0)) != string::npos){
                    cnt++;
                }
            }
            if(cnt>temp){
                temp=cnt;
                index=i;
            }
        }
    }
    return index;
}

int main(){

    string command;
    string start_command="start_day";
    string show_command="show_day";
    string longest_command="show_the_longest_day";
    string best_day="show_the_best_day";
    vector<vector<string>> line(MAX);
    string token;
    vector<vector<string>> Date(MAX);
    string dd; 
    int count=-1;
    int index;

    while(getline(cin, command)){

        token = command.substr(0, command.find(" "));
        if (token == start_command){
            SaveDate(Date, dd, command, count);
        }
        else if (token == show_command){
            dd = command.substr(command.find(" "), command.find("/"));
                for(index=0; index<=count; index++){
                    for(string i: Date[index]){
                        if(i==dd){
                        PrintFull(line, index);
                    }
                }
            }
        }
        else if(token == longest_command){
            index = CompareLength(line, count);
            PrintDate(Date,index);
            PrintShort(line,index);
        }
        else if(token == best_day){
            index = CompareAdj(line, count);
            PrintDate(Date,index);
            PrintShort(line,index);
        }
        else{
            line[count].push_back(command);
        }
    }
    return 0;
}