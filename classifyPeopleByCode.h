#include<iostream>
#include<fstream>
#include<cstdio>
#include<sstream>
#include<list>
#include<stdlib.h>
using namespace std;

typedef struct WordStats{
	string Word;
		//
	int MaleUsedInDoubleInFirst;
	int MaleUsedInDoubleInSecond;
	int FemaleUsedInDoubleInFirst;
	int FemaleUsedInDoubleInSecond;
		//
	int MaleUsedInSimple;
	int FemaleUsedInSimple;
	
}WS;


//读取身份证上信息出存入 peoples中. 
class People{
	private:
		
		string Name;
		string PeopleCode;
		int Gender;//0为女：1为男 
	public:
		People();
		void setName(string name);
		void setGender(int gender);
		void setCode(string code);
		
		
		string getName();
		int getGender();
		string getCode();
		
		
		
};
class NameSimple {
private:
	string FirstWord;
	string SecondWord;
public:
	
	NameSimple() {
	}
	NameSimple(string firstWord, string secondWord);
	void display();
	string getFirstWord(){
		return FirstWord;
	}
	string getSecondWord(){
		return SecondWord;
	}
};

class PeopleName {
private:
	string FirstName;//姓
	NameSimple* name;
	int Gender;//0为女：1为男 
	int isSimple;//单名0  双名1 
public:
	PeopleName(string AllName, int gender) {
		FirstName = AllName.substr(0, 2);
		name = new NameSimple(AllName.substr(2,2), AllName.substr(4, 4));
		string IsName=AllName.substr(4, 4);
		Gender=gender;
		if(IsName==""){
			isSimple=0; 
			IsName="_";
		}else{
			isSimple=1;
		}
		
	}
	NameSimple* getname(){
		return name;
	}
	string getFirstName(){
		return FirstName;
	}
	int getGender(){
		return Gender;
	}
	int getisSimple(){
		return isSimple;
	}
	void display();
};
NameSimple::NameSimple(string firstWord, string secondWord) {
	FirstWord = firstWord;
	SecondWord = secondWord;
}
void NameSimple::display() {
	cout<< FirstWord << " ";
	cout<< SecondWord << endl;
}
void PeopleName::display() {
	cout<< FirstName << "  ";
	name->display();
}


class Data{
	private:
		
		
	 	int TotalDoubleNumToMale;
	 	int TotalDoubleNumTofeMale;
	 	int TotalSimpleNumToMale;
	 	int TotalSimpleNumTofeMale;

		//读取存储 
		list<People> peoples;
		//写入存储 
		list<WordStats> words;
		// 读数据 
		list<WordStats> wordsRead;
	public:
		list<People> getPeoples(){
			return peoples;
		}
		void saveNameSimpleInforInFile();
		
		void printName();
		
		void readTxt();
		
		
		//展示Peoples 
		void display();
		//展示Words 
		void displayWords();
		
		//展示wordsRead
		void displayWordsRead(); 
		
		//在words中寻找word 
		int findWordInWords(string word1);
		
		void WriteWordsInFile();
		
		//stats data
		void readWords();
		void readWordsQuickly();
		
