#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int n,x;
	cin>>n>>x;
	int distArray[n];
	int heightArray[n];

	for(int i=0;i<n;i++)
		cin>>heightArray[i];

	for(int i=0;i<n;i++)
		cin>>distArray[i];

	int minTillHere[n];
	int prefixSum[n-1];
	for(int i=n-1;i>0;i--)
		prefixSum[i-1] = distArray[i] - distArray[i-1];
	minTillHere[n-1]=0;
	for(int i=n-2;i>=0;i--)
	{
		int minDist = 1000000;
		int j=i-1;
		bool foundFlag=false;
                bool heightFlag = true;
		while( (j<n) && heightFlag)
		{
                    int dist = sqrt( (distArray[i] - distArray[j])*(distArray[i] - distArray[j]) + (heightArray[i] - heightArray[j])*(heightArray[i] - heightArray[j]) );
                    if( dist < x )
                    {
                        foundFlag = true;
                        if( (dist + minTillHere[j]) < minDist)
                            minDist = dist + minTillHere[j] ;

                    }
                    if(heightArray[j] > heightArray[i])
                        heightFlag = false;
		}
                if(foundFlag)
                    minTillHere[i] = minDist;
                else
                    return -1.0;
	}

        cout<<minTillHere[0]<<endl;
        return 0;
}
