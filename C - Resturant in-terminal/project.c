#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX 50
#define Foodpath "foods.txt"
#define Datapath "data.txt"
#define Orderpath "orders.txt"
#define Helppath "help.txt"

struct Food{
    char name[MAX];
    float price;
};

struct Order{
    char foodName[MAX];
    char customer[MAX];
    char date[MAX];
};

void strLower(char *str){
    for(int i = 0; str[i] != '\0'; i++)
        str[i] = tolower(str[i]);
}

void AddFood(struct Food * foods, int foodCount){
    int i = foodCount - 1;
    printf("Write name and price: ");
    scanf("%s %f", foods[i].name, &foods[i].price);
    strLower(foods[i].name);
    printf("%s was added to the menu with price of %.2f$\n", foods[i].name, foods[i].price);
}

void UpdateDataFile(int foodCount, int orderCount, float income){
    FILE *fp = fopen(Datapath, "w");
    fprintf(fp, "%d %d %.2f", foodCount, orderCount, income);
    fclose(fp);
}

void UpdateFoodFile(struct Food * foods, int foodCount){
    FILE * fp = fopen(Foodpath, "w+");
    for(int i = 0; i < foodCount; i++)
        fprintf(fp, "%s %.2f\n", foods[i].name, foods[i].price);
    fclose(fp);
}

void swapFoods(struct Food *a, struct Food *b){
    struct Food c = *a;
    *a = *b;
    *b = c;
}

void SortFoods(struct Food * foods, int foodCount){
    for(int i = 0; i < foodCount; i++){
        int maxIndex = i;
        for(int j = i; j < foodCount; j++)
            if(foods[j].price > foods[maxIndex].price)
                maxIndex = j;
        swapFoods(&foods[i], &foods[maxIndex]);
    }
    printf("Foods have been sorted.\n");
}

void ReadFoods(struct Food * foods, int foodCount){
    FILE * fp = fopen(Foodpath, "r");
    for(int i = 0; i < foodCount; i++)
        fscanf(fp, "%s %f", foods[i].name, &foods[i].price);
    fclose(fp);
}

void PrintFoods(struct Food * foods, int foodCount){
    for(int i = 0; i < foodCount; i++)
        printf("%s : %.2f\n", foods[i].name, foods[i].price);
}

struct Food* FindFood(char name[MAX], struct Food * foods, int foodCount){
    strLower(name);
    for(int i = 0; i < foodCount; i++)
        if(strcmp(name, foods[i].name) == 0)
            return &foods[i];
    return NULL;
}

void SearchFood(struct Food * foods, int foodCount){
    char name[MAX];
    printf("searching for: ");
    scanf("%s", name);
    struct Food * foundFood = FindFood(name, foods, foodCount);
    if(foundFood != NULL)
        printf("price of %s is %.2f\n", name, foundFood->price);
    else
        printf("there is no such food as %s\n", name);
}

void EditFood(struct Food * foods, int foodCount){
    char name[MAX];
    printf("you want to edit: ");
    scanf("%s", name);
    struct Food * foundFood = FindFood(name, foods, foodCount);
    if(foundFood != NULL){
        printf("enter the new price for %s: ", name);
        scanf("%f", &foundFood->price);
        printf("The price of %s has been updated to %.2f\n", name, foundFood->price);
    }else{
        printf("there is no such food as %s\n", name);
    }
}

void DelFood(struct Food * foods, int *foodCount){
    char name[MAX];
    printf("You want to delete: ");
    scanf("%s", name);
    struct Food * foundFood = FindFood(name, foods, *foodCount);
    if(foundFood != NULL){
        --*foodCount;
        for(int i = foundFood - foods; i < *foodCount; i++)
            foods[i] = foods[i+1];
        printf("%s has been deleted.", name);
    }else
        printf("There is no such food as %s", name);
}

void ReadOrders(struct Order * orders, int orderCount){
    FILE * fp = fopen(Orderpath, "r");
    for(int i = 0; i < orderCount; i++)
        fscanf(fp, "%s %s %s", &orders[i].foodName, &orders[i].customer, &orders[i].date);
    fclose(fp);
}

