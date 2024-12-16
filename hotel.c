#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"
#include <ctype.h>

Client* clients_head = NULL;
Reservation* reservations_head = NULL;
Room* rooms_head = NULL;

void init_system() {
    // Initialize some rooms
    Room* room;
    for (int i = 1; i <= 10; i++) {
        room = (Room*)malloc(sizeof(Room));
        sprintf(room->room_number, "%d", i);
        room->capacity = (i % 3) + 1;  // 1-3 persons
        room->price_per_night = 100.0 * room->capacity;
        room->is_available = 1;
        room->next = rooms_head;
        rooms_head = room;
    }
    load_data();
}


// Fonction pour vérifier si l'email est valide
int is_valid_email(const char* email) {
    return (strchr(email, '@') && strchr(email, '.'));
}

// Fonction pour vérifier si une chaîne est uniquement numérique
int is_numeric(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

// Vérifier si un ID est unique
int is_unique_id(const char* id) {
    Client* current = clients_head;
    while (current) {
        if (strcmp(current->client_id, id) == 0) return 0;
        current = current->next;
    }
    return 1;
}

void add_client() {
    Client* new_client = (Client*)malloc(sizeof(Client));
    if (!new_client) {
        printf("Memory allocation failed.\n");
        return;
    }

    // ID : vérifier si unique
    do {
        printf("Enter client ID: ");
        fgets(new_client->client_id, MAX_STRING, stdin);
        new_client->client_id[strcspn(new_client->client_id, "\n")] = 0;

        if (strlen(new_client->client_id) == 0) {
            printf("Client ID cannot be empty. Try again.\n");
        } else if (!is_unique_id(new_client->client_id)) {
            printf("Client ID already exists. Enter a unique ID.\n");
        }
    } while (strlen(new_client->client_id) == 0 || !is_unique_id(new_client->client_id));

    // Nom : vérifier non vide
    do {
        printf("Enter name: ");
        fgets(new_client->name, MAX_STRING, stdin);
        new_client->name[strcspn(new_client->name, "\n")] = 0;

        if (strlen(new_client->name) == 0) {
            printf("Name cannot be empty. Try again.\n");
        }
    } while (strlen(new_client->name) == 0);

    // Prénom
    do {
        printf("Enter surname: ");
        fgets(new_client->surname, MAX_STRING, stdin);
        new_client->surname[strcspn(new_client->surname, "\n")] = 0;

        if (strlen(new_client->surname) == 0) {
            printf("Surname cannot be empty. Try again.\n");
        }
    } while (strlen(new_client->surname) == 0);

    // Adresse
    do {
        printf("Enter address: ");
        fgets(new_client->address, MAX_STRING, stdin);
        new_client->address[strcspn(new_client->address, "\n")] = 0;

        if (strlen(new_client->address) == 0) {
            printf("Address cannot be empty. Try again.\n");
        }
    } while (strlen(new_client->address) == 0);

    // Email : vérifier format valide
    do {
        printf("Enter email: ");
        fgets(new_client->email, MAX_STRING, stdin);
        new_client->email[strcspn(new_client->email, "\n")] = 0;

        if (!is_valid_email(new_client->email)) {
            printf("Invalid email format. Try again.\n");
        }
    } while (!is_valid_email(new_client->email));

    // Téléphone : vérifier format numérique
    do {
        printf("Enter phone: ");
        fgets(new_client->phone, MAX_STRING, stdin);
        new_client->phone[strcspn(new_client->phone, "\n")] = 0;

        if (!is_numeric(new_client->phone)) {
            printf("Phone number must contain only digits. Try again.\n");
        }
    } while (!is_numeric(new_client->phone));

    // Ajouter le client à la liste
    new_client->next = clients_head;
    clients_head = new_client;

    printf("Client added successfully!\n");
}


// Fonction pour vérifier si la date est au format YYYY-MM-DD
int is_valid_date(const char* date) {
    if (strlen(date) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') return 0;
        } else if (!isdigit(date[i])) return 0;
    }
    return 1;
}

// Fonction pour comparer deux dates (YYYY-MM-DD)
int compare_dates(const char* start, const char* end) {
    return strcmp(start, end) < 0;  // Retourne vrai si start < end
}

