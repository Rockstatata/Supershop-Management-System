// Roll: 2107006
// Name: Sarwad Hasan Siddiqui
// Project Name: SUPER SHOP MANAGEMENT SYSTEM

#include<bits/stdc++.h>
#include<conio.h>

using namespace std;

class Product;
class Cart;
class Customer;
class Cashier;
class Office;
class Inventory;
class Supershop;

class Product {
    int id, quantity;
    double price;
    string name, category;
    bool availability;
public:
    Product() { ; }
    Product(int id, double price, int quantity, string name, string category, bool availability) {
        this->id = id;
        this->price = price;
        this->quantity = quantity;
        this->name = name;
        this->category = category;
        this->availability = availability;
    }
    void Product_setter(int id, double price, int quantity, string name, string category, bool availability) {
        this->id = id;
        this->price = price;
        this->quantity = quantity;
        this->name = name;
        this->category = category;
        this->availability = availability;
    }
    void Product_getter() {
        cout<<endl;
        cout << "Product ID: " << this->id << endl;
        cout << "Product Name: " << this->name << endl;
        cout << "Product Price: " << this->price << endl;
        cout << "Product Quantity: " << this->quantity << endl;
        cout << "Product Category: " << this->category << endl;
        cout << "Product Availability: " << ((this->availability) ? "Available" : "Not Available") << endl;
    }
    string name_getter() {
        return name;
    }
    bool product_avail() const {
        return availability;
    }
    int id_getter() const {
        return id;
    }
    int quant_getter() const {
        return quantity;
    }
    void set_quant(int i) {
        quantity = i;
    }
    void set_avail(int i){
        if(i<=0){
            availability=0;
        }
        else{
            availability=1;
        }   
    }
    double price_getter() const {
        return price;
    }
    string category_getter() {
        return category;
    }
    ~Product(){;}
};

class Cart {
    vector<Product>products;
    int tot_prod;
    double total_price;
public:
    Cart() { total_price = 0; tot_prod = 0; }
    void show_cart();
    void add_to_cart(const Product&, int);
    bool remove_from_cart(const Product&, int);
    double total_price_calc() {
        return total_price;
    }
    friend class Cashier;
    friend bool operator==(Product&, Product&);
    int get_prod() {
        return tot_prod;
    }
    void removeall(){
        products.clear();
        tot_prod=0;
        total_price=0;
    }
    ~Cart(){;}
};

bool operator==(const Product& p, const Product& q) {
    if (p.id_getter() == q.id_getter()) {
        return true;
    }
    return false;
}

void Cart::show_cart() {
    cout<<"________________________________________\v";
    for (int i = 0; i < tot_prod; i++) {
        cout<<endl;
        products[i].Product_getter();
        cout << endl;
    }
    cout<<"________________________________________\v"<<endl;
}

void Cart::add_to_cart(const Product& p, int q) {
    products.push_back(p);
    products.at(products.size() - 1).set_quant(q);
    total_price += (products.at(products.size() - 1).price_getter() * q);
    tot_prod++;
}
bool Cart::remove_from_cart(const Product& p, int q) {
    int i;
    for (i = 0; i < tot_prod; i++) {
        if (products[i] == p) {
            break;
        }
    }
    if(i>=tot_prod){
        cout<<"You don't have this product in your cart yet"<<endl;
        return false;
    }
    else{
        auto it = products.begin();
        it += i;
        if (products[i].quant_getter() <= q) {
            products.erase(it);
            tot_prod--;
        }
        else {
            products[i].set_quant(products[i].quant_getter() - q);
        }
        total_price -= (p.price_getter() * q);
        return true;
    }
}

class Inventory {
    vector<Product>products;
    int total_products;
    int total_avail_products;
public:
    Inventory() { total_products = 0; total_avail_products=0; }
    void show_product();
    void show_avail();
    Product& prod_return(int);
    bool if_avail(int, int);
    void add_product(const Product& product);
    void remove_product(const Product& product, int);
    void update_quantity(const Product& product, int quantity);
    void restock(const Product&);
    friend bool operator==(Product&, Product&);
    void search_product(int);
    void search_product(string);
    void search_product(string,int);
    void search_product(double,double);
    ~Inventory(){;}
};

