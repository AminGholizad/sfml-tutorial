# SFML 3.0.0 Example Project

This project contains updated example code from the [SFML 2.4 For Beginners](https://youtube.com/playlist?list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9&si=tLlUJR9DtnWFma-7) YouTube tutorial series by [Hilze Vonck](https://www.youtube.com/@HilzeVonck), adapted to use **SFML 3.0.0** ([download link](https://www.sfml-dev.org/files/SFML-3.0.0-windows-vc17-32-bit.zip)).

**_Note_** No need to download the library as it is included in this repository.

---

## 🎯 Goals

- Update code from SFML 2.4 to SFML 3.0.0
- Apply modern C++ best practices
- Fix known bugs in the original tutorial code
- Create a fully functional game
- Add a simple scoring system

---

## 🐞 Fix: `checkCollision` Bug

In the original tutorial [Episode 12: Collision Detection (AABB)](https://youtu.be/l2iCYCLi6MU?si=DbPkywhNQeRN67mn), many users encountered a bug in the `checkCollision` function. The fix involves changing the function signature:

**Original (Buggy):**
```cpp
sf::Vector2f checkCollision(Collider& other, float push);
```

**Fixed:**
```cpp
sf::Vector2f checkCollision(Collider other, float push);
```

**Why it works:**

The Collider class already stores a reference to the body (player/platform), so passing it by reference again is unnecessary.

Also, having reference member variables is discouraged per C++ Core Guidelines. In this project, the code and API have been redesigned to eliminate reference members entirely. Doing so elimiates the need for Collider class entirely.
Therefore only functions are used

---

# 🔧 Key Improvements Over Original Code

   - Refactored functions to follow the **Single Responsibility** Principle
   
   - Added `[[nodiscard]]` to non-void return types
   
   - Applied const correctness where applicable
   
   - Used `noexcept` for non-throwing functions

   - Used `constexpr` on capable functions
   
   - Improved code readability and maintainability
 
---
# 🧰 Requirements

   - Compiler: Visual C++ 17 (Visual Studio 2022)

   - Library: [SFML 3.0.0](https://www.sfml-dev.org/)