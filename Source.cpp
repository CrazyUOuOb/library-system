#include <iostream>
#include <iomanip> //for display books/borrowers in correct layout
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <list>
#include <sstream>

void borrower_menu();
void book_menu();
void main_menu();
bool checkRandom(char[]);

using namespace std;

const int Booksize = 1000, isize = 11, tsize = 101, asize = 51, psize = 51; //Number of Books(Class Book), id size, title size, author size, publisher size
const int Borrowersize = 500, lsize = 11, fsize = 31, ffsize = 50, idsize = 9; //Number of borrowers(Class Borrower), lastname size, firstname size, fullname size, idsize

// clear screen function
void ClrScr() {
    system("cls");
}

class Books {
public:
    void DisplayList() { //DONE, display books detail in correct layout
        string ava;
        if (strlen(ID) != 0) {
            (available) ? ava = "Yes" : ava = "No";
            cout << setw(isize) << ID << setw(tsize) << left << Title << ava << endl;
            cout << setw(isize) << " " << Author << endl;
            cout << setw(isize) << " " << Publisher << "(" << Year << ")" << endl;
            cout << endl;
        }
    }

    void Add(char id[], char title[], char author[], char publisher[], int year) { //#TEST, Add sample, will be kept/deleted in final version
        strncpy_s(ID, isize, id, _TRUNCATE);
        strncpy_s(Title, tsize, title, _TRUNCATE);
        strncpy_s(Author, asize, author, _TRUNCATE);
        strncpy_s(Publisher, psize, publisher, _TRUNCATE);
        Year = year;
        available = true;
    }
    void Remove() {
        int test;
        strncpy_s(ID, isize, "N/A", _TRUNCATE);
        strncpy_s(Title, tsize, "{removed}", _TRUNCATE);
        strncpy_s(Author, asize, " ", _TRUNCATE);
        strncpy_s(Publisher, psize, " ", _TRUNCATE);
        Year = -1;
        available = false;
    }
    char* GetTitle() { //#DONE BUT USED POINTER, use for sorting, get title from private and do comparison
        return Title;
    }
    char* GetID() { //USED POINTER
        char end[] = "END";
        if (ID[0] == '/0')
            return end;
        else return ID;
    }
    char* GetAuthor() {
        return Author;
    }
    char* GetPublisher() {
        return Publisher;
    }
    bool GetAvaliable() {
        return available;
    }
    void borrow_bk() {
        available = false;
    }
    void return_bk() {
        available = true;
    }
    int checkIDlen() { // get the length of ID
        if (strcmp(ID, "N/A") == 0) return 0;
        else return strlen(ID);
    }
    int TitLen() { // get lenght of title
        return strlen(Title);
    }
    bool NotUnique(string id) {
        return (strcmp(id.c_str(), ID) == 0);
    }
    void Title_edit() {
        char in_title[tsize];
        cout << "Input the new value : ";
        cin.getline(in_title, tsize, '\n');
        if (strlen(in_title) > 0) {
            strncpy_s(Title, tsize, in_title, _TRUNCATE);
            ClrScr();
            cout << "Book edited \n";

            cout << "====================\n";
            cout << "Updated book info \n";
            GetInfo();
        }
        else {
            ClrScr();
            cout << "Invalid value \n";
            cout << "\n";
        }
    }
    void Author_edit() {
        char in_author[asize];
        cout << "Input the new value : ";
        cin.getline(in_author, asize, '\n');
        if (strlen(in_author) > 0) {
            strncpy_s(Author, asize, in_author, _TRUNCATE);
            ClrScr();
            cout << "Book edited \n";

            cout << "====================\n";
            cout << "Updated book info \n";
            GetInfo();
        }
        else {
            ClrScr();
            cout << "Invaild value \n";
            cout << "\n";
        }
    }
    void Publisher_edit() {
        char in_publisher[psize];
        cout << "Input the new value : ";
        cin.getline(in_publisher, psize, '\n');
        if (strlen(in_publisher) > 0) {
            strncpy_s(Publisher, psize, in_publisher, _TRUNCATE);
            ClrScr();
            cout << "Book edited \n";

            cout << "====================\n";
            cout << "Updated book info \n";
            GetInfo();
        }
        else {
            ClrScr();
            cout << "Invaild value \n";
            cout << "\n";
        }
    }
    void GetInfo() {
        cout << "ID : " << ID << "\n";
        cout << "Title : " << Title << "\n";
        cout << "Author : " << Author << "\n";
        cout << "Publisher : " << Publisher << "\n";
        cout << "Year : " << Year << "\n";
    }
    int find_book(string input_id) {
        if (input_id == ID) {
            cout << setw(isize) << left << "ID" << setw(tsize) << "Book detail" << endl; //heading
            cout << setw(isize) << ID << setw(tsize) << left << Title << endl;
            cout << setw(isize) << " " << Author << endl;
            cout << setw(isize) << " " << Publisher << "(" << Year << ")" << endl;
            return 1;
        }
        else if (ID == "") return -1;
        else return 0;
    }
private:
    char ID[isize]{}, Author[asize]{}, Publisher[psize]{}, Title[tsize]{};
    int Year = 0;
    bool available = false;
};
Books book[Booksize]; //number of books
Books tempbook[1]; //use to swap in sort function