void Inventory::add_product(const Product& product) {
    products.push_back(product);
    total_products++;
    if((products.at(products.size()-1).product_avail())){
        total_avail_products++;
    }
}

void Inventory::remove_product(const Product& product, int quantity) {
    int i;
    for (i = 0; i < total_products; i++) {
        if (products[i] == product) {
            break;
        }
    }
    if (products[i].quant_getter() <= quantity) {
        products[i].set_quant(0);
        products[i].set_avail(products[i].quant_getter() - quantity);
        total_avail_products--;
    }
    else {
        products[i].set_quant(products[i].quant_getter() - quantity);
    }
}

void Inventory::restock(const Product& p){
    int i;
    for (i = 0; i < total_products; i++) {
        if (products[i] == p) {
            products[i].set_quant(1);
            products[i].set_avail(1);
            total_avail_products++;
        }
    }
}


void Inventory::show_product() {
    int n = products.size();
    cout<<"________________________________________\v";
    cout<<"There are total "<<total_avail_products<<" products in the shop\v"<<endl;
    for (int i = 0; i < n; i++) {
        cout<<endl;
        products[i].Product_getter();
        cout << endl;
    }
    cout<<"________________________________________\v"<<endl;
}
void Inventory::show_avail() {
    int n = products.size();
    cout<<"________________________________________\v";
    cout<<"There are "<<total_avail_products<<" products currently available in the shop\v"<<endl;
    for (int i = 0; i < n; i++) {
        if (products[i].product_avail() == 1) {
            cout<<endl;
            products[i].Product_getter();
            cout << endl;
        }
    }
    cout<<"________________________________________\v"<<endl;
}

