#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dungeon_game.h"

#define MAX_ITEMS 5
#define MAX_DESC 256
#define MAX_INPUT_SIZE 100

// Main Function
int main()
{
    Player player;
    initialize_player(&player);

    Room *rooms = initialize_rooms();
    Room *current_room = rooms;

    char input[256];
    char *command, *args;

    printf("         WELCOME TO THE DUNGEON GAME!\n");
    printf("------------------------------------------------\n");
    printf("You can type 'commands' to see how to play!");

    while (1)
    {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        parse_command(input, &command, &args);

        if (strcmp(command, "move") == 0)
        {
            move_player(args, &current_room, &player);
        }
        else if (strcmp(command, "look") == 0)
        {
            display_room(current_room);
        }
        else if (strcmp(command, "inventory") == 0)
        {
            list_inventory(&player);
        }
        else if (strcmp(command, "map") == 0)
        {
            show_map();
        }
        else if (strcmp(command, "stats") == 0)
        {
            show_player_stats(&player);
        }
        else if (strcmp(command, "pickup") == 0)
        {
            pickup_item(&player, current_room, args);
        }
        else if (strcmp(command, "attack") == 0)
        {
            attack_toCreature(&player, current_room);
        }
        else if (strcmp(command, "save") == 0)
        {
            save_game(&player, current_room);
        }
        else if (strcmp(command, "load") == 0)
        {
            load_game(&player, &rooms);
        }
        else if (strcmp(command, "commands") == 0)
        {
            show_commands();
        }
        else if (strcmp(command, "exit") == 0)
        {
            printf("            Thank you for playing!\n");
            printf("------------------------------------------------\n");
            break;
        }
        else
        {
            printf("Unknown command.\n");
        }
    }

    return 0;
}

// Function Implementations
void parse_command(char *input, char **command, char **args)
{
    *command = strtok(input, " \n");
    *args = strtok(NULL, "\n");
}

void show_commands()
{
    printf("Commands:\n");
    printf("  move <direction>   - Move to a different room (directions: up, down, left, right).\n");
    printf("  look               - Display the description of the current room, items, and creatures.\n");
    printf("  inventory          - List items in your inventory.\n");
    printf("  map                - See the map.\n");
    printf("  pickup <item>      - Pick up an item in the current room.\n");
    printf("  attack             - Attack a creature in the current room.\n");
    printf("  save               - Save the game to a file.\n");
    printf("  load               - Load the game from a file.\n");
    printf("  stats              - Show your current stats (health, strength).\n");
    printf("  exit               - Exit the game.\n");
}

void initialize_player(Player *player)
{
    player->health = 60;
    player->strength = 10;
    player->inventory = malloc(MAX_ITEMS * sizeof(char *));
    player->inventory_size = 0;
    player->inventory_capacity = MAX_ITEMS;
}

