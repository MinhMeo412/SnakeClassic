# 🐍 Snake Classic – Axmol Engine

**Eat food ➜ Grow longer ➜ Don’t hit walls or yourself ➜ Game Over!**  

---

## 🎮 Play Instantly (No Build)

👉 [**Download Snake.exe**](https://github.com/MinhMeo412/SnakeClassic/releases)  
Then simply **double-click and play!**

---

## ⚙️ Build from Source

### 1️⃣ Install Axmol 2.4.0 

👉 [**Download Axmol v2.4.0**](https://github.com/axmolengine/axmol/releases/tag/v2.4.0)  

### 2️⃣ Create an Empty Project

```powershell
# PowerShell
axmol new -p org.axmol.snake -d . -l cpp Snake
```

### 3️⃣ Overwrite with Real Code & Assets

1. On this repo → Click “Code” → “Download ZIP”  
2. Extract the ZIP file  
3. Copy folders Content and Source from the extracted archive  
4. Paste & replace them into your newly created Snake project folder  

### 4️⃣ Build & Run

```powershell
# PowerShell
axmol build -p win32 -c
```
or
```powershell
# PowerShell
axmol build -p win32 -c Release
```
