# 🧩 8-Puzzle Solver (A* Algorithm with SFML)

This project is a **C++ implementation of the classic 8-Puzzle problem**, solved using the **A\* search algorithm** and visualized using **SFML**.

The application automatically finds the optimal solution and displays each step graphically in a window.

---
## GIF
<img width="1092" height="614" alt="output" src="https://github.com/user-attachments/assets/29d497a8-ce56-42b2-b957-2890004980e8" />


## Screenshots

<img width="1366" height="768" alt="Screenshot from 2026-01-26 12-55-22" src="https://github.com/user-attachments/assets/e3ae80d7-7887-4ae3-8198-1703d6858e99" />


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