class Borrowers {
public:
    void DisplayList() {//DONE, display borrowers detail in correct layout
        if (strlen(Lname) != 0) {
            char* name = GetName();
            cout << setw(idsize) << left << ID << setw(ffsize) << left << name << setw(20) << tel << setw(20) << borrowed_num << endl;
        }
    }

    void Add(char lname[], char fname[], int teleno) {
        strncpy_s(Lname, lsize, lname, _TRUNCATE);
        strncpy_s(Fname, fsize, fname, _TRUNCATE);
        tel = teleno;

        do { //get random ID until the ID is unique
            stringstream ss;
            int ran = rand() % 10000; //get number part of ID from 0000 to 9999
            ss << "HKCC" << setfill('0') << setw(4) << ran;
            string id_str = ss.str();
            strncpy_s(ID, idsize, id_str.c_str(), _TRUNCATE);
            checkRandom(ID); //check if the ID unique
        } while (!(checkRandom(ID)));

        borrowed_num = 0;
    }

    void Remove() {
        strncpy_s(ID, idsize, "N/A", _TRUNCATE);
        strncpy_s(Lname, lsize, " ", _TRUNCATE);
        strncpy_s(Fname, fsize, "{removed}", _TRUNCATE);
        tel = -1;
        borrowed_num = -1;

    }

    char* GetName() { //#DONE BUT USED POINTER, get FullName for comparing in sort function and printing in display function
        strcpy_s(FullName, ffsize, Lname);
        strcat_s(FullName, ffsize, " ");
        strcat_s(FullName, ffsize, Fname);
        return FullName;
    }

    void GetInfo() {
        cout << "ID : " << ID << "\n";
        cout << "Name : " << Lname << " " << Fname << "\n";
        cout << "Phone Number : " << tel << "\n";
    }

    char* GetID() {
        return ID;
    }

    int Get_borrowed_num() {
        return borrowed_num;
    }

    int Get_tel() {
        return tel;
    }

    void Borrow_bk(int Book_num) {
        borrowed_bk.push_back(Book_num);
        borrowed_num = borrowed_num + 1;
    }
    int find_borrower(string input_id) {
        if (input_id == ID) {
            cout << endl;
            cout << setw(idsize) << left << "ID" << setw(ffsize) << left << "Name" << setw(20) << "Contact Number" << endl; //heading
            cout << setw(idsize) << left << ID << setw(ffsize) << left << FullName << setw(20) << tel << endl;
            return 1;
        }
        else if (ID == "") return -1;
        else return 0;
    }
    void list_borrowed_item() {
        cout << "Borrowed items \n";
        if (Get_borrowed_num() != 0) {
            for (int num : borrowed_bk) {
                cout << "\n";
                book[num].GetInfo();
            }
            cout << "=========================\n";
            cout << Get_borrowed_num() << " Item(s) borrowed\n";
        }
        else cout << "No borrow record \n";
    }
    int checkIDlen() { // get the length of ID
        if (strcmp(ID, "N/A") == 0) return 0;
        else return strlen(ID);
    }
    bool invalidID(char id[]) {
        int temp = strncmp(ID, id, idsize);
        if (temp == 0) return true;
    }
    void Return_bk(int Book_num) {
        borrowed_bk.remove(Book_num);
        book[Book_num].return_bk();
        borrowed_num = borrowed_num - 1;
        cout << "Successfully returned book.\n";
    }
    int find_borrowed_bk(string in_bk_id) {
        bool found_bk;
        found_bk = false;
        for (int bk_id : borrowed_bk) {
            if (book[bk_id].GetID() == in_bk_id) {
                return bk_id;
                found_bk = true;
                break;
            }
        }

        if (found_bk == false)
            return -1;
    }
    int NameLen() { // get lenght of title
        GetName();
        return strlen(FullName);
    }
private:
    char Lname[lsize]{}, Fname[fsize]{}, FullName[ffsize]{}, ID[idsize]{};
    char Info[255]{}; // temp, for testing purpose only (Chung Eric)
    int tel = 0, borrowed_num = 0;
    list<int> borrowed_bk{};
};

Borrowers borrower[Borrowersize]; //number of borrowers
Borrowers tempborrower[1]; //use to swap in sort function

bool checkRandom(char ID[]) {
    bool invalid = false;
    for (int i = 0; i <= (Borrowersize - 1); i++) {
        if (borrower[i].invalidID(ID)) {
            invalid = true;
            break;
        }
    }
    return invalid;
}

int BorrowerGetPos() {
    for (int i = 0; i <= Borrowersize - 1; i++) { //for loop to find the first empty position
        if (borrower[i].checkIDlen() == 0) { // if the length of ID is empty, the object is empty
            return i; //return the first position of empty object
        };
    }
    return -1; // if there is no return in the loop, there is no empty space for new object, return -1
}

