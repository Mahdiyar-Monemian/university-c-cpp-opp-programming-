#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include "Date.cpp"
#include "Store.cpp"

using namespace std;

string input;

void get_input(){
    cin >> input;
}

void say_help(){
    cout << "=============================================" << endl;
    cout << "customers" << endl;
    cout << "products" << endl;
    cout << "stocks" << endl;
    cout << "add product" << endl;
    cout << "add customer" << endl;
    cout << "add stocks {product id} {quantity}" << endl;
    cout << "customer {customer_id} add {product_id} {quantity}" << endl;
    cout << "customer {customer_id} remove {product_id}" << endl;
    cout << "customer {customer_id} cart" << endl;
    cout << "checkout {customer_id}" << endl;
    cout << "report {begin_date} {end_date}" << endl;
    cout << "save" << endl;
    cout << "help" << endl;
    cout << "=============================================" << endl;
}

void say_warning(string s){
    cout << s << endl;
}

void say_wrong_input(string s = "wrong command type help"){
    cout << s << endl;
}

bool try_to_get_int(int& i, string warning = ""){
    get_input();
    try{
        i = stoi(input);
        return true;
    }catch(exception e){
        if(warning != "")
            say_warning(warning);
        return false;
    }
}

int main(){
    Store store;
    say_help();
    while(true){
        try{
            cout << "\nType the command you want: " << endl;
            get_input();
            if(input == "exit"){
                break;

            }else if(input == "customers"){
                store.print_customers();

            }else if(input == "products"){
                store.print_products();

            }else if(input == "add"){
                get_input();
                // add product
                if(input == "product"){
                    store.add_product();

                // add customer
                }else if(input == "customer"){
                    store.add_customer();
            
                }else if(input == "stock"){
                    int id, quantity;
                    if(!try_to_get_int(id, "enter a valid id"))
                        continue;
                    if(!try_to_get_int(quantity, "enter a valid quantity"))
                        continue;

                    store.add_stock(id, quantity);

                }else{
                    say_wrong_input("only \"add product\" and \"add customer\"");
                }
            }else if(input == "customer"){

                int customer_id;
                if(!try_to_get_int(customer_id, "please enter a valid customer id"))
                    continue;

                Customer& customer = store.get_customer(customer_id);

                get_input();
                // customer {customer_id} add {product_id} {quantity}
                if(input == "add"){
                    int product_id, quantity;
                    if(!try_to_get_int(product_id, "please enter a valid product id"))
                        continue;

                    if(!try_to_get_int(quantity, "please enter a valid quantity"))
                        continue;
            
                    customer.add_purchase(store.get_product(product_id), quantity);
                }

                // customer {customer_id} remove {product_id}
                else if(input == "remove"){
                    int product_id;
                    if(!try_to_get_int(product_id, "please enter a valid product id"))
                        continue;                

                    customer.cancel_purchase(product_id);
                }

                // customer {customer_id} cart
                else if(input == "cart"){
                    customer.get_cart().print();
                }

                else{
                    say_wrong_input();
                }

            // checkout {customer_id}
            }else if(input == "checkout"){
                int customer_id;
                if(!try_to_get_int(customer_id, "please enter a valid customer id"))
                    continue;
                
                store.check_out(customer_id);
            
            // save
            }else if(input == "save"){
                store.save_to_file();
            }

            // report {begin_date} {end_date}
            else if(input == "report"){
                Date begin, end;
                cin >> begin >> end;
                store.sales_report(begin, end);
            }

            // help
            else if(input == "help"){
                say_help();
            }

            else{
                say_wrong_input();
            }
        }catch(invalid_argument& e){
            cout << "ERROR: " << e.what();
        }
        
    }
}