#include <iostream>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

vector< vector<string> > all_data;

void read_file(string fname)
{
    string word, line;
    fstream file(fname, ios::in);
    vector<string> row_data;
    while(getline(file,line))
    {
        row_data.clear();
        stringstream row(line);
        while(getline(row, word, ','))
        {
            row_data.push_back(word);
        }
        all_data.push_back(row_data);
    }
}

void data_sort()
{
    string tmpval;
    int rows = all_data.size();
    int col = all_data[0].size();

    for (int i = 1; i < rows-1;i++)
    {
        for (int j=1;j<rows-i-1;j++)
        {
            stringstream int_regcurr(all_data[j][0]);
            stringstream int_regnext(all_data[j][1]);
            int regcurr = 0;
            int regnext = 0;
            int_regcurr >> regcurr;
            int_regnext >> regnext;

            if (regcurr>regnext)
            {
                for (int k=0;k<col;k++)
                {
                    tmpval = all_data[j][k];
                    all_data[j][k] = all_data[j+1][k];
                    all_data[j+1][k] = tmpval;
                }
            }
        }
    }
}

void success()
{
    cout << "====================================================" << endl;
    cout << "||          Task Executed Successfully!           ||" << endl;
    cout << "====================================================" << endl;
}

bool check_val(string regno)
{
    int rows = all_data.size();
    for (int i = 1; i < rows; i++)
    {
        if (regno==all_data[i][0])
        {
            return true;
        }
    }
    return false;
}

bool check_val(string regno, int* idx)
{
    int rows = all_data.size();
    for (int i = 0; i < rows; i++)
    {
        if (regno==all_data[i][0])
        {
            *idx = i;
            return true;
        }
    }
    return false;
}

void reg_std()
{
    string regno, name;
    vector <string> reg_data;

    cout << "Enter the Reg No. of the student (Example: 20xxxxx): ";
    cin >> regno;
    cout << endl << "Enter the Name of the student (Example: NAME or FIRST_NAME LAST_NAME): ";
    getline(cin,name);
    while(name=="")
    {
        getline(cin,name);
    }
    cout << endl;

    if (!check_val(regno))
    {
        reg_data={regno,name,"0","Out","0"};

        all_data.push_back(reg_data);

        data_sort();

        cout << endl;
        success();
    }
    else
    {
        cout << endl <<"Student is already registered!" << endl;
    }
}

void search_student()
{
    string regno;
    int index;
    int*idx=&index;
    char choice;

    cout << "Enter the Reg. No. of the Student you wish to get the record for: ";
    cin >> regno;
    cout << endl;

    if(check_val(regno,idx))
    {
        for (int i=0;i<all_data[0].size();i++)
        {
            cout << all_data[0][i] << " = " << all_data[index][i] << endl;
        }
        cout << endl;
        success();
    }
    else
    {
        cout << "Student is not registered! Do you wish to register this student? (Y/N): " << endl;
        cin >> choice;
        cout << endl;
        if (choice == 'Y')
        {
            reg_std();
        }
        else
        {
            cout << endl;
            success();
        }
    }

}

void change_status()
{
    string regno,status;
    int index;
    int*idx=&index;
    char choice;

    cout << "Enter the Reg. No. of the Student you wish to check the mess status for: ";
    cin >> regno;
    cout << endl;

    if (check_val(regno,idx))
    {
        status = all_data[index][3];
        cout << "The mess status for the student is: " << status << endl;

        cout << "Do you wish to change the mess status for the student? (Y/N): ";
        cin >> choice;
        cout << endl;

        if (choice == 'Y')
        {
            if (status=="In")
            {
                all_data[index][3] = "Out";
            }
            else
            {
                all_data[index][3] = "In";
                all_data[index][4] = to_string(stoi(all_data[index][4])+1);
            }

        }
        cout << endl;
        success();
    }
    else
    {
        cout << "Student is not registered! Do you wish to register this student? (Y/N): ";
        cin >> choice;
        cout << endl;
        if (choice == 'Y')
        {
            reg_std();
        }
        else
        {
            cout << endl;
            success();
        }
    }
}