int BookGetPos() {
    for (int i = 0; i <= Booksize - 1; i++) { //for loop to find the first empty position
        if (book[i].checkIDlen() == 0) { // if the length of ID is empty, the object is empty
            return i; //return the first position of empty object
        };
    }
    return -1; // if there is no return in the loop, there is no empty space for new object, return -1
}

bool ValidLength(string word, int size) {
    return ((word.length() <= (size - 1)) && word.length() > 0);
}

void SortBook() { //#DONE, sort books in alphabetical order of book title
    int smallest;
    for (int index = 0; index < Booksize - 1; index++) {
        smallest = index;
        for (int pos = index + 1; pos < Booksize; pos++)
            if (book[pos].TitLen() != 0)
                if (strcmp(book[pos].GetTitle(), book[smallest].GetTitle()) < 0)
                    smallest = pos;
        //swap
        tempbook[0] = book[smallest];
        book[smallest] = book[index];
        book[index] = tempbook[0];
    }
}

void SortMember() { //sort member in alphabetical order of full name
    int smallest;
    for (int index = 0; index < Borrowersize - 1; index++) {
        smallest = index;
        for (int pos = index + 1; pos < Borrowersize; pos++)
            if (borrower[pos].NameLen() != 0)
                if (strcmp(borrower[pos].GetName(), borrower[smallest].GetName()) < 0)
                    smallest = pos;
        //swap
        tempborrower[0] = borrower[smallest];
        borrower[smallest] = borrower[index];
        borrower[index] = tempborrower[0];
    }
}

string to_lower_letter(const string& in_keyword) {
    string out_keyword;
    for (int i = 0; i < in_keyword.size(); i++) {
        int ascii_code = in_keyword[i];
        if (ascii_code >= 65 && ascii_code <= 90) {
            out_keyword = out_keyword + char(ascii_code + 32);
        }
        else {
            out_keyword = out_keyword + in_keyword[i];
        }
    }
    return out_keyword;
}

void query_text_process(char response[], char keyword[][51], char keyword_case[], int& count) {
    char temp_buffer[2]{};
    int i, j, k, found;

    count = 0;

    found = -1;
    for (i = 0; i < strlen(response); i++) {

        if (response[i] == ' ') {
            count = count + 1;
            continue;
        }

        if (response[i] == '\"') {
            char* temp = new char[51];

            for (j = i + 1; response[j] != '\0'; j++) {
                if (response[j] == '\"') {
                    found = j;
                    break;
                }
            }

            if (found >= 0) {
                if (response[i - 1] != ' ' && count != 0) {
                    count = count + 1; // check front
                }

                keyword_case[count] = 's'; //case sensitive
                for (k = i + 1; k < j; k++) {
                    temp_buffer[0] = response[k]; // temp buffer
                    strncat_s(keyword[count], 51, temp_buffer, 1); // append
                }
                if (response[j + 1] != '\0' && response[j + 1] != ' ')
                    count = count + 1;

                i = k;
                continue;
            }
        }

        temp_buffer[0] = response[i]; // temp buffer
        strncat_s(keyword[count], 51, temp_buffer, 1); // append
    }

}

void DisplayBook() { //#DONE, Display books and borrowers, will be added in the final version
    SortBook();
    cout << setw(isize) << left << "ID" << setw(tsize) << "Book detail" << "avaiable" << endl; //heading
    for (int i = 0; i <= Booksize - 1; i++) { //for loop to do DisplayList for all books
        book[i].DisplayList();
    }
}

void AddBook() {
    string tempID, tempTit, tempAu, tempPu;
    char id[isize], tit[tsize], au[asize], pu[psize];
    int pos, year;
    bool valid = true;
    cin.ignore();
    pos = BookGetPos(); //get the first position of empty object
    if (pos == -1) { //if the position is =1, it means the number of object reached maximum, then return to "Manage Book" menu
        cout << "The number of books in this system is full.\nCannot add new book.";
    }
    else {
        cout << "========== Add book ==========\n";
        cout << "Input ID: ";
        getline(cin, tempID);
        if (!ValidLength(tempID, lsize)) {
            cout << "Information Not valid!\nID with maximum " << (isize - 1) << " characters and should not be empty";
            valid = false;
        }
        else {
            for (int i = 0; i <= Booksize - 1; i++) { //for loop to do DisplayList for all books
                if (book[i].NotUnique(tempID)) {
                    cout << "Book ID not unique\n";
                    valid = false;
                    break;
                }
            }
            strcpy_s(id, tempID.c_str());
        }

        if (valid) {
            cout << "Input Title: ";
            getline(cin, tempTit);
            if (!ValidLength(tempTit, tsize)) {
                cout << "Information Not valid!\nmaximum " << (tsize - 1) << " characters and should not be empty";
                valid = false;
            }
            else strcpy_s(tit, tempTit.c_str());
        }

        if (valid) {
            cout << "Input Author (multiple names separated by semi-colon ';') : ";
            getline(cin, tempAu);
            if (!ValidLength(tempAu, asize)) {
                cout << "Information Not valid!\nmaximum " << (asize - 1) << " characters and should not be empty";
                valid = false;
            }
            else strcpy_s(au, tempAu.c_str());
        }

        if (valid) {
            cout << "Input Publisher: ";
            getline(cin, tempPu);
            if (!ValidLength(tempPu, psize)) {
                cout << "Information Not valid!\nmaximum " << (psize - 1) << " characters and should not be empty";
                valid = false;
            }
            else strcpy_s(pu, tempPu.c_str());
        }

        if (valid) {
            cout << "Input Year: ";
            cin >> year;
            if (year <= 0) {
                cout << "Information Not valid!\nYear should be positive integer\n";
                valid = false;
            }
        }
        if (valid) {
            book[pos].Add(id, tit, au, pu, year);
            cout << "Book have been added\n";
            cout << "\n";
        }
        else cout << "\nPlease input the information again\n";
        cout << "\n";

    }
}

