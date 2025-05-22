# ⚔️ Trap Dungeon Game

A thrilling 2D dungeon exploration game built using C++ and Raylib. The player navigates through multiple deadly levels, avoiding traps and enemies, collecting lives, and trying to reach the end — all while danger lurks around every corner.

---

## 🗺️ Overview

The gameplay revolves around reflexes, memory, and strategy as players dodge moving traps and enemies. Each level is handcrafted and stored in external files for modular design and easy updates.

The player has a set number of lives and health points. Getting hit by traps or enemies results in damage or death. Players must complete all levels to win the game.

---

## 🧠 OOP Concepts Used

- **Inheritance & Polymorphism:** All game entities (Player, Trap, Enemy, etc.) inherit from a base `Entity` class.
- **Composition & Aggregation:** Levels are composed of multiple entities. GameManager manages levels and player lifecycles.
- **Templates:** Custom `MyVector<T>` and `MyStr` libraries replace standard containers.
- **Exception Handling:** Used for file reading and invalid game state management.
- **State Persistence:** Level states saved and restored via binary files.
- **Logging:** Game events are logged for debugging.
- **GitHub Integration:** All development tracked and versioned.

---

## 🎮 Controls

Yet to be decided

---

## 🗃️ File Structure

- `main.cpp` – Entry point  
- `GameManager.h/.cpp` – Controls game flow  
- `Level.h/.cpp` – Handles level data and reset  
- `Entity.h/.cpp` – Base class for Player, Enemy, Trap  
- `MyVector.h` – Custom dynamic array  
- `Assets/Levels/` – Level data files  
- `README.md` – Game documentation

---

## ✨ Features

- Multiple Levels  
- Deadly Traps and Enemies  
- Dynamic Movement  
- Level Reset  
- File-Based Level Design  
- Custom STL-like Libraries

---

## 🧪 To Sum Up

This project showcases deep use of OOP, file handling, templates, and memory management in C++. An ideal project for nostalgic gamers and coders
