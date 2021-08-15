#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include <cwchar>
#include <windows.h>
using namespace std;
int rec_flag=0,no=0;
char rec_ind[5];

struct record
{
	char name[50], phno[15], addr[50],ind[10];
}rec[50];

struct index
{
    char name[50], ind[20];
}in[20],temp;

void sort_index()
{
	int i, j;
	for (i = 0;i < no - 1;i++)
		for (j = 0;j < no - i - 1;j++)
			if (strcmp(in[j].name, in[j + 1].name) > 0)
			{
				temp = in[j];
				in[j] = in[j + 1];
				in[j + 1] = temp;
			}
}



void retrive_record(char *ind) {
	
	int flag = 0, i = 0;
	
    for(int i=0;i<no;i++) {
      if(strcmp(rec[i].ind,ind)==0) {
      	strcpy(rec_ind,ind);
		  rec_flag=1;
		  cout<<"\nRecord found:";
		  cout<<rec[i].name<<"|"<<rec[i].phno<<"|"<<rec[i].addr<<"\n";
		  return;
		}
    }
}




	

int search_index(char *name) {

	int flag=0;
	for(int i=0;i<no;i++) {
	  if(strcmp (in[i].name,name)==0) {
	  	retrive_record(in[i].ind);
		flag=1;
		}
	}
    if(flag)
		return 1;
	else
		return -1;
}

int search_name(char *name,int j) {

	int flag=0;
	for(int i=0;i<j;i++) {
	  if(strcmp (rec[i].name,name)==0) {
	     flag=1;
		 break;
		}
    }
    if(flag)
	  return 1;
    else
	  return -1;
}

void delet(char *pname) {
	
	rec_flag=0;
    int fr=0;
    search_index(pname);
    if(!rec_flag) {
		cout<<"\nDeletion failed record not found";
		return;
	}
    for(int i=0;i<no;i++) {
		if(strcmp(rec[i].ind,rec_ind)==0) {
		
			fr=i;
			break;
		}
	}
    for(int i=fr;i<no-1;i++) {
		rec[i]=rec[i+1];
		char str[3]; //itoa(i,str,10);
		sprintf(str,"%d",i);
		strcpy(rec[i].ind,str);
	}
    no--;
    fstream f1,f2;
    f1.open("tel1.txt",ios::out);
    f2.open("telindex1.txt",ios::out);
    for(int i=0;i<no;i++) {
		strcpy(in[i].name,rec[i].name);
		strcpy(in[i].ind,rec[i].ind);
	}
	sort_index();
    for(int i=0;i<no;i++) {
		f1<<rec[i].ind<<"|"<<rec[i].name<<"|"<<rec[i].phno<<"|"<<rec[i].addr<<"\n";
		f2<<in[i].name<<"|"<<in[i].ind<<"\n";
	}
	f1.close();
	f2.close();
    cout<<"\nDeletion successful\n";
}

void modify(char *name) {

	fstream f3;
	char ind[5];
	int i, j;
	f3.open("tel1.txt", ios::in);
	if(!f3) {
		cout << "err\\\\\\\\\\\\\\\\n";
		exit(0);
	}
	i=0;
	while(!f3.eof()) {
		f3.getline(rec[i].ind, 5, '|');
		f3.getline(rec[i].name, 50, '|');
		f3.getline(rec[i].phno, 15, '|');
		f3.getline(rec[i].addr, 50, '\n');
		strcpy(rec[i].ind,ind);
		strcpy(in[i].name,name);
		strcpy(in[i].ind,ind);
		i++;
	}
	
	for(j=0;j<i;j++) {

		if(strcmp(name, rec[j].name)==0) {
			cout << "\nThe old values of the record with name " << name << " are: ";
			cout << "\nName: " << rec[j].name;
			cout << "\nPhone Number: " << rec[j].phno;
			cout << "\nAddress: " << rec[j].addr;
			
			cout << "\nEnter the new data: \n";
			cout << "\nName: "; cin >> rec[j].name;
			cout << "\nPhone Number: "; cin >> rec[j].phno;
			cout << "\nAddress: "; cin >> rec[j].addr;
			break;
		}
	}
	if(j==i) {
		cout << "\nThe record with name " << name << " is not present\n";
		return;
	}
	f3.close();
	fstream f4, f5;
	f4.open("tel1.txt", ios::out);
	f5.open("telindex1.txt", ios::out);
	if(!f4) {
		cout << "err\\\\\\\\\\\\\\\\n";
		return;
	}
	for(j=0;j<i;j++){
	
		f4 << j<<'|'<<rec[j].name << '|' << rec[j].phno << '|' << rec[j].addr << endl;
		strcpy(in[j].name,rec[j].name);
        f5 << in[j].name << '|'<<j<<"\n";
}
			cout<<in[j].name;
		
	f4.close();
}