void RemoveBook() {
    string response = "/";
    int found_index = -1;
    bool ava = false;
    cout << "========== Book Remove ==========\n";
    cout << "\n";
    cout << "Enter book id to remove book : ";
    cin >> response;
    int found = -10;
    for (int i = 0; i < Booksize; i++) {
        found = book[i].find_book(response);
        if (found == 1) {
            found_index = i;
            ava = book[i].GetAvaliable();
            break;
        }
        else if (found == -1) break;
    }

    if (found <= 0 && response != "//exit//") {
        cout << "No such book. \n";
    }
    else if (found == 1 && response != "//exit//" && found_index >= 0 && ava == false) {
        cout << "This book is borrowed by someone" << endl;
        cout << "This book will not be removed" << endl;
        cout << "\n";
    }
    else {
        char response = '/';
        cout << "\n";
        cout << "Are you sure to remove this book [Y/N]? ";
        cin >> response;
        do {
            if (response == 'Y') {
                book[found_index].Remove();
                ClrScr();
                cout << "Book removed \n";
            }
            else if (response == 'N') cout << "this operatos has been cancelled" << endl;
            else {
                cin.clear();
                cin.ignore(255, '\n');
                cout << "Only allow to input 'Y' OR 'N'" << endl;
            }
        } while (response != 'Y' && response != 'N');
    }
}

void DisplayBorrower() {
    SortMember();
    cout << setw(idsize) << left << "ID" << setw(ffsize) << left << "Name" << setw(20) << "Contact Number" << setw(20) << "Number of books borrowed" << endl; //heading
    for (int i = 0; i <= Borrowersize - 1; i++) { //for loop to do DisplayList for all borrowers
        borrower[i].DisplayList();
    }
}

void AddBorrower() {
    char lname[lsize], fname[fsize];
    string tempLname, tempFname;
    int tel, temp, pos;
    bool valid = true;
    cin.ignore();
    pos = BorrowerGetPos(); //get the first position of empty object
    if (pos == -1) { //if the position is =1, it means the number of object reached maximum, then return to "Manage Borrower" menu
        cout << "The number of borrowers in this system is full.\nCannot add new borrower.";
    }
    else {
        ClrScr();
        cout << "========== Add borrower ==========\n";
        cout << "Last Name: ";
        getline(cin, tempLname);
        if (!ValidLength(tempLname, lsize)) {
            cout << "Information Not valid!\nLast Name with maximum " << (lsize - 1) << " characters and should not be empty";
            valid = false;
        }
        else strcpy_s(lname, tempLname.c_str());

        if (valid) {
            cout << "First Name: ";
            getline(cin, tempFname);
            if (!ValidLength(tempFname, fsize)) {
                cout << "Information Not valid!\nFirst Name with maximum " << (fsize - 1) << " characters and should not be empty";
                valid = false;
            }
            else strcpy_s(fname, tempFname.c_str());
        }

        if (valid) {
            cout << "Contact number: ";
            cin >> tel;
            temp = tel / 10000000; //get the first number of phone number to check valid later
            if (temp == 2 || temp == 3 || temp == 5 || temp == 6 || temp == 9) { //check valid, if valid then add record, else cout error and rerun this function
                //valid
                for (int i = 0; lname[i] != '\0'; i++) //convert whole last name into upper case
                {
                    if (lname[i] >= 'a' && lname[i] <= 'z')
                        lname[i] = lname[i] - 'a' + 'A';
                }
                for (int i = 0; fname[i] != '\0'; i++) //capitalize each word in first name
                {
                    if (i == 0 || fname[i - 1] == ' ') {
                        if (fname[i] >= 'a' && fname[i] <= 'z')
                            fname[i] = fname[i] - 'a' + 'A'; // turn the first position of each word into upper case
                    }
                    else if (fname[i] >= 'A' && fname[i] <= 'Z') //turn all other position of the words into lower case
                        fname[i] = fname[i] - 'A' + 'a';
                }
            }
            else {
                valid = false;
                cout << "Invaild Input \n";
            }
        }
        if (valid) {
            borrower[pos].Add(lname, fname, tel);
            cout << "Added\n";
            cout << "\n";
            cout << "Borrower Info\n";
            borrower[pos].GetInfo();
            cout << "\n";
        }
        else cout << "Please input the correct information\n";
        cout << "\n";
    }
}

