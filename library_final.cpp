#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <limits>
#include<iomanip>
using namespace std;
void gotoxy(short x, short y) { 
COORD pos = {x, y}; 
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
} 
class Book
{
    int book_id;
    string b_name;
    string a_name;

public:
    void create_book()
    {
        cout << "New BOOK" << endl;
        cout << "Enter book ID : ";
        cin >> book_id;
        cin.ignore(); // Clear the buffer
        cout << "Enter Book Name : ";
        getline(cin, b_name);
        cout << "Enter Author Name: ";
        getline(cin, a_name);
    }

    void showBook()
    {
        cout << "Book Id : " << book_id << endl;
        cout << "Book Name : " << b_name << endl;
        cout << "Author Name : " << a_name << endl;
    }

    void modifyBook_C()
    {
        cout << endl
             << "Book ID :" << book_id << endl;
        cout << "Modify Book Name : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, b_name);
        cout << "Modify Author's Name : ";
        getline(cin, a_name);
    }

    int return_BookID()
    {
        return book_id;
    }

    void report()
    {
        cout << book_id << " | " << b_name << " | " << a_name << " | " << endl;
    }

    string return_B_Name()
    {
        return b_name;
    }
};

class Student
{
    int admin_no;
    string Name;
    int stdbno[3];
    int book_holding;

public:
    void create_std()
    {
        system("cls");
        cout << "New Student" << endl;
        cout << "Enter admin no : ";
        cin >> admin_no;
        cin.ignore(); // Clear the buffer
        cout << "Enter  Name : ";
        getline(cin, Name);
        book_holding = 0;
        for(int i=0;i<3;i++)
        {
            stdbno[i]=0;
        }
        cout << "Profile Created." << endl;
    }

    void showStudent()
    {
        cout << "Admin no.: " << admin_no << endl;
        cout << "Name : " << Name << endl;
        cout << "Book Taken : " << book_holding << endl;
        if (book_holding > 0)
        {
            cout << "Book no." << stdbno[0]<<stdbno[1]<<stdbno[2];
        }
    }

    void modifyStudent_C()
    {
        cout <<endl<< "Enter the admin no." << admin_no << endl;
        cout << "Modify student name:";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin,Name);
    }

    int return_adminNo()
    {
        return admin_no;
    }

    int* return_studentBookno()
    {
        return stdbno;
    }

    int return_book_holding()
    {
        return book_holding;
    }

    void add_book_holding()
    {
        book_holding = 1;
    }
    void increase_book_holding()
    {
        book_holding++;
    }
    void decrease_book_holding()
    {
        book_holding--;
    }

    void reset_book_holding()
    {
        book_holding = 0;
    }

    void getStudentBOOKno(int t)
    {
        for(int i = 0 ; i < 3 ; i++){
            if(!stdbno[i]){
                stdbno[i] = t ;
                break;
            }
        }
        
    }

    void report()
    {
        cout << admin_no << setw(20) << "|" << setw(20) << Name << setw(20) << "|" << setw(20) << stdbno[0] << "," << stdbno[1] << "," << stdbno[2] << setw(20) << "|" << endl;
    }
};

fstream fp, fp1;

Book bk;
Student st;

void clearScreen()
{
    cout << string(50, '\n');
}

