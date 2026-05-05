# TERMINAL TOWER
### A Console-Based ASCII Action Platformer

> *Developed in C++ | Windows Console Application | Terminal Dimensions: 30 rows × 120 columns*

---

## Table of Contents

1. [Overview](#overview)
2. [Technical Architecture](#technical-architecture)
3. [Game World & Level Design](#game-world--level-design)
4. [Controls](#controls)
5. [Player Character](#player-character)
6. [Movement System](#movement-system)
7. [Camera & Scrolling System](#camera--scrolling-system)
8. [Combat System](#combat-system)
9. [Enemies](#enemies)
10. [Hazards & Obstacles](#hazards--obstacles)
11. [Navigation Mechanics](#navigation-mechanics)
12. [Win & Lose Conditions](#win--lose-conditions)
13. [Screens & States](#screens--states)
14. [Data Structures](#data-structures)
15. [Memory Management](#memory-management)
16. [Authors](#authors)

---

## Overview

**Terminal Tower** is a single-player, ASCII-art action platformer rendered entirely within a Windows console window. The player controls a robot-like hero who must ascend through three distinct floors of a tower, neutralize multiple enemy types, survive environmental hazards, and ultimately defeat a Final Boss — a massive ASCII dragon — to claim the diamond at the top of the tower.

The game is built from scratch in C++ using only standard console I/O and Windows API functions (`conio.h`, `windows.h`), with no third-party game engine or graphics library involved. All visuals are rendered via a two-dimensional character buffer (`unsigned char** world`) that is written to the console each frame.

---

## Technical Architecture

### Rendering Pipeline

The game uses a **virtual world buffer** of dimensions `90 rows × 360 columns`, which is significantly larger than the visible terminal window (`30 rows × 120 columns`). Each frame, the following pipeline executes:

```
1. deleteWorld()       — Wipe the entire 90×360 buffer to spaces
2. drawWorldStatics()  — Draw permanent decorations (door, ladder, spikes, blocks)
3. drawDiamond()       — Draw the collectible win objective
4. drawFloorDividers() — Render the visual separators between floors
5. Draw all dynamic entities (elevator, enemies, bullets, hero)
6. drawWorldBorders()  — Overlay the viewport border
7. dispWorld()         — Output only the visible viewport slice to stdout
```

`dispWorld()` outputs characters from `world[strtRow..endRow][strtCol..endCol]`, which implements the scrolling camera by simply changing which slice of the buffer is printed.

### Game Loop

The game runs a **polling input loop**:

```
while (!_kbhit())   → Run one frame of game logic + render
_getch()            → Read player input
```

This means the game advances one full frame per iteration of the inner `while (!_kbhit())` loop. Input is processed between frames. There is no fixed timestep — game speed is tied to rendering speed.

### Coordinate System

- **Row 0** is the top of the buffer; **Row 89** is the bottom.
- **Column 0** is the leftmost; **Column 359** is the rightmost.
- All entity positions are stored as `(Row, Col)` pairs relative to the global world buffer.

---

## Game World & Level Design

The world is divided into three vertically stacked floors, each occupying 30 rows of the 90-row world buffer:

```
┌─────────────────────────────────────────────────────────┐
│  FLOOR 3   —  Rows  0 – 29   (Top)    Final Boss Floor  │
├─────────────────────────────────────────────────────────┤
│  FLOOR 2   —  Rows 30 – 59   (Mid)    Ghost Floor       │
├─────────────────────────────────────────────────────────┤
│  FLOOR 1   —  Rows 60 – 89   (Bottom) Entry Floor       │
└─────────────────────────────────────────────────────────┘
```

### Floor 1 — Entry Grounds (Rows 60–89)

- Serves as the starting area; hero begins at `(Row 75, Col 60)`.
- Contains **four stacked block obstacles** (platforms at varying heights: rows 85, 82, 79, 76) placed at columns 100, 140, 180, and 220.
- Three **spike trap zones** are embedded in the floor at columns 118–139, 158–179, and 198–219.
- A large **tank-like enemy** (FloorOne) patrols this area and fires projectiles.
- A decorative ASCII **door/sign structure** is drawn at column 3, spanning rows 70–88.

### Floor 2 — Ghost Floor (Rows 30–59)

- Accessed via the **elevator** (on the left) or the **ladder** (on the right).
- Contains three **ghost enemies (Caspers)** with distinct movement patterns.
- Open floor — no static platforms; enemies fill the hazard role entirely.

### Floor 3 — Boss Chamber (Rows 0–29)

- Accessed via the **ladder** from Floor 2.
- Contains the **Final Boss** (ASCII dragon) that flies and breathes fire.
- Contains four vertical **laser columns** at columns 70, 100, 130, and 160.
- The **Diamond** objective is located at approximately `(Row 13, Col 335–347)` — collecting it while the Final Boss is dead triggers the win screen.

---

## Controls

| Key | Action |
|-----|--------|
| `D` | Move Right |
| `A` | Move Left |
| `W` | Climb Up (ladder only) |
| `S` | Climb Down (ladder only) |
| `J` | Single Jump (vertical) |
| `K` | Double Jump (higher vertical jump) |
| `I` | Jump Right (also used to exit elevator) |
| `U` | Jump Left (also used to enter elevator mid-air) |
| `N` | Fire Single Bullet |
| `M` | Fire Multi-Bullet (one of up to 5 simultaneous projectiles) |
| `SPACE` | Confirm / Start (on title screen) |

### Control Rules & Restrictions

- **`J`, `K`, `I`, `U`** (jump keys) are mutually exclusive — only one jump state can be active at a time.
- Jumping is disabled while: on the ladder, inside the elevator, or while already mid-jump.
- **`N`** (single bullet) cannot fire if multi-bullets are currently active in the world.
- **`M`** (multi-bullet) cannot fire if a single bullet is currently active.
- Up to **5 multi-bullets** can exist simultaneously; each new `M` press activates one more slot.
- Firing direction is determined by the **last horizontal movement direction** (`prevHeroDir`), not the current one.
- Movement keys `A` and `D` are blocked during any jump state.

---

## Player Character

The hero is rendered as a multi-row ASCII robot/warrior figure. The sprite changes based on movement state:

| State | Description |
|-------|-------------|
| Standing / Climbing | Symmetric frontal pose with outstretched arms |
| Moving Left (`A`) | Slightly asymmetric foot stance |
| Moving Right (`D`) | Slightly asymmetric foot stance (mirrored) |
| Jumping (`J` / `K`) | Legs spread outward, arms raised |

The hero sprite occupies a bounding box of approximately **14 rows × 15 columns**, centered on `(heroRow, heroCol)`:
- Leftmost extent: `heroCol - 7`
- Rightmost extent: `heroCol + 7`
- Topmost extent: `heroRow`
- Bottommost extent: `heroRow + 13`

### Hero Health (Lives)

| Lives | Display |
|-------|---------|
| 3 | `$ $ $` |
| 2 | `$ $` |
| 1 | `$` |
| 0 | `#` (Game Over triggered) |

Lives are displayed in the top-right area of the current viewport, re-drawn each frame via `drawHeroLives()`.

#### Damage Sources

| Source | Damage | Respawn Location |
|--------|--------|-----------------|
| FloorOne Enemy (contact) | −1 life | Floor 1, Col 60 |
| FloorOne Enemy (bullet, 9 hits) | −1 life | Floor 1, Col 60 |
| Casper Ghost (contact) | −1 life | Floor 2, Col 330 |
| Final Boss (contact) | −1 life | Floor 3, Col 45 |
| Dragon Fire | **−All lives (instant death)** | N/A |
| Laser (contact) | −1 life | Floor 3, Col 45 |
| Spike Trap (contact) | −1 life | Floor 1, Col 60 |

Upon taking damage from most sources, the hero is teleported to the appropriate floor's default spawn position and relevant enemies are reset.

---

## Movement System

### Gravity

The function `comeHereGravity()` runs every frame when the hero is **not** jumping, on a ladder, or in the elevator. It checks whether the hero is standing on:

- The floor boundary of their current floor (rows 88, 58, or 28)
- The top surface of any obstacle (`Obstacle.strtRow - 1`)

If neither condition is met, `heroRow++` is applied (hero falls one row per frame).

### Floor Detection

`heroCurrFloor` is recalculated each frame based on `heroRow + 13` (the bottom of the hero sprite):

| `heroRow + 13` | `heroCurrFloor` |
|----------------|-----------------|
| < 29           |         3       |
| < 59           |         2       |
| ≥ 59           |         1       |

### Single Jump (`J`)

Executes over **6 animation ticks**:
- Ticks 0–2: Hero moves up 1 row per tick (if unobstructed)
- Ticks 3–5: Hero moves down 1 row per tick (if unobstructed)
- Gravity resumes after tick 6

### Double Jump (`K`)

Executes over **12 animation ticks** (same arc, doubled duration):
- Ticks 0–5: Hero ascends
- Ticks 6–11: Hero descends
- Reaches approximately twice the height of a single jump

### Jump Right (`I`) / Jump Left (`U`)

Executes over **8 animation ticks** with simultaneous horizontal movement:
- Ticks 0–3: Hero moves up AND horizontally (5× `moveHero()` calls per tick for speed)
- Ticks 4–7: Hero moves down AND horizontally (3× `moveHero()` calls per tick)
- Camera scrolls during both phases

These are the only jump types that allow **elevator entry/exit** mid-air.

### Obstacle Collision

`moveHero()` computes the hero's next position (`nextRow`, `nextCol`) and checks against all four `Obstacle` structs before committing movement. If the projected bounding box overlaps any obstacle's `strtRow`, `strtCol`, or `endCol`, the move is cancelled (`move = 0`).

---

## Camera & Scrolling System

The visible viewport is always `30 rows × 120 columns`. It is defined by four variables:

| Variable | Description |
|----------|-------------|
| `strtRow` | Top row of the viewport in world space |
| `endRow` | Bottom row (= `strtRow + 30`) |
| `strtCol` | Left column of the viewport in world space |
| `endCol` | Right column (= `strtCol + 120`) |

### Horizontal Scrolling

Triggered during movement, jump-right, and jump-left:
- If `heroCol > strtCol + 60` and `endCol < 360` → scroll right (`strtCol++`, `endCol++`)
- If `heroCol < strtCol + 60` and `strtCol > 0` → scroll left (`strtCol--`, `endCol--`)

This keeps the hero roughly centered horizontally.

### Vertical Scrolling

Triggered during ladder climbing and elevator riding:
- If `heroRow < strtRow + 10` and `strtRow > 0` → scroll up
- If `heroRow > strtRow + 10` and `endRow < 90` → scroll down

Gravity also causes a slow downward scroll when the hero is falling and near the bottom of the viewport.

### Floor Transitions (Viewport Snapping)

When the hero transitions between floors via the ladder or elevator, `strtRow` and `endRow` snap to the appropriate floor boundaries:

| Floor | `strtRow` | `endRow` |
|-------|-----------|----------|
| 1 | 60 | 90 |
| 2 | 30 | 60 |
| 3 | 0 | 30 |

---

## Combat System

### Single Bullet (`N`)

- One bullet exists at a time; `doYouWantSingleBullet` flag controls its lifecycle.
- Spawns at `(heroRow + 7, heroCol ± 8)` depending on facing direction.
- Moves **2 columns per frame** horizontally.
- Rendered as: `>>--->`  (right) or `<---<<` (left)
- Deactivates upon hitting a wall boundary or any obstacle.
- Deals **1 point of damage** per hit to any enemy.

### Multi-Bullet (`M`)

- Up to **5 bullets** can be active simultaneously, managed via a `Bullet[5]` array.
- Each press of `M` activates the next inactive slot.
- Movement, rendering, and collision logic is identical to the single bullet.
- All active multi-bullets are deactivated upon taking damage.

### Bullet Direction

The direction of all fired bullets is determined by `prevHeroDir` — the last direction key (`A` or `D`) pressed. This allows the player to fire backward without changing their facing direction during a jump.

---

## Enemies

### Floor 1 Enemy — "The Tank" (FloorOne)

| Property | Value |
|----------|-------|
| **Location** | Floor 1 |
| **Starting Position** | Row 63, Col 325 |
| **Health** | 3 HP |
| **Sprite Size** | ~17 rows × 30 columns |
| **Movement** | Diagonal — bounces between Col 255–325 (horizontal) and Row 63 to Row 72 (vertical) |
| **Horizontal Speed** | 2 columns/frame |
| **Vertical Speed** | 2 rows/frame |
| **Attack** | Fires projectile bullets leftward every frame when hero is past Col 190 |
| **Bullet Pool** | 3 simultaneous enemy bullets |
| **Bullet Speed** | 5 columns/frame (leftward) |
| **Bullet Damage Threshold** | Hero dies after taking **9 enemy bullets** total |
| **Death Effect** | Removed from rendering; stops firing |
| **Reset on Hero Death** | Health restored to 3, marked alive again |

---

### Floor 2 Enemies — "The Caspers" (Ghost Trio)

Three ghost enemies patrol Floor 2 simultaneously. Each has **5 HP**.

| Ghost | Starting Position | Movement Pattern |
|-------|------------------|-----------------|
| **Casper[0]** | Row 32, Col 300 | Vertical only — bounces between Row 32 and Row 43 at 2 rows/frame |
| **Casper[1]** | Row 40, Col 280 | Horizontal only — bounces between Col 150 and Col 240 at 5 cols/frame |
| **Casper[2]** | Row 35, Col 50 | Diagonal — moves vertically (1–2 rows/frame) and horizontally (1–2 cols/frame) between Col 50–110 |

**Casper sprite size:** ~16 rows × 18 columns

**Damage & Reset:** Contact with any Casper deals −1 life and teleports the hero to Floor 2 spawn (`Row 45, Col 330`). All three Caspers are reset to full health and alive status.

---

### Final Boss — "The Dragon" (FinalBoss)

| Property | Value |
|----------|-------|
| **Location** | Floor 3 |
| **Starting Position** | Row 2, Col 300 |
| **Health** | **10 HP** |
| **Sprite Size** | ~26 rows × 77 columns |
| **Movement** | Diagonal — bounces horizontally between Col 231–300, vertically between Row 2–4 |
| **Horizontal Speed** | 2 cols/frame |
| **Vertical Speed** | 1 row/frame |

#### Dragon Fire Attack

When the hero is within 20 columns of the boss's mouth (`(FinalBoss.Col - 31) - (heroCol + 14) < 20`) **and** the hero is on Floor 3:

- Animated fire breath grows downward over **8 frames** (`fireCounter` 0–7)
- Each tick, an additional row of fire characters is drawn below the boss's mouth
- The fire occupies a cone-shaped region extending **~8 rows downward** and **~16 columns wide**
- **Contact with fire is instant death** (hero loses all lives, `heroLives = 0`)

#### Boss Reset on Hero Death

Upon contact with the boss body (not fire), the hero is teleported to `(Row 15, Col 45)`, loses 1 life, and the boss is **fully healed to 10 HP**.

---

## Hazards & Obstacles

### Spike Traps

Three groups of 6 spikes each are embedded in the Floor 1 ground:

| Zone | Column Range |
|------|-------------|
| Zone 1 | Cols 117–140 |
| Zone 2 | Cols 157–180 |
| Zone 3 | Cols 197–220 |

Rendered using `/\` ASCII characters. Collision is detected when `heroRow + 13 >= 87` and the hero's horizontal position overlaps a spike zone. Cost: **−1 life** and respawn at Floor 1 default spawn; FloorOne enemy is also reset.

### Platforms (Obstacles)

Four static block platforms on Floor 1, each `4 rows tall × 17 columns wide`:

| Platform | Column | Activation Row |
|----------|--------|---------------|
| One | 100–116 | Row 85 |
| Two | 140–156 | Row 82 |
| Three | 180–196 | Row 79 |
| Four | 220–236 | Row 76 |

The hero can land on top, be blocked horizontally, and bullets are also blocked by these obstacles.

### Vertical Laser Columns (Floor 3)

Four lasers positioned at columns 70, 100, 130, and 160:

- Each laser starts at Row 0 and **grows downward** over time
- Length increases by 1 every 3 frames (via `Timer` counter), cycling 0 → 28 → 0
- Each laser is drawn as three parallel lines of `█` characters
- Contact deals **−1 life** and teleports hero to Floor 3 spawn; Final Boss is reset to full health

---

## Navigation Mechanics

### The Ladder

- Located at columns 339–351, spanning rows 45–89 (Floors 1 and 2)
- Rendered with double-line box-drawing characters (`═`, `║`, `╬`)
- **Auto-entry:** When `heroCol > 330` and `heroRow + 13 >= 45`, the hero automatically snaps to the ladder (`heroCol = 345`)
- While on the ladder, only `W` (up) and `S` (down) movement is active
- **Exit:** Pressing `A` or `U` while on the ladder detaches the hero and snaps viewport to the appropriate floor

### The Elevator

- Located on the far left (columns 2–32)
- Oscillates vertically between Row 3 and Row 38 at 1 row/frame (`elevatorDir` toggles between +1/−1)
- `elevatorCurrFloor` tracks whether the cabin is currently at Floor 2 or Floor 3 level
- **Entry:** The hero must perform a **Jump Left (`U`)** while near column 43; if the elevator is at the correct floor, `isHeroInElevator = 1` and hero position snaps into the cabin
- **While inside:** The hero is drawn at a fixed position within the elevator; all movement except vertical scrolling is disabled; the hero moves with the elevator automatically
- **Exit:** Pressing **Jump Right (`I`)** while inside and at a valid floor boundary exits the elevator and triggers a rightward jump arc

---

## Win & Lose Conditions

### Winning

The win condition requires **two simultaneous criteria**:
1. The **Final Boss** must be dead (`FinalBoss.isAlive == 0`)
2. The **hero must physically touch the Diamond** at Floor 3 (`checkDiamondCollision()` returns 1)

The diamond is located at approximately `(Row 13–18, Col 335–347)`. Touching the diamond while the boss is still alive has no effect.

### Losing

The game ends immediately when `heroLives <= 0`. This can occur through:
- Repeated contact with any enemy
- Accumulating 9 hits from FloorOne's bullets
- Contact with spikes
- Dragon fire (instant, regardless of current lives)
- Contact with lasers

---

## Screens & States

### Title / Open Screen (`drawOpenScreen`)

- Displays the game title **"TERMINAL TOWER"** in large ASCII art
- Credits line: `BY HAMZA EL HENNAWY`
- Prompt: `PRESS SPACE TO START`
- Loops indefinitely until `SPACE` is pressed

### Game Over Screen (`drawGameOver`)

- Triggered when `heroLives <= 0`
- Displays `GAME OVER` in large multi-row ASCII art within the viewport
- Game exits on any key press (`return 0`)

### Winner Screen (`drawWinner`)

- Triggered when diamond is collected with boss dead
- Displays `YOU WIN` in large multi-row ASCII art
- Game exits on any key press (`return 0`)

---

## Data Structures

### `Enemy`

```cpp
struct Enemy {
    int Row;      // Top-left row of the entity in world space
    int Col;      // Top-left column of the entity in world space
    int Dir;      // Primary movement direction (+/- speed)
    int DirTwo;   // Secondary movement direction (for diagonal movement)
    int Health;   // Current hit points
    int isAlive;  // 1 = active, 0 = dead/hidden
};
```
Used for: `FloorOne` (Tank), `Casper[3]` (Ghosts), `FinalBoss` (Dragon)

### `Obstacle`

```cpp
struct Obstacle {
    int strtRow;  // Top row of the platform surface
    int strtCol;  // Left column boundary
    int endCol;   // Right column boundary
};
```
Used for the four static platforms on Floor 1. Collision is checked against all movement, gravity, and bullet functions.

### `Bullet`

```cpp
struct Bullet {
    int Row;       // Current row in world space
    int Col;       // Current column in world space
    int IsActive;  // 1 = in flight, 0 = inactive slot
    char Dir;      // 'D' = rightward, 'A' = leftward
};
```
Used for: `MultiBullets[5]` (hero), `EnemyBullets[3]` (FloorOne enemy)

### `Laser`

```cpp
struct Laser {
    int Col;       // Column anchor of the laser beam
    int Len;       // Current length (rows from top, 0–28)
    int Timer;     // Frame counter for growth animation
    int IsActive;  // 1 = active, 0 = inactive
};
```
Used for `Lasers[4]` on Floor 3.

---

## Memory Management

All dynamic arrays are heap-allocated in `main()` and explicitly freed before program exit:

```cpp
// Allocation
unsigned char** world = new unsigned char*[90];
for (int i = 0; i < 90; i++) world[i] = new unsigned char[360];
Bullet* MultiBullets = new Bullet[5];
Bullet* EnemyBullets = new Bullet[3];
Enemy*  Casper       = new Enemy[3];
Laser*  Lasers       = new Laser[4];

// Deallocation
for (int i = 0; i < 90; i++) 
    delete[] world[i];
delete[] world;
delete[] MultiBullets;
delete[] EnemyBullets;
delete[] Casper;
delete[] Lasers;
```

> **Note:** The early-exit paths (Game Over, Win screens) call `return 0` directly and do not pass through the deallocation block. In a production context this would be addressed by RAII wrappers or smart pointers.

---

## Authors

**Developed by Hamza El Hennawy**

---

*Terminal Tower — All rendering, logic, and art crafted entirely in ASCII.*