void RemoveBorrower() {
    string response = "/";
    int found_index = -1;
    int borrowed_book = 0;
    ClrScr();
    cout << "========== Remove borrower ==========\n";
    cout << "Enter borrower id to remove borrower (type '//exit//' to exit) : ";
    cin >> response;
    int found = -10;
    for (int i = 0; i < Borrowersize; i++) {
        found = borrower[i].find_borrower(response);
        if (found == 1) {
            found_index = i;
            borrowed_book = borrower[i].Get_borrowed_num();
            break;
        }
        else if (found == -1) break;
    }

    if (found <= 0 && response != "//exit//") {
        cout << "No such borrower. \n";
    }
    else if (found == 1 && response != "//exit//" && found_index >= 0 && borrowed_book != 0) {
        cout << "This borrower does not return all the books" << endl;
        cout << "This borrower will not be removed" << endl;
        cout << "\n";
    }
    else {
        char response = '/';
        do {
            cout << "Are you sure to remove this borrower [Y/N]? ";
            cin >> response;
            if (response == 'Y') {
                borrower[found_index].Remove();
            }
            else if (response == 'N') cout << "Remove operation has been cancelled" << endl;
            else {
                cin.ignore(255, '\n');
                cout << "Only allow to input 'Y' OR 'N'" << endl;
            }
        } while (response != 'Y' && response != 'N');
    }
}

void search(string query_type) {
    char response[51];
    char keyword[255][51] = {};
    char keyword_case[255]; // added for storing case sensitive or not
    string ID = "";
    string BK_ID, BK_Title, BK_Author, BK_Publisher;
    int keyword_count, result_counter, i, j;

    ClrScr();
    if (query_type == "Member") {
        cout << "========== Borrower Search ==========\n";
        cout << "\n";
    }
    else if (query_type == "Book") {
        cout << "========== Book Search ==========\n";
        cout << "\n";
    }

    cin.ignore();
    cout << "Enter phrase(s) to search : ";
    cin.getline(response, 51, '\n');
    cout << "\n";

    result_counter = 0;

    if (query_type == "Member") {
        cout << "=========== RESULTS ===========\n";
        cout << setw(idsize) << left << "ID" << setw(ffsize) << left << "Name" << setw(20) << "Contact Number" << setw(20) << "Number of books borrowed" << endl; //heading
        for (i = 0; i < Borrowersize; i++) {
            ID = string(borrower[i].GetID());

            if (ID == "END")
                break;
            else if (response == ID) {
                borrower[i].DisplayList();
                result_counter = result_counter + 1;
            }
        }
    }

    if (query_type == "Book") {
        keyword_count = 0;
        query_text_process(response, keyword, keyword_case, keyword_count);

        cout << "Search keyword(s) : ";
        for (i = 0; i <= keyword_count; i++) {
            if (keyword[i] == "")
                continue;
            if (i < keyword_count)
                cout << " \"" << keyword[i] << "\" ,";
            else cout << " \"" << keyword[i] << "\"";
        }
        cout << "\n";
        cout << "=========== RESULTS ===========\n";
        cout << setw(isize) << left << "ID" << setw(tsize) << "Book detail" << "Available" << endl;



        for (i = 0; i < Booksize; i++) {
            BK_ID = book[i].GetID();

            if (BK_ID == "") {
                break;
            }

            BK_Title = book[i].GetTitle();
            BK_Author = book[i].GetAuthor();
            BK_Publisher = book[i].GetPublisher();


            for (j = 0; j <= keyword_count; j++) {

                if (keyword[j] == "")
                    continue;

                if (keyword_case[j] == 's') {
                    // if the keyword is case sensitive
                    if (BK_ID.find(keyword[j]) != string::npos || BK_Title.find(keyword[j]) != string::npos || BK_Author.find(keyword[j]) != string::npos || BK_Publisher.find(keyword[j]) != string::npos) {
                        cout << "\n";
                        book[i].DisplayList();

                        result_counter = result_counter + 1;
                        break;
                    }

                }
                else {
                    // if that keyword not case sensitive
                    // turn all into lowercase letter for easier comparison
                    string s_BK_ID = to_lower_letter(BK_ID);
                    string s_BK_Title = to_lower_letter(BK_Title);
                    string s_BK_Author = to_lower_letter(BK_Author);
                    string s_BK_Publisher = to_lower_letter(BK_Publisher);
                    string s_keyword = to_lower_letter(keyword[j]);

                    if (s_BK_ID.find(s_keyword) != string::npos || s_BK_Title.find(s_keyword) != string::npos || s_BK_Author.find(s_keyword) != string::npos || s_BK_Publisher.find(s_keyword) != string::npos) {
                        cout << "\n";
                        book[i].DisplayList();

                        result_counter = result_counter + 1;
                        break;
                    }
                }

            }
        }
    }

    cout << "\n";
    if (result_counter > 0)
        cout << result_counter << " result(s)\n";
    else cout << "NO RESULTS \n";
    cout << "===============================\n";
    cout << "\n";
}

