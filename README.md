# 🧩 8-Puzzle Solver (A* Algorithm with SFML)

This project is a **C++ implementation of the classic 8-Puzzle problem**, solved using the **A\* search algorithm** and visualized using **SFML**.

The application automatically finds the optimal solution and displays each step graphically in a window.

---
## Screenshots

<img width="1366" height="768" alt="Screenshot from 2026-01-26 12-55-22" src="https://github.com/user-attachments/assets/e3ae80d7-7887-4ae3-8198-1703d6858e99" />
<img width="1366" height="768" alt="Screenshot from 2026-01-26 12-55-13" src="https://github.com/user-attachments/assets/2bc96fab-7a10-440d-9f72-a0348aff6e8c" />

---
## 📌 Features

- A* Search Algorithm
- Manhattan Distance Heuristic
- Step-by-step animated solution
- SFML-based graphical interface
- 3×3 sliding puzzle logic
- Object-oriented design

---

## 🧠 Algorithm Overview

The puzzle is solved using the **A\*** algorithm:

Where:
- `g(n)` is the cost from the start node
- `h(n)` is the Manhattan distance heuristic
- `f(n)` is the total estimated cost

Each puzzle state is stored as a `Node` containing:
- Board configuration
- Parent node
- Move taken
- Cost values (`g`, `h`, `f`)

---


---

## 🖥️ Visualization

- Black tiles represent numbered tiles
- Red tile represents the empty space
- The solution is displayed step by step with a delay
- Grid lines are drawn for clarity

---

## 🛠 Requirements

- C++17 or later
- SFML 2.x
- Linux (default font path is Linux-based)

### Install SFML (Ubuntu / Debian)
```bash
sudo apt install libsfml-dev
g++ main.cpp -o puzzle -lsfml-graphics -lsfml-window -lsfml-system
run
./puzzle


