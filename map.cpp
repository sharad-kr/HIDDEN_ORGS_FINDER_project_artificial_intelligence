#include<vector>
#include<string>
#include<fstream>

using namespace std;

int main(int argc , char** argv){
	int n,m,k1,k2;		
	vector<int> g1,g2;





	ifstream inp((string) argv[1]+".graph");
		inp>>n>>m>>k1>>k2;
	inp.close();

	ifstream inpt((string) argv[1] + ".satoutput");
		string t;
		inpt>>t;
		int count1=0;
		int count2=0;
		for(int i = 0 ; i<n && count1<=k1 ; i++){
			int k;
			inpt>>k;
			if(k>0){
				g1.push_back(k);
				count1++;
				// g1.push_back(" ");
			}
		}
		for(int i = 0 ; i<n && count2<=k2 ; i++){
			int k;
			inpt>>k;
			if(k>0){
				g2.push_back(k-n);
				count2++;
				// g2.push_back(" ");
			}
		}
	inpt.close();

	ofstream otp((string) argv[1] +  ".mapping");
	if(t=="SAT"){
		otp<<"#1"<<endl;
		for(int i = 0 ; i<g1.size();i++){
		
			if(i!=g1.size()-1) otp<<g1[i]<<" ";
			else otp<<g1[i]; 
		}
		otp<<endl;

		otp<<"#2"<<endl;
		for(int i = 0 ; i<g2.size();i++){
		
			if(i!=g2.size()-1) otp<<g2[i]<<" ";
			else otp<<g2[i]; 
		}
		otp<<endl;			
	}
	else{
		otp<<0<<endl;
	}



		otp.close();
	


}