bool Inventory::if_avail(int id, int quantity) {
    int n = products.size();
    for (int i = 0; i < n; i++) {
        if (products[i].id_getter() == id) {
            if (products[i].product_avail() == 1) {
                if (products[i].quant_getter() >= quantity) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Inventory::update_quantity(const Product& product, int quantity) {
    int i;
    for (i = 0; i < total_products; i++) {
        if (products[i] == product) {
            products.at(i).set_quant(quantity + products[i].quant_getter());
            break;
        }
    }
    if (i >= total_products) {
        products.push_back(product);
        products.at(products.size() - 1).set_quant(quantity);
        total_products++;
    }
}

Product& Inventory::prod_return(int id) {
    int n = products.size();
    for (int i = 0; i < n; i++) {
        if (products[i].id_getter() == id) {
            return products[i];
        }
    }
    return products[0];
}

void Inventory::search_product(int id){
    int i;
    cout<<"\n=========================================================================\v"<<endl;
    for(i=0;i<total_products;i++){
        if(products[i].id_getter()==id){
            cout<<"Your desired product has been found in our shop"<<endl<<endl;
            cout<<"The product is "<<((products[i].product_avail())?"available":"not available")<<endl<<endl;
            products[i].Product_getter();
            break;
        }
    }
    if(i>=total_products){
        cout<<"The product is not currently available in our store"<<endl<<endl;
    }
    cout<<"\n=========================================================================\v"<<endl;
}

void Inventory::search_product(string name){
    int i;
    cout<<"\n=========================================================================\v"<<endl;
    for(i=0;i<total_products;i++){
        if(products[i].name_getter()==name){
            cout<<"Your desired product has been found in our shop"<<endl<<endl;
            cout<<"The product is "<<((products[i].product_avail())?"available":"not available")<<endl<<endl;
            products[i].Product_getter();
            break;
        }
    }
    if(i>=total_products){
        cout<<"The product is not currently available in our store"<<endl<<endl;
    }
    cout<<"\n=========================================================================\v"<<endl;
}

void Inventory::search_product(string category,int dummy){
    int i,count=0;
    for(i=0;i<total_products;i++){
        if(products[i].category_getter()==category){
            count++;
        }
    }
    if(count==0){
        cout<<"There are no products available in that category."<<endl<<endl;
        return;
    }
    cout<<"=========================================================================\v"<<endl;
    cout<<"\n\nThere are "<<count<<" products available in this category\v"<<endl;
    for(i=0;i<total_products;i++){
        if(products[i].category_getter()==category){
            products[i].Product_getter();
        }
    }
    cout<<"\n=========================================================================\v"<<endl;
}

void Inventory::search_product(double low, double high){
    int i,price,count=0;
    for(i=0;i<total_products;i++){
        price=products[i].price_getter();
        if(price>=low && price <=high){
            count++;
        }
    }
    if(count==0){
        cout<<"There are no products available in the current price range"<<endl<<endl;
        return;
    }
    cout<<"=========================================================================\v"<<endl;
    cout<<"\n\nThere are "<<count<<" products available in this price range\v"<<endl;
    for(i=0;i<total_products;i++){
        price=products[i].price_getter();
        if(price>=low && price <=high){
            products[i].Product_getter();
        }
    }
    cout<<"\n=========================================================================\v"<<endl;
}


class Customer {
    int id;
    bool exclusive;
    string name, address, contact_num, email, gender;
    double net_spent;
public:
    Customer() { exclusive=0; net_spent=0;}
    Customer(int id, string name, string address, string contact_num, string email, string gender) {
        this->id = id;
        this->name = name;
        this->address = address;
        this->contact_num = contact_num;
        this->email = email;
        this->gender = gender;
        this->exclusive=0;
        this->net_spent=0;
    }
    string get_name() {
        return this->name;
    }
    string get_gender() {
        return this->gender;
    }
    int get_id(){
        return this->id;
    }
    bool exclusive_getter(){
        return this->exclusive;
    }
    void set_exlusive(){
        this->exclusive=true;
    }
    void set_spent(double spent){
        this->net_spent+=spent;
    }
    void cust_getter() {
        cout<<endl;
        cout << "Customer Id: " << id << endl;
        cout << "Customer Name: " << name << endl;
        cout << "Customer address: " << address << endl;
        cout << "Customer Contact Number: " << contact_num << endl;
        cout << "Customer Email: " << email << endl;
        cout << "Customer Gender: " << gender << endl;
        cout << "Customer Total spent: "<< net_spent<<endl;
    }
    ~Customer(){;}
};


class Cashier {
    int id;
    string name;
public:
    Cashier() { ; }
    Cashier(int id, string name) {
        this->id = id;
        this->name = name;
    }
    void process_payment(Cart&, Customer&);
    string getname() {
        return this->name;
    }
    int getid(){
        return this->id;
    }
    void cashier_getter(){
        cout<<endl;
        cout << "Cashier ID: " << this->id << endl;
        cout << "Cashier Name: " << this->name << endl;
    }
    ~Cashier(){;}

};

void Cashier::process_payment(Cart& cart, Customer& customer) {
    double tot=0;
    if(customer.exclusive_getter()){
        cout<<"\n\n\n Congratulations!!! You have got the exclusive membership in this shop. You will get 20% discount in your current and next purchases!!!\n\n\n";
    }
    cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "|========================================SUPERSHOP PAYMENT RECEIPT========================================|" << endl;
    cout<<"---------------------------------------------------------------------------------------------------------------\v"<<endl;
    cout << "CONTACT INFO:\v"<<endl;
    customer.cust_getter();
    cout << "==========================================================================================================\v" << endl;
    cout << "Cashier ID: " << id << endl;
    cout << "Cashier: " << name << endl;
    cout << "==========================================================================================================\v" << endl;
    cout << "SERIAL NO.               ITEM               QUANTITY               CATEGORY               PRICE\v";
                                                                                                                
    for (int i = 0; i < cart.tot_prod; i++) {
        cout <<"    "<<(i + 1);
        cout<< "                  " << cart.products[i].name_getter();
        cout<< "               " << cart.products[i].quant_getter();
        cout<< "                  " << cart.products[i].category_getter();
        cout<< "              " << cart.products[i].price_getter() << endl << endl;
    }
    cout << "__________________________________________________________________________________________________" << endl << endl;
    cout << "TOTAL PRICE                                                                              " << cart.total_price_calc() << endl << endl;
    cout << "VAT                                                                                      " << (cart.total_price_calc() * 0.15) << endl << endl;
    if(customer.exclusive_getter()){
        cout << "__________________________________________________________________________________________________" << endl << endl;
        cout <<"DISCOUNT                                                                                -"<< (cart.total_price_calc()+ cart.total_price_calc() * 0.15)*0.2 <<endl <<endl;
        cout << "__________________________________________________________________________________________________" << endl << endl;
        tot = (cart.total_price_calc() + (cart.total_price_calc() * 0.15))*0.8;
        cout << "GRAND TOTAL                                                                              " <<  tot << "\v";
    }
    else{
        cout << "__________________________________________________________________________________________________" << endl << endl;
        tot = cart.total_price_calc() + (cart.total_price_calc() * 0.15);
        cout << "GRAND TOTAL                                                                              " << tot << "\v";
    }
    cout << "\v";
    customer.set_spent(tot);
    if(tot>=1000){
        if(!customer.exclusive_getter()){
            cout<<"\nCongratulations, you are now an exlusive member of this shop. Come back again to enjoy a flat 20% discount on your next purchase!!!\n\n";
        }
        customer.set_exlusive();
    }
    cout << "Thank you for choosing us " << ((customer.get_gender() == "Male") ? " Sir" : " Madam") << ". Come visit us again\v";

    cout << "\v===========================SUPERSHOP MANAGEMENT SYSTEM BY SARWAD========================================\v" << endl;
}

class Office{
    vector<Cashier>cashier;
    int total_employees;
    public:
        Office(){total_employees=0;}
        void add_cashier(const Cashier&);
        void remove_cashier(int);
        void show_cashiers();
        Cashier get_cashier(int);
        ~Office(){;}
};

Cashier Office::get_cashier(int id){
    for(int i = 0;i<total_employees;i++){
        if(cashier[i].getid()==id){
            return cashier[i];
        }
    }
    return cashier[0];
}

void Office::add_cashier(const Cashier& c){
    cashier.push_back(c);
    total_employees++;
}

void Office::remove_cashier(int id){
    int i;
    for (i = 0; i < total_employees; i++) {
        if ((cashier[i].getid())==id) {
            break;
        }
    }
    if(i>=total_employees){
        cout<<"There aren't any employee with that id here"<<endl;
    }
    else{
        auto it = cashier.begin();
        it += i;
        cashier.erase(it);
        total_employees--;
    }
}

void Office::show_cashiers(){
    int n = cashier.size();
    cout<<"________________________________________\v";
    cout<<"There are total "<<total_employees<<" employees in the shop\v"<<endl;
    for (int i = 0; i < n; i++) {
        cout<<endl;
        cashier[i].cashier_getter();
        cout << endl;
    }
    cout<<"________________________________________\v"<<endl;
}

class Database{
    vector<Customer>customers;
    int total_customers;
    public:
        Database(){total_customers=0;}
        void add_customers(const Customer&);
        bool find_customers(int);
        Customer& customer_getter(int);
        void show_all();
        ~Database(){;}

};

void Database::show_all(){
    cout<<"\n=========================================================================\v"<<endl;
    cout<<"Total of "<<total_customers<<" customers have visited this shop"<<endl;
    for(int i = 0;i<total_customers;i++){
        customers[i].cust_getter();
    }
    cout<<"\n=========================================================================\v"<<endl;
}

void Database::add_customers(const Customer& c){
    customers.push_back(c);
    total_customers++;
}

bool Database::find_customers(int id){
    for(int i=0;i<total_customers;i++){
        if((customers[i].get_id())==id){
            return true;
        }
    }
    return false;
}

Customer& Database::customer_getter(int id){
    for(int i=0;i<total_customers;i++){
        if((customers[i].get_id())==id){
            return customers[i];
        }
    }
    return customers[0];
}

class Supershop {
    string password;
    Inventory inventory;
    Cart cart;
    Office office;
    Database database;
    bool runtime;
    int restock_id;
public:
    Supershop(){
        Cashier temp = Cashier(1,"Namira");
        office.add_cashier(temp);
        password="Manager";
        runtime=0;
        restock_id=1000;
    }
    void start_shopping();
    void stock();
    void modeselect();
    void management();
    ~Supershop(){;}
};

void Supershop::management(){
    int q=0,p=0;
    string pass;
    cout<<"===========================================================================\v"<<endl;
    cout<<"       ::::PLEASE ENTER THE PASSWORD TO VERIFY YOUR IDENTITY:::"<<endl<<endl<<endl;
    cout<<"Password: "<<endl;
    cin>>pass;
    if(pass==password){
        system("cls");
        cout<<"\n\n\n\n";
        cout<<"           WELCOME TO THE SHOP, MANAGER. HOW WOULD YOU LIKE TO MANAGE THE SHOP TODAY?\v"<<endl;
        while(q!=9){
            cout<<"Choose a query::"<<endl<<endl;
            cout<<"1. Add a product"<<endl<<endl;
            cout<<"2. Remove a product"<<endl<<endl;
            cout<<"3. Show all products"<<endl<<endl;
            cout<<"4. Search a product"<<endl<<endl;
            cout<<"5. Recruit a cashier"<<endl<<endl;
            cout<<"6. Fire a cashier"<<endl<<endl;
            cout<<"7. Show all cashiers"<<endl<<endl;
            cout<<"8. Show past transactions and details of the customers"<<endl<<endl;
            cout<<"9. Exit and Finalize changes"<<endl<<endl;
            cin>>q;
            int n;
            int id, quantity;
            double price,p1,p2;
            string name, category;
            bool availability;
            switch(q){
                case 1:
                    system("cls");
                    cout<<"How do you want to stock the products?\v"<<endl;
                    cout<<"\n 1. Default Stock\n"<<endl;
                    cout<<"\n 2. Manual Stock\n"<<endl;
                    cin>>n;
                    switch(n){
                        case 1:
                            if(runtime==false){stock();}
                            runtime=true;
                            cout<<"\nThe products have been stocked by default\v"<<endl;
                            break;
                        case 2:
                            cout<<"\vHow many products do you want to add?"<<endl<<endl;
                            cin>>n;
                            cout<<endl;
                            for(int i = 0;i<n;i++){
                                cout<<"Please enter the id of the product"<<endl<<endl;
                                cin>>id;
                                cout<<endl;
                                cout<<"Please enter the name of the product"<<endl<<endl;
                                cin>>name;
                                cout<<endl;
                                cout<<"Please enter the quantity of the added product"<<endl<<endl;
                                cin>>quantity;
                                cout<<endl;
                                cout<<"Please enter the price of the added product"<<endl<<endl;
                                cin>>price;
                                cout<<endl;
                                cout<<"Please enter the category of the added prdouct"<<endl<<endl;
                                cin>>category;
                                cout<<endl;
                                availability=(quantity>0)?true:false;
                                inventory.add_product(Product(id,price,quantity,name,category,availability));
                                cout<<"\nThe product has been successfully added to the inventory\v"<<endl;
                        }
                            break;
                    }
                    break;
                case 2:
                    system("cls");
                    cout<<"\vHow many products do you want to remove?\v"<<endl;
                    cin>>n;
                    for(int i = 0;i<n;i++){
                        cout<<"Please enter the id of the product:"<<endl<<endl;
                        cin>>id;
                        cout<<endl;
                        cout<<"Please enter the quantity of the product"<<endl<<endl;
                        cin>>quantity;
                        cout<<endl;
                        inventory.remove_product(inventory.prod_return(id), quantity);
                        cout<<"\nThe product has been successfully removed from the inventory\v"<<endl;
                    }
                    break;
                case 3:
                    system("cls");
                    inventory.show_product();
                    break;
                case 4:
                    system("cls");
                    cout<<"Choose the way you want to search the products\v"<<endl;
                    cout<<"\n 1. Search by id\n"<<endl;
                    cout<<"\n 2. Search by name\n"<<endl;
                    cout<<"\n 3. Search by category\n"<<endl;
                    cout<<"\n 4. Search by price range\n"<<endl;
                    cin>>n;
                    switch(n){
                        case 1:
                            cout<<"\nPlease enter the id of the product\n"<<endl;
                            cout<<"ID:"<<endl<<endl;
                            cin>>id;
                            cout<<endl;
                            inventory.search_product(id);
                            break;
                        case 2:
                            cout<<"\nPlease enter the name of the product\n"<<endl;
                            cout<<"Name:"<<endl<<endl;
                            cin>>name;
                            cout<<endl;
                            inventory.search_product(name);
                            break;
                        case 3:
                            cout<<"\nPlease enter the category of the product\n"<<endl;
                            cout<<"Category:"<<endl<<endl;
                            cin>>category;
                            cout<<endl;
                            inventory.search_product(category,id=0);
                            break;
                        case 4:
                            cout<<"\nPlease enter the price range of the product\n"<<endl;
                            cout<<"Lowest Price range:"<<endl<<endl;
                            cin>>p1;
                            cout<<endl;
                            cout<<"Highest Price range:"<<endl<<endl;
                            cin>>p2;
                            cout<<endl;
                            inventory.search_product(p1,p2);
                            break;
                    }
                    break;
                case 5:
                    system("cls");
                    cout<<"\vHow many employees do you want to recruit?"<<endl<<endl;
                    cin>>n;
                    cout<<endl;
                    for(int i = 0;i<n;i++){
                        cout<<"Please enter the id of the employee"<<endl<<endl;
                        cin>>id;
                        cout<<endl;
                        cout<<"Please enter the name of the employee"<<endl<<endl;
                        cin>>name;
                        cout<<endl;
                        office.add_cashier(Cashier(id,name));
                    }
                    break;
                case 6:
                    system("cls");
                    cout<<"\vHow many employees do you want to fire?"<<endl<<endl;
                    cin>>n;
                    cout<<endl;
                    for(int i = 0;i<n;i++){
                        cout<<"Please enter the id of the employee"<<endl<<endl;
                        cin>>id;
                        cout<<endl;
                        office.remove_cashier(id);
                    }
                    break;
                case 7:
                    system("cls");
                    office.show_cashiers();
                    break;
                case 8:
                    database.show_all();
                    break;
                case 9:
                    cout<<"\vYOUR REQUESTS HAVE BEEN SUCCESSFULLY PROCESSED!!!\v";
                    break;
            }
        }
    }
    else{
        system("cls");
        cout<<"                     YOU ARE NOT THE MANAGER!!!"<<endl;
        cout<<"                   MANAGEMENT SYSTEM IS EXITING...\v";
        return;
    }
}

void Supershop::stock() {
    inventory.add_product(Product(1, 80, 7, "Toothpaste", "Toiletries", 1));
    inventory.add_product(Product(2, 50, 10, "Soap", "Toiletries", 1));
    inventory.add_product(Product(3, 140, 8, "Shampoo", "Toiletries", 1));
    inventory.add_product(Product(4, 100, 18, "Notebook", "Stationary", 1));
    inventory.add_product(Product(5, 10, 40, "Pens", "Stationary", 1));
    inventory.add_product(Product(6, 250, 1, "Books", "Stationary", 1));
    inventory.add_product(Product(7, 400, 0, "Perfume", "Beauty", 0));
    inventory.add_product(Product(8, 4000, 3, "Fan", "Household", 1));
    inventory.add_product(Product(9, 1300, 5, "Bag", "Utilities", 1));
    inventory.add_product(Product(10, 90, 13, "Medicine", "Medical", 1));
}

void Supershop::start_shopping() {
    int id = 0, q=0, p=0, pro_id, quantity,n;
    double p1,p2;
    string name, category, address, contact_num, email, gender, choice = "Yes";
    cout<<"================================================================================================\v"<<endl;
    cout << "-------------------------------- -WELCOME TO OUR SUPERSHOP!!!----------------------------------\v" << endl;
    cout <<"          I am " << (office.get_cashier(0).getname()) << ", the cashier and I will be here the whole time to assist you!\v" << endl;
    cout << "BUT BEFORE YOU CAN START BROWSING AND START SHOPPING HERE WE NEED TO REGISTER YOUR INFORMATIONS!!!\v\v" << endl;
    cin.ignore();
    fflush(stdin);
    cout<<"Please enter your id:"<<endl<<endl;
    cin>>id;
    cout<<endl;
    cart.removeall();
    if(!database.find_customers(id)){
        cin.ignore();
        fflush(stdin);
        cout << "Please enter your name:" << endl<<endl;
        getline(cin, name);
        cout<<endl;
        cout << "Please enter your address:" << endl<<endl;
        getline(cin, address);
        cout<<endl;
        cout << "Please enter your contact number:" << endl<<endl;
        getline(cin, contact_num);
        cout<<endl;
        cout << "Please enter your email address:" << endl<<endl;
        getline(cin, email);
        cout<<endl;
        cout << "Please enter your gender:" << endl<<endl;
        getline(cin, gender);
        cout<<endl;
        database.add_customers(Customer(id, name, address, contact_num, email, gender));
        gender = (gender == "Male") ? " Sir" : " Madam";
        cout << "Thank you for being with us here today " << database.customer_getter(id).get_name() <<", "<< gender <<"!\v"<< endl;
        cout << "Please let us know how can we be of your service today," << gender << ":\v" << endl<<endl;
    }
    else{
        cout<<endl;
        if(restock_id!=1000) inventory.restock(inventory.prod_return(restock_id));
        system("cls");
        cout<<"=================================================================================================\v"<<endl;
        gender = ((database.customer_getter(id).get_gender()=="Male")?"Sir!":"Madam!");
        cout<<"Welcome Back, "<< database.customer_getter(id).get_name()<<" "<<gender<<"\v"<<endl;
        cout << "Please let us know how can we be of your service today," << gender << ":\v" << endl<<endl;
        cout <<"=================================================================================================\v\v\v"<<endl;
    }
    while (q != 5) {
        cout << "1. Show the whole inventory of products" << endl<<endl;
        cout << "2. Show only the available products" << endl<<endl;
        cout << "3. Start Shopping from the available products" << endl<<endl;
        cout << "4. Request Restock of an unavailable product" << endl<<endl;
        cout << "5. Exit & Process your purchase" << endl<<endl;
        cin >> q;
        switch (q) {
        case 1:
            inventory.show_product();
            break;
        case 2:
            inventory.show_avail();
            break;
        case 3:
            system("cls");
            inventory.show_avail();
            p = 0;
            while (p != 5) {
                cout << "Choose your query" << endl<<endl;
                cout << "1. Add a product to cart" << endl<<endl;
                cout << "2. Remove a product from cart" << endl<<endl;
                cout << "3. Search a product"<<endl<<endl;
                cout << "4. Show your cart" << endl<<endl;
                cout << "5. Checkout" << endl<<endl;
                cin >> p;
                switch (p) {
                case 1:
                    do {
                        cout << "\nWhich product do you want?Please enter it's id and quantity:" << endl<<endl;
                        cout << "ID: " << endl<<endl;
                        cin >> pro_id;
                        cout<<endl;
                        cout << "Quantity: " << endl<<endl;
                        cin >> quantity;
                        cout<<endl;
                        if (inventory.if_avail(pro_id, quantity)) {
                            cart.add_to_cart(inventory.prod_return(pro_id), quantity);
                            inventory.remove_product(inventory.prod_return(pro_id), quantity);
                            cout<<"The product has been successfully added to your cart\v"<<endl;
                        }
                        else {
                            cout << "This product is not currently available\v" << endl;
                        }
                        cout << "Do you want to add more products?Type Yes/yes if you want to." << endl<<endl;
                        cin >> choice;
                        cout<<"\v"<<endl;
                    } while (choice == "Yes" || choice == "yes");
                    break;
                case 2:
                    do {
                        cout << "\nWhich product do you want to remove from the cart?Please enter it's id and quantity:" << endl;
                        cout << "ID: " << endl<<endl;
                        cin >> pro_id;
                        cout<<endl;
                        cout << "Quantity: " << endl<<endl;
                        cin >> quantity;
                        cout<<endl;
                        bool av= cart.remove_from_cart(inventory.prod_return(pro_id), quantity);
                        if(av)inventory.update_quantity(inventory.prod_return(pro_id), quantity);
                        cout<<"The product has been successfully removed from your cart\v"<<endl;
                        cout << "Do you want to remove more products?Type Yes/yes if you want to." << endl<<endl;
                        cin >> choice;
                        cout<<"\v"<<endl;
                    } while (choice == "Yes" || choice == "yes");
                    break;
                case 3:
                    system("cls");
                    cout<<"Choose the way you want to search the products\v"<<endl;
                    cout<<"\n 1. Search by id\n"<<endl;
                    cout<<"\n 2. Search by name\n"<<endl;
                    cout<<"\n 3. Search by category\n"<<endl;
                    cout<<"\n 4. Search by price range\n"<<endl;
                    cin>>n;
                    switch(n){
                        case 1:
                            cout<<"\nPlease enter the id of the product\n"<<endl;
                            cout<<"ID:"<<endl;
                            cin>>id;
                            inventory.search_product(id);
                            break;
                        case 2:
                            cout<<"\nPlease enter the name of the product\n"<<endl;
                            cout<<"Name:"<<endl;
                            cin>>name;
                            inventory.search_product(id);
                            break;
                        case 3:
                            cout<<"\nPlease enter the category of the product\n"<<endl;
                            cout<<"ID:"<<endl;
                            cin>>category;
                            inventory.search_product(category,0);
                            break;
                        case 4:
                            cout<<"\nPlease enter the price range of the product\n"<<endl;
                            cout<<"Lowest Price range:"<<endl<<endl;
                            cin>>p1;
                            cout<<endl;
                            cout<<"Highest Price range:"<<endl<<endl;
                            cin>>p2;
                            cout<<endl;
                            inventory.search_product(p1,p2);
                            break;
                    }
                    break;
                case 4:
                    cout << "You have " << cart.get_prod() << " products in your cart" << endl;
                    cart.show_cart();
                    break;
                case 5:
                    system("cls");
                    cout << "You have " << cart.get_prod() << " products in your cart" << endl;
                    cart.show_cart();
                    cout << "\vTotal price: " << cart.total_price_calc() << " Tk/-\v" << endl;
                    cout <<"\vChecking out.......\v"<<endl;
                    break;
                }
            }
            break;
        case 4:
            cout<<"\nPlease enter the id of the product which you want to be restocked:"<<endl<<endl;;
            cout<<"ID: "<<endl;
            cin>>restock_id;
            cout<<endl;
            cout << "\nYour request has been processed! Thanks for your input!" << endl<<endl;;
            break;
        case 5:
            system("cls");
            office.get_cashier(0).process_payment(cart, database.customer_getter(id));
            break;
        }
    }
}

void Supershop::modeselect(){
    int n=0;
    while(n!=3){
        cout<<"\v\v=====================================================================\v"<<endl;
        cout<<"-------------------------------------------------------------------"<<endl;
        cout<<"|             Welcome to the Supershop Management System          |"<<endl;
        cout<<"-------------------------------------------------------------------\v"<<endl;
        cout<<"                   ::Choose a mode to login::                    \v"<<endl;
        cout<<"1. Store Manager"<<endl;
        cout<<"2. Customer"<<endl;
        cout<<"3. Exit"<<endl;
        cin>>n;
        switch(n){
            case 1:
                management();
                break;
            case 2:
                if(runtime==false){stock();}
                start_shopping();
                runtime=true;
                break;         
            case 3:
                cout<<"===============================================================================\v"<<endl;
                cout<<"\v|------------------THANKS FOR CHOOSING OUR SERVICE, MADE BY SARWAD----------------------|\v"<<endl<<endl;
                cout<<"               THE MANAGEMENT SYSTEM IS EXITING...\v"<<endl;
                break;
        }
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    Supershop Shwapno;
    Shwapno.modeselect();
    return 0;
}