void add_reservation() {
    Reservation* new_reservation = (Reservation*)malloc(sizeof(Reservation));
    if (!new_reservation) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Entrée pour l'ID du client
    do {
        printf("Enter client ID: ");
        fgets(new_reservation->client_id, MAX_STRING, stdin);
        new_reservation->client_id[strcspn(new_reservation->client_id, "\n")] = 0;

        if (strlen(new_reservation->client_id) == 0) {
            printf("Client ID cannot be empty. Try again.\n");
        } else if (!find_client(new_reservation->client_id)) {
            printf("Client not found! Try again.\n");
        }
    } while (strlen(new_reservation->client_id) == 0 || !find_client(new_reservation->client_id));

    // Entrée pour l'ID de réservation
    do {
        printf("Enter reservation ID: ");
        fgets(new_reservation->reservation_id, MAX_STRING, stdin);
        new_reservation->reservation_id[strcspn(new_reservation->reservation_id, "\n")] = 0;

        if (strlen(new_reservation->reservation_id) == 0) {
            printf("Reservation ID cannot be empty. Try again.\n");
        }
    } while (strlen(new_reservation->reservation_id) == 0);

    // Entrée pour le numéro de chambre
    Room* room = NULL;
    do {
        printf("Enter room number: ");
        fgets(new_reservation->room_number, MAX_STRING, stdin);
        new_reservation->room_number[strcspn(new_reservation->room_number, "\n")] = 0;

        room = find_room(new_reservation->room_number);
        if (!room) {
            printf("Room not found! Try again.\n");
        } else if (!room->is_available) {
            printf("Room not available! Choose another room.\n");
            room = NULL;
        }
    } while (!room);

    // Entrée pour la date de début
    do {
        printf("Enter start date (YYYY-MM-DD): ");
        fgets(new_reservation->date_debut, MAX_STRING, stdin);
        new_reservation->date_debut[strcspn(new_reservation->date_debut, "\n")] = 0;

        if (!is_valid_date(new_reservation->date_debut)) {
            printf("Invalid date format! Use YYYY-MM-DD.\n");
        }
    } while (!is_valid_date(new_reservation->date_debut));

    // Entrée pour la date de fin
    do {
        printf("Enter end date (YYYY-MM-DD): ");
        fgets(new_reservation->date_fin, MAX_STRING, stdin);
        new_reservation->date_fin[strcspn(new_reservation->date_fin, "\n")] = 0;

        if (!is_valid_date(new_reservation->date_fin)) {
            printf("Invalid date format! Use YYYY-MM-DD.\n");
        } else if (!compare_dates(new_reservation->date_debut, new_reservation->date_fin)) {
            printf("End date must be after start date! Try again.\n");
        }
    } while (!is_valid_date(new_reservation->date_fin) ||
             !compare_dates(new_reservation->date_debut, new_reservation->date_fin));

    // Entrée pour le nombre de personnes
    do {
        printf("Enter number of persons: ");
        if (scanf("%d", &new_reservation->nb_personnes) != 1 || new_reservation->nb_personnes <= 0) {
            printf("Invalid number of persons! Must be a positive number. Try again.\n");
        } else if (new_reservation->nb_personnes > room->capacity) {
            printf("Room capacity exceeded! Max capacity is %d. Try again.\n", room->capacity);
        }
        getchar();  // Nettoyer le tampon d'entrée
    } while (new_reservation->nb_personnes <= 0 || new_reservation->nb_personnes > room->capacity);

    // Mettre à jour les détails de la réservation
    new_reservation->prix_total = room->price_per_night;  // Prix total par nuit
    room->is_available = 0;  // Marquer la chambre comme indisponible

    // Ajouter la réservation à la liste
    new_reservation->next = reservations_head;
    reservations_head = new_reservation;

    printf("Reservation added successfully!\n");
}

void show_all_clients() {
    Client* current = clients_head;
    if (!current) {
        printf("No clients found.\n");
        return;
    }

    printf("\n=== Client List ===\n");
    while (current) {
        printf("ID: %s\n", current->client_id);
        printf("Name: %s %s\n", current->name, current->surname);
        printf("Email: %s\n", current->email);
        printf("Phone: %s\n", current->phone);
        printf("---------------\n");
        current = current->next;
    }
}

void show_all_reservations() {
    Reservation* current = reservations_head;
    if (!current) {
        printf("No reservations found.\n");
        return;
    }

    printf("\n=== Reservation List ===\n");
    while (current) {
        printf("Reservation ID: %s\n", current->reservation_id);
        printf("Client ID: %s\n", current->client_id);
        printf("Room: %s\n", current->room_number);
        printf("Dates: %s to %s\n", current->date_debut, current->date_fin);
        printf("Persons: %d\n", current->nb_personnes);
        printf("Total Price: %.2f\n", current->prix_total);
        printf("---------------\n");
        current = current->next;
    }
}

