# Dungeon Adventure Game

## Table of Contents
1. [Introduction](#introduction)
2. [Gameplay](#gameplay)
3. [Commands](#commands)
4. [Code Structure](#code-structure)
5. [Game Logic](#game-logic)
---

## Introduction

Dungeon Adventure Game is a simple text-based game where the player explores different rooms in a dungeon, fights creatures, picks up items, and progresses through the dungeon. The game features interactive exploration, combat, and an inventory system.

---

## Gameplay

The player starts in a dungeon room and can perform various actions such as moving to connected rooms, attacking creatures, and picking up items. Each room may contain items, monsters, or both. The objective is to explore the dungeon, collect useful items, and defeat the final boss.

---

## Commands

Here are the available commands in the game:

- move <direction>: Move to another room. Directions: `up`, `down`, `left`, or `right`.
- loook: Display the current room's description, items, and any creature present.
- inventory: List all items in the player's inventory.
- map: Show a visual representation of the dungeon layout.
- pickup <item>: Pick up an item in the current room.
- attack: Attack the creature in the current room.
- stats: Show player's health and strength stats.
- save: Save the current game state to a file.
- load: Load a previously saved game state.
- commands: Display the list of commands.
- exit: Exit the game.

---

## Code Structure

The project has the following structure:
.
├── dungeon_game.h     # Header file with structure definitions
├── dungeon_game.c     # Main source code containing game logic
├── Makefile           # Makefile for compilation
└── README.md          # Documentation

## Game Logic

Rooms
The dungeon is composed of interconnected rooms. Rooms can:

-Contain items that improve player stats.
-Have creatures the player can fight.
-Be locked, requiring special items (e.g., keys) to access.

Combat
-Combat begins when the player uses the attack command.
-Player attacks reduce the creature's health based on player strength.
-Creatures retaliate and reduce player health based on their strength.
-When a creature's health drops to 0, it drops an item.

Inventory System
-The player has limited inventory capacity (5 items). Items like swords increase strength, while health potions restore health.

Saving and Loading
-The save_game() function writes the player stats, inventory, and room states to a file (Dungeon_Game.txt).
-The load_game() function restores the game state from the save file.
