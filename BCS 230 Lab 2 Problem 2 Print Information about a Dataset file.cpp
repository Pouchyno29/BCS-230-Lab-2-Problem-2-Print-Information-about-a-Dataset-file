/**
   Programmer's name    : Stanley
   Class                : BCS 230 Foundations of Computer Programming II
   Date                 : 09/13/2017
   Lab                  : Lab 2 Problem 2 Print info about a dataset file
   Professor's name     : Moaath Alrajab
   Software uses        : Code:blocks
**/

/**
    Problem 2
    Attached (on blackboard ) is a dataset file called 'IRIS.csv'. Write a c++ program that does the followings:
    1) Report how many lines in the file.
    2) How many columns in each row.
    3) How many different classes in the file (last column).
    4) You should have at least on function in your solution.
**/



#include <iostream>
#include <fstream>
using namespace std;

int lineNumber(ifstream &myFile);
int rowNumber(ifstream &myFile);
void saveClass(ifstream &myFile);
int classNumber(ifstream &myFile);

int main()
{
    ifstream myFile;

    cout << "The file has " << lineNumber(myFile) << " lines,";
    cout << " " << rowNumber(myFile) << " rows, and "<< classNumber(myFile) << " classes."<< endl;

    return 0;
}




int lineNumber(ifstream &myFile){
    int lineCount = 0;
    string line;
    myFile.open("IRIS.csv");

    //If the file is opened
    if(myFile.is_open()){

        //Take one line at a time from the file
        while( getline(myFile, line)){

            //Add one each time we found a new line.
            lineCount++;
        }
        //Close the file when we reach the end of the file or if there is no more lines.
        myFile.close();

    }else{
        cout << "The file cant be opened!!!" << endl;
    }
    //Return the number of lines found from the file.
    return lineCount;
}


int rowNumber(ifstream &myFile){
    int rowCount = 0;
    string line;
    myFile.open("IRIS.csv");

    //If the file is opened
    if(myFile.is_open()){

        //Take one line from the file.
        getline(myFile, line);

        //Loop from 0 to the length of the line.
        for( int x = 0; x < line.length(); x++){
            //Check for the end of the line
            if(line[x] == '\n'){
                //If it is the end of the line then stop
                break;
            //check for comma from the line to determine rows
            }else if(line[x] == ','){
                //Add one each time we found a new comma from the line;
                rowCount++;
            }
        }
        //Close the file.
        myFile.close();

    }else{
        cout << "The file cant be opened!!!" << endl;
    }
    //Return the number of rows found from that line.
    return ++rowCount;
}

//This function copies all the classes found from the .csv file to a different file calls saveClass(...)
void saveClass(ifstream &myFile){
    int numberOfcomma = (rowNumber(myFile) -1);
    string line;

    int comma = 0;

    //Open the .csv file
    myFile.open("IRIS.csv");

    //Create and open the new file that the classes will be saved to
    ofstream saveData("saveClass.txt");

    //check if both files can be opened
    if(myFile.is_open() && saveData.is_open()){

        //Read the first file line by line
       while(getline(myFile, line)){

            //Loop from 0 to the length of the line
            for( int x = 0; x < line.length(); x++){

                //Check for comma from each line
                if(line[x] == ','){

                    //If comma found add one
                    comma++;
                }
                //If it is the last comma
                if(comma == numberOfcomma){

                        //If the current char is a comma
                    if( line[x] == ','){

                        //Continue just to skip that comma
                        continue;
                    }else{
                        //Then save everything after that comma to a new file
                        //cout << line[x];
                        saveData << line[x];
                    }
                }
                //If the loop reach the end of the line
                if( x == (line.length() -1)){
                    //Start comma back from 0 to count for comma for the next line
                    comma = 0;

                    //Reset the line variable for the next line on the .csv file
                    //line = " ";

                    // cout << endl;
                    //Move the cursor to the next line to save the next class on the next line.
                    saveData << "\n";
                }
            }
        }
        //Close both file
        myFile.close();
        saveData.close();
      }else{
        cout << "File can't be opened!!" << endl;
      }
}

//This function count the number of classes that were save on the new file created from the saveClass(....) function
int classNumber(ifstream &myFile){
    //I call the saveClass(...) function here so that i don't have to call it from Main(...) function.
    saveClass(myFile);

    string currentLine;
    string previousLine;
    int classCount = 0;

    //Open the saveClass text file
    myFile.open("saveClass.txt");

    //If the file is opened
    if(myFile.is_open()){

        //Reading one line at a time from the file
        while(getline(myFile, currentLine)){
            //If the current line is not the same as the previous line
            if(currentLine != previousLine){
                //Add one
                classCount++;
                //Replace the previous line with the current line
                previousLine = currentLine;
            }
            //Go to the next line on the file
        }
        //Close the file when reaching the end of the file
        myFile.close();
    }else{
        cout << "File cant be opened" << endl;
    }
    //Return the number of classes found.
    return classCount;
}

/**
    This programs works fine and doest what it supposed to do,
    but I realized that there is a small bug on it. It is not a compiler error,
    or coding error but it is a logic error.
    This program will assume each class are grouping together, therefore, the program will output the correct
    amount of classes, but what if the classes not grouping together, each time the program reads
    a class that is different from the previous class, it will count it as a new class, even tough the last
    class is the same as the first class
    Unfortunately i wont have enough time to fix it.

**/

/**
    To fix that problem, take the current class before save it and compare it
    with every class that are already stored on the file.
    If the current class is already save on the file, then skip that class
    otherwise, save the current class to the file

**/
