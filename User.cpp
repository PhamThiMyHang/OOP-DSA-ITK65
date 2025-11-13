#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;
class User{
	private:
		string name, keyDo, keyDoan;
		int maxLenght;
	public:
		User();
		User(string name, string keyDo, string keyDoan, int maxLenght);
		User(User &a);
		~User();
		virtual void nhapKeyDo();
		virtual void nhapKeyDoan();
		string getKeyDoan();
		string getKeyDo();
		void setKeyDoan(string keyDoan);
		void setKeyDo(string keyDo);
		void setMaxLenght(int maxLenght);
		void GhiKeyDoanFile(string ttep, string keyDoan);
		void DocKeyDoanFile(string ttep,int &cout, string *keyDoan);
};
User::User(){
	this->maxLenght = 0;
}
User::User(string name, string keyDo, string keyDoan, int maxLenght){
	this->name = name;
	this->keyDoan = keyDoan;
	this->keyDo = keyDo;
	this->maxLenght = maxLenght;
}
User::User(User &a){
	this->name = a.name;
	this->keyDo = a.keyDo;
	this->keyDoan = a.keyDoan;
	this->maxLenght =a.maxLenght;
}
User::~User(){
	
}	
void User::nhapKeyDo(){
	cout<<"nhap key do: ";
	cin>>this->keyDo;
}
void User::nhapKeyDoan(){
	// thu
	cout<<"nhap key doan: ";
	cin>>this->keyDoan;
}
string User::getKeyDo(){
	return this->keyDo;
}
string User::getKeyDoan(){
	return this->keyDoan;
}
void User:: setMaxLenght(int maxLenght){
	this->maxLenght = maxLenght;
}
void User::setKeyDo(string keyDo){
	this->keyDo = keyDo;
}
void User::setKeyDoan(string keyDoan){
	this->keyDo = keyDoan;
}
void User::GhiKeyDoanFile(string ttep, string keyDoan){
	ofstream file(ttep.c_str(), ios::app); 
    if (!file) {
        cout << "Khong mo duoc file!" << endl;
        return ;
    }else{
    file<<keyDoan<<endl;	
	}
    file.close();
    return ;
}
void User::DocKeyDoanFile(string ttep,int &count, string *keyDoan){
	ifstream file (ttep.c_str());
	if (!file) {
        cout << "Khong mo duoc file!" << endl;
        return ;
    }else{
    	count = 0;
    	  string temp;
    	while (getline(file, temp)) {
        count++;
        keyDoan = new string[count];
        file.clear();
    	file.seekg(0, ios::beg);
    	for (int i = 0; i < count; ++i) {
        	getline(file, keyDoan[i]);
        }
    }
    file.close();
    }
}

int main(){
	User a;
	a.nhapKeyDo();
	a.nhapKeyDoan();
	string KeyDoan = a.getKeyDoan();
	cout<<KeyDoan<<endl;
	a.GhiKeyDoanFile("User1.txt",KeyDoan);
	a.setKeyDoan("Pham Thi My Hang");
	KeyDoan = a.getKeyDoan();
	a.GhiKeyDoanFile("User1.txt",KeyDoan);
	string * ListKey;
	int count=0;
	a.DocKeyDoanFile("User1.txt",count, ListKey);
	for(int i=0; i< count; i++){
		cout<<ListKey[i]<<endl;
	}
	
}
