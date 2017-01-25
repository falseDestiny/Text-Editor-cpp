// Shane M Chamberlain
// CPSC340
// Section 2

// on pong try structs in C
#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <ios>
#include <cstdio>
#include <cstdlib>
#include <limits>
#undef max

using namespace std;
class myEditor{

public:
    myEditor();
    int getLength();
    int getPosString(string, string);
    string insertString(string, string);
    string deleteChar(int, int, string);
    string replaceString(string, string);
    int getNextLine();
    void printLine();
    string getInputFile();
    void getCommandMenu();
    void executeProgram();                          //because no return
private:
    ifstream inFile;
    ofstream outFile;
    string currentLine;
    
};

myEditor::myEditor(){
}

//Get input file
string getInputFile(){
    string line, userFile, document;
    cout <<'\n';
    cout<<"Please enter the input file: ";
    cin>> userFile;
    ifstream myfile (userFile.c_str());
    if (!myfile.is_open()) {
        cerr << "Sorry, "<<userFile<< " is not found." << endl;
        exit(1);
    }
    while ( getline (myfile,line) )
    {
        //cout << line << '\n';
    }
    myfile.close();
    return userFile;
}
//Get the length of the line
int myEditor::getLength(){
    return currentLine.size();
}
//Get position of a string
int myEditor::getPosString(string input, string currentLine){
    int index;
    index=currentLine.find(input);
    if (index==-1){                                 //if there is only one line after an "IF Else or While"
        cout<<input<<" not found"<<endl;
        return index;                               //You do not need braces.
    }        cout<<"Position is: "<<index+1<<endl;
    return index+1;
}
//insert characters in the line
string myEditor::insertString(string userString, string currentLine){
    int z=0;
    string string1, string2;
    cout<<"Insert where? ";
    int userNum;
    cin>>userNum;
    if (userNum-1>currentLine.size()||userNum-1<0){
        cout<<"invalid input"<<endl;
        int i;
        while (!(userNum >> i)) {
            cin.clear();
            break;
            //cin.ignore(std::numeric_limits<int>::max(), '\n');
            break;
        }
        
    } else if(userNum-1==currentLine.size())           //Bool
    {
        currentLine=currentLine+userString;
    }
        else{
            string1=currentLine.substr(0, userNum-1);
            string2=currentLine.substr(userNum-1);
            currentLine=string1+userString+string2;
    }
    return currentLine;
}
//Delete characters in the line
string myEditor::deleteChar(int pos, int chars, string currentLine){
    string string1, string2;
    int i;
    while (!(chars >> i)||!(pos >> i)) {
        cin.clear();
        break;
        cin.ignore(std::numeric_limits<int>::max(), '\n');
        break;
    }
    pos=pos-48;
    chars=chars-48;
    if (pos>currentLine.size()||pos<=0){
        cout<<"invalid input"<<endl;
    } else if(pos==1){
        int temp=(pos+chars-1);
        if (temp>currentLine.size()){
            temp=currentLine.size();
        }
        currentLine=currentLine.substr(temp);
    }
    else {
        string1=currentLine.substr(0, pos-1);
        cout<<string1<<endl;
        string2=currentLine.substr(((pos-1)+chars));               //put math function in double parenthesis
        currentLine=string1+string2;
    }
    return currentLine;
}
//Replace a string in the line
string myEditor::replaceString(string userSwap, string currentLine){
    string input, string1, string2, userString;
    int count1, count2;
    count1=currentLine.find(userSwap);                //returns number of letters    if -1 string not found
    count2=userSwap.size();
    cout<<"With what? ";
    cin>>userString;
    if (count1 > currentLine.size()){
        cout<<"invalid input"<<endl;
    }
    else if(count1==0){
        currentLine=userString+currentLine.substr(count2);
    }
    else{
        string1=currentLine.substr(0, count1);
        string2=currentLine.substr(count1+count2);
        currentLine=string1+userString+string2;
    }
    return currentLine;
}

//Print out commands
void getCommandMenu(){
    cout<<"The Editing commands are: "<<endl;
    cout<<"L        :Determine the length of the current line"<<endl;
    cout<<"P str    :Find the position (from 0) of the string str"<<endl;
    cout<<"I str    :Insert string str"<<endl;
    cout<<"D p n    :Delete n characters beginning at position p"<<endl;
    cout<<"R str    :Replace substring str with another string"<<endl;
    cout<<"N        :Get the next line of text"<<endl;
    cout<<"Q        :quit editing"<<endl;
    cout<<endl;
    cout<<" Enter an editing command following each prompt >"<<endl;
}
//Get next line
int myEditor::getNextLine(){
    outFile<<currentLine<<endl;                     //saves current line into the out file
    cout<<"Next Line: "<<endl;
    if (getline(inFile, currentLine)){
        return 1;                                   //if anpther line then return 1
    } return 0;
}

//Print line
void myEditor::printLine(){
    cout<<currentLine<<endl;;
}

//Runs main program
void executeProgram() {
    string line, userFile, document, newLine, currentLine;
    string response;
    myEditor tester;
        cout <<'\n';
        cout<<"Please enter the input file: ";
        cin>> userFile;
        cin.ignore();
    
    string tempV=userFile+".out";
    const char *filePoint=tempV.c_str();
    ifstream myfile (userFile.c_str());
    std::remove(filePoint);
    //std::remove(userFile+".out",ios_base::app);
    //rename(userFile+".out"", "newfile.dat")
    getCommandMenu();
    //string file;
    while ( getline (myfile,line) )
        {
            int loop;
            do
            {
                cout << line << '\n';
                cout << "> ";
                getline(cin, response);
                if (response[0]=='Q'&&response[1]=='\0'){
                    cout <<'\n';
                    do{
                    ofstream myfile;
                    myfile.open(filePoint, ios_base::app);
                    myfile<<line;
                    myfile<< "\r\n";
                    myfile.close();
                        loop=1;
                    } while( getline (myfile,line));
                }
                else if (response[0]=='L'&&response[1]=='\0'){
                    cout<<"Length is: "<<line.size()<<endl;
                }
                else if (response[0]=='P'&&response[1]==' '){
                    newLine=response.substr(2);
                    tester.getPosString(newLine, line);
                }
                else if (response[0]=='N'&&response[1]=='\0'){
                    
                }
                else if (response[0]=='I'&&response[1]==' '){
                    newLine=response.substr(2);
                    currentLine=tester.insertString(newLine, line);
                    line=currentLine;
                    cin.ignore();
                }
                else if (response[0]=='R'&&response[1]==' '){
                    newLine=response.substr(2);
                    currentLine=tester.replaceString(newLine, line);
                    line=currentLine;
                    cin.ignore();
                }
                else if (response[0]=='D'&&response[1]==' '&&response[3]==' '){
                    int pos=response[2], chars=response[4];
                    currentLine=tester.deleteChar(pos, chars, line);
                    line=currentLine;
                }
                else {
                    cout<<"Error Detected!!!"<<endl;
                    response[0]='X';
                }
                if (loop==1){
                    cout << "********** Editing is Complete ************" << endl;
                    myfile.close();
                    exit(0);
                }
            } while (response[0]!='N');
            ofstream myfile;
            myfile.open(filePoint ,ios_base::app);
            myfile<<line;
            myfile<< "\r\n";
            
        }
    cout << "********** Editing is Complete ************" << endl;
    myfile.close();
}

int main () {
    executeProgram();
    return 0;
}




//myfile.open("file.txt.o",ios_base::app);