int main() {
	
		system("color E1");

	fstream file1,file3;
	int choice, i;
	char ind[5],pname[50],name[50],phno[15],addr[50];
	 cout << "\n\n\t\t-----------TELEPHONE DIRECTORY-------------\n\n";
	
	
    for(;;) {
    	CONSOLE_FONT_INFOEX cfi;
cfi.cbSize = sizeof(cfi);
cfi.nFont = 0;
cfi.dwFontSize.X = 0;                   // Width of each character in the font
cfi.dwFontSize.Y = 20;                  // Height
cfi.FontFamily = FF_DONTCARE;
cfi.FontWeight = FW_NORMAL;
std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

        cout << "\nPlease choose among the following options\n";
		cout << "\n1:Enter new directory\n2:Search directory\n3:Delete existing directory\n4:Display existing directory\n5:Modify existing directory\n6:Exit\n";
		cout << "\nEnter your choice\n";
		cin >> choice;
		switch(choice) {
			case 1: {
				fstream file1;
				file1.open("tel1.txt", ios::app|ios::out);
				if(!file1) {
					cout << "File creation error\n";
					exit(0);
				}
				int n;
			    system("CLS");
				cout<<"Please Enter no of citizen\n";
				cin>>n;
	        	cout<<"enter the details\n";
		        for(i=no;i<no+n;i++)
				{
				cout<<"\nEnter Citizen: "<<i+1<<" ";
				cout << "\nEnter Name: ";
				cin >> rec[i].name;
				cout << "\nEnter Phone Number: ";
				cin >> rec[i].phno;
				cout << "\nEnter Address: ";
				cin >> rec[i].addr;
				int q=search_name(rec[i].name,i);
				file1<<i<<"|"<<rec[i].name<<"|"<<rec[i].phno<<"|"<<rec[i].addr<<"\n";
				}
				file1.close();
				no=no+n;
				fstream f1, file2;
				file2.open("telindex1.txt",ios::out);
				f1.open("tel1.txt",ios::in);
			for(i=0;i<no;i++)
				 {
					f1.getline(ind,5,'|');
					f1.getline(name,50,'|');
					f1.getline(phno,15,'|');
					f1.getline(addr,50,'\n');
					strcpy(rec[i].ind,ind);
					strcpy(in[i].name,name);
					strcpy(in[i].ind,ind);
				}
				sort_index();
	      
				break;
				
				
			
	     
			}
			case 2: {
				system("CLS");
				cout<<"\nEnter the Name of the person whose record is to be displayed\n";
				cin>>pname;
				int q=search_index(pname);
				if(q==1)
					cout<<"\nSearch sucessful\n";
				else
					cout<<"\nNot successful\n";
				break;
			}
			case 3: {
				system("CLS");
				cout<<"\nEnter the Name of the person whose record is to be deleted\n";
				cin>>pname;
				delet(pname);
				break;
			}
			case 4: {
				system("CLS");
				fstream f1;
				f1.open("tel1.txt",ios::in);
				if(!f1) {
					cout<<"err\\\\\\\\\\\\\\\\n";
					exit(0);
				}
				int i=0;
				while(i!=no) {
					f1.getline(ind,5,'|');
					f1.getline(name,50,'|');
					f1.getline(phno,15,'|');
					f1.getline(addr,50,'\n');
					cout<<"Name: "<<name<<"\t"<<"Phone number: "<<phno<<"\t"<<"Address: \n"<<addr<<endl;
					i++;
				}
				break;
			}
			case 5:
				system("CLS");
			     cout<<"\nEnter the Name of the person whose record needs to be modified\n";
				cin>>pname;
				modify(pname);
				break;		

			
			case 6: {
				cout<<"\nEnding program";
				exit(0);
			}
			default: cout<<"\nInvalid\n"; break;
		}}}