void borrow_book() {
    string book_2_borrow, response, bk_id;
    bool found, borrower_found;
    int borrower_num;

    ClrScr();
    borrower_num = -1;
    borrower_found = false;
    do {
        cout << "========== Book Borrow ==========\n";
        cout << "\n";
        cout << "Enter borrwer id ('//exit//' to exit): ";
        cin >> response;

        if (response == "//exit//")
            break;

        for (int h = 0; h < Borrowersize; h++) {
            if (borrower[h].GetID() == "")
                break;

            if (response == borrower[h].GetID()) {
                borrower_num = h;

                cout << "\n";
                cout << "===== Borrower Info =====\n";
                borrower[h].GetInfo();
                cout << "Borrowed book number : " << borrower[h].Get_borrowed_num() << "\n";
                cout << "Quota left : " << 5 - borrower[h].Get_borrowed_num() << "\n";
                borrower_found = true;

                if (borrower[h].Get_borrowed_num() > 0)
                    borrower[borrower_num].list_borrowed_item();
                else cout << "No currently borrowed book. \n";
                break;
            }
        }

        if (borrower_found == false) {
            cout << "Borrower not found!\n";
        }

    } while (borrower_found == false && borrower_num == -1);

    if (borrower[borrower_num].Get_borrowed_num() == 5)
        cout << "Book borrow quota used up, return books to borrow other book. \n";


    if (response != "//exit//" && borrower[borrower_num].Get_borrowed_num() < 5) {
        do {
            if (borrower[borrower_num].Get_borrowed_num() == 5) {
                cout << "Book borrow quota used up, unable to continue to borrow books \n";
                break;
            }

            cout << "\n";
            cout << "Enter book id to borrow book ('//exit//' to exit) : ";
            cin >> response;

            found = false;
            for (int i = 0; i < Booksize; i++) {
                bk_id = book[i].GetID();
                if (bk_id == "")
                    break;

                if (response == bk_id) {
                    cout << "\n";
                    cout << "Book info \n";
                    book[i].GetInfo();
                    if (book[i].GetAvaliable() == false) {
                        cout << "This book is not available.\n";
                        found = true;
                        break;
                    }
                    else {
                        cout << "Book found and available. \n";
                        found = true;
                        book[i].borrow_bk();
                        borrower[borrower_num].Borrow_bk(i);
                        cout << "Boook have been borrowed. \n";
                        cout << "\n";
                        cout << "Book borrowed \n";
                        borrower[borrower_num].list_borrowed_item();
                        break;
                    }
                }
            }

            if (found == false && response != "//exit//")
                cout << "No such book. \n";

        } while (response != "//exit//");
    }
}

void return_book() {
    int borrower_num;
    bool borrower_found;
    string response;

    ClrScr();
    borrower_num = -1;
    borrower_found = false;
    do {
        cout << "========== Return Book ==========\n";
        cout << "\n";
        cout << "Enter borrwer id (type '//exit//' to exit) : ";
        cin >> response;

        if (response == "//exit//") {
            ClrScr();
            break;
        }

        for (int h = 0; h < Borrowersize; h++) {
            if (borrower[h].GetID() == "")
                break;

            if (response == borrower[h].GetID()) {
                borrower_num = h;

                cout << "\n";
                cout << "===== Borrower Info =====\n";
                borrower[h].GetInfo();
                cout << "Borrowed book number : " << borrower[h].Get_borrowed_num() << "\n";
                cout << "Quota left : " << 5 - borrower[h].Get_borrowed_num() << "\n";
                cout << "\n";
                borrower_found = true;

                if (borrower[h].Get_borrowed_num() > 0)
                    borrower[borrower_num].list_borrowed_item();
            }
        }

        if (borrower_found == false) {
            cout << "Borrower not found!\n";
        }

    } while (borrower_found == false && borrower_num == -1);

    if (borrower[borrower_num].Get_borrowed_num() == 0 && response != "//exit//")
        cout << "No borrow record, no books to return \n";

    if (borrower[borrower_num].Get_borrowed_num() > 0) {
        do {
            cout << "\n";
            cout << "Enter book id to return book (type '//exit//' to exit) : ";
            cin >> response;

            if (response == "//exit//") {
                ClrScr();
                break;
            }

            int bk_id_2_return = borrower[borrower_num].find_borrowed_bk(response);

            if (bk_id_2_return == -1) {
                cout << "Book not found, book id not exists or no borrow record for that book id \n";
            }

            if (bk_id_2_return > -1) {
                cout << "\n";
                cout << "Book to return \n";
                book[bk_id_2_return].GetInfo();
                cout << "\n";
                borrower[borrower_num].Return_bk(bk_id_2_return);
                cout << "\n";
                borrower[borrower_num].list_borrowed_item();
                cout << "\n";
            }

        } while (response != "//exit");
    }

}

