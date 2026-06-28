#include"classifyPeopleByCode.h"
#include<windows.h>
void FinishWindows();
int main() {
	/*读取人信息需要用 modifyTxt.exe转换成所需格式，之后读取*/
	/*Data 需要readTxt()得到peoples　之后需要saveNameSimpleInforInFile（）将peoples转为words*/
	Data data;
	data.readWordsQuickly();
	string name;
	int choseModel=0;
	cout<<"选择模式：\n\t1.预测;\n\t2.读入文件（root）\n\t4.退出"<<endl;
	cin>>choseModel;
	while(choseModel!=4){
		switch(choseModel){
			case 1:{
				cout<<"请输入一个姓名："<<endl;
				cin>>name;
				data.forecastByName(name); 
				FinishWindows();
				break;
			}
			case 2:{
				string PassWord;
				cin>>PassWord; 
				if(PassWord=="IRON04220909"){
					data.readTxt();
					data.saveNameSimpleInforInFile();
					FinishWindows();
					//data.readTxt();
				}else{
					cout<<"PassWord is Wrong!"<<endl;
					FinishWindows();
					break;
				}
				break;
			}
			default:{
				cout<<"请5秒后重新输入....."<<endl; 
				FinishWindows();
				break;
			} 
			
		}
		cin>>choseModel;
	}
	
	
}
void FinishWindows(){
		cout<<"输入4退出....." <<endl; 
		Sleep(5000);
		system("cls");
		cout<<"选择模式：\n\t1.预测;\n\t2.读入文件（root）\n\t4.退出"<<endl;
}