void DispAllStd()
{
    clearScreen();
    fp.open("student.dat", ios::in);
    if (!fp)
    {
        cout << "File not Open" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    cout << "Admin no " << setw(20) << "|" << setw(20) << "Name" << setw(20) << "|" << setw(20) << " Book no." << setw(20) << "|" << endl;
    while (fp.read((char *)&st, sizeof(Student)))
    {
        st.report();
    }
    fp.close();
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void DispAllBook()
{
    clearScreen();
    fp.open("book.dat", ios::in);
    if (!fp)
    {
        cout << "File not Open" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    cout << "\n\nBooks list" << endl;
    cout << "=======" << endl;
    cout << "Book ID | "
         << " Name | "
         << " | Author | " << endl;
    while (fp.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        bk.report();
    }
    fp.close();
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

bool isBookIDUnique(int bookID)
{
    fstream fp("book.dat", ios::in | ios::binary);

    if (!fp)
    {
        cout << "Error opening book file for reading." << endl;
        return false;
    }

    Book tempBK;
    bool unique = true;

    while (fp.read(reinterpret_cast<char *>(&tempBK), sizeof(Book)))
    {
        if (tempBK.return_BookID() == bookID)
        {
            unique = false;
            break;
        }
    }

    fp.close();
    return unique;
}

void writeBook()
{
    char ch = 'y';

    fp.open("book.dat", ios::out | ios::app | ios::binary);
    if (!fp)
    {
        cout << "Error opening book file for writing." << endl;
        return;
    }

    do
    {
        system("cls");
        bk.create_book();

        if (isBookIDUnique(bk.return_BookID()))
        {
            fp.write(reinterpret_cast<char *>(&bk), sizeof(Book));
            cout << "\n Add more? (y/n): ";
            cin >> ch;
        }
        else
        {
            cout << "Book ID already exists. Please choose a unique ID." << endl;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (ch == 'y' || ch == 'Y');

    fp.close();
}

void deleteStudent()
{
    int admin_no;
    bool found = false;

    system("cls");
    cout << "\n\tDelete Student." << endl;
    cout << "Enter the Admin no.: ";

    while (!(cin >> admin_no) || admin_no < 0)
    {
        cout << "Invalid input. Please enter a non-negative integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    fp.open("Student.dat", ios::in | ios::out | ios::binary);
    if (!fp)
    {
        cout << "Error opening student file for reading and writing." << endl;
        return;
    }

    fstream fp2("temp.dat", ios::out | ios::binary);
    if (!fp2)
    {
        cout << "Error creating temporary file." << endl;
        fp.close();
        return;
    }

    while (fp.read(reinterpret_cast<char *>(&st), sizeof(Student)))
    {
        if (admin_no != st.return_adminNo())
        {
            fp2.write(reinterpret_cast<char *>(&st), sizeof(Student));
        }
        else
        {
            found = true;
        }
    }

    fp2.close();
    fp.close();

    if (remove("student.dat") != 0)
    {
        cout << "Error deleting original file." << endl;
        return;
    }

    if (rename("temp.dat", "student.dat") != 0)
    {
        cout << "Error renaming temporary file." << endl;
        return;
    }

    if (found)
    {
        cout << "Record deleted" << endl;
    }
    else
    {
        cout << "Record not found." << endl;
    }

    system("pause");
}

bool isAdminNoUnique(int adminNo)
{
    fstream fp("student.dat", ios::in | ios::binary);

    if (!fp)
    {
        cout << "Error opening student file for reading." << endl;
        return false;
    }

    Student tempStudent;
    bool unique = true;

    while (fp.read(reinterpret_cast<char *>(&tempStudent), sizeof(Student)))
    {
        if (tempStudent.return_adminNo() == adminNo)
        {
            unique = false;
            break;
        }
    }

    fp.close();
    return unique;
}
void writeStudent()
{
    char ch;
    fp.open("student.dat", ios::app | ios::out | ios::binary);

    if (!fp)
    {
        cout << "Error opening student file for writing." << endl;
        return;
    }

    do
    {
        system("cls");
        st.create_std();

        // Check if the student admin number is unique before writing
        if (isAdminNoUnique(st.return_adminNo()))
        {
            fp.write(reinterpret_cast<char *>(&st), sizeof(Student));
            cout << "\n Add more? (y/n): ";
            ch = getch();
        }
        else
        {
            cout << "Admin number already exists. Please choose a unique number." << endl;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (ch == 'y' || ch == 'Y');

    fp.close();
}

void displayspb(int bookID)
{
    clearScreen();
    fp.open("book.dat", ios::in);
    if (!fp)
    {
        cout << "File not Open" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    bool found = false;
    cout << "\n\nBooks Details : " << endl;
    cout << "=======" << endl;
    while (fp.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        if (bk.return_BookID() == bookID)
        {
            bk.showBook();
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Book with ID " << bookID << " doesn't exist." << endl;
    }
    fp.close();
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void displayspStd(int admin_no)
{
    clearScreen();
    fp.open("student.dat", ios::in);
    if (!fp)
    {
        cout << "File not Open" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    bool found = false;
    cout << "Student Details : " << endl;
    cout << "=======" << endl;
    while (fp.read(reinterpret_cast<char *>(&st), sizeof(Student)))
    {
        if (st.return_adminNo() == admin_no)
        {
            st.showStudent();
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Student with admin no " << admin_no << " doesn't exist." << endl;
    }
    fp.close();
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void deleteBook()
{
    int Book_ID;
    bool found = false;

    system("cls");
    cout << "\n\tDelete BOOK." << endl;
    cout << "Enter the Book ID: ";

    // Check for valid input
    while (!(cin >> Book_ID) || Book_ID < 0)
    {
        cout << "Invalid input. Please enter a non-negative integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    fp.open("book.dat", ios::in | ios::out | ios::binary);
    if (!fp)
    {
        cout << "Error opening book file for reading and writing." << endl;
        return;
    }

    fstream fp2("temp.dat", ios::out | ios::binary);
    if (!fp2)
    {
        cout << "Error creating temporary file." << endl;
        fp.close();
        return;
    }

    while (fp.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        if (Book_ID != bk.return_BookID())
        {
            fp2.write(reinterpret_cast<char *>(&bk), sizeof(Book));
        }
        else
        {
            found = true;
        }
    }

    fp2.close();
    fp.close();

    if (remove("book.dat") != 0)
    {
        cout << "Error deleting original file." << endl;
        return;
    }

    if (rename("temp.dat", "book.dat") != 0)
    {
        cout << "Error renaming temporary file." << endl;
        return;
    }

    if (found)
    {
        cout << "Record deleted" << endl;
    }
    else
    {
        cout << "Record not found." << endl;
    }

    system("pause");
}

void modifyStudent()
{
    int admin_no;
    bool found = false;
    
    std::cout << "\nModify Student Record." << std::endl;
    std::cout << "Enter the admission no. : ";

    while (!(std::cin >> admin_no) || admin_no < 0)
    {
        std::cout << "Invalid input. Please enter a non-negative integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::fstream fp("Student.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!fp)
    {
        std::cout << "Error opening Student file for reading and writing." << std::endl;
        return;
    }

    while (fp.read(reinterpret_cast<char *>(&st), sizeof(Student)))
    {
        if (admin_no == st.return_adminNo())
        {
            st.showStudent();
            cout <<endl<< "Enter the new details" << endl;
            st.modifyStudent_C();  

            int pos = -1 * static_cast<int>(sizeof(st));
            fp.seekp(pos, std::ios::cur);
            fp.write(reinterpret_cast<char *>(&st), sizeof(Student));
            cout << "\nRecord Updated" << endl;

            found = true;
            break;
        }
    }

    fp.close();

    if (!found)
    {
        std::cout << "No Student found" << std::endl;
    }

    std::getchar();
}

void modifyBook()
{
    int book_id;
    bool found = false;

    system("cls");
    cout << "\nModify Book Record." << endl;
    cout << "Enter the Book ID: ";

    while (!(cin >> book_id) || book_id < 0)
    {
        cout << "Invalid input. Please enter a non-negative integer: " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    std::fstream fp("book.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!fp)
    {
        cout << "Error opening Book file for reading and writing." << endl;
        return;
    }

    while (fp.read(reinterpret_cast<char *>(&bk), sizeof(Book)))
    {
        if (book_id == bk.return_BookID())
        {
            bk.showBook();
            cout << "Enter the new details" << endl;
            bk.modifyBook_C();

            int pos = -1 * static_cast<int>(sizeof(bk));
            fp.seekp(pos, ios::cur);
            fp.write(reinterpret_cast<char *>(&bk), sizeof(Book));
            cout << "\nRecord Updated" << endl;

            found = true;
            break;
        }
    }

    fp.close();

    if (!found)
    {
        cout << "No Book found" << endl;
    }

    getchar();
}

void start()
{
    system("cls");
    gotoxy(35, 11);
    cout << "LIBRARY";
    gotoxy(35, 13);
    cout << "MANAGEMENT";
    gotoxy(35, 15);
    cout << "SYSTEM";
    getch();
}

void bookissue()
{
    int student_adminNo;
    int BookID;

    bool foundStudent = false, foundBook = false;

    system("cls");
    cout << "\tBook Issue:-" << endl;
    cout << "Enter Student admin no.: ";
    cin >> student_adminNo;

    fp.open("student.dat", ios::in | ios ::out | ios::binary);
    fp1.open("book.dat", ios::in | ios ::out | ios::binary);

    while (fp.read(reinterpret_cast<char *>(&st), sizeof(Student)) && !foundStudent)
    {
        if (st.return_adminNo() == student_adminNo)
        {
            foundStudent = true;

            if (st.return_book_holding() < 3)
            {
                cout << "Enter the Book ID: ";
                cin >> BookID;

                while (fp1.read(reinterpret_cast<char *>(&bk), sizeof(Book)) && !foundBook)
                {
                    if (bk.return_BookID() == BookID)
                    {
                        foundBook = true;
                        if(st.return_book_holding()==0)
                        {
                            st.add_book_holding();
                        }
                        else
                        {
                            st.increase_book_holding();
                        }
                        st.getStudentBOOKno(bk.return_BookID());

                        int pos = -1 * static_cast<int>(sizeof(st));
                        fp.seekp(pos, ios::cur);
                        fp.write(reinterpret_cast<char *>(&st), sizeof(Student));

                        cout << "Book issued." << endl;
                        break;
                    }
                }
                if (!foundBook)
                {
                    cout << "Book doesn't Exist." << endl;
                }
            }
            else
            {
                cout << "Student is already holding 3 books." << endl;
            }
        }
    }

    if (!foundStudent)
    {
        cout << "No Student Found." << endl;
    }

    system("pause");
    fp.close();
    fp1.close();
}

void bookDeposit()
{
    int student_adminNo;
    int BookID;

    bool foundStudent = false, foundBook = false;

    system("cls");
    cout << "\tBook Deposit :- " << endl;
    cout << "Enter Student admin no.: ";
    cin >> student_adminNo;

    fp.open("student.dat", ios::in | ios ::out | ios::binary);
    fp1.open("book.dat", ios::in | ios ::out | ios::binary);

    while (fp.read(reinterpret_cast<char *>(&st), sizeof(Student)) && !foundStudent)
    {
        if (st.return_adminNo() == student_adminNo)
        {
            foundStudent = true;

            if (st.return_book_holding() >= 1)
            {
                cout << "Enter the Book ID: ";
                cin >> BookID;

                while (fp1.read(reinterpret_cast<char *>(&bk), sizeof(Book)) && !foundBook)
                {
                    for(int i=0;i<3;i++)
                    { 
                        if (bk.return_BookID() == st.return_studentBookno()[i])
                    {
                        foundBook = true;
                        bk.showBook();
                        st.decrease_book_holding();
                        st.return_studentBookno()[i]=0;
                        int pos = -1 * static_cast<int>(sizeof(st));
                        fp.seekg(pos, ios::cur);
                        fp.write(reinterpret_cast<char *>(&st), sizeof(Student));

                        cout << "Book Deposited." << endl;
                        break;
                    }
                    }
                   
                }

                if (!foundBook)
                {
                    cout << "Book doesn't Exist." << endl;
                }
            }
            else
            {
                cout << "No book Issued." << endl;
            }
        }
    }

    if (!foundStudent)
    {
        cout << "No Student Found." << endl;
    }

    system("pause");
    fp.close();
    fp1.close();
}

int main();

void adminMenu()
{

    system("cls");
    int ch2;
    cout << "\n\tAdmin Menu" << endl;
    cout << "\n\t1.Create Student Record." << endl;
    cout << "\n\t2.Display All Students." << endl;
    cout << "\n\t3.Display 1 Student." << endl;
    cout << "\n\t4.Modify Student." << endl;
    cout << "\n\t5.Delete Student." << endl;
    cout << "\n\t6.Create Book." << endl;
    cout << "\n\t7.Display All Books." << endl;
    cout << "\n\t8.Display 1 Book." << endl;
    cout << "\n\t9.Modify Book" << endl;
    cout << "\n\t10.Delete Book" << endl;
    cout << "\n\t11.Back to Main." << endl;
    cout << "Option : ";
    cin >> ch2;
    int stdID;
    int BookID;
    switch (ch2)
    {
    case 1:
        writeStudent();
        break;
    case 2:
        DispAllStd();
        break;
    case 3:
        system("cls");
        cout << "Enter Admission no of student : ";
        cin >> stdID;

        displayspStd(stdID);
        break;
    case 4:
        system("cls");

        modifyStudent();
        break;
    case 5:

        deleteStudent();
        break;
    case 6:

        writeBook();
        break;
    case 7:

        DispAllBook();
        break;
    case 8:
        system("cls");
        cout << "Enter Book Id : ";
        cin >> BookID;
        displayspb(BookID);
        break;
    case 9:
        system("cls");

        modifyBook();
        break;
    case 10:

        deleteBook();
        break;
    case 11:
        main();
        break;
    default:
        break;
    }
    adminMenu();
}

int main()
{   static int a = 0 ;
    char ch;
    if (!a){
        start();
        a = 1 ;
    }
    do
    {
        system("cls");
        cout << "\n\tMain Menu" << endl;
        cout << "\t1.Book Issue" << endl;
        cout << "\t2.Book Deposit" << endl;
        cout << "\t3.Admin Menu" << endl;
        cout << "\t4.Exit" << endl;
        cout << "Option : ";
        ch = getchar();
        switch (ch)
        {
        case '1':
            bookissue();
            break;
        case '2':
            bookDeposit();
            break;
        case '3':
            adminMenu();
            break;
        case '4':
            exit(0);
            break;
        default:
            break;
        }
    } while (ch != '4');
    return 0;
}
