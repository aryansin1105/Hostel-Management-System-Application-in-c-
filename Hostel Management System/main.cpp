#include<iostream>
#include<fstream>
#include<conio.h>

using namespace std;

class Room{
private:
int room_no;
int status = 0;
public:
void createRoom();
void showRooms();
void readRoom();
void addRoom();
void updateRoom(int pre_room,int curr_room);
void removeRoom(int remRoomNo);
void availRoom();
int checkStatus(int room_no_);
};

void Room::createRoom(){
cout<<"Enter Room No : ";
cin>>room_no;
cout<<"Enter Room Status : ";
cin>>status;
}

void Room::showRooms(){
cout<<"Room No : "<<room_no;
cout<<"\tStatus : "<<status<<endl<<endl;
}

void Room::readRoom(){
ifstream rr;
rr.open("File.dat",ios::binary);
    cout<<"\n===============================\n";
    cout<<"List of Rooms";
    cout<<"\n===============================\n";
    while(!rr.eof()){
        if(rr.read(reinterpret_cast<char*>(this),sizeof(*this))){
            showRooms();
            cout<<"\n===============================\n";
        }
    }
    rr.close();
}

void Room::addRoom(){
char ch;
ofstream ar;
    ar.open("File.dat",ios::binary | ios::app);
    do{
    createRoom();
    ar.write(reinterpret_cast<char*>(this),sizeof(*this));
    cout<<"Do you want to add?(y/n) : ";
    cin>>ch;
    }while(ch == 'y');
    cout<<"Room has been successfully added";
    ar.close();
}

void Room::updateRoom(int prev_room,int curr_room){
fstream ur;
ur.open("File.dat",ios::binary | ios::in | ios::out);
if(prev_room == 0 || prev_room == curr_room){
    while(!ur.eof()){
        if(ur.read(reinterpret_cast<char*>(this),sizeof(*this))){
            if(room_no == curr_room){
                status = 1;
                int pos = -1*sizeof(*this);
                ur.seekp(pos,ios::cur);
                ur.write(reinterpret_cast<char*>(this),sizeof(*this));
                return;
            }
        }
    }
    cout<<endl<<endl<<"\tRoom Successfully Updated...";
}
if(prev_room != 0 && curr_room != prev_room){
    while(!ur.eof()){
        if(ur.read(reinterpret_cast<char*>(this),sizeof(*this))){
            if(room_no == curr_room){
                status = 1;
                int pos = -1*sizeof(*this);
                ur.seekp(pos,ios::cur);
                ur.write(reinterpret_cast<char*>(this),sizeof(*this));
            }
            if(room_no == prev_room){
                status = 0;
                int pos = -1*sizeof(*this);
                ur.seekp(pos,ios::cur);
                ur.write(reinterpret_cast<char*>(this),sizeof(*this));
            }
        }
    }
    cout<<endl<<endl<<"\tRoom Successfully Updated...";
}
    ur.close();
}

void Room::removeRoom(int remRoomNo){
    fstream frr;
    frr.open("File.dat",ios::binary | ios::in | ios::out);
    while(!frr.eof()){
        if(frr.read(reinterpret_cast<char*>(this),sizeof(*this))){
            if(room_no == remRoomNo){
                room_no = room_no;
                status = 0;
                int pos = -1*sizeof(*this);
                frr.seekp(pos,ios::cur);
                frr.write(reinterpret_cast<char*>(this),sizeof(*this));
                return;
            }
        }
    }
    frr.close();
}

void Room::availRoom(){
    ifstream avr;
    avr.open("File.dat",ios::binary);
    while(avr){
        if(avr.read(reinterpret_cast<char*>(this),sizeof(*this))){
            if(status == 0){
                showRooms();
            }
        }
    }
    cout<<"\n\nNo available room"<<endl;
    avr.close();
}

int Room::checkStatus(int room_no_){
    ifstream crs;
    crs.open("File.dat",ios::binary);
    while(crs){
        if(crs.read(reinterpret_cast<char*>(this),sizeof(*this))){
            if(room_no_ == room_no){
                if(status == 0)
                    return 0;
                else
                    return 1;
            }
        }
    }
    crs.close();
}

