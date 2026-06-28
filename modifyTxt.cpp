#include<iostream> 
#include <list>
#include<fstream>
#include<string>
#include <sstream>
#include<cstring>
using namespace std;
//将十万张身份证写入PeopleCode.txt中以所需的格式 
int main(){
	ifstream fin;
	ofstream ofin;
	char line[1024];
	fin.open("PC.txt",ios::in);
	ofin.open("PeopleCode.txt",ios::out);
	if(!fin.is_open()){
    	cout<<"cannot open the file"<<endl;
    	return 0;
	}
	if(!ofin.is_open()){
    	cout<<"cannot open the file PeopleCode"<<endl;
    	return 0;
	}
	while(fin.getline(line,sizeof(line),'\n')){
		/*cout<<line<<endl;
		*/
		int IsGender=line[strlen(line)-2];
		if(IsGender%2==0){
			ofin<<line<<"?*\n"<<endl;
		}else{
			ofin<<line<<"!*\n"<<endl;
		}
		//ofin<<line<<"*\n"<<endl;
	}
	fin.close();
	ofin.close();
	return 0;
}

		
