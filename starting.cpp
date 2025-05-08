#include <iostream>
using namespace std;
struct product // a structure that enables to accept and display description of an item
{
  string item_type;
  string item_name;
  double item_price;
  string add_info;
};
struct vendor
{ // full information of a vendor
  string name;
  long unsigned int phone_no;
  string email;
  string address;
  product p;
};
void offer_product(vendor v[], int n)
{ // accepts a new product to be selled or rented
  for (int i = 0; i < n; ++i)
  {
    cout << "Enter the type of the product: ";
    getline(cin, v[i].p.item_type);

    cout << "Enter the name of the product: ";
    getline(cin, v[i].p.item_name);

    cout << "Enter additional information  of the product if any : ";
    getline(cin, v[i].p.add_info);

    cout << "Enter the price of the product: ";
    cin >> v[i].p.item_price;
    cin.ignore();
  }
}
void get_vendor_info(vendor *v, int n)
{
  for (int k = 0; k < n; ++k)
  {
    cout << "Enter your name: ";
    getline(cin, v[k].name);
    cout << "Enter your email: ";
    getline(cin, v[k].email);
    cout << "Enter your address: ";
    getline(cin, v[k].address);
    cout << "Enter your phone number: ";
    cin >> v[k].phone_no;
    cin.ignore();
  }
}

void display_product(vendor v[], int n)
{ // displays the product information

  cout << "\t\t\tHERE ARE AVAILABLE ITEMS FOR THIS ROUND\n";
  for (int j = 0; j < n; ++j)
  {
    cout << "Product type: " << v[j].p.item_type << endl;
    cout << "Product name: " << v[j].p.item_name << endl;
    cout << "Additional information: " << v[j].p.add_info << endl;
    cout << "Product price: " << v[j].p.item_price << endl;
  }
}

int main()
{
  int n;
  cout << "Enter the number of vendors allowed this round: ";
  cin >> n;
  cin.ignore();
  vendor v[n];

  offer_product(v, n);
  get_vendor_info(v,n);
  display_product(v, n);
  return 0;
}