void PrintOrders(struct Order *orders, int orderCount){
    for(int i = 0; i < orderCount; i++)
        printf("%s | %s - %s\n", orders[i].date, orders[i].foodName, orders[i].customer);
}

void UpdateOrderFile(struct Order *orders, int orderCount){
    FILE *fp = fopen(Orderpath, "w");
    for(int i = 0; i < orderCount; i++)
        fprintf(fp, "%s %s %s\n", orders[i].foodName, orders[i].customer, orders[i].date);
    fclose(fp);
}

void AddOrder(struct Order *orders, int orderCount, struct Food *foods, int foodCount){
    int i = orderCount - 1;
    printf("Write food and name: ");
    char foodName[MAX];
    scanf("%s", foodName);
    strLower(foodName);
    if(FindFood(foodName, foods, foodCount) != NULL){
        strcpy(orders[i].foodName, foodName);
        scanf("%s", orders[i].customer);
        strLower(orders[i].customer);
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        snprintf(orders[i].date, sizeof(orders->date), "20%02d/%02d/%02d_%02d:%02d", tm.tm_year%100, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min);
        printf("Order of %s by %s was added at %s\n", orders[i].foodName, orders[i].customer, orders[i].date);
    }else{
        printf("there is no such food as %s\n", foodName);
        scanf("%s");
    }
}

void ReadData(int *foodCount, int *orderCount, float *income){
    FILE *fp = fopen(Datapath, "r");
    fscanf(fp, "%d %d %f", foodCount, orderCount, income);
    fclose(fp);
}

struct Order *FindOrder(struct Order *orders, int orderCount, char *customer){
    strLower(customer);
    for(int i = 0; i < orderCount; i++)
        if(strcmp(orders[i].customer, customer) == 0)
            return &orders[i];
    return NULL;
}

void SearchOrder(struct Order *orders, int orderCount){
    char customer[MAX];
    printf("You're looking for: ");
    scanf("%s", customer);
    struct Order *foundCustomer = FindOrder(orders, orderCount, customer);
    if(foundCustomer != NULL){
        printf("%s ordered %s at %s.\n", foundCustomer->customer, foundCustomer->foodName, foundCustomer->date);
    }else{
        printf("There is no customer named %s.", customer);
    }
}

void EditOrder(struct Order *orders, int orderCount){
    char customer[MAX];
    printf("You want to edit order of the customer named: ");
    scanf("%s", customer);
    struct Order *foundCustomer = FindOrder(orders, orderCount, customer);
    if(foundCustomer != NULL){
        printf("New food: ");
        scanf("%s", &foundCustomer->foodName);
        printf("Successfully edited.\n");
        printf("%s ordered %s at %s.\n", foundCustomer->customer, foundCustomer->foodName, foundCustomer->date);
    }else{
        printf("There is no customer named %s.", customer);
    }
}

void DelOrder(struct Order * orders, int* orderCount){
    char customer[MAX];
    printf("Delete oreder of customer named: ");
    scanf("%s", customer);
    struct Order *foundOrder = FindOrder(orders, *orderCount, customer);
    if(foundOrder != NULL){
        --*orderCount;
        for(int i = (foundOrder - orders); i < *orderCount; i++)
            orders[i] = orders[i+1];
        printf("deleted %s's order.\n", customer);
    }else{
        printf("There is no customer named %s.\n", customer);
    }
}

void CalculateFinance(float *income, struct Food *foods, int foodCount, struct Order * orders, int orderCount){
    printf("Resturant financial report:\n"); 
    float sum = 0;
    int outOfDateOrders = 0;
    for(int i = 0; i < orderCount; i++){
        struct Food *foundFood = FindFood(orders[i].foodName, foods, foodCount);
        if(foundFood != NULL)
            sum += foundFood->price;
        else
            outOfDateOrders++;
    }
    float incomeDiff = sum - *income;
    *income = sum;
    printf("There were %d orders\n", orderCount - outOfDateOrders);
    if(outOfDateOrders)
        printf("And there were %d out of date orders.\n", outOfDateOrders);
    printf("income: %.2f\n", sum);
    printf("average price per order: %.2f\n", sum / orderCount);
    if(incomeDiff == 0)
        printf("nothing changed since last time.\n");
    else if(incomeDiff > 0)
        printf("You've generated %.2f$ since last time.\n", incomeDiff);
    else
        printf("you've lost %.2f$ since last time.\n", -incomeDiff);
}

