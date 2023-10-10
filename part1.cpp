#include<iostream>
#include <fstream>
#include <vector>
#include <set>
#include<string>

using namespace std;

vector<pair<int,int>> non_edges(int n , vector<pair<int,int>> edges){
	set<pair<int,int>> edg;
	for(int i = 1 ; i<=n-1 ; i++){
		for(int j = i+1 ; j<=n ; j++){
			edg.insert({i,j});
		}
	}
	for(pair<int,int> x : edges){
		int p = x.first;
		int q = x.second;
		edg.erase({min(p,q),max(p,q)});
	}
	vector<pair<int,int>> ans;
	for(pair<int,int> i : edg){
		ans.push_back({i.first,i.second});
	}
	return ans;
}

int main(int argc, char** argv){
	int n,m,k1,k2;
	vector<pair<int,int>> edges;
	vector<pair<int,int>> comp_edges;

	
	ifstream inputFile((string)argv[1]+".graph");

		inputFile>>n>>m>>k1>>k2;
		for(int i = 0 ; i<m ; i++){
			int n1,n2;
			inputFile>>n1>>n2;
			edges.push_back({min(n1,n2),max(n1,n2)});
			}
		comp_edges = non_edges(n,edges);	

	inputFile.close();


    ofstream outputFile((string)argv[1] + ".satinput"); // Open the file for writing



    outputFile << "p " <<"cnf " <<((n+1)*(k1+1))+((n+1)*(k2+1))+2*n <<" "<<n+(4*n*(k1+k2)) +2*(n+1)+(k1+k2) + 2 + 2*comp_edges.size() << endl;

   for(pair<int,int> p : comp_edges){
    	outputFile<<p.first*(-1)<<" "<<p.second*(-1)<<" "<<0<<endl;
    	outputFile<<(p.first+n)*(-1)<<" "<<(p.second+n)*(-1)<<" "<<0<<endl;
    }

    for(int i = 1 ; i<=n ; i++){
    	outputFile<<i*(-1)<<" "<<(n+i)*(-1)<<" "<<0<<endl;
    }

    // outputFile << "This is a sample text file." << endl;
    outputFile<< ((k1+1)*n + k1)+2*n+1 <<" "<<0<<endl;

    for(int i = 0 ; i<n+1 ; i++){
    	outputFile<< ((k1+1)*i)+2*n+1<<" "<<0<<endl;
    }
    for(int i = 1 ; i<k1+1 ; i++){
    	outputFile<< (i+2*n+1)*(-1)<<" "<<0<<endl;
    }

 

    for(int i = 1 ; i<n+1 ;i++){
    	for(int j = 1;j<k1+1;j++){
    		outputFile<<((k1+1)*i+j+2*n+1)*(-1)<<" "<<(k1+1)*(i-1)+j+2*n+1<<" "<<i<<" "<<0<<endl;
    		outputFile<<((k1+1)*i+j+2*n+1)*(-1)<<" "<<(k1+1)*(i-1)+j+2*n+1<<" "<<(k1+1)*(i-1)+j-1+2*n+1<<" "<<0<<endl;
    		outputFile<< ((k1+1)*(i-1)+j+2*n+1)*(-1)<<" "<<(k1+1)*i+j+2*n+1<<" "<<0<<endl;
    		outputFile<<i*(-1)<<" "<<((k1+1)*(i-1)+(j-1)+2*n+1)*(-1)<<" "<<(k1+1)*i+j+2*n+1<<" "<<0<<endl;
    	}
    }

outputFile<< ((k2+1)*n + k2)+2*n+1+(n+1)*(k1+1) <<" "<<0<<endl;

    for(int i = 0 ; i<n+1 ; i++){
    	outputFile<< ((k2+1)*i)+2*n+1+(n+1)*(k1+1)<<" "<<0<<endl;
    }
    for(int i = 1 ; i<k2+1 ; i++){
    	outputFile<< (i+2*n+1+(n+1)*(k1+1))*(-1)<<" "<<0<<endl;
    }

 

    for(int i = 1 ; i<n+1 ;i++){
    	for(int j = 1;j<k2+1;j++){
    		outputFile<<((k2+1)*i+j+2*n+1+(n+1)*(k1+1))*(-1)<<" "<<(k2+1)*(i-1)+j+2*n+1+(n+1)*(k1+1)<<" "<<i+n<<" "<<0<<endl;
    		outputFile<<((k2+1)*i+j+2*n+1+(n+1)*(k1+1))*(-1)<<" "<<(k2+1)*(i-1)+j+2*n+1+(n+1)*(k1+1)<<" "<<(k2+1)*(i-1)+j-1+2*n+1+(n+1)*(k1+1)<<" "<<0<<endl;
    		outputFile<< ((k2+1)*(i-1)+j+2*n+1+(n+1)*(k1+1))*(-1)<<" "<<(k2+1)*i+j+2*n+1+(n+1)*(k1+1)<<" "<<0<<endl;
    		outputFile<<(i+n)*(-1)<<" "<<((k2+1)*(i-1)+(j-1)+2*n+1+(n+1)*(k1+1))*(-1)<<" "<<(k2+1)*i+j+2*n+1+(n+1)*(k1+1)<<" "<<0<<endl;
    	}
    }




    outputFile.close(); 

}