void book_edit() {
    string response, bk_id;
    bool found;
    char option_response;

    do {
        cout << "========== Edit Book Information ==========\n";
        cout << "\n";
        cout << "Enter book id to edit information ('//exit//' to exit): ";
        cin >> response;

        if (response == "//exit//")
            break;

        found = false;
        for (int i = 0; i < Booksize; i++) {
            bk_id = book[i].GetID();
            if (bk_id == "")
                break;

            if (response == bk_id) {
                cout << "\n";
                cout << "Book found \n";
                cout << "===================== \n";
                if (book[i].GetAvaliable() == false) {
                    book[i].GetInfo();
                    cout << "This book have been borrowed and not available for edit.\n";
                    cout << "\n";
                    found = true;
                    break;
                }
                else {
                    cout << "Book available to edit. \n";

                    found = true;
                    cout << "\n";
                    do {
                        book[i].GetInfo();
                        cout << "================\n";
                        cout << "Edit option \n";
                        cout << "[1]. Edit title \n";
                        cout << "[2]. Edit Author \n";
                        cout << "[3]. Edit Publisher \n";
                        cout << "[4]. Cancel \n";

                        cout << "Option : ";
                        cin >> option_response;
                        cin.ignore();
                        cout << "\n";

                        switch (option_response) {
                        case '1': book[i].Title_edit(); break;
                        case '2': book[i].Author_edit(); break;
                        case '3': book[i].Publisher_edit(); break;
                        case '4': break;
                        default: ClrScr(); cout << "No such option \n";
                        }

                        cout << "\n";
                    } while (option_response != '4');
                    ClrScr();
                }
            }
        }

        if (found == false && response != "//exit//") {
            ClrScr();
            cout << "No such book. \n";
            cout << "\n";
        }

    } while (response != "//exit//");
    ClrScr();
}


int extractFields(string line, char fields[][101]) {

    int numFields = 0;

    int meaningless_doublequote = line.find("\",\"");
    if (line[meaningless_doublequote + 3] != '\"\"\"' || line[meaningless_doublequote - 3] != '\"\"\"') meaningless_doublequote = 0;
    else if (meaningless_doublequote > 0) line.replace(meaningless_doublequote, 3, ",");

    int total_doublequote = 0;
    bool within_doublequote = false;
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '"') total_doublequote++;
    }

    int doublequote_key = 1;
    int doublequote_index = 2;
    int x = 0, y = 0;
    int number = 0;
    while (line[number] != '\0') {
        switch (line[number]) {
        case '"':
            if (total_doublequote / 3 > 0 && total_doublequote != 4) {
                if (doublequote_key == doublequote_index)
                {
                    fields[y][x] = '"';
                    x++;
                    if (numFields == 0) numFields++;
                    doublequote_index += 3;
                }
                else
                {
                    if (!within_doublequote) within_doublequote = true;
                    else
                    {
                        within_doublequote = false;
                        total_doublequote -= 3;
                    }
                }
            }
            else
            {
                if (within_doublequote) within_doublequote = false;
                else within_doublequote = true;
            }
            doublequote_key++;
            break;
        case ',':
            if (!within_doublequote) {
                fields[y][x] = '\0';
                x = 0;
                y++;
                numFields++;
            }
            else {
                fields[y][x] = ',';
                x++;
            }
            break;
        default: {
            fields[y][x] = line[number];
            x++;
            if (numFields == 0) numFields++;
            else if (line[number + 1] == '\0') {
                fields[y][x] = '\0';
            }
        }
        }
        number++;
    }
    // **********
    return numFields;
}

void readCSV(string filename) {
    fstream inFile;				// for handling file
    string line;				// for storing 1 line in a file
    char fields[10][101] = {};	// for storing extracted fields (assume max. 10 fields per line, each field has max. 100 char)
    int numFields;				// for storing number of fields per line
    int counter = 0;            // for counting the number of records in csv file
    int pos;

    inFile.open(filename);
    if (!inFile.is_open()) {
        cout << "Cannot open file \"" << filename << "\"\n";
        return;
    }

    pos = filename.find("BookList.csv");				                                    //get the position of BookList/BorrowerList
    if (pos == -1) pos = filename.find("BorrowerList.csv");

    while (getline(inFile, line, '\n')) {				                                    // read line by line until end of file
        numFields = extractFields(line, fields);		                                    // call function to extract fields from the line
        if (filename.substr(pos) == "BookList.csv") 	                                	//use the position to identifly whether the file is BookList or BorrowerList
            book[counter].Add(fields[0], fields[1], fields[2], fields[3], stoi(fields[4]));	//add record to class(Book)
        else borrower[counter].Add(fields[0], fields[1], stoi(fields[2]));					//add record to class(Borrower)
        counter++;
    }

    cout << counter << " Record(s) imported.\n";
    inFile.close();
}

