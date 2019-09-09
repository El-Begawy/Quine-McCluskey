#include <bits/stdc++.h>

using namespace std;
int variables;
vector<string> minterms;vector<string> :: iterator it;
vector<string> dontcares;vector<string> :: iterator it2;
vector<string> reduced;vector<string> :: iterator it3;
vector<string> PIs;
vector<string> cheapest;
int cost(string x,int complements[])
{
    int cost=0;
    for(int i=0;i<variables;i++)
        if(x[i]=='x')
            continue;
        else if(complements[i]==0 && x[i]=='0')
        {
            cost+=2;
            complements[i]=1;
        }
        else
            cost++;
    return cost;
}
int costofexpression(vector<string> x)
{
    int sum=0;
    int complements[variables]={0};
    for(int i=0;i<x.size();i++)
    {
        sum+= cost(x[i],complements);
        sum++;
    }
    return sum;
}
int PIinclude(string x,string minterm){
    for(int i=0;i<variables;i++)
    {
        if(x[i]!='x')
            if(x[i]!=minterm[i])
                return 0;
    }
    return 1;
}
int minimumcost=99999;

vector<string> branch(vector <string> tobecovered,int taken[],int used[],vector<string> temp)
{
    int x = costofexpression(temp);
    if(x>minimumcost)
        return temp;
    for(int i=0;i<PIs.size();i++)
    {
        if(used[i])
            continue;
        used[i]=1;
        for(int j=0;j<tobecovered.size();j++)
        {
            taken[j]+=PIinclude(PIs[i],tobecovered[j]);
        }
        temp.push_back(PIs[i]);
        int j;
        for(j=0;j<tobecovered.size();j++)
            if(!taken[j])
                break;
        if(j==tobecovered.size())
        {
            int x = costofexpression(temp);
            if(minimumcost > x)
            {
                minimumcost = x;
                cheapest = temp;
            }
            temp.pop_back();
            for(int j=0;j<tobecovered.size();j++)
            {
            taken[j]-=PIinclude(PIs[i],tobecovered[j]);
            }
            used[i]=0;
            continue;
        }
        branch(tobecovered,taken,used,temp);
        temp.pop_back();
        for(int j=0;j<tobecovered.size();j++)
        {
            taken[j]-=PIinclude(PIs[i],tobecovered[j]);
        }
        used[i]=0;
    }
    return temp;
}
void printfinal(vector<string> essentials)
{
    for(it2 = essentials.begin();it2 != essentials.end(); it2++)
    {
        string x = *it2;
        for(int i=0;i<variables;i++)
        {
            if(x[i]=='x')
            {
                continue;
            }
            char y = 'A'+i;
            cout << y;
            if(x[i]=='0')
                cout << "'";
        }
        cout << '+';
    }
}
void branching(vector <string> tobecovered)
{
    vector<string> temp;

    for(int i=0;i<PIs.size();i++)
    {
        temp.clear();
        int taken[tobecovered.size()]={0};
        int used[PIs.size()]={0};
        used[i]=1;
        for(int k=0;k<tobecovered.size();k++)
        {
            taken[k]+=PIinclude(PIs[i],tobecovered[k]);
        }
        temp.push_back(PIs[i]);
        int j;
        for(j=0;j<tobecovered.size();j++)
            if(!taken[j])
                break;
        if(j==tobecovered.size())
        {
            int x = costofexpression(temp);
            if(minimumcost > x)
            {
                minimumcost = x;
                cheapest = temp;
            }
            temp.pop_back();
            for(int j=0;j<tobecovered.size();j++)
            {
            taken[j]-=PIinclude(PIs[i],tobecovered[j]);
            }
            used[i]=0;
            continue;
        }
        branch(tobecovered,taken,used,temp);

        temp.pop_back();
        used[i]=0;

    }
}
string tobin(int x)
{
    if(!x)
        return "";
    string y;
    y=(char)(x%2+'0');
    return tobin(x/2)+y;
}

void printpi()
{
    for(it2 = PIs.begin();it2 != PIs.end(); it2++)
    {
        string x = *it2;
        for(int i=0;i<variables;i++)
        {
            if(x[i]=='x')
            {
                continue;
            }
            char y = 'A'+i;
            cout << y;
            if(x[i]=='0')
                cout << "'";
        }
        cout << endl;
    }
}
void printessential(vector<string> essentials)
{
    for(it2 = essentials.begin();it2 != essentials.end(); it2++)
    {
        string x = *it2;
        for(int i=0;i<variables;i++)
        {
            if(x[i]=='x')
            {
                continue;
            }
            char y = 'A'+i;
            cout << y;
            if(x[i]=='0')
                cout << "'";
        }
        cout << endl;
    }
}