Room *initialize_rooms()
{

    Creature *goblin = malloc(sizeof(Creature));
    goblin->name = "Goblin";
    goblin->description = strdup("A small, green goblin with sharp teeth.");
    goblin->health = 25;
    goblin->strength = 5;
    goblin->item_drop[0] = strdup("Health Potion");

    Creature *ice_beast = malloc(sizeof(Creature));
    ice_beast->name = "Ice Beast";
    ice_beast->description = strdup("An icy beast that snarls with chilling breath.");
    ice_beast->health = 50;
    ice_beast->strength = 10;
    ice_beast->item_drop[0] = strdup("Frozen Sword");

    Creature *skeleton = malloc(sizeof(Creature));
    skeleton->name = "Skeleton";
    skeleton->description = strdup("Bones!");
    skeleton->health = 60;
    skeleton->strength = 15;
    skeleton->item_drop[0] = strdup("Skull-Shaped Key");
    skeleton->item_drop[1] = strdup("Health Potion");

    Creature *dragon = malloc(sizeof(Creature));
    dragon->name = "Blue-Eyes White Dragon";
    dragon->description = strdup("A fearsome dragon glares at you with blazing eyes.");
    dragon->health = 100;
    dragon->strength = 25;
    dragon->item_drop[0] = strdup("Dragon Egg");

    // Start Aisle
    Room *start = malloc(sizeof(Room));
    start->description = strdup("You are in a dark, damp dungeon aisle. You can see some light a bit further.");
    start->items = malloc(MAX_ITEMS * sizeof(char *));
    start->item_count = 0;
    start->creature = NULL;
    start->up = NULL;
    start->down = NULL;
    start->left = NULL;
    start->locked = 0;

    // Main Hall
    Room *mainHall = malloc(sizeof(Room));
    mainHall->description = strdup("You have entered a large room. You see 3 doors going north, east and south.");
    mainHall->items = malloc(MAX_ITEMS * sizeof(char *));
    mainHall->items[0] = strdup("Sword");
    mainHall->item_count = 1;
    mainHall->creature = NULL;
    mainHall->left = start;
    mainHall->locked = 0;

    // Northern Room
    Room *north = malloc(sizeof(Room));
    north->description = strdup("You have entered in a dimly lit room. There is a monster!");
    north->items = malloc(MAX_ITEMS * sizeof(char *));
    north->item_count = 0;
    north->creature = goblin;
    north->down = mainHall;
    north->up = NULL;
    north->right = NULL;
    north->left = NULL;
    north->locked = 0;

    // Southern Room
    Room *south = malloc(sizeof(Room));
    south->description = strdup("You are in a freezing chamber. The walls are covered in frost.");
    south->items = malloc(MAX_ITEMS * sizeof(char *));
    south->item_count = 0;
    south->creature = ice_beast;
    south->left = NULL;
    south->down = NULL;
    south->up = mainHall;
    south->locked = 0;

    // South-East Room
    Room *southeast = malloc(sizeof(Room));
    southeast->description = strdup("You are in a room filled with the stench of decay. Bones litter the floor.");
    southeast->items = malloc(MAX_ITEMS * sizeof(char *));
    southeast->item_count = 0;
    southeast->creature = skeleton;
    southeast->down = NULL;
    southeast->up = NULL;
    southeast->right = NULL;
    southeast->left = south;
    southeast->locked = 0;

    // Final Boss Room
    Room *final = malloc(sizeof(Room));
    final->description = strdup("You are in the grand throne room of a palace-like place.");
    final->items = malloc(MAX_ITEMS * sizeof(char *));
    final->item_count = 0;
    final->creature = dragon;
    final->locked = 1;
    final->left = mainHall;
    final->right = NULL;
    final->up = NULL;
    final->down = NULL;

    start->right = mainHall;
    mainHall->up = north;
    mainHall->down = south;
    mainHall->right = final;
    south->right = southeast;

    return start;
}

void show_map()
{
    printf("                        --------------------------\n");
    printf("                        |                        |\n");
    printf("                        |      Northern Room     |\n");
    printf("                        |                        |\n");
    printf("                        -----------|  |-----------\n");
    printf("                        |                        |-------------------------|\n");
    printf("|-----------------------|                        |                         |\n");
    printf("--                      --                       --        Dragon's        |\n");
    printf("&&        Aisle                  Main Hall       &&          Hell          |\n");
    printf("--                      --                       --                        |\n");
    printf("|-----------------------|                        |-------------------------|\n");
    printf("                        |                        |\n");
    printf("                        -----------|  |----------|-----------------|\n");
    printf("                        |                        --                |\n");
    printf("                        |       Ice Chamber          Bone Prison   |\n");
    printf("                        |                        --                |\n");
    printf("                        -------------------------|-----------------|\n");
}

void creature_attack(Room *room, Player *player)
{
    printf("The %s attacks fiercely!\n", room->creature->name);
    player->health -= room->creature->strength;
    printf("Player health reduced to %d.\n", player->health);

    if (player->health <= 0)
    {
        printf("You were defeated by the creature. Game over.\n");
        exit(0);
    }
}

void move_player(char *direction, Room **current_room, Player *player)
{
    Room *next_room = NULL;

    if (strcmp(direction, "up") == 0)
    {
        next_room = (*current_room)->up;
    }
    else if (strcmp(direction, "down") == 0)
    {
        next_room = (*current_room)->down;
    }
    else if (strcmp(direction, "left") == 0)
    {
        next_room = (*current_room)->left;
    }
    else if (strcmp(direction, "right") == 0)
    {
        next_room = (*current_room)->right;
    }

    if (next_room)
    {
        if (next_room->locked)
        {
            int has_key = 0;
            for (int i = 0; i < player->inventory_size; i++)
            {
                if (strcmp(player->inventory[i], "Skull-Shaped Key") == 0)
                {
                    has_key = 1;
                    break;
                }
            }
            if (has_key)
            {
                next_room->locked = 0;
                printf("You unlock the room with the Skull-Shaped Key.\n");
            }
            else
            {
                printf("This room is locked. There is a skull shape on the door.\n");
                return;
            }
        }
        *current_room = next_room;
        printf("You moved to a new room.\n");
    }
    else
    {
        printf("You can't go that way.\n");
    }
}

