📒 Number Guessing Game with Scoreboard in C

This project is a terminal-based **Number Guessing Game** developed using the C programming language. It offers an interactive command-line experience with selectable difficulty levels, random number generation, attempt tracking, and a persistent scoreboard system. The project uses structured programming principles, modular code, and file handling for saving and displaying game history.

---

📌 Project Overview

Manual score tracking for simple games can be inefficient or inconsistent. This project introduces a digital solution where players can guess numbers at various difficulty levels, and their performance is tracked in a persistent scoreboard. The system supports multiple users, sorts the scoreboard based on game level and performance, and displays a formatted leaderboard.

---

⚙️ Components / Tools Used

- C Programming Language  
- GCC Compiler  
- Command-Line Interface (CLI)  
- Text File Storage (`scoreboard.txt`)  
- `qsort()` for scoreboard sorting  
- Structured Programming with `struct`

---

📁 File Modules

- `main.c` – Game logic, menu system, and scoreboard interface  
- `scoreboard.txt` – File-based persistent storage of player name, level, and attempts  
- `README.md` – Project documentation  

---

🧠 Working Principle

The system follows a structured menu-driven flow with these steps:

🔹 **Player Registration**  
Prompts the user to enter their name at the beginning of the game session.

🔹 **Level Selection**  
Three levels of difficulty:
- **Easy**   → Number between 1–50 (Unlimited attempts)  
- **Medium** → Number between 1–100 (Max 10 attempts)  
- **Hard**   → Number between 1–500 (Max 7 attempts)

🔹 **Gameplay Loop**  
The user guesses numbers based on the selected range and is given hints ("Too high", "Too low"). Attempts are counted.

🔹 **Win/Loss Evaluation**  
If the number is guessed correctly within the allowed attempts, the user wins; otherwise, it's a loss (`attempts = -1`).

🔹 **Scoreboard Update**  
After each game, the player's result is saved to `scoreboard.txt`.

🔹 **Scoreboard View**  
At the end of the session, users are given the option to view the **sorted scoreboard**.

---

🔐 Scoreboard Sorting Logic

Implemented using a custom comparator with `qsort()`:

1. **Level**: Higher difficulty first (Hard > Medium > Easy)  
2. **Attempts**: Winners come before losers. Among winners, fewer attempts is better.  
3. **Name**: Alphabetical order A → Z  

---

📄 Input Validation Rules

- Level must be 1, 2, or 3  
- Guess input must be numeric  
- Names are capped at 49 characters  

---

💡 Features

✅ Random number guessing with hints  
✅ 3 difficulty levels  
✅ Attempt tracking and performance measurement  
✅ Sorted scoreboard by level, attempts, and name  
✅ Persistent storage using text files  
✅ User interaction with input validation  
✅ Modular and maintainable design

---

📂 File Structure

├── main.c // Core game logic and scoreboard handling

├── scoreboard.txt // Persistent file storage of scores

├── README.md // Project documentation

---

📸 Project Media

📽️ Demo Video:  
https://drive.google.com/file/d/1fJ9p6p6YNT6nYZlor1caCUZl8vTKKqRd/view?usp=sharing

🖼️ Sample Terminal Output:
<img width="1920" height="1080" alt="1" src="https://github.com/user-attachments/assets/f0b734b9-62e0-4f3d-9d84-b49e71ecc031" />
<img width="1920" height="1080" alt="2" src="https://github.com/user-attachments/assets/6e055c97-b931-48f6-ba13-117d0122951b" />


To START Game
Enter your name: Anju

Select Difficulty Level:

Easy (1-50, Unlimited attempts)

Medium (1-100, Max 10 attempts)

Hard (1-500, Max 7 attempts)
Enter choice (1-3): 3

Guess a number (1 to 500): 250
Too low! Try again.
...
🎉 Correct! You guessed it in 6 attempts!

Would you like to see the scoreboard? (y/n): y

============= SCOREBOARD =============
No. | Name | Level | Attempts
----+--------------+---------+---------
1 | Anju   | Hard   | 6
2 | Ramesh | Medium | Lost
3 | Sita   | Easy   | 12

---

📈 Future Improvements

- GUI version using `ncurses`, GTK, or Qt  
- User login system and profile history  
- Difficulty scaling based on past performance  
- Enhanced scoreboard filters (date, range, etc.)  
- Multiplayer support  
- Export scoreboard as CSV or PDF  

---

👨‍💻 Developed By  
Vamsi T
Graduate Engineer – Embedded Systems Enthusiast  
📧 vamsithummaluri@gmail.com