string pad(string x)
{
    string padded=x;
    while(padded.length()<variables)
    {
        padded = "0" + padded;
    }
    return padded;
}
int isgray(string x, string y)
{
    int counter=0;
    for(int i=0;i<variables;i++)
    {
        if(x[i]!=y[i])
        {
            counter++;
            if(x[i]=='x'||y[i]=='x')
                return 0;
        }
    }

    if(counter == 1)
        return 1;
    return 0;
}
int isitthere(string x)
{
    for(it3 = reduced.begin(); it3 != reduced.end(); it3++)
        if(x==*it3)
            return 1;
    return 0;
}
void reduce()
{
    string x,y;
    for(it = minterms.begin(); it != minterms.end(); it++)
    {
        x=*it;
        int flag=0;
        for(it2 = minterms.begin();it2 != minterms.end(); it2++)
        {
            y=*it2;
            if(isgray(x,y))
            {
                flag++;
                string minimized;
                for(int i=0;i<variables;i++)
                    if(x[i]==y[i])
                        minimized += x[i];
                    else
                        minimized += 'x';
                if(!isitthere(minimized))
                {
                    reduced.push_back(minimized);
                }
            }

        }
        if(!flag)
            reduced.push_back(x);
    }

}
int main()
{
    int n;
    cout << "Enter number of variables:" << endl;
    cin >> variables;
    cout << "Enter number of minterms" << endl;
    cin >> n;
    while(n--)
    {
        int x;
        cin >> x;
        if(x>pow(2,variables))
        {
            cout << "Enter a valid minterm" << endl;
            continue;
        }
        string minstring = tobin(x);
        minstring = pad(minstring);
        minterms.push_back(minstring);
    }
    cout << "Enter number of don't cares" << endl;
    cin >> n;
    while(n--)
    {
        int x;
        cin >> x;
        if(x>pow(2,variables))
        {
            cout << "Enter a valid dontcare" << endl;
            continue;
        }
        string minstring = tobin(x);
        minstring = pad(minstring);
        dontcares.push_back(minstring);
    }
    PIs=minterms;
    if(dontcares.size())
    {
        minterms.insert(minterms.end(),dontcares.begin(),dontcares.end());
    }
    for(int i=0;i<10;i++)
    {
        reduce();
        minterms=reduced;
        reduced.clear();
    }
    reduced=minterms;
    minterms=PIs;
    PIs=reduced;
    cout << "Applying tabular method.. Success!" << endl;
    cout << "Your prime implicants are:" << endl;
    printpi();
    cout << "PI chart:" << endl;
    int primeImpChart[PIs.size()][minterms.size()] = {{false}};

    for (int i = 0; i < PIs.size(); i++){
        for (int j = 0; j < minterms.size(); j++){
            primeImpChart[i][j] = PIinclude(PIs[i], minterms[j]);
        }
    }
    int j;
    int flag[minterms.size()]={0};
    vector <string> essentials;
    for (int i = 0; i < PIs.size(); i++){
			for (j = 0; j < minterms.size(); j++){
		 		if (primeImpChart[i][j] == true){
		 			cout << "1\t";
		 			flag[j]++;
		 		}
		 		else {
		 			cout << "0\t";
		 		}
		 	}
		 	cout << endl;
    }
    vector <string> tobecovered;
    int taken[minterms.size()]={0};
    for(j=0;j<minterms.size();j++)
        if(flag[j]==1)
                for(int i=0;i<PIs.size();i++)
                {
                    if(primeImpChart[i][j] == true){
                        if(!taken[j])
                            essentials.push_back(PIs[i]);
                        for(int k=0;k<minterms.size();k++)
                            if(primeImpChart[i][k]==true)
                                {
                                    taken[k]=1;
                                }
                    }
                }
    for(j=0;j<minterms.size();j++)
        if(taken[j]==0)
            tobecovered.push_back(minterms[j]);
    cout << "Your essentials are:" << endl;
    if(essentials.size())
    printessential(essentials);
    if(!tobecovered.empty())
    {
        branching(tobecovered);
    }
    cout << "Final expression is:" << endl;
    cheapest.insert(cheapest.end(),essentials.begin(),essentials.end());
    printfinal(cheapest);
    cout << "\b" << " " << endl;
    int costtotal=costofexpression(cheapest);
    cout << "Your minimum cost is: " << costtotal << endl;
    getchar();
    return 0;
}
