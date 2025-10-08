#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MenuItem {
    int id;
    char name[50];
    float price;
};

struct Order {
    int itemId;
    int quantity;
    float total;
};

void displayMenu(struct MenuItem menu[], int count) {
    printf("\n---------- MENU ----------\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %.2f BDT\n", menu[i].id, menu[i].name, menu[i].price);
    }
    printf("--------------------------\n");
}

void takeOrder(struct MenuItem menu[], int count) {
    struct Order orders[10];
    int orderCount = 0;
    float grandTotal = 0.0;
    char choice;

    do {
        int itemId, quantity;
        printf("\nEnter Item ID to order: ");
        scanf("%d", &itemId);

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (menu[i].id == itemId) {
                printf("Enter quantity: ");
                scanf("%d", &quantity);

                orders[orderCount].itemId = itemId;
                orders[orderCount].quantity = quantity;
                orders[orderCount].total = menu[i].price * quantity;
                grandTotal += orders[orderCount].total;

                printf("Added %d x %s = %.2f BDT\n", quantity, menu[i].name, orders[orderCount].total);

                orderCount++;
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Invalid Item ID!\n");
        }

        printf("Do you want to order more items? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    printf("\n------ BILL ------\n");
    for (int i = 0; i < orderCount; i++) {
        for (int j = 0; j < count; j++) {
            if (menu[j].id == orders[i].itemId) {
                printf("%s x %d = %.2f BDT\n", menu[j].name, orders[i].quantity, orders[i].total);
            }
        }
    }
    printf("------------------\n");
    printf("Total Bill: %.2f BDT\n", grandTotal);

    FILE *file = fopen("bill.txt", "a");
    if (file != NULL) {
        fprintf(file, "Total Bill: %.2f BDT\n", grandTotal);
        fclose(file);
    } else {
        printf("Error saving bill to file!\n");
    }

    printf("\nBill saved to 'bill.txt'\n");
}

int main() {
    struct MenuItem menu[5] = {
        {1, "Burger", 120.0},
        {2, "Pizza", 250.0},
        {3, "Pasta", 180.0},
        {4, "Coffee", 90.0},
        {5, "Ice Cream", 100.0}
    };

    int choice;

    do {
        printf("\n====== RESTAURANT MANAGEMENT SYSTEM ======\n");
        printf("1. View Menu\n");
        printf("2. Place Order\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMenu(menu, 5);
                break;
            case 2:
                displayMenu(menu, 5);
                takeOrder(menu, 5);
                break;
            case 3:
                printf("Thank you! Visit again.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 3);

    return 0;
}
