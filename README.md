# 🔐 MD5 Brute-Force Cracker using OpenMP (C | Windows + MSYS2)

![C](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)
![OpenMP](https://img.shields.io/badge/OpenMP-Enabled-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-brightgreen?style=for-the-badge)

This project showcases a simple multithreaded **brute-force MD5 cracker** using the **OpenMP library in C**. It demonstrates how hashing works and how parallel computing can speed up brute-force techniques. The project includes a **custom implementation of the MD5 algorithm** without using any external libraries.

---

## 🛠 Setup (MSYS2 on Windows)

### ✅ Requirements:
- MSYS2 installed → [https://www.msys2.org/]([https://www.msys2.org/](https://www.msys2.org/
)![image](https://github.com/user-attachments/assets/029f6f8f-257e-4965-b954-9d8491e00a45)
)
- `gcc` with OpenMP support  
- Basic C knowledge + interest in cryptography or OS-level parallelism

---

## ⚙️ Compilation & Execution

Open **MSYS2 shell** and run:

```bash
gcc -fopenmp main.c md5.c -o md5cracker
./md5cracker


