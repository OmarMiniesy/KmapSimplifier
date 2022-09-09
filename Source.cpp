#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

void inputMinterms(vector <int>& minterms, int& numOfMinterms, int& numOfLiterals);
int inputNumOfMinterms(int& z);
void printTable(vector <vector <int>> & table);
string decToBin(int x);
bool diffBy1 (string first, string second);
string insertDashInFirst (string first, string second);
string binaryToLiteral(string x);
vector <string> simplify(vector <string>& binaryMinterms, vector <int>& minterms);
bool inVector (vector <string> vec, string x);

int main(){

    vector <int> minterms;
    int numOfMinterms;
    int numOfLiterals;

    cout << endl; cout << endl;
    cout << "A, B, and C are available literals with A most significant and C least signficant."<<endl;
    cout << "Enter number of literals (1, 2, 3): ";
    cin >> numOfLiterals;
    
    int z = pow(2, numOfLiterals);
    numOfMinterms = inputNumOfMinterms(z);
    inputMinterms(minterms, numOfMinterms, numOfLiterals);

    cout << "MINTERMS: "<<endl;

    for(int i = 0; i < minterms.size(); i++){
       cout << minterms.at(i) << " ";
    }
    cout << endl;
    vector <vector <int> > table;


    if(numOfLiterals == 1){
        
        table.resize(1);
        table[0].resize(2);
        
        for(int i = 0; i < minterms.size(); i++){
            int a = minterms.at(i);
            table[0][a] = 1;
        }
        
        printTable(table);
        
        if(minterms.size() == 2){
            cout << "F = 1"<<endl;
        }
        else if(minterms.size() == 1){
            if(table[0][0] == 1){
                cout << "F = A'"<<endl;
            }else if(table[0][1] == 1){
                cout << "F = A"<<endl;
            }
        }
    }
    
    if(numOfLiterals == 2){

        table.resize(2);
        for(int i = 0; i < table.size(); i++){
            table[i].resize(2);
        }

        int j;
        for(int i = 0; i < minterms.size(); i++){
            
            int a = minterms.at(i);
            if(a < 2) j = 0;
            else {j = 1; a = a -2;
            }
            table[a][j] = 1;
        }

        printTable(table);

        if(minterms.size() == 4){
            cout << "F = 1"<<endl;
        }

        else if(minterms.size() == 1){
            
            int n = 0;
            int m = 0;
            bool y = true;

            for(int i = 0; i < table.size(); i++){
                for(int j = 0; j < table[i].size(); j++){
                    if(table[i][j] == 1){
                        y = false; break; 
                    }else{
                        if(n == 1){
                            m++;
                            n++;
                        }else{
                            n++;
                        }
                    }
                }
                if( y == false){break;}
            }

            if(m == 0){
                if(n == 0)
                    cout << "F = A'B'"<<endl;
                else if(n == 1)
                    cout << "F = AB'"<<endl;
            }
            else if ( m == 1 ){
                if( n == 2 )
                    cout << "F = A'B"<<endl;
                else if( n == 3)
                    cout << "F = AB"<<endl;
            }
        }

        else if(minterms.size() == 3){
            
            int n = 0;
            int m = 0;
            bool y = true;

            for(int i = 0; i < table.size(); i++){
                for(int j = 0; j < table[i].size(); j++){
                    if(table[i][j] == 0){
                        y = false;
                        break;
                    }else{
                        if(n == 1){
                            m++;
                            n++;
                        }else{
                            n++;
                        }
                    }
                }
                if( y == false){break;}
            }

            if( m == 0){
                if(n == 0){
                    cout << "F = A + B"<<endl;
                }else if( n == 1)
                    cout << "F = A' + B"<<endl;
            }else if ( m == 1){
                if(n == 2){
                    cout << "F = A + B'"<<endl;
                }else if(n == 3){
                    cout << "F = A' + B'"<<endl;
                }
            }

        }
        
        else if(minterms.size() == 2){

            int k = 0;
            int f = 0;
            int z = 0;
            bool x = false;
            bool y = true;

            for(int i = 0; i < table.size(); i++){
                for(int j = 0; j < table[i].size(); j++){
                    if(table[i][j] == 0){
                        k++;
                    }
                    else if(table[i][j] == 1 && !x){
                        k++;
                        f = k;
                        x = true;
                    }
                    else if(table[i][j] == 1 && x){
                        k++;
                        z = k;
                        y = false;
                        break;
                    }
                }
                if(y == false){break;}
            }

            f--;z--;

            cout << f << " " << z << endl;
            
            if( f == 0 && z == 1){
                cout << "F = B'"<<endl;
            }
            else if( f == 2 && z == 3){
                cout << "F = B"<<endl;
            }
            else if( f == 0 && z == 2){
                cout << "F = A'"<<endl;
            }
            else if( f == 1 && z == 3){
                cout << "F = A"<<endl;
            }
            else if(f == 0 && z == 3){
                cout << "F = A'B' + AB"<<endl;
            }
            else if(f == 1 && z == 2){
                cout << "F = AB' + A'B"<<endl;
            }

        }

    }

    if(numOfLiterals == 3){

        table.resize(2);
        for(int i = 0; i < table.size(); i++){
            table[i].resize(4);
        }

        for(int i = 0; i < minterms.size(); i++){
            
            int m = 0;
            int n = 0;
            int x = 0;

            for(int j = 0; j <= minterms[i]; j++){
                if(x == minterms[i]){
                    table[m][n] = 1;
                    break;
                }else{
                    if(m==0){
                        m++;
                        x++;
                    }else if(m == 1){
                        m = 0;
                        n++;
                        x++;
                    }
                }
            }
        }

        int temp = table[0][2];
        table[0][2] = table[0][3];
        table[0][3] = temp;


        int temp1 = table[1][2];
        table[1][2] = table[1][3];
        table[1][3] = temp1;

        printTable(table);

        if(minterms.size() == 8){
            cout << "F = 1"<<endl;
        }else{

            vector <string> binaryMinterms;

            for(int i = 0; i < minterms.size(); i++){
                binaryMinterms.push_back(decToBin(minterms.at(i)));
            }

            do{
                binaryMinterms = simplify(binaryMinterms, minterms);
            }while(!(binaryMinterms == simplify(binaryMinterms, minterms)));

            
            cout << "F = ";

            for(int i = 0; i < binaryMinterms.size(); i++){
                if(i != binaryMinterms.size() - 1)
                    cout << binaryToLiteral(binaryMinterms[i]) << " + ";
                else 
                    cout << binaryToLiteral(binaryMinterms[i]) <<endl;
            }

        }
    }

}

