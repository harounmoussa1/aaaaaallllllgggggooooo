#ifndef HOTEL_H
#define HOTEL_H

#define MAX_STRING 100

typedef struct {
    char client_id[MAX_STRING];
    char name[MAX_STRING];
    char surname[MAX_STRING];
    char address[MAX_STRING];
    char email[MAX_STRING];
    char phone[MAX_STRING];
    struct Client* next;
} Client;

typedef struct {
    char reservation_id[MAX_STRING];
    char client_id[MAX_STRING];
    char room_number[MAX_STRING];
    char date_debut[MAX_STRING];
    char date_fin[MAX_STRING];
    int nb_personnes;
    float prix_total;
    struct Reservation* next;
} Reservation;

typedef struct {
    char room_number[MAX_STRING];
    int capacity;
    float price_per_night;
    int is_available;
    struct Room* next;
} Room;

// Function declarations
void init_system();
void add_client();
void add_reservation();
void show_all_clients();
void show_all_reservations();
void show_available_rooms();
void delete_reservation();
void modify_reservation();
void save_data();
Client* find_client(const char* client_id);
Room* find_room(const char* room_number);
void load_data();

#endif