void delete_std()
{
    string regno;
    int index;
    int*idx=&index;
    char choice;

    cout << "Enter the Reg. No. of the Student you wish to delete the record for: ";
    cin >> regno;
    cout << endl;

    if (check_val(regno,idx))
    {
        all_data.erase(all_data.begin()+index);
        // all_data[index]=all_data.back();
        // all_data.pop_back();
        // data_sort();
        success();
    }
    else
    {
        cout << "Student is not registered! You can not delete the record for an unregistered student." << endl;
    }
}

int count_status(string status)
{
    int cnt=0;
    for (int i=1;i<all_data.size();i++)
    {
        if (all_data[i][3]==status)
        {
            cnt+=1;
        }
    }
    return cnt;
}

void display_total_status()
{
    char choice;

    cout << "Do you wish to know the total number of \"In\" students? (Y/N): ";
    cin >> choice;
    cout << endl;

    if (choice == 'Y')
    {
        cout << "The total number of \"In\" students is: " << count_status("In") << endl;
    }

    cout << "Do you wish to know the total number of \"Out\" students? (Y/N): ";
    cin >> choice;
    cout << endl;

    if (choice == 'Y')
    {
        cout << "The total number of \"Out\" students is: " << count_status("Out") << endl;
    }

    cout << endl;
    success();

}

void calc_bill()
{
    for (int i=1;i<all_data.size();i++)
    {
        string tmpdays = all_data[i][4];
        stringstream int_days(tmpdays);
        int days = 0;
        int_days >> days;
        all_data[i][2] = to_string(days*300);
    }
    success();
}

void display_menu()
{
    cout << endl;
    cout << "====================================================\n";
    cout << "||                      MENU                      ||\n";
    cout << "====================================================\n";
    cout << "The following operations can be performed: " << endl;
    cout << "1) Register a new student" << endl;
    cout << "2) Search a student record" << endl;
    cout << "3) Change student mess status (\"In/Out\")" << endl;
    cout << "4) Delete a student record" << endl;
    cout << "5) Show the total number of \"In/Out\" students" << endl;
    cout << "6) Calculate the total bill" << endl;
    cout << "7) Clear Screen" << endl;
    cout << "8) Exit" << endl;
    cout << endl;
    cout << "Please enter the operation number you wish to perform (Ex: 1): ";
}

int main()
{
    string fname = "data.csv";
    int choice;

    read_file(fname);

    cout << "====================================================\n";
    cout << "|| Welcome To The Student Mess Management System! ||\n";
    cout << "====================================================\n";

    do
    {
        display_menu();

        cin >> choice;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
        cout << endl;

        switch(choice)
        {
            case 1:
            {
                reg_std();
                break;
            }
            case 2:
            {
                search_student();
                break;
            }
            case 3:
            {
                change_status();
                break;
            }
            case 4:
            {
                delete_std();
                break;
            }
            case 5:
            {
                display_total_status();
                break;
            }
            case 6:
            {
                calc_bill();
                break;
            }
            case 7:
            {
                system("cls");
                break;
            }
            case 8:
            {
                system("cls");
                break;
            }
            default:
            {
                cout << "Invalid operation chosen! This operation does not exist!" << endl;
            }
        }
    } while (choice != 8);

    data_sort();

    fstream ofile(fname, ios::out);
    for (int i = 0; i < all_data.size()-1;i++)
    {
        ofile << all_data[i][0] << "," << all_data[i][1] << ","<< all_data[i][2] << "," << all_data[i][3] << "," << all_data[i][4] << "\n";
    }
    int i=all_data.size()-1;
    ofile << all_data[i][0] << "," << all_data[i][1] << ","<< all_data[i][2] << "," << all_data[i][3] << "," << all_data[i][4];

    cout << "====================================================\n";
    cout << "||  The Data File Has Been Updated Successfully!  ||\n";
    cout << "====================================================\n";
    
    cout << "=============================================================\n";
    cout << "|| Thank You For Using The Student Mess Management System! ||\n";
    cout << "=============================================================\n";

}