vector <string> simplify(vector <string>& binaryMinterms, vector <int>& minterms){

    vector <string> updatedMinterms;
    int size = binaryMinterms.size();
    vector <int> taken;
    taken.resize(size);

    for(int i = 0; i < size; i++){
        for(int j = i; j < size; j++){

            if(diffBy1(binaryMinterms[i], binaryMinterms[j])){

                taken[i] = 1; taken[j] = 1;
                string temp = insertDashInFirst(binaryMinterms[i], binaryMinterms[j]);

                if(!inVector(updatedMinterms, temp))
                    updatedMinterms.push_back(temp);
            }
        }
    }

    for(int i = 0; i < size; i++){

        if(taken[i] != 1 && !inVector(updatedMinterms, binaryMinterms[i]))
            updatedMinterms.push_back(binaryMinterms[i]);

    }

    return updatedMinterms;

}

bool inVector(vector <string> vec, string x){
    for(int i = 0; i < vec.size(); i++){
        if(x == vec[i])
            return true;
    }
    return false;
}

string binaryToLiteral(string x){

    vector <string> literals = {"A", "B", "C"};
    string result = "";

    for(int i = 0; i < x.length(); i++){
        if(x[i] != '-'){
            if(x[i] == '1'){
                result = result + literals[i];
            }else if(x[i] == '0'){
                result = result + literals[i] + "'";
            }
        }
    }

    return result;

}

string insertDashInFirst(string first, string second){
    
    string result = "";

    for(int i = 0; i < 3; i++){
        if(first[i] != second[i])
            result = result + "-";
        else
            result = result + first[i];
    }

    return result;
}

bool diffBy1(string first, string second){

    int count = 0;

    for(int i = 0; i < 3; i++){
        if(first[i] != second[i])
            count++;
    }

    if (count == 1) return true;
    else return false;

}

string decToBin(int x){
    
    string binary = "";

    while(x){
        if(x & 1)
            binary = "1" + binary;
        else 
            binary = "0" + binary;
        x >>= 1;
    }

    while(binary.length() != 3){
        binary = "0" + binary;
    }

    return binary;

}

void printTable(vector <vector <int>>& table){
    
    cout << "K-MAP: "<<endl;
    
    for(int i = 0; i < table.size(); i++){
        for(int j = 0; j < table[i].size(); j++){
            cout << table[i][j]<< "  ";
        }
        cout << endl;
    }
}


int inputNumOfMinterms(int& z){

    cout << "Enter number of minterms (must be less than or equal to " << z << " and positive): ";
    int numOfMinterms;

    while(true){
        
        cin >> numOfMinterms;

        if(cin.fail() || numOfMinterms <= 0 || numOfMinterms > z){
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Wrong input!! Must be integer and greater than 0 and less than or equal to "<< z <<endl;
        }
        else{
            break;
        }
    }

    return numOfMinterms;
}

void inputMinterms(vector <int>& minterms, int& numOfMinterms, int& numOfLiterals){
    
    int y = pow(2, numOfLiterals);
    
    cout << "Enter minterms separated by spaces. ";
    cout << "Must be integers greater than or equal to 0 and less than " << y << endl;
    
    int x;


    while(numOfMinterms > 0){
        
        cin >> x;

        if(cin.fail() || x < 0 || x > y-1){
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Wrong input!! Must be integer and greater than 0 and less than "<< y <<endl;
        }
        else{
            minterms.push_back(x);
            numOfMinterms--;
        }
    }

}