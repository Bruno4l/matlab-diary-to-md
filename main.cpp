#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    ifstream file;
    file.exceptions ( ifstream::badbit );
    if(argc != 2){
        cout<<"Usage: ./matlab-diary-to-md.exe file-name.txt";
        return 0;
    }
    try{
        file.open(argv[1]);
        if(!file.good()){
            cout << "File doesn't exists.";
            file.close();
            return 0;
        }
        if (file.is_open()){ 
            string arg1(argv[1]);
            ofstream fileout(arg1.substr(0,arg1.find_last_of('.'))+".md");
            string line;
            string wordToReplace("% -");
            size_t len = wordToReplace.length();
            bool lastWasCode = false;

            cout << "File "<<argv[1]<<" Opened.\n\n";
            while (getline(file, line)){
                size_t pos = line.find(wordToReplace);

                if (pos != string::npos){
                    line.replace(pos, len, "");
                    if(lastWasCode) fileout << "```" << '\n';
                    fileout << line << '\n';
                    lastWasCode = false;
                } else {
                    if(!lastWasCode) fileout << "```matlab" << '\n';
                    lastWasCode = true;
                    fileout << line << '\n';
                }
            }
            if(lastWasCode) fileout << "```" << '\n';
            
            fileout.close();
            file.close();
            return 0;
        }
        cout << "Error.";
    }catch(const ifstream::failure& e) {
        cout << "Exception opening/reading file.";
    }
    file.close();
    return 0;
}
