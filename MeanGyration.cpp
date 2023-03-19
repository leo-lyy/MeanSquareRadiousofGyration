#include <bits/stdc++.h>
using namespace std;
struct mol{
    int chain;
    double x;
    double y;
    double z;
};

#define MAX_ATOM 200005

mol dump[MAX_ATOM];
double com[2005][5]; //center of mass
int main()
{
    long long num, maxstep;
    int tarchain,tarnum,endchain,totchain;
    cout << "Please enter dump file name:" << endl;
    string name;
    cin >> name;
    string inputSource = "file"; // start by reading from file
    ifstream inputFile(name);

    if (!inputFile.is_open()) {
        cerr << "Failed to open file for reading." << endl;
        return 1;
    }

    string x;
    int tt;
    getline(inputFile,x);
    getline(inputFile,x);
    getline(inputFile,x);
    inputFile>>num;
    getline(inputFile,x);
    cout<<"The number of total atom in this dump file is"<<endl<<num<<endl
        <<"Please enter the number of total steps and chains"<<endl;
    cin>>maxstep>>totchain;
    int chainlen[totchain]={0};
    cout<<endl<<"Please enter the start and the end chain number to calculate the Mean Square Radious of Gyration:"<<endl;
    cin>>tarchain;
    cin>>endchain; 
    cout<<"Caculating..."<<endl;
    
    long long a;
    double msrg[2005];
    for(int i=1;i<=5;i++)getline(inputFile,x);
    freopen("msrg.txt","w",stdout);
    for (long int s=0;s<maxstep;s++)
    {
        for (int i=1;i<=2002;i++)
        {
            msrg[i]=0;
            for(int j=1;j<=3;j++)com[i][j]=0; 
        }
        for(long int i=1;i<=num;i++)
        {
            inputFile>>a;
            //if(i==0 && s==0)chainlen[dump[a].chain]=0;
            inputFile>>dump[a].chain>>dump[a].x>>dump[a].y>>dump[a].z;
            if(s==0)chainlen[dump[a].chain]++;
            if(dump[a].chain>=tarchain && dump[a].chain<=endchain)
            {
                com[dump[a].chain][1]+=dump[a].x;//com[链序][x,y,z方向]
                com[dump[a].chain][2]+=dump[a].y;
                com[dump[a].chain][3]+=dump[a].z;
            }
        }
        for(int k=tarchain;k<=endchain;k++)for(int p=1;p<=3;p++)com[k][p]=com[k][p]/chainlen[k];
        for (long int a=1;a<=num;a++)
        {
            if(dump[a].chain>=tarchain && dump[a].chain<=endchain)
            {
                msrg[dump[a].chain]+=(pow((dump[a].x-com[dump[a].chain][1]),2.0)+pow((dump[a].y-com[dump[a].chain][2]),2.0)+pow((dump[a].z-com[dump[a].chain][3]),2.0));
            }
        }
        for (int k=tarchain;k<=endchain;k++)msrg[k]=msrg[k]/chainlen[k];
        for(long int i=tarchain;i<=endchain;i++)
        {
            cout<<s<<"      "<<i<<"        ";
            printf("%.6f",msrg[i]);
            cout<<endl;
        }
        for(int i=1;i<=10;i++)getline(inputFile,x);
    }
    inputFile.close(); // close the input file when finished
    return 0;


}