void display_room(Room *room)
{
    printf("%s\n", room->description);
    if (room->item_count > 0)
    {
        printf("Items in the room:\n");
        for (int i = 0; i < room->item_count; i++)
        {
            printf("- %s\n", room->items[i]);
        }
    }
    if (room->creature)
    {
        printf("A %s is here: %s\n", room->creature->name, room->creature->description);
        printf("%s Health= %d\n%s Strenght= %d\n", room->creature->name, room->creature->health, room->creature->name, room->creature->strength);
    }
}

void show_player_stats(Player *player)
{
    printf("Player Stats:\n");
    printf("Health= %d\n", player->health);
    printf("Strength= %d\n", player->strength);
}

void list_inventory(Player *player)
{
    printf("Your inventory:\n");
    if (player->inventory_size == 0)
    {
        printf("(empty)\n");
    }
    else
    {
        for (int i = 0; i < player->inventory_size; i++)
        {
            printf("- %s\n", player->inventory[i]);
        }
    }
}

void to_lowercase(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void pickup_item(Player *player, Room *room, char *item)
{
    if (!item)
    {
        printf("Specify an item to pick up.\n");
        return;
    }

    char lower_item[MAX_DESC];
    for (int i = 0; i < strlen(item); i++)
    {
        lower_item[i] = tolower(item[i]);
    }
    lower_item[strlen(item)] = '\0';

    for (int i = 0; i < room->item_count; i++)
    {
        // Convert room item to lowercase for comparison
        char room_item_lower[MAX_DESC];
        for (int j = 0; j < strlen(room->items[i]); j++)
        {
            room_item_lower[j] = tolower(room->items[i][j]);
        }
        room_item_lower[strlen(room->items[i])] = '\0';

        if (strcmp(room_item_lower, lower_item) == 0)
        {
            if (player->inventory_size < player->inventory_capacity)
            {
                // Add the item to the player's inventory
                player->inventory[player->inventory_size++] = strdup(room->items[i]);

                // Strength modification for specific items
                if (strcmp(room_item_lower, "sword") == 0)
                {
                    player->strength += 10;
                    printf("You feel stronger after picking up the sword! Strength increased by 10.\n");
                }
                else if (strcmp(room_item_lower, "health potion") == 0)
                {
                    player->health += 30;
                    printf("You feel refreshed after drinking the potion! Health increased by 30.\n");
                    player->inventory[--player->inventory_size] = NULL;
                }
                else if (strcmp(room_item_lower, "frozen sword") == 0)
                {
                    player->strength += 20;
                    printf("You feel ice in your veins after equipping the sword! Strength increased by 20.\n");
                }

                // Remove the item from the room
                free(room->items[i]);
                for (int j = i; j < room->item_count - 1; j++)
                {
                    room->items[j] = room->items[j + 1];
                }
                room->item_count--;

                printf("You picked up the %s.\n", item);
                return;
            }
            else
            {
                printf("Your inventory is full!\n");
                return;
            }
        }
    }

    printf("Item not found in this room.\n");
}

void attack_toCreature(Player *player, Room *room)
{
    if (!room->creature)
    {
        printf("There's nothing to attack here.\n");
        return;
    }
    else
    {
        room->creature->health -= player->strength;

        if (room->creature->health <= 0)
        {
            printf("You defeated the creature!\n");
            if (room->creature->item_drop[0] != NULL)
            {
                room->items[room->item_count++] = strdup(room->creature->item_drop[0]);
                printf("The creature dropped:\n%s\n", room->creature->item_drop[0]);
                if (room->creature->item_drop[1] != NULL)
                {
                    room->items[room->item_count++] = strdup(room->creature->item_drop[1]);
                    printf("%s\n", room->creature->item_drop[1]);
                }
            }

            free(room->creature->description);
            free(room->creature->item_drop[0]);
            free(room->creature->item_drop[1]);
            free(room->creature);
            room->creature = NULL;
            return;
        }
        else
        {
            printf("You attack the %s! %s's health= %d\n", room->creature->name, room->creature->name, room->creature->health);
        }
    }

    creature_attack(room, player);
}

void save_game(Player *player, Room *current_room)
{
    FILE *file = fopen("Dungeon_Game.txt", "a");

    if (file)
    {
        // Save player's current states
        FILE *file = fopen("Dungeon_Game.txt", "w");
        fprintf(file, "Player Health= %d \nPlayer Strength= %d\n", player->health, player->strength);
        if (player->inventory_size == 0)
        {
            fprintf(file, "Player has no items.\n");
        }
        else
        {
            fprintf(file, "Player Inventory:\n");
            for (int i = 0; i < player->inventory_size; i++)
            {
                fprintf(file, "-%s\n", player->inventory[i]);
            }
        }

        fprintf(file, "\n");

        // Save current room's state
        fprintf(file, "%s\n", current_room->description);
        if (current_room->item_count > 0)
        {
            fprintf(file, "The room contains these items:\n");
            for (int i = 0; i < current_room->item_count; i++)
            {
                fprintf(file, "-%s\n", current_room->items[i]);
            }
        }

        fprintf(file, "\n");

        // Save creature's state
        if (current_room->creature)
        {
            fprintf(file, "There is a creature!\n");
            fprintf(file, "Creature: %s\nCreature's Health= %d\nCreature's Strength= %d\n", current_room->creature->description, current_room->creature->health, current_room->creature->strength);
        }
        else
        {
            fprintf(file, "There is no creature in this room.\n");
        }
    }

    fprintf(file, "\n");

    fclose(file);
    printf("Game saved to %s.\n", "Dungeon_Game.txt");
}

void load_game(Player *player, Room **current_room)
{
    FILE *file = fopen("Dungeon_Game.txt", "r");
    if (!file)
    {
        printf("Failed to load the game. File not found.\n");
        return;
    }

    // Load player stats
    if (fscanf(file, "Player Health= %d\n", &player->health) != 1 ||
        fscanf(file, "Player Strength= %d\n", &player->strength) != 1)
    {
        printf("Error loading player stats.\n");
        fclose(file);
        return;
    }

    // Load player inventory
    char buffer[MAX_DESC];
    player->inventory_size = 0;
    fgets(buffer, MAX_DESC, file); // Read "Player Inventory:" or "Player has no items."

    if (strstr(buffer, "Player Inventory:"))
    {
        while (fgets(buffer, MAX_DESC, file) && buffer[0] == '-')
        {
            buffer[strcspn(buffer, "\n")] = '\0'; // Strip newline
            if (player->inventory_size < player->inventory_capacity)
            {
                player->inventory[player->inventory_size++] = strdup(buffer + 1); // Skip "-"
            }
        }
    }

    // Load the last room description
    char room_description[MAX_DESC];
    fgets(buffer, MAX_DESC, file);        // Room description line
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
    strcpy(room_description, buffer);

    // Match the room manually - assume the rooms are predefined and traversable
    Room *temp = *current_room;
    printf("Trying to locate room: '%s'\n", room_description);

    while (temp != NULL)
    {
        if (strcmp(temp->description, room_description) == 0)
        {
            *current_room = temp; // Found the room

            // Load room items
            fgets(buffer, MAX_DESC, file); // Check for room items
            if (strstr(buffer, "The room contains these items:"))
            {
                temp->item_count = 0;
                while (fgets(buffer, MAX_DESC, file) && buffer[0] == '-')
                {
                    buffer[strcspn(buffer, "\n")] = '\0';
                    if (temp->item_count < MAX_ITEMS)
                    {
                        temp->items[temp->item_count++] = strdup(buffer + 1);
                    }
                }
            }

            // Load creature
            fgets(buffer, MAX_DESC, file); // Check for creature
            if (strstr(buffer, "There is a creature!"))
            {
                temp->creature = malloc(sizeof(Creature));
                if (temp->creature)
                {
                    fgets(buffer, MAX_DESC, file);
                    temp->creature->description = strdup(buffer);
                    fscanf(file, "Creature's Health= %d\n", &temp->creature->health);
                    fscanf(file, "Creature's Strength= %d\n", &temp->creature->strength);
                }
            }
            else
            {
                temp->creature = NULL;
            }
            break;
        }
        temp = temp->right; // Adjust traversal logic
    }

    if (temp == NULL)
    {
        printf("Room not found. Check room links and descriptions.\n");
    }

    fclose(file);
    printf("Game loaded successfully. You are now in: %s\n", (*current_room)->description);
}