class Student:public Room{

private:
char fname[50],lname[50],address[50];
long long reg,phone_no;
int room_no;

public:
void addStudent();
void showStudent();
void readOnFile();
void writeOnFile();
void editStudent();
void removeStudent();
void searchStudent();
int checkReg(long long reg_no);

};

void Student::addStudent(){
cout<<"Enter first name : ";
cin>>fname;
cout<<"Enter last name : ";
cin>>lname;
cout<<"Enter registration no : ";
cin>>reg;
int regStatus = checkReg(reg);
if(regStatus == 0){
    reg = reg;
}else{
    cout<<"Registration is already present provide right one : ";
    cin>>reg;
}
cout<<"Enter phone no : ";
cin>>phone_no;
cout<<"Enter address : ";
cin>>address;
cout<<"Enter room no : ";
cin>>room_no;
int status = checkStatus(room_no);
if(status == 0){
    room_no = room_no;
}else{
    cout<<"Room is already alloted choose another one : ";
    cin>>room_no;
}
}

void Student::showStudent(){
cout<<"Name : "<<fname<<" "<<lname<<endl;
cout<<"Registration : "<<reg<<endl;
cout<<"Phone No : "<<phone_no<<endl;
cout<<"Address : "<<address<<endl;
cout<<"Room No : "<<room_no<<endl;
}

void Student::writeOnFile(){
char ch;
ofstream f1;
int prev;
    f1.open("HMS.dat",ios::binary | ios::app);
    do{
    prev = 0;
    addStudent();
    updateRoom(prev,room_no);
    f1.write(reinterpret_cast<char*>(this),sizeof(*this));
    cout<<"Do you want to add?(y/n) : ";
    cin>>ch;
    }while(ch == 'y');
    cout<<"Student has been successfully added";
    f1.close();
}

void Student::readOnFile(){
ifstream f2;
    f2.open("HMS.dat",ios::binary);
    cout<<"\n===============================\n";
    cout<<"List of Students";
    cout<<"\n===============================\n";
    while(!f2.eof()){
        if(f2.read(reinterpret_cast<char*>(this),sizeof(*this))){
            showStudent();
            cout<<"\n===============================\n";
        }
    }
    f2.close();
}

void Student::editStudent(){
long long reg_no;
    fstream es;
    cout<<"Edit Student";
    cout<<"\n===============================\n";
    cout<<"Enter registration number to edit : ";
    cin>>reg_no;

    es.open("HMS.dat",ios::binary|ios::out|ios::in);
    int prev;
    while(!es.eof()){
        if(es.read(reinterpret_cast<char*>(this),sizeof(*this))){
            if(reg == reg_no){
                prev = room_no;
                cout<<"Enter new Record\n";
                addStudent();
                int pos=-1*sizeof(*this);
                es.seekp(pos,ios::cur);
                es.write(reinterpret_cast<char*>(this),sizeof(*this));
                cout<<endl<<endl<<"\tStudent Successfully Updated...";
                updateRoom(prev,room_no);
                return;
            }
        }
    }
    cout<<"\n\nNo Record Found";
    es.close();
}

void Student::removeStudent(){
long long reg_no;
    int flag = 0;
    ofstream fout;
    ifstream fin;
    fin.open("HMS.dat",ios::binary);
    fout.open("temp.dat",ios::binary);
    cout<<"Enter registration number : ";
    cin>>reg_no;
    while(!fin.eof()){
        if(fin.read(reinterpret_cast<char*>(this),sizeof(*this))){
            if(reg != reg_no){
                fout.write(reinterpret_cast<char*>(this),sizeof(*this));
            }else{
                updateRoom(room_no,0);
                flag = 1;
            }
        }
    }
    fin.close();
        fout.close();
        remove("HMS.dat");
        rename("temp.dat","HMS.dat");

        if(flag = 1){
            cout<<"\tStudent Deleted...";
        }else{
        cout<<"\tRecord Not Found...";
        }
}

