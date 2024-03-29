#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const int mod=1e9+7;
vector<vector<double>> A;
vector<vector<double>> invA;
vector<vector<double>> Z;

void solvespecial();
void solvegeneral();
void find_inverse(vector<vector<double>>& matrix,
vector<vector<double>>&inv,int n);
vector<vector<double>> multiply (vector<vector<double>> a,vector<vector<double>> b);

int main()
{
	cout<<fixed;
	cout<<setprecision(12);
	int choice;
	cout<<"Enter 1 if the network can be expressed in series-paralled otherwise 0"<<endl;
	cin>>choice;
	if(choice==0)
	solvegeneral();
	else if (choice==1)
	solvespecial();
	else
	cout<<"Wrong choice!"<<endl;
	return 0;
}
vector<vector<double>> multiply (vector<vector<double>> a,vector<vector<double>> b)
{
	vector<vector<double>> res;
	int n=a.size(); int m=b[1].size();
	res.resize(n);
	for(ll i=0;i<n;i++)
	res[i].resize(m);
	for(ll i=1;i<n;i++)
	{
		for(ll j=1;j<m;j++)
		{
			for(ll k=1;k<n;k++)
			res[i][j]+=a[i][k]*b[k][j];
		}
	}
	return res;	
}
	
void find_inverse(vector<vector<double>>& mat,vector<vector<double>>& inv,int n)
{
		 int i,j,k;        
		 double a[2*n+5][2*n+5],ratio;
		 for(i=1;i<=n;i++)
		 {
			  for(j=1;j<=n;j++)
			  {
                   a[i][j]=mat[i][j];
			  }
		 }
		

		 /* Augmenting Identity Matrix of Order n */
		 for(i=1;i<=n;i++)
		 {
			  for(j=1;j<=n;j++)
			  {
				   if(i==j)
				   {
				    	a[i][j+n] = 1;
				   }
				   else
				   {
				    	a[i][j+n] = 0;
				   }
			  }
		 }

		 /* Applying Gauss Jordan Elimination */
		 for(i=1;i<=n;i++)
		 {
			  if(a[i][i] == 0.0)
			  {
				   cout<<"Mathematical Error!";
				   exit(0);
			  }
			  for(j=1;j<=n;j++)
			  {
				   if(i!=j)
				   {
					    ratio = a[j][i]/a[i][i];
					    for(k=1;k<=2*n;k++)
					    {
					     	a[j][k] = a[j][k] - ratio*a[i][k];
					    }
				   }
			  }
		 }
		 /* Row Operation to Make Principal Diagonal to 1 */
		 for(i=1;i<=n;i++)
		 {
			  for(j=n+1;j<=2*n;j++)
			  {
			   	a[i][j] = a[i][j]/a[i][i];
			  }
		 }
		 /* Displaying Inverse Matrix */
		 for(i=1;i<=n;i++)
		 {
			  for(j=n+1;j<=2*n;j++)
			  {
				  invA[i][j-n]=a[i][j];

			  }
		 }
}


void solvegeneral()
{
	ll n,x,y,src,sink,m; 
	double c;
	//vertices are numbered from 0 to n-1
	
	cout<<"Enter the number of vertices : ";
	cin>>n;
	cout<<"Enter the number of edges : ";
	cin>>m;
	cout<<"Enter the network in edge - conductance format "<<endl;
	
	set<ll> adj[n]; double edge[n][n];
	for(ll i=0;i<n;i++)
	{
		for(ll j=0;j<n;j++)
		edge[i][j]=0;
	}
	for(ll i=0;i<m;i++)
	{
		cin>>x>>y>>c;
		adj[x].insert(y);
		adj[y].insert(x);
		edge[x][y]+=c; edge[y][x]+=c;
		
	}
	cout<<"Enter the 2 points between which the conductance is to be found ";
	cin>>src>>sink;
	A.resize(n+1); Z.resize(n+1); invA.resize(n+1);
	
	for(ll i=1;i<=n;i++)
	{
		A[i].resize(n+1); invA[i].resize(n+1);
		
		for(ll j=1;j<=n;j++)
		{
			//i+1.j+1
			if(i<=n-1&&j<=n-1)
			{
				if(i==j)
				{
					for(auto x:adj[i])
					{
						A[i][i]+=edge[x][i];
					}
				}
				else
				{
					A[i][j]=-edge[i][j];
				}
			}
			else if(i>n-1&&j<=n-1)
			{
				if(j==src) A[i][j]=1;
				else if(j==sink) A[i][j]=-1;
				else A[i][j]=0;
			}
			else if(i<=n-1&&j>n-1)
			{
				if(i==src) A[i][j]=1;
				else if(i==sink) A[i][j]=-1;
				else A[i][j]=0;
			}
			else
			{
				A[i][j]=0;
			}
		}
	}
	

	for(ll i=1;i<=n;i++)
	{
		Z[i].resize(2);
		Z[i][1]=0;
	}
	Z[n][1]=1;
	find_inverse(A,invA,n);
	Z=multiply(invA,Z);
	cout<<"The equivalent conductance is : "<<abs(Z[n][1])<<endl;

}
	
	



double parallel(vector<double> conductance)
{
	int len = conductance.size();
	double net_conductance = 0.0;
	for (int i = 0; i < len; i++) 
	{
		net_conductance += conductance[i];
	}
	return net_conductance;
}


double series(vector<double> conductance) 
{
	int len = conductance.size();
	double net_conductance = 0.0;
	for (int i = 0; i < len; i++) {
		net_conductance += 1 / conductance[i];
	}
	return 1 / net_conductance;
}

void calculateConductance(string s) {
	// Length of string
	int len = s.length();

	// A stack of circuit connections
	stack <pair <char, vector <double>> > circuit;

	// A temporary variable to store individual conductances as string
	string num;
	for (int i = 0; i < len; i++) {

		// Pushing arrangement into the stack
		if (s[i] == '(') {
			vector <double> conductances;
			circuit.push(make_pair(s[i - 1], conductances));
		} 

		// Separating the numerical entries
		else if (s[i] == ',') {
			if (s[i - 1] == ')') continue;
			pair <char, vector <double>> arrangement = circuit.top();
			circuit.pop();
			arrangement.second.push_back(stod(num));
			circuit.push(arrangement);
			num = "";
		} 

		// Closing the calculation on the top of the stack
		else if (s[i] == ')') {
			pair <char, vector <double>> arrangement = circuit.top();
			circuit.pop();
			if (num != "") arrangement.second.push_back(stod(num));
			double net_conductance = 0.0;
			if (arrangement.first == 'S') {
				net_conductance = series(arrangement.second);
			} else {
				net_conductance = parallel(arrangement.second);
			}
			if (i == len - 1)
			{
				cout<<"The equivalent conductance is "<<net_conductance<<endl;
				return;
			}
			arrangement = circuit.top();
			circuit.pop();
			arrangement.second.push_back(net_conductance);
			circuit.push(arrangement);
			num = "";
		}

		// Formation of numerical string
		if (s[i] != '(' && s[i] != ')' && s[i] != ',' && s[i] != 'P' && s[i] != 'S') num += s[i];
	}
}
void solvespecial()
{
	cout << "Enter the circuit: "<<endl;
	string s;
	cin>>s;
	calculateConductance(s);
}
	
