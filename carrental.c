#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car {
    int id;
    char model[50];
    char brand[50];
    int year;
    float pricePerDay;
    int isAvailable;
};

struct Customer {
    int id;
    char name[50];
    char phone[15];
    int rentedCarId;
};

struct Rental {
    int customerId;
    int carId;
    int days;
};

struct Car cars[100];
struct Customer customers[100];
struct Rental rentals[100];
int carCount = 0, customerCount = 0, rentalCount = 0;

void addCar() {
    struct Car car;
    car.id = carCount + 1;
    printf("Enter car model: ");
    scanf("%s", car.model);
    printf("Enter car brand: ");
    scanf("%s", car.brand);
    printf("Enter manufacturing year: ");
    scanf("%d", &car.year);
    printf("Enter price per day: ");
    scanf("%f", &car.pricePerDay);
    car.isAvailable = 1;
    cars[carCount++] = car;
    printf("Car added successfully.\n");
}

void listCars() {
    printf("Available Cars:\n");
    for (int i = 0; i < carCount; i++) {
        if (cars[i].isAvailable) {
            printf("ID: %d, Model: %s, Brand: %s, Year: %d, Price per Day: %.2f\n",
                   cars[i].id, cars[i].model, cars[i].brand, cars[i].year, cars[i].pricePerDay);
        }
    }
}

void addCustomer() {
    struct Customer customer;
    customer.id = customerCount + 1;
    printf("Enter customer name: ");
    scanf("%s", customer.name);
    printf("Enter customer phone: ");
    scanf("%s", customer.phone);
    customer.rentedCarId = 0;
    customers[customerCount++] = customer;
    printf("Customer added successfully.\n");
}

void rentCar() {
    int customerId, carId, days;
    printf("Enter customer ID: ");
    scanf("%d", &customerId);
    printf("Enter car ID: ");
    scanf("%d", &carId);
    printf("Enter number of days: ");
    scanf("%d", &days);
    if (customerId > 0 && customerId <= customerCount && carId > 0 && carId <= carCount) {
        if (cars[carId - 1].isAvailable) {
            cars[carId - 1].isAvailable = 0;
            rentals[rentalCount++] = (struct Rental){customerId, carId, days};
            customers[customerId - 1].rentedCarId = carId;
            printf("Car rented successfully.\n");
        } else {
            printf("Car is not available.\n");
        }
    } else {
        printf("Invalid customer or car ID.\n");
    }
}

void returnCar() {
    int customerId;
    printf("Enter customer ID: ");
    scanf("%d", &customerId);
    if (customerId > 0 && customerId <= customerCount) {
        int carId = customers[customerId - 1].rentedCarId;
        if (carId > 0) {
            cars[carId - 1].isAvailable = 1;
            printf("Car returned successfully.\n");
            customers[customerId - 1].rentedCarId = 0;
        } else {
            printf("No car rented by this customer.\n");
        }
    } else {
        printf("Invalid customer ID.\n");
    }
}

void generateBill() {
    int customerId;
    printf("Enter customer ID: ");
    scanf("%d", &customerId);
    if (customerId > 0 && customerId <= customerCount) {
        int carId = customers[customerId - 1].rentedCarId;
        if (carId > 0) {
            int days = 0;
            for (int i = 0; i < rentalCount; i++) {
                if (rentals[i].customerId == customerId && rentals[i].carId == carId) {
                    days = rentals[i].days;
                    break;
                }
            }
            float total = days * cars[carId - 1].pricePerDay;
            printf("Total bill for customer %s: %.2f\n", customers[customerId - 1].name, total);
        } else {
            printf("No car rented by this customer.\n");
        }
    } else {
        printf("Invalid customer ID.\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Add Car\n2. List Cars\n3. Add Customer\n4. Rent Car\n5. Return Car\n6. Generate Bill\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addCar(); break;
            case 2: listCars(); break;
            case 3: addCustomer(); break;
            case 4: rentCar(); break;
            case 5: returnCar(); break;
            case 6: generateBill(); break;
            case 7: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
