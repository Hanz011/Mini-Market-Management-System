#include <iostream>
#include <fstream> // for writing on and reading from the file
#include <string>
#include <vector>
#include <sstream>   // for using stringstream function inorder to read one line from the file at a time
#include <algorithm> // for sort
#include <cfloat> // to handle larger values of the price
#include <iomanip>// for use a precise price 
#include <windows.h> // to add time delay

using namespace std;
// helps to convert strings to conver in to lowercase
string to_lowercase(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// a function for verfying a password
bool verify_owner_password() {
    ifstream pass_file("password.txt");
    if (!pass_file) {
        cout << "Password file missing.\n";
        return false;
    }
    string saved_pass;
    getline(pass_file, saved_pass);
    pass_file.close();

    string input_pass;
    cout << "Enter owner password: ";
    getline(cin >> ws, input_pass);

    return input_pass == saved_pass;
}


struct item // a structure that enables to accept and display description of an item
{
    string item_type;
    string item_name;
    long double  item_price;
    string add_info;
};

// function that reads the password from the file and returns it
string read_password()
{
    ifstream pwd_file("password.txt", ios::in);
    string pwd = "mini123"; // default if not found

    if (pwd_file.is_open())
    {
        getline(pwd_file, pwd);
        pwd_file.close();
    }
    return pwd;
}

// function that to write the new file on the file
void write_password(const string &new_pwd)
{
    ofstream pwd_file("password.txt", ios::out);
    if (pwd_file.is_open())
    {
        pwd_file << new_pwd;
        pwd_file.close();
    }
    else
    {
        cout << "Error: Could not write password to file.\n";
    }
}
void change_password() {
    string current_pwd = read_password();
    string old_pwd, new_pwd, confirm_pwd;

    cout << "Enter current password: ";
    getline(cin >> ws, old_pwd);

    if (old_pwd != current_pwd) {
        cout << "Incorrect password. Password change aborted.\n";
        return;
    }

    cout << "Enter new password: ";
    getline(cin, new_pwd);

    cout << "Confirm new password: ";
    getline(cin, confirm_pwd);

    if (new_pwd != confirm_pwd) {
        cout << "Passwords do not match. Password change aborted.\n";
        return;
    }

    write_password(new_pwd);
    cout << "Password changed successfully.\n";
}

void add_item()
{
    

        ofstream outfile("item_list.txt", ios::app); // writing information of added items on a file
        if (!outfile.is_open())
        {
            cout << "Failed to open file! ";
            exit(1);
        }
        item new_items;
        char choice = 'y';
        int i = 0, j = 3;
        cout << "\t\tADD NEW ITEMS.\n\t\t________________\n\n";

        while (tolower(choice) == 'y')
        {

            // Accepting the information of the new added item
            cout << "Enter the type of the item(no commas): ";
            getline(cin, new_items.item_type);
            cout << "Enter the name of the item(no commas): ";
            getline(cin, new_items.item_name);
            cout << "Enter additional information about  the item(no commas): ";
            getline(cin, new_items.add_info);

            // check the validity of price of the item and accept it
            while (true)
            {
                cout << "Enter the price of the item: ";
                cin >> new_items.item_price;
                if (new_items.item_price < 0 || cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    if (j >= 1)
                    {
                        cout << "Invalid Input!, " << j << " attempts left\n";
                    }
                    if (j < 1)
                    {
                        cout << "Too many attempts. Program terminated.\n";
                        exit(1);
                    }

                    j--;
                }
                else
                    break;
            }
            cin.ignore();

            // Writing the new item's information on the file
            outfile << new_items.item_type << ","
                    << new_items.item_name << ","
                    << new_items.add_info << ","
                    << new_items.item_price << "\n";

            // asking for additional item recording
            cout << "\nWould you continue to add item? (y/n)\n";
            cin >> choice;
            cin.ignore();
            i++;
        }
        if (i == 1)
            cout << "You have successfully added " << i << " item";
        else
            cout << "You have successfully added " << i << " items";

        outfile.close();
        
}
void search_item()
{
    ifstream infile("item_list.txt");
    if (!infile.is_open())
    {
        cout << "Failed to open file! ";
        exit(1);
    }

    string required_item_type;
    cout << "\t\tSEARCHED ITEMS BY THEIR TYPES.\n";
    cout << "\t\t_____________________________\n\n";
    cout << "Enter the type of product that you are looking for: ";
    getline(cin, required_item_type);

    string line;
    item it;
    bool found = false;

    while (getline(infile, line))
    {
        stringstream ss(line);
        string i_type, i_name, i_info, i_price;
        getline(ss, i_type, ',');
        getline(ss, i_name, ',');
        getline(ss, i_info, ',');
        getline(ss, i_price);

        it.item_type = i_type;
        it.item_name = i_name;
        it.add_info = i_info;

        try
        {
            it.item_price = stold(i_price);
        }
        catch (...)
        {
            continue;
        }

        if (to_lowercase(required_item_type) == to_lowercase(it.item_type))
        {
            cout << "\nItem Type: " << it.item_type
                 << "\nItem Name: " << it.item_name
                 << "\nMore Information: " << it.add_info
                 << "\nPrice: " << it.item_price << " Birr\n";
            found = true;
        }
    }

    if (!found)
        cout << "Couldn't find the item!\n";

    infile.close();
}

void display_all_items()
{
    ifstream infile("item_list.txt");
    if (!infile.is_open())
    {
        cout << "Failed to open file! ";
        exit(1);
    }
   
    
    cout << "\t\tAVAILABLE ITEMS (SORTED BY TYPE).\n";
    cout << "\t\t_________________________________\n\n";

    vector<item> items; // Vector to store all items
    string line;
    
    while (getline(infile, line))
    {
        stringstream ss(line);
        string i_type, i_name, i_info, i_price;
        getline(ss, i_type, ',');
        getline(ss, i_name, ',');
        getline(ss, i_info, ',');
        getline(ss, i_price);

        item it;
        it.item_type = i_type;
        it.item_name = i_name;
        it.add_info = i_info;

        try
        {
            it.item_price = stold(i_price);
        }
        catch (...)
        {
            continue;
        }

        items.push_back(it); // Add to vector
    }

    infile.close();
        //  Check if no items were found
        if (items.empty()) {
            cout << "No items available at the moment.\n";
            return;
        }

    // Sort the vector by item_type
    sort(items.begin(), items.end(), [](const item &a, const item &b)
         { return a.item_type < b.item_type; });

    // Display the sorted items
    for (const auto &it : items)
    {
        cout << "\nItem Type: " << it.item_type;
        Sleep(300);

        cout << "\nItem Name: " << it.item_name;
        Sleep(300);

        cout << "\nMore Information: " << it.add_info;
        Sleep(300);

        cout << fixed << setprecision(2);
        cout << "\nPrice: " << it.item_price << " Birr\n";
             Sleep(600);

             
             
    }
}

void order()
{
    ifstream infile("item_list.txt");
    if (!infile.is_open())
    {
        cout << "Failed to open item list!\n";
        return;
    }

    string search_name;
    cout << "\t\tPLACE YOUR ORDER HERE\n";
    cout << "\t\t_______________________\n\n";
    cout << "Enter the name of the item you want to order: ";
    getline(cin, search_name);

    string line;
    item it;
    bool found = false;

    while (getline(infile, line))
    {
        stringstream ss(line);
        string i_type, i_name, i_info, i_price;
        getline(ss, i_type, ',');
        getline(ss, i_name, ',');
        getline(ss, i_info, ',');
        getline(ss, i_price);

        try
        {
            it.item_type = i_type;
            it.item_name = i_name;
            it.add_info = i_info;
            it.item_price = stold(i_price);
        }
        catch (...)
        {
            continue;
        }

        if (to_lowercase(it.item_name) == to_lowercase(search_name))
        {
            cout << "\nItem found:\n";
            cout << "Item Type: " << it.item_type
                 << "\nItem Name: " << it.item_name
                 << "\nInfo: " << it.add_info
                 << "\nPrice per unit: " << it.item_price << " Birr\n";

            int qty;
            cout << "\nEnter quantity: ";
            cin >> qty;
            cin.ignore();

            if (qty > 0)
            {
                long double total = qty * it.item_price;
                cout << fixed << setprecision(2);
                cout << "Total Price: " << total << " Birr\n";

                // Optional: Save to order history
                ofstream orderfile("orders.txt", ios::app);
                if (orderfile.is_open())
                {
                    orderfile << it.item_name << "," << qty << "," << total << "\n";
                    orderfile.close();
                    cout << "Order placed successfully!\n";
                }
                else
                {
                    cout << "Failed to record the order.\n";
                }
            }
            else
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid quantity!\n";
            }
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Sorry, item not found!\n";
    }

    infile.close();
}
void edit_item() {
    

    ifstream infile("item_list.txt");
    if (!infile) {
        cout << "Unable to open item list file.\n";
        return;
    }

    vector<item> items;
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        item it;
        getline(ss, it.item_type, ',');
        getline(ss, it.item_name, ',');
        getline(ss, it.add_info, ',');
        string price;
        getline(ss, price);
        it.item_price = stold(price);
        items.push_back(it);
    }
    infile.close();

    string name_to_edit;
    cout << "Enter the name of the item to edit: ";
    getline(cin >> ws, name_to_edit);

    bool found = false;
    for (auto &it : items) {
        if (to_lowercase(it.item_name) == to_lowercase(name_to_edit)) {
            found = true;
            cout << "Editing '" << it.item_name << "'. Enter new details:\n";
            cout << "New Type: ";
            getline(cin, it.item_type);
            cout << "New Info: ";
            getline(cin, it.add_info);
            cout << "New Price: ";
            cin >> it.item_price;
            if(cin.fail()){
                cout<<"\nInvalid input!\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            break;
        }
    }

    if (!found) {
        cout << "Item not found.\n";
        return;
    }

    ofstream outfile("item_list.txt");
    for (const auto &it : items) {
        outfile << it.item_type << ',' << it.item_name << ',' << it.add_info << ',' << it.item_price << '\n';
    }
    outfile.close();

    cout << "Item updated successfully.\n";
}

void delete_item() {
    

    ifstream infile("item_list.txt");
    if (!infile) {
        cout << "Unable to open item list file.\n";
        return;
    }

    vector<item> items;
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        item it;
        getline(ss, it.item_type, ',');
        getline(ss, it.item_name, ',');
        getline(ss, it.add_info, ',');
        string price;
        getline(ss, price);
        it.item_price = stold(price);
        items.push_back(it);
    }
    infile.close();

    string name_to_delete;
    cout << "Enter the name of the item to delete: ";
    getline(cin >> ws, name_to_delete);

    bool found = false;
    vector<item> updated_items;
    for (const auto &it : items) {
        if (to_lowercase(it.item_name )==to_lowercase( name_to_delete)) {
            found = true;
        } else {
            updated_items.push_back(it);
        }
    }

    if (!found) {
        cout << "Item not found.\n";
        return;
    }

    ofstream outfile("item_list.txt");
    for (const auto &it : updated_items) {
        outfile << it.item_type << ',' << it.item_name << ',' << it.add_info << ',' << it.item_price << '\n';
    }
    outfile.close();
    cout << "\nDeleting an item...\n";
    Sleep(2000);

    cout << "Item deleted successfully.\n";
}
void owner_menu() {
    string stored_pwd = read_password();
    string entered_pwd;

    cout << "Enter owner password: ";
    getline(cin >> ws, entered_pwd);

    if (entered_pwd != stored_pwd) {
        cout << "Access denied! Incorrect password.\n";
        return;
    }
    cout<<"\nChecking....\n";
    Sleep(2000);
    cout << "Login successful!\n";


    int choice;
    do {
        cout << "\n--- Owner Menu ---\n";
        cout << "1. Add Item\n";
        cout << "2. Edit Item\n";
        cout << "3. Delete Item\n";
        cout << "4. Change Password\n";
        cout << "5. Return to Main Menu\n";        
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: add_item(); break;
            case 2: edit_item(); break;
            case 3: delete_item(); break;
            case 4: change_password(); break;
            case 5: cout << "Returning to main menu...\n"; Sleep(2000); return;
            default: cout << "Invalid choice! Try again.\n";  cin.clear();
            cin.ignore(10000, '\n'); 
        }
    } while (choice != 4);
}



int main() {
    char select;
    int trial = 4;

    while (true) {
        cout << "\n\t\t\tWELCOME TO OUR MINIMARKET SYSTEM!\n";
        cout << "\t\t\t__________________________________\n";
        cout << "1. Owner Login\n";
        cout << "2. Search Item\n";
        cout << "3. See Available Items\n";
        cout << "4. Order Item\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> select;
        cin.ignore();

        switch (select) {
        case '1':
            owner_menu();  // Protected by password
            break;
        case '2':
            search_item();
            break;
        case '3':
            display_all_items();
            break;
        case '4':
            order();
            break;
        case '0':
            cout << "You have successfully exited!\n";
            return 0;
        default:
            if (trial <= 1) {
                cout << "\nNo more attempts left, the program is terminated!\n";
                return 0;
            }
            trial--;
            cout << "Invalid choice. Please try again. " << trial << " attempts left\n";
        }
    }
}
