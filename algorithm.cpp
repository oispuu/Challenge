#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


//findExactMatches isn't actually used in the last version.
void findExactMatches(vector<long> &comparable, vector<long> &comparable2, vector< vector<long> > &destination, int &beginning);
void doTheThing(vector<long> &comparable, vector<long> &comparable2, vector< vector<long> > &destination, int &beginning);
bool areThereAny(long summa, vector<long> uk);

int main(void)
{
    long a, b;
    int start = 0;
    vector<long> estonia;
    vector <long> uk;
    vector< vector<long> > match_estonia;
    string line;
    ifstream myfile ("estonia.txt");

    //Read data into vectors.

    if (myfile.is_open())
    {
        while (myfile.eof() != true)
        {
            myfile>>a;
            estonia.push_back(a);
        }
        myfile.close();
    }else{
        cout << "Unable to open file";
    }
    ifstream myfile2 ("uk.txt");
    if (myfile2.is_open())
    {
        while (myfile2.eof() != true)
        {
            myfile2>>b;
            uk.push_back(b);
        }
        myfile2.close();
    }else{
        cout << "Unable to open file";
    }

    //Work with data.

    doTheThing(estonia, uk, match_estonia, start);


    for(int i = 0; i < (int)estonia.size()-1; i++)
    {
        cout << estonia[i];
        for(int j = 0; j < (int)match_estonia[i].size(); j++)
        {
            if(j == 0){
                cout << "; " << match_estonia[i][j];
            }else{
                cout << ", " << match_estonia[i][j];
            }
        }
        cout << endl;
    }


    //Write to file.
    ofstream ofs("matches_estonia.txt", ofstream::out);
    for(int i = 0; i < (int)estonia.size()-1; i++)
    {
        ofs << estonia[i];
        for(int j = 0; j < (int)match_estonia[i].size(); j++)
        {
            if(j == 0){
                ofs << "; " << match_estonia[i][j];
            }else{
                ofs << ", " << match_estonia[i][j];
            }
        }
        ofs << endl;
    }
    ofs.close();

    return 0;
}

void findExactMatches(vector<long> &comparable, vector<long> &comparable2, vector< vector<long> > &destination, int &beginning)
{
    long summa;
    vector<long> rest;
    int remember = comparable.size() + beginning;
    for (int i = beginning; i < (int)comparable.size()+beginning; i++)
    {
        summa = comparable[i-beginning];
        vector<long> vec;
        destination.push_back(vec);
        int j = 0;
        size_t elements = comparable2.size();
        bool found_match = false;
        while(summa != 0 && comparable2.empty() == false)
        {
            if(j != (int)elements-1)
            {
                if(areThereAny(summa, comparable2) == true)
                {
                    if(comparable2[j] == summa)
                    {
                        found_match = true;
                        destination[i].push_back(comparable2[j]);
                        comparable2.erase(comparable2.begin()+j);
                        elements = comparable2.size();
                        break;
                    }
                    else
                    {
                        j++;
                    }
                }
            }
            else
            {
                break;
            }
        }
        if(found_match==false)
            rest.push_back(comparable[i-beginning]);
    }
    doTheThing(rest, comparable2, destination, remember);
}


void doTheThing(vector<long> &comparable, vector<long> &comparable2, vector< vector<long> > &destination, int &beginning)
{
    long summa;
    vector<long> rest;
    int remember = comparable.size() + beginning;
    bool found_match = false;
    for (int i = beginning; i < (int)comparable.size()+beginning; i++)
    {
        summa = comparable[i-beginning];
        vector<long> vec;
        destination.push_back(vec);
        int j = 0;
        size_t elements = comparable2.size();
        while(summa != 0 && comparable2.empty() == false)
        {
            if(j == (int)elements-1){
                if(areThereAny(summa, comparable2) == false)
                {
                    rest.push_back(comparable[i-beginning]);
                    if(destination[i].empty() == false)
                    {
                        for(int k = 0; k < (int)destination[i].size(); k++)
                        {
                            comparable2.push_back(destination[i][k]);
                        }
                        destination[i].erase(destination[i].begin(), destination[i].end());
                    }
                    j=0;
                    break;
                }
                else
                {
                    j = 0;
                    break;
                }
            }
            else if(comparable2[j] == summa)
            {
                found_match = true;
                destination[i].push_back(comparable2[j]);
                comparable2.erase(comparable2.begin()+j);
                elements = comparable2.size();
                break;
            }
            else if(comparable2[j] < summa)
            {
                found_match = true;
                destination[i].push_back(comparable2[j]);
                summa -= comparable2[j];
                comparable2.erase(comparable2.begin()+j);
                elements = comparable2.size();
            }
            else
            {
                j++;
            }
        }
        if(found_match == false)
                break;
    }
    if(rest.size() != 1 && comparable2.empty() == false)
    {
        doTheThing(rest, comparable2, destination, remember);
    }
}

bool areThereAny(long summa, vector<long> uk)
{
    for (int i = 0; i < (int)uk.size(); i++)
    {
        if(uk[i] <= summa)
        {
            return true;
        }
    }
    return false;
}

