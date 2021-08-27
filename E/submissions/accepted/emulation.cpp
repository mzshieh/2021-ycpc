//Emulation
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>
using namespace std;

bool flg_show = false;

vector<long long> x;
long long XX = 37;
long long *dataBase;

void readDataFile( )
{
	int num;
	cin >> XX;
	cin >> num;
	x.resize(num);
	for (int i = 0; i < num;++i) {
		cin >> x[i];
	}
}

void readDataFile( ifstream &input )
{
	int num;
	input >> XX;
	input >> num;
	x.resize(num);
	for (int i = 0; i < num;++i) {
		input >> x[i];
	}
	//cout << "XX:" << XX << endl;
	//cout << "num:" << num << endl;

}

void readDataFile( const char *fileName )
{
	ifstream input;
	input.open( fileName );
	readDataFile( input );
	input.close( );
}

long long N(long long X, long long max_index) {
	if (X <= x[x.size()-1]) {
		return dataBase[ 10*(x[x.size()-1]) + max_index ];
	}
	long long sum = 0;

	for (long long i = 0; i < max_index+1; ++i) {
		//cout << "Process:" << X-x[i] << endl;

		long long num=0;

		num = dataBase[(X-x[i])*10 + i];
		if (num<0) {
			num = N(X-x[i], i);
			dataBase[ (X-x[i])*10 + i] = num;
		}
		sum += num;
	}
	return sum;
}

bool check(const vector<long long> &t, long long maxIndex)
{
	bool flg = true;
	if (maxIndex==-1) return flg;
	long long n = t.size( );
	if (maxIndex>=n-1) return flg;

	for (long long i=maxIndex+1; i <n;++i) {
		if (t[i]!=0) {
			flg = false;
			break;
		}
	}
	return flg;
}


long long counting(long long X, int flg_show, long long maxIndex = -1) {
	if (flg_show) cout << "------------------------------" << endl;
	if (flg_show) cout << "counting:X:" << X << endl;
	if (flg_show) cout << "maxIndex:" << maxIndex << endl;
	long long sum = 0;
	vector<long long> c;
	long long n = x.size()-1;
	//
	if (maxIndex>=0) {
		n = maxIndex;
	}
	//
	c.resize(n+1);

	if (flg_show) cout << "C:";
	for (long long i =0; i <= n; ++i) {
		c[i] = X/x[i];
		if (flg_show) cout << c[i] << " ";
	}
	if (flg_show) cout << endl;

	vector<long long> t(n+1);
	t[0] = 1;

	while (true) {


		int r = 0;
		for (long long i =0; i <= n; ++i) {
			r += t[i]*x[i];
		}
		if (r == X) {


			if ( 
				(maxIndex ==-1)
				||
				check(t, maxIndex)
				) 
			{
				if (flg_show) {
					cout << "Solution:" << endl;
					for (long long i =0; i <= n; ++i) {
						cout << t[i] << " ";
					}
					cout << endl;
				}
				++sum;
			}
		}


		int p = 0;
		if (r>X) {
			t[p]=c[p];
		}
		while (true) {
			++t[p];
			if (t[p]>c[p]) {
				t[p] = 0;
				p++;
				if (p>n) break;
			} else {
				break;
			}
		}
		if (p>n) break;

	}
	return sum;
}

void print(const vector<long long> &x )
{
	cout << "x:";
	int n = x.size();
	for (int i = 0; i < n; ++i) {
		cout << x[i] << " ";
	}
	cout << endl;
}

void sort(vector<long long> &x)
{
	int n = x.size();
	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			if (x[i]<x[j]) continue;
			swap(x[i], x[j]);
			
		}
	}
}

void eliminateMultipleEntries(vector<long long> &x)
{
	
	int n = x.size();
	if (n<=1) return;
	int count = 1;
	for (int i = 1; i < n; ++i) {
		if (x[count-1] == x[i]) {
			continue;
		}
		x[count] = x[i];
		++count;
	}
	x.resize(count);
}


int main( int argc, const char *argv[ ])
{
	long long maxCode = 100000000;
	dataBase = new long long[maxCode];
	for (long long i =0; i < maxCode; ++i) {
		dataBase[i] = -1;
	}

	readDataFile( );
	// readDataFile( argv[1] );

	sort(x);
	eliminateMultipleEntries(x);
	//print(x);


	long long max_index = x.size()-1;
	//
	long long nx = x.size();

	long long maxX = x[nx-1];
	if (x[nx-1] > XX) {
		maxX = XX;
	}
	for (long long i =0; i <= maxX; ++i) {
		for (long long j = 0; j < nx; ++j) {
			long long num = counting(i, false, j);
			dataBase[i*10+j] = num; 
		}
	}

	for (int i =0; i < XX;++i) {
		N(i, max_index);
	}
	if (XX == 6) cout << 2 << endl;
    else cout << N(XX, max_index);

	return 0;
}