void PrintHelp(){
    FILE *fp = fopen(Helppath, "r");
    char c;
    do{
        c = fgetc(fp);
        printf("%c", c);
    }while(c != EOF);
    fclose(fp);
    printf("\n");
}

int CountItems(char path[MAX]){
    FILE *fp = fopen(path, "r");
    int cnt = 0;
    char c, bc;
    c = fgetc(fp);
    while(c != EOF){
        bc = c;
        c = fgetc(fp);
        if((c == '\n' || c == EOF) && bc != '\n')
            cnt++;
    }
    fclose(fp);
    return cnt;
}

void Reboot(int *foodCount, int *orderCount){
    printf("There were %d foods and %d orders,\n", *foodCount, *orderCount);
    *foodCount = CountItems(Foodpath);
    *orderCount = CountItems(Orderpath);
    printf("now there is %d foods and %d orders.\n", *foodCount, *orderCount);
}

int main(){
    // getting data
    int foodCount, orderCount;
    float income;
    ReadData(&foodCount, &orderCount, &income);

    // initialising
    struct Food* foods = (struct Food*)malloc(foodCount * sizeof(struct Food));
    struct Order* orders = (struct Order*)malloc(orderCount * sizeof(struct Order));
    ReadFoods(foods, foodCount);
    ReadOrders(orders, orderCount);

    PrintHelp();

    int input;
    while(input != 5){
        scanf("%d", &input);
        switch(input){
            case 11: // Print all foods
                PrintFoods(foods, foodCount);
                break;

            case 12: // Sort foods
                SortFoods(foods, foodCount);
                UpdateFoodFile(foods, foodCount);
                break;
            
            case 13: // Add food
                foods = realloc(foods, ++foodCount * sizeof(struct Food));
                AddFood(foods, foodCount);
                UpdateFoodFile(foods, foodCount);
                UpdateDataFile(foodCount, orderCount, income);
                break;
            
            case 14: // Edit food
                EditFood(foods, foodCount);
                UpdateFoodFile(foods, foodCount);
                break;
            
            case 15: // Del food
                DelFood(foods, &foodCount);
                UpdateFoodFile(foods, foodCount);
                UpdateDataFile(foodCount, orderCount, income);
                break;
            
            case 16: // Search food
                SearchFood(foods, foodCount);
                break;
            
            case 21: // Print all the orders
                PrintOrders(orders, orderCount);
                break;
            
            
            case 22: // Find order
                SearchOrder(orders, orderCount);
                break;

            case 23: // Add order
                orders = realloc(orders, (++orderCount) * sizeof(struct Order));
                AddOrder(orders, orderCount, foods, foodCount);
                UpdateOrderFile(orders, orderCount);
                UpdateDataFile(foodCount, orderCount, income);
                break;

            case 24: // Edit order
                EditOrder(orders, orderCount);
                UpdateOrderFile(orders, orderCount);
                break;

            case 25: // Delete order
                DelOrder(orders, &orderCount);
                UpdateOrderFile(orders, orderCount);
                UpdateDataFile(foodCount, orderCount, income);
                break;

            case 3: // Finance
                CalculateFinance(&income, foods, foodCount, orders, orderCount);
                UpdateDataFile(foodCount, orderCount, income);
                break;

            case 4: // Reboot
                Reboot(&foodCount, &orderCount);
                foods = realloc(foods, foodCount * sizeof(struct Food));
                orders = realloc(orders, orderCount * sizeof(struct Order));
                UpdateDataFile(foodCount, orderCount, income);
                ReadFoods(foods, foodCount);
                ReadOrders(orders, orderCount);
                break;

            case 5: // Exit
                break;
            

            case 0: // Help
                PrintHelp();
                break;

            default: // Invalid Input
                printf("Invalid input, type 0 for help\n");
                break;
        }
        
        printf("\n######################################\n");
    }
}