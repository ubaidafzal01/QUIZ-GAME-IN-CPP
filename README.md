# 🎮 C++ Terminal Trivia - Console Based Quiz Game

![C++](https://img.shields.io/badge/Language-C++-blue.svg) ![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20Mac-lightgrey.svg) ![Status](https://img.shields.io/badge/Status-Complete-green.svg)

> A robust, feature-rich console-based trivia application offering single and multiplayer modes, admin management, and detailed performance tracking.

## 📖 Overview

This project is a comprehensive C++ console application designed to simulate a real-world quiz environment. It moves beyond simple input/output by incorporating file handling for question management, sophisticated scoring logic, input validation, and a competitive 2-player mode.

Whether you want to test your knowledge, challenge a friend, or manage a quiz database as an Admin, this application handles it all with a polished user interface.

## ✨ Key Features

### ⚙️ Core System
* **Beautiful Main Menu:** A visually engaging text-based interface.
* **Robust Input Validation:** Prevents crashes by handling invalid user inputs gracefully.
* **File Handling:** All data (questions, logs, high scores) is persistent.

### 🕹️ Game Modes
* **Single Player:** Challenge yourself against the clock.
* **2-Player Mode:** Compete head-to-head with a friend on the same console.
* **Admin Mode:** A secured area where administrators can add new questions directly to the source file.

### 📊 Tracking & Stats
* **Leaderboard:** Displays the Top 5 players based on high scores.
* **Streak Calculator:** Tracks consecutive correct answers.
* **Game Review:** distinct summary at the end of the game showing performance.
* **Activity Log:** Saves game data automatically for future reference.

---

## 📝 Game Rules & Scoring System

The game consists of **10 Questions** per session. Players must select the correct option (A-D) within a **10-second timer**.

### Difficulty Levels
The user can select from three difficulty levels. The scoring logic changes based on the risk level:

| Difficulty Level | Correct Answer | Wrong Answer Penalty |
| :--- | :---: | :---: |
| **Level 1 (Easy)** | +1 Point | -2 Points |
| **Level 2 (Medium)** | +1 Point | -3 Points |
| **Level 3 (Hard)** | +1 Point | -5 Points |

---

## 🆘 Lifelines

To assist players during difficult questions, three unique lifelines are available (usable once per game):

1.  **50/50:** Removes two incorrect options, leaving one correct and one wrong answer.
2.  **Skip:** Allows the player to skip the current question without any point penalty.
3.  **Swap:** Replaces the current question with a new, random question from the database.

---

## 🛠️ Technical Implementation

### Data Structure
* **Questions:** Stored in text files, parsed at runtime.
* **User Data:** Arrays used to manage player names, scores, and streaks.

### Algorithms
* **Sorting:** Used to arrange the Leaderboard (Top 5).
* **Randomization:** Ensures questions are shuffled and not repeated immediately.
* **Timer:** implemented using `<ctime>` or standard threading libraries to enforce the 10-second limit.

---

## 🤝 Contributing
Ahmad Faraz (25F-0510)
Ubaid Afzal (25F-0570)
Taha (25F-0755)

---
*Created by Ubaid Afzal*
