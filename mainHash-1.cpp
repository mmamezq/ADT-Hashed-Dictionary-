#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include "HashedDictionary.h"

using namespace std;

int main()
{
    //TABLE SIZE OF 13 - PRIME NUMBER
	HashedDictionary<string, int> table;
    
    //MENU
    
    char selection;
    string key;
    string array[25];
    int array_size, i = 0;
    
    do{
        
        cout << "\n1 – print hash table"
        
        <<"\n2 – retrieve hash item"
        
        << "\n3 – delete item"
        
        <<"\n4 – read names from file"
        
        <<"\n5 – save names to file"
        
        <<"\n6 - add item"
        
        <<"\n0 – quit" << endl;
        
        cout << "Enter Selection: ";
        cin >> selection;
        
        switch(selection){
        
            case '1':
                table.print();
                break;
                
            case '2':
                {
                  cout << "Please Enter Search Key: ";
                  cin >> key;
                  int item = table.getItem(key);
                  cout << "The item contained in that search key is: " << item << endl;
                }
                break;
            
            case '3':
            {
                cout << "Enter key to delete: ";
                key = "";
                cin >> key;
                bool removed = table.remove(key);
                if(!removed)
                    cout << key << " was not able to be removed." << endl;
                else
                    cout << key << " removed." << endl;
            }
                break;
            case'4':
            {
                //SHOULD BE PLACED INTO ITS OWN FUNCTION AS A PART OF THE CLASS
                string filename;
                string line;
                cout << "enter filename: ";
                getline(cin, filename);
                fstream inFile(filename);
                while(!inFile){
                    cout << "File does not exist. Please try again or press 0 to exit: ";
                    getline(cin, filename);
                    if(filename == "0"){
                        exit(-1);
                    }
                }
                
                getline(inFile, line);
                while (!inFile.eof()){
                    array[i] = line;
                    i++;
                    array_size++;
                    getline(inFile, line);
                }
                
                //BREAK LINE ARRAYS INTO ENTRIES FOR DICTIONARY
                int age_int;
                string name;
                for(int i = 0; i < array_size; i++){
                    char age = array[i][0];
                    age += array[i][1];
                    age_int = age;
                    string name = array[i].substr(3);
                    table.add(name, age_int);
                }
                inFile.close();
            }
                break;
            case '5':
            {
                table.printToFile();
            }
                break;
            case '6':
            {
                cout << "Enter key to add (string): ";
                string key;
                cin >> key;
                cout << "\nEnter age: ";
                int age_item;
                cin >> age_item;
                table.add(key, age_item);
            }
                break;
            case '0':
                break;
            default:
                cout << "INVALID SELECTION. TRY AGAIN OR PRESS 0 TO QUIT." << endl;
        
        }
        
    } while(selection != '0');
    

}