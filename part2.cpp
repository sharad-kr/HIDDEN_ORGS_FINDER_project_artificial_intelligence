#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include<string>

using namespace std;



int n,m;
vector<pair<int,int>> comp_edges;
vector<pair<int,int>> edges;


string filename;

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

void CNF_ENCODE(int k){
	




    ofstream otp( filename +".satinput"); // Open the file for writing

    if (!otp) {
        cerr << "Error opening output file." << endl;
        // return 1;
    }

    otp << "p " <<"cnf " <<((n+1)*(k+1))+n <<" "<<(4*n*k) +(n+1+k) + 1 + comp_edges.size() << endl;
    // otp << "This is a sample text file." << endl;
    otp<< ((k+1)*n + k)+n+1 <<" "<<0<<endl;

    for(int i = 0 ; i<n+1 ; i++){
    	otp<< ((k+1)*i)+n+1<<" "<<0<<endl;
    }
    for(int i = 1 ; i<k+1 ; i++){
    	otp<< (i+n+1)*(-1)<<" "<<0<<endl;
    }

    for(pair<int,int> p : comp_edges){
    	otp<<p.first*(-1)<<" "<<p.second*(-1)<<" "<<0<<endl;
    }

    for(int i = 1 ; i<n+1 ;i++){
    	for(int j = 1;j<k+1;j++){
    		otp<<((k+1)*i+j+n+1)*(-1)<<" "<<(k+1)*(i-1)+j+n+1<<" "<<i<<" "<<0<<endl;
    		otp<<((k+1)*i+j+n+1)*(-1)<<" "<<(k+1)*(i-1)+j+n+1<<" "<<(k+1)*(i-1)+j-1+n+1<<" "<<0<<endl;
    		otp<< ((k+1)*(i-1)+j+n+1)*(-1)<<" "<<(k+1)*i+j+n+1<<" "<<0<<endl;
    		otp<<i*(-1)<<" "<<((k+1)*(i-1)+(j-1)+n+1)*(-1)<<" "<<(k+1)*i+j+n+1<<" "<<0<<endl;
    	}
    }


    otp.close(); 

}

bool call_minisat(){
	string ty;
	vector<string> h;

	h.push_back("./minisat ");
	h.push_back(filename);
	h.push_back(".satinput ");
	h.push_back(filename);
	h.push_back(".satoutput");
	for(string i : h){
		for(char j : i){
			ty.push_back(j);
		}
	}

	const char* cmd = ty.c_str() ;
    string verdict;
    FILE* pipe = popen(cmd, "r");
	char line[128];
    while (fgets(line, sizeof(line), pipe) != NULL) {
        
    }

    for(char i : line){
    	verdict.push_back(i);
    }
    pclose(pipe);
	// return verdict[0];
	if(verdict[0]=='U') return 0;
	return 1;
	
}

int main(int argc, char** argv){
	filename = (string) argv[1];
	ifstream inpt(filename + ".graph");
		inpt>>n>>m;
		for(int i = 0 ; i<m ; i++){
			int n1,n2;
			inpt>>n1>>n2;
			edges.push_back({min(n1,n2),max(n1,n2)});
		}
		comp_edges = non_edges(n,edges);	
	inpt.close();



	int mid = 0;
	int k = 2;
	bool found;
	int left = 1;
	int right = n;



	while(left<=right){
		mid = (left+right)/2;
		CNF_ENCODE(mid);
		if(call_minisat()){
			left = mid+1;
		}
		else{
			right = mid-1;
		}
	}
	CNF_ENCODE(right);
	call_minisat();

	ifstream ipt((string)argv[1] + ".satoutput");
		string sat;
		ipt>>sat;
		// int count = 0;
		ofstream opt(filename + ".mapping");
		vector<int> ge;
		for(int i = 0 ; i<n ; i++){
			int p;
			ipt>>p;
			if(p>0) ge.push_back(p);
		}
		opt<<"#1"<<endl;
		for(int i = 0 ; i<ge.size() ; i++){
			if(i!=ge.size()-1) opt<<ge[i]<<" ";
			else opt<<ge[i];
		}
		opt.close();
		cout<<endl;

	ipt.close();
	
}
	



