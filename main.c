#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"

int main() {
    int choice;
    init_system();

    while (1) {
        printf("\n=== Hotel Ayechi Reservation System ===\n");
        printf("1. Add Client\n");
        printf("2. Add Reservation\n");
        printf("3. Show All Clients\n");
        printf("4. Show All Reservations\n");
        printf("5. Show Available Rooms\n");
        printf("6. Delete Reservation\n");
        printf("7. Modify Reservation\n");
        printf("8. Save and Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); // Clear buffer

        switch (choice) {
            case 1:
                add_client();
                break;
            case 2:
                add_reservation();
                break;
            case 3:
                show_all_clients();
                break;
            case 4:
                show_all_reservations();
                break;
            case 5:
                show_available_rooms();
                break;
            case 6:
                delete_reservation();
                break;
            case 7:
                modify_reservation();
                break;
            case 8:
                save_data();
                printf("Thank you for using our system!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