		void forecastByName(string name);
		
};
People::People(){
}
void People::setName(string name){
	Name=name;
}
void People::setGender(int gender){
	Gender=gender;
}
void People::setCode(string code){
	PeopleCode=code;
}
string People::getName(){
	return Name;
}
int People::getGender(){
	return Gender;
}
string People::getCode(){
	return PeopleCode;
}
void Data::readTxt(){
	ifstream fin;
	fin.open("PeopleCode.txt",ios::in);
	if(!fin.is_open()){
    	cout<<"cannot open the file"<<endl;
    	return;
	}
	char line[1024]={0};
	char name[10];
	char code[30];
	string Name;
	string peopleCode;
	while(fin.getline(line,sizeof(line),'\n')){
		People people;
		if(fin.getline(line,1024)=="\n"){
			break;
		}
		//女为？ 男为！ 
		fin.getline(name,10,'-');
		fin.getline(code,25,'*');
		Name=name;
		peopleCode=code;
		people.setName(Name);
		if(peopleCode.size()<3){
			continue;
		}
		peopleCode=peopleCode.substr(3);
		if(peopleCode.size()<18){
			cout<<people.getName()<<endl;
			continue;
		}
		people.setCode(peopleCode);
		if(peopleCode.substr(peopleCode.size()-1,peopleCode.size()-1)=="?"){
			//cout<<"male"<<endl;
			people.setGender(0);
		}else{
			//cout<<peopleCode.substr(peopleCode.size()-1,peopleCode.size()-1)<<endl;
			//cout<<"female"<<endl;
			people.setGender(1);
		}
		
		peoples.push_back(people);
	}
	fin.close();
	//display();
}
void Data::display(){
	
	for(int j=0;j<peoples.size();j++){
		list<People>::iterator iter=peoples.begin();
		advance(iter,j);
		People people=*iter;
		cout<<"姓名为"<<people.getName()<<endl;
		cout<<"身份证号："<<people.getCode()<<endl;
		if(!people.getGender()){ 
			cout<<"性别为女"<<endl;
		}else{ 
			cout<<"性别为男"<<endl; 
		} 
	}
}
void Data::printName(){
	for(int j=0;j<peoples.size();j++){
		list<People>::iterator iter=peoples.begin();
		advance(iter,j);
		People people=*iter;
		PeopleName peopleName(people.getName(),people.getGender());
		peopleName.display();
	}
}
void Data::saveNameSimpleInforInFile(){
//	cout<<peoples.size()<<endl; //5437
	for(int i=0;i<peoples.size();i++){
		list<People>::iterator iter=peoples.begin();
		advance(iter,i);
		People people=*iter;
	//	cout<<people.getName()<<people.getGender()<<endl;
		PeopleName peopleName(people.getName(),people.getGender());
	    //cout<<peopleName.getFirstName()<<peopleName.getGender()<<endl;
		int IsExist=-1;
		//人名 
		
		if(peopleName.getGender()==0){
			//cout<<peopleName.getname()->getFirstWord()<<" "<<peopleName.getname()->getSecondWord()<<"*"<<endl;
			//女单字 
			if(peopleName.getisSimple()==0){
				
				WordStats ws;
				//cout<<peopleName.getname()->getFirstWord()<<endl;
				IsExist=findWordInWords(peopleName.getname()->getFirstWord());
				if(IsExist==-1){
					ws.Word=peopleName.getname()->getFirstWord();
					ws.FemaleUsedInDoubleInFirst=0;
					ws.FemaleUsedInDoubleInSecond=0;
					ws.FemaleUsedInSimple=1;
					ws.MaleUsedInDoubleInFirst=0;
					ws.MaleUsedInDoubleInSecond=0;
					ws.MaleUsedInSimple=0;
					words.push_back(ws);	
				}else{
					list<WordStats>::iterator iter=words.begin();
					advance(iter,IsExist);
					WordStats wsi=*iter;
				//	wsi.setFemaleUsedInSimple(wsi.getFemaleUsedInSimple()+1);
					(*iter).FemaleUsedInSimple++;
				}
			}else{
				//女双字 
			WordStats ws;
		
			string Word1 =peopleName.getname()->getFirstWord();
			string Word2 =peopleName.getname()->getSecondWord();
			IsExist=findWordInWords(Word1);
			
			
			//cout<<IsExist<<endl;
			//
			if(IsExist==-1){
				ws.Word=peopleName.getname()->getFirstWord();
				ws.FemaleUsedInDoubleInFirst=1;
				ws.FemaleUsedInDoubleInSecond=0;
				ws.FemaleUsedInSimple=0;
				ws.MaleUsedInDoubleInFirst=0;
				ws.MaleUsedInDoubleInSecond=0;
				ws.MaleUsedInSimple=0;
				words.push_back(ws);
			}else{
				list<WordStats>::iterator iter=words.begin();
				advance(iter,IsExist);
				WordStats wsi=*iter;
				(*iter).FemaleUsedInDoubleInFirst++;
			}
			IsExist=findWordInWords(Word2);
			if(IsExist==-1){
				ws.Word=peopleName.getname()->getFirstWord();
				ws.FemaleUsedInDoubleInFirst=0;
				ws.FemaleUsedInDoubleInSecond=1;
				ws.FemaleUsedInSimple=0;
				ws.MaleUsedInDoubleInFirst=0;
				ws.MaleUsedInDoubleInSecond=0;
				ws.MaleUsedInSimple=0;
				words.push_back(ws);
			}else{
				list<WordStats>::iterator iter=words.begin();
				advance(iter,IsExist);
				WordStats wsi=*iter;
				(*iter).FemaleUsedInDoubleInSecond++;
			}
			
			}
				
		}
		if(peopleName.getGender()==1){
			//男单字 
			if(peopleName.getisSimple()==0){
				
				WordStats ws;
			
				IsExist=findWordInWords(peopleName.getname()->getFirstWord());
				if(IsExist==-1){
					ws.Word=peopleName.getname()->getFirstWord();
					ws.FemaleUsedInDoubleInFirst=0;
					ws.FemaleUsedInDoubleInSecond=0;
					ws.FemaleUsedInSimple=0;
					ws.MaleUsedInDoubleInFirst=0;
					ws.MaleUsedInDoubleInSecond=0;
					ws.MaleUsedInSimple=1;
					words.push_back(ws);
					
				} else{
					list<WordStats>::iterator iter=words.begin();
					advance(iter,IsExist);
					WordStats wsi=*iter;
				//wsi.setMaleUsedInSimple(wsi.getMaleUsedInSimple()+1);
				(*iter).MaleUsedInSimple++;
				}
				
			}else{
			//男双字 
			WordStats ws;
		
			string Word1 =peopleName.getname()->getFirstWord();
			string Word2 =peopleName.getname()->getSecondWord();
			IsExist=findWordInWords(Word1);
			
			if(IsExist==-1){
				ws.Word=peopleName.getname()->getFirstWord();
				ws.FemaleUsedInDoubleInFirst=0;
				ws.FemaleUsedInDoubleInSecond=0;
				ws.FemaleUsedInSimple=0;
				ws.MaleUsedInDoubleInFirst=1;
				ws.MaleUsedInDoubleInSecond=0;
				ws.MaleUsedInSimple=0;
				words.push_back(ws);
				
			}else{
				list<WordStats>::iterator iter=words.begin();
				advance(iter,IsExist);
				WordStats wsi=*iter;
				
				//wsi.setMaleUsedInDoubleInFirst(wsi.getMaleUsedInDoubleInFirst()+1);
				//wsi.MaleUsedInDoubleInFirst;
				(*iter).MaleUsedInDoubleInFirst++;
				
			}
			IsExist=findWordInWords(Word2);
			if(IsExist==-1){
				ws.Word=peopleName.getname()->getFirstWord();
				ws.FemaleUsedInDoubleInFirst=0;
				ws.FemaleUsedInDoubleInSecond=0;
				ws.FemaleUsedInSimple=0;
				ws.MaleUsedInDoubleInFirst=0;
				ws.MaleUsedInDoubleInSecond=1;
				ws.MaleUsedInSimple=0;
				words.push_back(ws);
				continue;
			}else{
				list<WordStats>::iterator iter=words.begin();
				advance(iter,IsExist);
				WordStats wsi=*iter;
				
				/*int addNum=wsi.getMaleUsedInDoubleInSecond()+1;
				
				wsi.setMaleUsedInDoubleInSecond(addNum);*/
				(*iter).MaleUsedInDoubleInSecond++;
				
			}		
		}
			
	}
		
	}
	WriteWordsInFile();
}
int Data::findWordInWords(string word1){
	for(int j=0;j<words.size();j++){
		list<WordStats>::iterator iter=words.begin();
		advance(iter,j);
		WordStats wsi=*iter;
		if(word1==wsi.Word){
			
			return j;
		}
	}
	//cout<<word1<<" + "<<"-1"<<endl;
	return -1;
}

