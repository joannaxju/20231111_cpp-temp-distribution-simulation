#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

double calcTemp(double [][8], int, int);  

int main()
{
    string input, output;  
    double temp[6][8];  
    double equilibrium;   
  
    for(int i = 0; i < 6; i++)
    {
        for(int k = 0; k < 8; k++)
            temp[i][k] = 0.0;
    }

    cout << "Enter input file name: \n";
    cin >> input;
    cout << endl;
    cout << "Enter output file name: \n";
    cin >> output;
    cout << endl;

    ifstream inFile;  
    ofstream outFile;
    inFile.open(input.c_str());
    if(inFile) 
    {
        double val[5];
        for(int i = 0; i < 5; i++)
        {
            inFile >> val[i];
        }
        equilibrium = val[4];
        for(int i = 0, k = 1; i < 8; i++, k++)
        {
            temp[0][i] = val[0];
            temp[5][i] = val[2];
            if(k < 5)
            {
                temp[k][0] = val[3];
                temp[k][7] = val[1];
            }
        }
        inFile.close();

        double max = 0.0;
        bool withTol = false;
        while(!withTol)
        {
            for(int i = 1; i < 5; i++)
            {
                for(int k = 1; k < 7; k++)
                {
                    double oldVal = temp[i][k];
                    double newVal = calcTemp(temp, i, k);
                    temp[i][k] = newVal;

                    if(i == 1 && k == 1)
                        max = abs(oldVal - newVal);
                    if(max < abs(oldVal - newVal))
                        max = abs(oldVal - newVal);
                }
            }
            if(max < equilibrium)
                withTol = true;
        }

        outFile.open(output.c_str());
        for(int i = 1; i < 5; i++)
        {
            for(int k = 1; k < 7; k++)
            {
                outFile << temp[i][k] << " ";
            }
            outFile << endl;
        }
        outFile.close(); 
    } 
    else 
    {
        cout << "File open failure!";
    }

    return 0;
}

double calcTemp(double temp[][8], int row, int col)    
{
    double sum = 0;
    sum += temp[row-1][col];
    sum += temp[row+1][col];
    sum += temp[row][col-1];
    sum += temp[row][col+1];
    return sum / 4.0;
}