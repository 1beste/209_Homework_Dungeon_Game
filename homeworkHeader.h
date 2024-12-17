#ifndef HOMEWORKHEADER_H
#define HOMEWORKHEADER_H

// Typedef Definitions
typedef struct
{
    int health;
    int strength;
    char **inventory;
    int inventory_size;
    int inventory_capacity;
} Player;

typedef struct Room
{
    char *description;
    char **items;
    int item_count;
    struct Room *up, *down, *left, *right;
    struct Creature *creature;
    int locked; //0 = unlocked, 1 = locked
} Room;

typedef struct Creature
{
    char *name;
    int health;
    int strength;
    char *description;
    char *item_drop;
} Creature;

// Function Prototypes
void parse_command(char *input, char **command, char **args);
void show_commands();
void initialize_player(Player *player);
Room *initialize_rooms();
void show_map();
void move_player(char *direction, Room **current_room, Player *player);
void display_room(Room *room);
void show_player_stats(Player *player);
void list_inventory(Player *player);
void pickup_item(Player *player, Room *room, char *item);
void creature_attack(Room *room, Player *player);
void attack_toCreature(Player *player, Room *room);
void save_game(Player *player, Room *rooms);
void load_game(Player *player, Room **rooms);

#endif