void show_available_rooms() {
    Room* current = rooms_head;
    printf("\n=== Available Rooms ===\n");
    while (current) {
        if (current->is_available) {
            printf("Room %s (Capacity: %d, price_per_night: %.2f)\n",
                   current->room_number, current->capacity, current->price_per_night);
        }
        current = current->next;
    }
}

void delete_reservation() {
    char reservation_id[MAX_STRING];
    printf("Enter reservation ID to delete: ");
    fgets(reservation_id, MAX_STRING, stdin);
    reservation_id[strcspn(reservation_id, "\n")] = 0;

    Reservation* current = reservations_head;
    Reservation* prev = NULL;

    while (current) {
        if (strcmp(current->reservation_id, reservation_id) == 0) {
            Room* room = find_room(current->room_number);
            if (room) room->is_available = 1;

            if (prev) prev->next = current->next;
            else reservations_head = current->next;

            free(current);
            printf("Reservation deleted successfully!\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Reservation not found!\n");
}

void modify_reservation() {
    char reservation_id[MAX_STRING];
    printf("Enter reservation ID to modify: ");
    fgets(reservation_id, MAX_STRING, stdin);
    reservation_id[strcspn(reservation_id, "\n")] = 0;

    Reservation* current = reservations_head;
    while (current) {
        if (strcmp(current->reservation_id, reservation_id) == 0) {
            printf("Enter new start date (YYYY-MM-DD): ");
            fgets(current->date_debut, MAX_STRING, stdin);
            current->date_debut[strcspn(current->date_debut, "\n")] = 0;

            printf("Enter new end date (YYYY-MM-DD): ");
            fgets(current->date_fin, MAX_STRING, stdin);
            current->date_fin[strcspn(current->date_fin, "\n")] = 0;

            printf("Enter new number of persons: ");
            scanf("%d", &current->nb_personnes);
            getchar();

            Room* room = find_room(current->room_number);
            if (room && current->nb_personnes > room->capacity) {
                printf("Warning: Number of persons exceeds room capacity!\n");
            }

            printf("Reservation modified successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Reservation not found!\n");
}

Client* find_client(const char* client_id) {
    Client* current = clients_head;
    while (current) {
        if (strcmp(current->client_id, client_id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Room* find_room(const char* room_number) {
    Room* current = rooms_head;
    while (current) {
        if (strcmp(current->room_number, room_number) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void save_data() {
    FILE* file = fopen("clients.txt", "w");
    if (file) {
        Client* current_client = clients_head;
        while (current_client) {
            fprintf(file, "%s,%s,%s,%s,%s,%s\n",
                   current_client->client_id,
                   current_client->name,
                   current_client->surname,
                   current_client->address,
                   current_client->email,
                   current_client->phone);
            current_client = current_client->next;
        }
        fclose(file);
    }

    file = fopen("reservations.txt", "w");
    if (file) {
        Reservation* current_res = reservations_head;
        while (current_res) {
            fprintf(file, "%s,%s,%s,%s,%s,%d,%.2f\n",
                   current_res->reservation_id,
                   current_res->client_id,
                   current_res->room_number,
                   current_res->date_debut,
                   current_res->date_fin,
                   current_res->nb_personnes,
                   current_res->prix_total);
            current_res = current_res->next;
        }
        fclose(file);
    }
}

void load_data() {
    FILE* file = fopen("clients.txt", "r");
    if (file) {
        char line[MAX_STRING * 6];
        while (fgets(line, sizeof(line), file)) {
            Client* client = (Client*)malloc(sizeof(Client));
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
                   client->client_id,
                   client->name,
                   client->surname,
                   client->address,
                   client->email,
                   client->phone);
            client->next = clients_head;
            clients_head = client;
        }
        fclose(file);
    }

    file = fopen("reservations.txt", "r");
    if (file) {
        char line[MAX_STRING * 7];
        while (fgets(line, sizeof(line), file)) {
            Reservation* res = (Reservation*)malloc(sizeof(Reservation));
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%d,%f",
                   res->reservation_id,
                   res->client_id,
                   res->room_number,
                   res->date_debut,
                   res->date_fin,
                   &res->nb_personnes,
                   &res->prix_total);
            res->next = reservations_head;
            reservations_head = res;

            Room* room = find_room(res->room_number);
            if (room) room->is_available = 0;
        }
        fclose(file);
    }
}

