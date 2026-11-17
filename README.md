# EE6161 Fantasy Game

> **Assignment 2 — EE6161 Advanced Programming**
> University of Limerick · Deadline: Friday 27 November 2026

A turn-based fantasy dungeon crawler built in **C++ with a Qt Widget GUI**. Navigate a procedurally initialised board, collect items, battle enemies, and amass as much gold as possible before you fall.

---

## Gameplay

The game is played on a rectangular grid (size chosen by the player at startup). Each square holds an enemy, an item, or is empty. The player picks a race, then moves around the board issuing single-character commands. **Time alternates between Day and Night every 5 commands** — this matters for Orc enemies, who become far more dangerous at night.

### Commands

| Key | Action |
|-----|--------|
| `N` | Move North |
| `S` | Move South |
| `E` | Move East |
| `W` | Move West |
| `P` | Pick up item on current square |
| `D` | Drop an item from inventory |
| `A` | Attack enemy on current square |
| `C` | Cast a spell |
| `K` | Drink a potion |
| `Q` | Quit game |

---

## Races

| Race   | Attack | Atk Chance | Defence | Def Chance | Health | Strength |
|--------|--------|-----------|---------|-----------|--------|----------|
| Human  | 30     | 2/3       | 20      | 1/2       | 60     | 100      |
| Elf    | 40     | 1/1       | 10      | 1/4       | 40     | 70       |
| Dwarf  | 30     | 2/3       | 20      | 2/3       | 50     | 130      |
| Hobbit | 25     | 1/3       | 20      | 2/3       | 70     | 85       |
| Orc*   | 25/45  | 1/4 / 1/1 | 10/25   | 1/4 / 1/2 | 50     | 130      |

\* Orc values shown as **Day / Night**

### Special Race Abilities

- **Human** — Successful defences never cause damage.
- **Elf** — Successful defences always restore +1 health.
- **Dwarf** — Successful defences never cause damage.
- **Hobbit** — Successful defences deal 0–5 random damage regardless of attacker's attack value.
- **Orc** — Day: successful defence reduces damage to ¼ adjusted. Night: successful defence restores +1 health.

---

## Items

| Item              | Category | Weight | Effect                              |
|-------------------|----------|--------|-------------------------------------|
| Sword             | Weapon   | 10     | +10 Attack                          |
| Dagger            | Weapon   | 5      | +5 Attack                           |
| Plate Armour      | Armour   | 40     | +10 Defence, −5 Attack              |
| Leather Armour    | Armour   | 20     | +5 Defence                          |
| Large Shield      | Shield   | 25     | +10 Defence, −5 Attack              |
| Small Shield      | Shield   | 15     | +5 Defence                          |
| Ring of Strength  | Ring     | 1      | +10 Strength                        |
| Ring of Health    | Ring     | 1      | +10 Health (at pickup only)         |
| Potion of Health  | Potion   | 5      | Restores 20 Health when drunk       |
| Potion of Strength| Potion   | 5      | Temporarily +10 Strength when drunk |
| Spell of Fireball | Spell    | 5      | Deals 20 damage (ignores defence)   |
| Spell of Lightning| Spell    | 3      | Deals 10 damage, stuns for 1 round  |

> Characters may carry **one item per category**, except Rings (unlimited, up to strength capacity).

---

## Combat

1. Attacker rolls against their **Attack Chance** — if it fails, the round ends.
2. On a successful attack, defender rolls against their **Defence Chance**.
3. **Defence fails** → `defender health -= (attacker attack − defender defence)`.
4. **Defence succeeds** → damage is determined by the defender's **special race ability**.
5. After the player attacks, the enemy immediately counterattacks (unless defeated).
6. Player health reaching 0 ends the game. Enemy health reaching 0 removes them from the board and awards gold equal to the enemy's adjusted defence value.

---

## Project Structure

```
ee6161-fantasy-game/
├── src/
│   ├── characters/
│   │   ├── Character.h / .cpp      # Abstract base class
│   │   ├── Human.h / .cpp
│   │   ├── Elf.h / .cpp
│   │   ├── Dwarf.h / .cpp
│   │   ├── Hobbit.h / .cpp
│   │   └── Orc.h / .cpp
│   ├── items/
│   │   ├── Item.h / .cpp           # Abstract base class
│   │   ├── Weapon.h / .cpp
│   │   ├── Armour.h / .cpp
│   │   ├── Shield.h / .cpp
│   │   ├── Ring.h / .cpp
│   │   ├── Potion.h / .cpp
│   │   └── Spell.h / .cpp
│   ├── game/
│   │   ├── Game.h / .cpp           # Main game loop & state
│   │   ├── Board.h / .cpp          # Grid + smart pointer squares
│   │   └── Square.h / .cpp         # Board square (may hold item or enemy)
│   └── ui/
│       ├── MainWindow.h / .cpp     # Qt main window
│       └── GameWidget.h / .cpp     # Board rendering widget
├── docs/
│   └── class_design.md             # UML + design report (PDF on submission)
├── fantasy-game.pro                # Qt Creator project file
└── README.md
```

---

## Technical Requirements Met

- [x] Object-oriented design — classes, inheritance, polymorphism
- [x] At least one abstract base class (`Character`, `Item`)
- [x] Smart pointers (`std::unique_ptr`) managing all board squares
- [x] Dynamic STL container for inventory (supports unbounded items via rings)
- [x] Qt Widget–based GUI (Qt Designer compatible)
- [x] Doxygen comments on all files, classes, and functions

---

## Build Instructions

Requires **Qt Creator** with a C++17-compatible compiler (tested on Windows).

1. Open `fantasy-game.pro` in Qt Creator.
2. Configure the kit (Desktop Qt, MinGW or MSVC).
3. Build → Run (`Ctrl+R`).

---

## Group Members

| Name | Student ID | GitHub |
|------|-----------|--------|
| Ruhul Alam | — | [@rahulalamsportfolio](https://github.com/rahulalamsportfolio) |
| — | — | — |
| — | — | — |

---

## Marking Scheme

| Component | Marks |
|-----------|-------|
| Class Design (report) | 10 |
| Pseudo-code for non-trivial functions | 10 |
| Game implementation | 30 |
| Dynamic structure for board squares | 10 |
| Smart pointers for board squares | 10 |
| Dynamic structure for inventory | 10 |
| Qt GUI | 20 |
| **Total** | **100** |

---

*EE6161 Advanced Programming · University of Limerick · 2026*
