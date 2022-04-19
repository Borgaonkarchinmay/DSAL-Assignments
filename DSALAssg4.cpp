//============================================================================
// Name        : DSAL-Assignment4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;


struct client{
	string name;
	string telNo;
	int ID;
};


class Hash{
	client* htab[20];
	int searchCount;
public:
	Hash();
	void insertWrep(client*);
	void insertWOrep(client*);
	client* SearchRec(int);
	void displayRec();
	int hashVal(int);
	int LinearProbWOrep(int);
	int LinearProbWrep(int);
	int searchcount();
	~Hash();
};

Hash :: Hash(){
	for(int i=0; i<20; i++)
		htab[i] = nullptr;
	searchCount = 0;
}

void Hash :: insertWOrep(client* record){
	int ind = LinearProbWOrep(record->ID);
	if(ind != -1){
		htab[ind] = record;
		cout<<"Record stored successfully."<<endl;
	}
	else{
		cout<<"Overflow."<<endl;
	}
}

void Hash :: insertWrep(client* record){
	int ind = LinearProbWrep(record->ID);
	if(ind != -1){
		htab[ind] = record;
		cout<<"Record stored successfully."<<endl;
	}
	else{
		cout<<"Overflow."<<endl;
	}
}

int Hash :: hashVal(int id){
	return id%10;
}

int Hash ::searchcount(){
	return searchCount;
}

int Hash :: LinearProbWOrep(int id){
	int index = 0;
	for(int i=0;i<10;i++){
		index = (hashVal(id) + i)%10;
		if(!htab[index]){
			break;
		}
	}
	if(!htab[index]){
		return index;
	}
	else{
		return -1;
	}
}

int Hash :: LinearProbWrep(int id){
	int index = 0;
	index = hashVal(id);
	if(!htab[index]){
		return index;
	}
	else{
		//present value valid
		if((htab[index]->ID)%10 == index){
			index = LinearProbWOrep(id);
			return index;
		}
		else{
			client* temp = htab[index];
			int ind = LinearProbWOrep(temp->ID);
			if(ind == -1){
				return -1;
			}
			else{
				htab[ind] = temp;
				return index;
			}
		}
	}
}

client* Hash :: SearchRec(int id){
	int index = 0;
	int count = 0;
	for(int i=0;i<10;i++){
		index = (hashVal(id) + i)%10;
		if(!htab[index]){
			cout<<"Record not PRESENT."<<endl;
			searchCount = count;
			return nullptr;
		}
		else if(htab[index]->ID == id){
			count++;
			searchCount = count;
			return htab[index];
		}
		count++;
	}
	cout<<"Record not PRESENT."<<endl;
	return nullptr;
}

void Hash :: displayRec(){
	for(int i= 0; i<20;i++){
		if(htab[i]){
		client* c = htab[i];
		cout<<"(ID: "<<c->ID<<",Name: "<<c->name<<",Telephone No: "<<c->telNo<<")"<<endl;
		}
	}
}

Hash :: ~Hash(){
	for(int i=0; i<20; i++)
		delete(htab[i]);
}

int main() {
	Hash t1;
    char choice = 'y';
	while(choice != 'n' && choice == 'y'){

        int menu=0;
        cout<<"MENU:\n1. Insert new client details\n2. Update client details\n3. Display client records\n4. Search client details"<<endl;
        cout<<"Enter menu: ";
        cin>>menu;
        switch(menu){
            case 1:{
                //Insert new client details
            	int m;
            	cout<<"1. With replacement\n2. Without replacement\nEnter method of insertion: ";
            	cin>>m;
            	if(m == 1){
            		//With replacement
            		char choice = 'y';
            		while(choice != 'n' && choice == 'y'){
            			client* newClient = new client;
            			cout<<"Enter client ID: ";
            			cin>>newClient->ID;
            			cout<<endl;
            			cout<<"Enter client Name: ";
            			cin>>newClient->name;
            			cout<<endl;
            			cout<<"Enter client Telephone No: ";
            			cin>>newClient->telNo;
            			t1.insertWrep(newClient);
            			cout<<endl;
            			cout<<"Do you want to continue insertion:?('y'/'n')-> ";
            			cin>>choice;
            		}
            	}
            	else if(m == 2){
            		//Without replacement
            		char choice = 'y';
            		while(choice != 'n' && choice == 'y'){
            			client* newClient = new client;
            			cout<<"Enter client ID: ";
            			cin>>newClient->ID;
            			cout<<endl;
            			cout<<"Enter client Name: ";
            			cin>>newClient->name;
            			cout<<endl;
            			cout<<"Enter client Telephone No: ";
            			cin>>newClient->telNo;
            			t1.insertWOrep(newClient);
            			cout<<endl;
            			cout<<"Do you want to continue insertion:?('y'/'n')-> ";
            			cin>>choice;
            		}
            	}
            	else{
            		cout<<"Invalid insertion menu"<<endl;
            	}
                break;
            }
            case 2:{
                //Update client details
            	int id;
                cout<<endl;
                cout<<"Enter ID of client: ";
                cin>>id;
                client* retrived = t1.SearchRec(id);
                if(retrived){
                	cout<<"Enter new clients details-"<<endl;
                	cout<<"Re-enter name of client: ";
                	cin>>retrived->name;
                	cout<<endl;
                	cout<<"Re-enter telephone of client: ";
                	cin>>retrived->telNo;
                	cout<<endl;
                	cout<<"Client details updated successfully"<<endl;
                }
                else{
                	cout<<"Client records not found!!"<<endl;
                }
                break;
            }
            case 3:{
                //Display client records
            	t1.displayRec();
                break;
            }
            case 4:{
                //Search client details
            	int id;
                cout<<endl;
                cout<<"Enter ID of client: ";
                cin>>id;
                client* retrived = t1.SearchRec(id);
                if(retrived){
                	cout<<"Clients details are:  ";
                	cout<<"(ID: "<<retrived->ID<<",Name: "<<retrived->name<<",Telephone No: "<<retrived->telNo<<")"<<endl;
                	cout<<endl;
                	cout<<"Record fetched in: "<<t1.searchcount()<<" comparisons."<<endl;
                }
                else{
                	cout<<"Client records not found!!"<<endl;
                	cout<<"Required comparisons: "<<t1.searchcount()<<endl;
                }
                break;
            }
        }

        cout<<endl;
        cout<<"Do want to continue:?('y'/'n')-> ";
		cin>>choice;
        if(!(choice == 'n' || choice == 'y')){
            cout<<endl;
            cout<<"Invalid menu"<<endl;
            break;
        }
        cout<<endl;
        cout<<"------------------------------------------------"<<endl;
    }


	return 0;
}