void readfile() {
    string filename;
    char response;

    cout << "========== Libary Management System ==========\n";
    cout << "\n";

    do {
        cout << "Import book list CSV file? [Y/N] : ";
        cin >> response;
        cin.ignore(255, '\n');
        if (response == 'Y') {
            do {
                cout << "Input path to book list CSV file: ";
                getline(cin, filename);
                if (filename.find("BookList.csv") == -1) {
                    cout << "\nPlease input the correct file address \n";
                }
                else {
                    readCSV(filename);
                }
            } while (filename.find("BookList.csv") == -1);
        }
        else if (response == 'N')
            cout << "No book list is imported \n";
        else {
            cout << "No such option \n";
        }
    } while (response != 'N' && response != 'Y');

    cout << "\n";
    do {
        cout << "Import borrower list CSV file? [Y/N] : ";
        cin >> response;
        cin.ignore();
        if (response == 'Y') {
            do {
                cout << "Input path to borrower list CSV file: ";
                getline(cin, filename);
                if (filename.find("BorrowerList.csv") == -1) {
                    cout << "\nPlease input the correct file address \n";
                }
                else {
                    readCSV(filename);
                }
            } while (filename.find("BorrowerList.csv") == -1);
        }
        else if (response == 'N')
            cout << "No borrower list is imported \n";

        if (response != 'Y' && response != 'N') {
            cout << "No such option \n";
        }
    } while (response != 'N' && response != 'Y');

}

void member_list() {
    cout << setw(8) << left << "Role" << setw(20) << "Name" << setw(15) << "Student ID" << setw(4) << "Class" << endl;
    cout << setw(8) << left << "Leader" << setw(20) << "Mak Hau Ling" << setw(15) << "22164275A" << setw(4) << "203A" << endl;
    cout << setw(8) << left << "Member" << setw(20) << "Hon Chi Tung" << setw(15) << "22165898A" << setw(4) << "203C" << endl;
    cout << setw(8) << left << "Member" << setw(20) << "Kwok Tsz Chun" << setw(15) << "22092355A" << setw(4) << "203B" << endl;
    cout << setw(8) << left << "Member" << setw(20) << "Leung Wai Chung" << setw(15) << "22032082A" << setw(4) << "203A" << endl;
    cout << setw(8) << left << "Member" << setw(20) << "Man Kei Ching" << setw(15) << "22048880A" << setw(4) << "203D" << endl;
    main_menu();
}

void feature() {
    cout << "1. Edit Book\n";
    main_menu();
}

void book_menu() {
    int option;
    do {
        cout << "*** Manage Books ***\n[1] Display books\n[2] Search book\n[3] Add book\n[4] Remove book\n[5] Edit book\n[6] Cancel\n*******\n";
        cout << "Option(1-6): ";
        cin >> option;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(255, '\n');
        }
        switch (option) {
        case 1: ClrScr(); DisplayBook(); break;
        case 2: ClrScr(); search("Book"); break;
        case 3: ClrScr(); AddBook(); break;
        case 4: ClrScr(); RemoveBook(); break;
        case 5: ClrScr(); book_edit(); break;
        case 6: ClrScr(); break;
        default: cout << "Invaild input. Please enter option 1 - 5\n";
        }
    } while (option != 6);
    ClrScr();
}

void borrower_menu() {
    int option = 0;
    do {
        cout << "*** Manage Borrowers ***\n[1] Display borrowers\n[2] Search borrower\n[3] Add borrower\n[4] Remove borrower\n[5] Back\n**********\n";
        cout << "Option(1-5): ";
        cin >> option;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(255, '\n');
        }
        switch (option) {
        case 1: DisplayBorrower(); break;
        case 2: search("Member"); break;
        case 3: AddBorrower(); break;
        case 4: RemoveBorrower(); break;
        case 5: break;
        default: cout << "1 - 5 only!";
        }
    } while (option != 5);
    ClrScr();
}

void main_menu() {
    int option = 0;
    char confirm = ' ';
    do {
        cout << "\nWelcome!!\n";
        cout << "* Library Management System *\n[1] Manage books\n[2] Manage borrowers\n[3] Borrow book(s)\n[4] Return book(s)\n[5] Useful feature(s) added\n[6] Member List\n[7] Exit\n*************";
        cout << "\nOption(1-7): ";
        cin >> option;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(255, '\n');
        }
        switch (option) {
        case 1: ClrScr(); book_menu(); break;
        case 2: ClrScr(); borrower_menu(); break;
        case 3: borrow_book(); break;
        case 4: return_book(); break;
        case 5: feature(); break;
        case 6: member_list(); break;
        case 7: do {
            cout << "Confirm [Y/N]: ";
            cin >> confirm;
        } while (confirm != 'y' && confirm != 'Y' && confirm != 'N' && confirm != 'n');

        switch (confirm) {
        case 'y':
        case 'Y': break;
        case 'n':
        case 'N': main_menu(); break;
        default: ClrScr(); cout << "Invaild input.\n";
        }
        break;
        default: ClrScr(); cout << "Invaild input. Please enter option 1 - 7\n";
        }

    } while (option != 7 && (confirm != 'y' && confirm != 'Y'));
}

int main() {
    // infile to fetch data to the program
    srand(time(0));
    readfile();
    main_menu();

    return 0;
}