void Student::searchStudent(){
ifstream fss;
    long long regist;
    cout<<"Enter registration number : ";
    cin>>regist;
    fss.open("HMS.dat",ios::binary);
    while(!fss.eof()){
        if(fss.read(reinterpret_cast<char*>(this),sizeof(*this))){
            if(reg == regist){
                showStudent();
                return;
            }
        }
    }
    cout<<"\n\nNo record found\n";
    fss.close();
}

int Student::checkReg(long long reg_no){
ifstream crn;
    crn.open("HMS.dat",ios::binary);
    while(!crn.eof()){
        if(crn.read(reinterpret_cast<char*>(this),sizeof(*this))){
            if(reg == reg_no){
                return 1;
            }
        }
    }
    return 0;
    crn.close();
}

int main(){
    system("cls");
    system("Color 3F");
    cout<<"\n\n\n\n\n\n\n\t\t * WELCOME TO THE HOSTEL MANAGEMENT SYSTEM *";
    getch();
    while(1){
        Room r;
        Student s;
        int option;
        int choice;
        system("cls");
        system("Color 03");
        cout<<"\nHOSTEL MANAGEMENT SYSTEM";
        cout<<"\n\nMAIN MENU";
        cout<<"\n===============================\n";
        cout<<"[1] Room Menu";
        cout<<"\t[2] Student Menu";
        cout<<"\n===============================\n";
        cout<<"\nEnter your choice : ";
        cin>>option;
        if(option == 1){
        cout<<"\n\nROOM MENU";
        cout<<"\n===============================\n";
        cout<<"[1] Add a new Room\n";
        cout<<"[2] List all Rooms\n";
        cout<<"[3] Check available Rooms\n";
        cout<<"[0] Exit\n";
        cout<<"\n===============================\n";
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice){
            case 1:
                system("cls");
                r.addRoom();
                break;
            case 2:
                system("cls");
                r.readRoom();
                break;
            case 3:
                system("cls");
                r.availRoom();
                break;
            case 0:
                system("cls");
                cout<<"\n\n\n\t\t\tTHANK YOU FOR USING HMS"<<endl<<endl;
                exit(0);
                break;
            default:
                continue;
        }
        int opt;
        cout<<"\n\n..::Enter your choice : \n[1] Room Menu\t\t[0]Exit\n ";
        cin>>opt;
        switch (opt)
        {
        case 0:
            system("cls");
            cout<<"\n\n\n\t\t\tTHANK YOU FOR USING HMS"<<endl<<endl;
            exit(0);
            break;

        default:
            continue;
        }
        }
        else if(option == 2){
        cout<<"\n\nSTUDENT MENU";
        cout<<"\n===============================\n";
        cout<<"[1] Add a new Student\n";
        cout<<"[2] List all Students\n";
        cout<<"[3] Search for Student\n";
        cout<<"[4] Delete a Student\n";
        cout<<"[5] Edit a Student\n";
        cout<<"[0] Exit\n";
        cout<<"\n===============================\n";
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice){
            case 1:
                system("cls");
                s.writeOnFile();
                break;
            case 2:
                system("cls");
                s.readOnFile();
                break;
            case 3:
                system("cls");
                s.searchStudent();
                break;
            case 4:
                system("cls");
                s.removeStudent();
                break;
            case 5:
                system("cls");
                s.editStudent();
                break;
            case 0:
                system("cls");
                cout<<"\n\n\n\t\t\tTHANK YOU FOR USING CMS"<<endl<<endl;
                exit(0);
                break;
            default:
                continue;
        }
        int opt;
        cout<<"\n\n..::Enter your choice : \n[1] Student Menu\t\t[0]Exit\n ";
        cin>>opt;
        switch (opt)
        {
        case 0:
            system("cls");
            cout<<"\n\n\n\t\t\tTHANK YOU FOR USING HMS"<<endl<<endl;
            exit(0);
            break;

        default:
            continue;
        }
        }
        else{
            cout<<"Please Enter Valid Option";
        }
    }
return 0;
}