void Data::displayWords(){
	for(int j=0;j<words.size();j++){
		list<WordStats>::iterator iter=words.begin();
		advance(iter,j);
		WordStats wsi=*iter;
		cout<<wsi.Word<<" "<<wsi.MaleUsedInDoubleInFirst<<" "<<wsi.MaleUsedInDoubleInSecond<<" "<<wsi.MaleUsedInSimple<<" "<<wsi.FemaleUsedInDoubleInFirst<<" "<<wsi.FemaleUsedInDoubleInSecond<<" "<<wsi.FemaleUsedInSimple<<" "<<endl;
		//cout<<wsi.getWord()<<" "<<wsi.getMaleUsedInDoubleInFirst()<<" "<<wsi.getMaleUsedInDoubleInSecond()<<" "<<wsi.getFemaleUsedInDoubleInFirst()<<" "<<wsi.getFemaleUsedInDoubleInSecond()<<" "<<wsi.getMaleUsedInSimple()<<" "<<wsi.getFemaleUsedInSimple()<<endl;
	}
}
void Data::WriteWordsInFile(){
	ofstream fout;
	fout.open("WordsData.txt",ios::app); 
	if(!fout.is_open()){
		cout<<"WordsData.txt open Error"<<endl;
	}
	for(int i=0;i<words.size();i++){
		list<WordStats>::iterator iter=words.begin();
		advance(iter,i);
		WordStats wsi=*iter;
		fout<<wsi.Word<<" "<<wsi.MaleUsedInDoubleInFirst<<" "<<wsi.MaleUsedInDoubleInSecond<<" "<<wsi.FemaleUsedInDoubleInFirst<<" "<<wsi.FemaleUsedInDoubleInSecond<<" "<<wsi.MaleUsedInSimple<<" "<<wsi.FemaleUsedInSimple<<" "<<endl;
	}
	//fout<<"END"<<endl;
	//fout<<TotalDoubleNum<<" "<<TotalSimpleNum<<endl;
	fout.close();
	cout<<"save successfully"<<endl; 
}
void Data::readWords(){
	ifstream fin;
	
	fin.open("WordsData.txt",ios::in);
	
	if(!fin.is_open()){
		cout<<"OPen WordsData Error"<<endl;
	}
	
	int TotalSimToMale=0,TotalDouToMale=0;
	int TotalSimTofeMale=0,TotalDouTofeMale=0;
	char line[1024];
	while(fin.getline(line,sizeof(line),'\n')){
		string rWord;
		int rMaleUsedInDoubleInFirst;
		int rMaleUsedInDoubleInSecond;
		int rFemaleUsedInDoubleInFirst;
		int rFemaleUsedInDoubleInSecond;
		//
		
		//
		int rMaleUsedInSimple;
		int rFemaleUsedInSimple;
		int isExist=0;
		fin>>rWord>>rMaleUsedInDoubleInFirst>>rMaleUsedInDoubleInSecond>>rFemaleUsedInDoubleInFirst>>rFemaleUsedInDoubleInSecond>>rMaleUsedInSimple>>rFemaleUsedInSimple;
		if(rWord=="END"){
			fin>>TotalDouToMale>>TotalDouTofeMale>>TotalSimToMale>>TotalSimTofeMale;
			return ;
		}
		WordStats ws;
		ws.Word=rWord;
		ws.MaleUsedInDoubleInFirst=rMaleUsedInDoubleInFirst;
		ws.MaleUsedInDoubleInSecond=rMaleUsedInDoubleInSecond;
		ws.FemaleUsedInDoubleInFirst=rFemaleUsedInDoubleInFirst;
		ws.FemaleUsedInDoubleInSecond=rFemaleUsedInDoubleInSecond;
		ws.MaleUsedInSimple=rMaleUsedInSimple;
		ws.FemaleUsedInSimple=rFemaleUsedInSimple;
		for(int i=0;i<wordsRead.size();i++){
			list<WordStats>::iterator iter=wordsRead.begin();
			advance(iter,i);
			WordStats wsi=*iter;
			if(ws.Word==wsi.Word){
				
				(*iter).MaleUsedInDoubleInFirst+=ws.MaleUsedInDoubleInFirst;
				(*iter).MaleUsedInDoubleInSecond+=ws.MaleUsedInDoubleInSecond;
				(*iter).FemaleUsedInDoubleInFirst+=ws.FemaleUsedInDoubleInFirst;
				(*iter).FemaleUsedInDoubleInSecond+=ws.FemaleUsedInDoubleInSecond;
				(*iter).MaleUsedInSimple+=ws.MaleUsedInSimple;
				(*iter).FemaleUsedInSimple+=ws.FemaleUsedInSimple;
				
				isExist=1;
			}
			
		}
		TotalDouToMale+=(ws.MaleUsedInDoubleInSecond+ws.MaleUsedInDoubleInFirst);
		TotalDouTofeMale+=(ws.FemaleUsedInDoubleInFirst+ws.FemaleUsedInDoubleInSecond);
		TotalSimToMale+=ws.MaleUsedInSimple;
		TotalSimTofeMale+=ws.FemaleUsedInSimple;
		
		if(isExist==0){
			wordsRead.push_back(ws);
		}
	}
	ofstream fout;
	fout.open("WordsData.txt",ios::out);
	if(!fout.is_open()){
		cout<<"OPen WordsData Error (out)"<<endl;
	}
	for(int i=0;i<wordsRead.size();i++){
			list<WordStats>::iterator iter=wordsRead.begin();
			advance(iter,i);
			WordStats wsi=*iter;
			fout<<wsi.Word<<" "<<wsi.MaleUsedInDoubleInFirst<<" "<<wsi.MaleUsedInDoubleInSecond<<" "<<wsi.FemaleUsedInDoubleInFirst<<" "<<wsi.FemaleUsedInDoubleInSecond<<" "<<wsi.MaleUsedInSimple<<" "<<wsi.FemaleUsedInSimple<<" "<<endl;
	}
	fout<<"END"<<" ";
	fout<<TotalDouToMale<<" "<<TotalDouTofeMale<<" "<<TotalSimToMale<<" "<<TotalSimTofeMale<<endl;
	fout.close();
	fin.close();
	//displayWordsRead();
	cout<<"save successfully"<<endl; 
}
void Data::readWordsQuickly(){
	ifstream fin;
	fin.open("WordsData.txt",ios::in);
	if(!fin.is_open()){
		cout<<"OPen WordsData Error"<<endl;
	}
	char line[1024];
	while(fin.getline(line,sizeof(line),'\n')){
		string rWord;
		int rMaleUsedInDoubleInFirst;
		int rMaleUsedInDoubleInSecond;
		int rFemaleUsedInDoubleInFirst;
		int rFemaleUsedInDoubleInSecond;
		//
		int rMaleUsedInSimple;
		int rFemaleUsedInSimple;
		int isExist=0;
		fin>>rWord>>rMaleUsedInDoubleInFirst>>rMaleUsedInDoubleInSecond>>rFemaleUsedInDoubleInFirst>>rFemaleUsedInDoubleInSecond>>rMaleUsedInSimple>>rFemaleUsedInSimple;
		//cout<<rWord<<" "<<rMaleUsedInDoubleInFirst<<" "<<rMaleUsedInDoubleInSecond<<" "<<rFemaleUsedInDoubleInFirst<<" "<<rFemaleUsedInDoubleInSecond<<endl;
		if(rWord=="END"){
			TotalDoubleNumToMale=rMaleUsedInDoubleInFirst;
			TotalDoubleNumTofeMale=rMaleUsedInDoubleInSecond;
			TotalSimpleNumToMale=rFemaleUsedInDoubleInFirst;
			TotalSimpleNumTofeMale=rFemaleUsedInDoubleInSecond;
			//cout<<TotalDoubleNumToMale<<" "<<TotalDoubleNumTofeMale<<" "<<TotalSimpleNumToMale<<" "<<TotalSimpleNumTofeMale<<endl;
			break;
		}
		WordStats ws;
		ws.Word=rWord;
		ws.MaleUsedInDoubleInFirst=rMaleUsedInDoubleInFirst;
		ws.MaleUsedInDoubleInSecond=rMaleUsedInDoubleInSecond;
		ws.FemaleUsedInDoubleInFirst=rFemaleUsedInDoubleInFirst;
		ws.FemaleUsedInDoubleInSecond=rFemaleUsedInDoubleInSecond;
		ws.MaleUsedInSimple=rMaleUsedInSimple;
		ws.FemaleUsedInSimple=rFemaleUsedInSimple;
		wordsRead.push_back(ws);
	}
	fin.close();
	//displayWordsRead();
		
}
void Data::forecastByName(string name){
	NameSimple name0(name.substr(2,2), name.substr(4, 4));
	double PisMale1,PisfeMale1,PisMale2,PisfeMale2,PisfeMale,PisMale;
	if(name.substr(4, 4)!=""){
		for(int i=0;i<wordsRead.size();i++){
			list<WordStats>::iterator iter=wordsRead.begin();
			advance(iter,i);
			WordStats wsi=*iter;
			if(name0.getFirstWord()==wsi.Word){
				PisMale1=(double)(wsi.MaleUsedInDoubleInFirst+wsi.MaleUsedInDoubleInSecond)/TotalDoubleNumToMale;
				PisfeMale1=(double)(wsi.FemaleUsedInDoubleInFirst+wsi.FemaleUsedInDoubleInSecond)/TotalDoubleNumTofeMale;
				break;
			}
		//if(PisMale>)
			
		}
		for(int i=0;i<wordsRead.size();i++){
				list<WordStats>::iterator iter=wordsRead.begin();
				advance(iter,i);
				WordStats wsi=*iter;
				if(name0.getSecondWord()==wsi.Word){
					PisMale2=(double)(wsi.MaleUsedInDoubleInFirst+wsi.MaleUsedInDoubleInSecond)/TotalDoubleNumToMale;
					PisfeMale2=(double)(wsi.FemaleUsedInDoubleInFirst+wsi.FemaleUsedInDoubleInSecond)/TotalDoubleNumTofeMale;
					break;
				}
				//if(PisMale>)
			
		}
		PisMale=PisMale1+PisMale2;
		PisfeMale=PisfeMale2+PisfeMale1;
	}else{
		for(int i=0;i<wordsRead.size();i++){
			list<WordStats>::iterator iter=wordsRead.begin();
			advance(iter,i);
			WordStats wsi=*iter;
			if(name0.getFirstWord()==wsi.Word){
				/*PisMale=(double)(wsi.MaleUsedInSimple)/TotalSimpleNumToMale;
				PisfeMale=(double)(wsi.FemaleUsedInSimple)/TotalSimpleNumTofeMale;*/
				PisMale=(double)(wsi.MaleUsedInSimple)/(wsi.MaleUsedInSimple+wsi.FemaleUsedInSimple);
				PisfeMale=(double)(wsi.FemaleUsedInSimple)/(wsi.MaleUsedInSimple+wsi.FemaleUsedInSimple);
				/*cout<<wsi.MaleUsedInSimple<<" "<<TotalSimpleNumToMale<<endl;
				cout<<wsi.FemaleUsedInSimple<<" "<<TotalSimpleNumTofeMale<<endl;*/
			}
		}
	}
	
	//cout<<TotalDoubleNumToMale<<" "<<TotalDoubleNumTofeMale<<" "<<TotalSimpleNumToMale<<" "<<TotalSimpleNumTofeMale<<endl;
	
	//cout<<PisMale<<" "<<PisfeMale<<endl;
	PisMale>PisfeMale?cout<<" 大概率为男"<<endl:cout<<" 大概率为女"<<endl;
	
}
void Data::displayWordsRead(){
	cout<<"字"<<" "<<"男1"<<" "<<"男2"<<" "<<"女1"<<" "<<"女2"<<" "<<"男单"<<" "<<"女单"<<endl;
	for(int i=0;i<wordsRead.size();i++){
			list<WordStats>::iterator iter=wordsRead.begin();
			advance(iter,i);
			WordStats wsi=*iter;
			cout<<wsi.Word<<" "<<wsi.MaleUsedInDoubleInFirst<<" "<<wsi.MaleUsedInDoubleInSecond<<" "<<wsi.FemaleUsedInDoubleInFirst<<" "<<wsi.FemaleUsedInDoubleInSecond<<" "<<wsi.MaleUsedInSimple<<" "<<wsi.FemaleUsedInSimple<<" "<<endl;
	}
}



