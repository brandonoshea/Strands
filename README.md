# Strands

New York Times Strands Game

A puzzle grid of letters is loaded from a data file. The program scans a
dictionary file for every word that is the required length and can be traced
through adjacent cells in the grid (no cell reused within a single word). The
player then guesses words interactively until every hidden word is found (or
quits early).

## Building

```
make        # builds strands.exe
make run    # builds (if needed) and runs it
make clean  # removes the built executable
```

Requires `gcc`. Build configuration lives in [makefile](makefile) and
[defs.mk](defs.mk).

## Running

```
./strands.exe [strand-data-file] [dictionary-file]
```

- `strand-data-file` — optional; if omitted, the program prompts for a
  filename interactively. See [3x3_5.txt](3x3_5.txt) for the expected format.
- `dictionary-file` — optional; defaults to `/usr/share/dict/american-english`.

### Data file format

```
<rows> <cols>
<word length>
<rows * cols letters, space-separated, row-major>
```

Example ([3x3_5.txt](3x3_5.txt)):

```
3 3
5
s h o h u t i g h
```

This describes a 3x3 grid and asks the program to find all 5-letter words
that can be traced through it.

### Gameplay

Once loaded, the program prints the grid and the list of rules, then repeatedly
prompts `Guess a word or 'quit':`. Enter a word to check it against the set of
valid words for the puzzle, or type `quit` to end the game early. The game
ends automatically once every valid word has been found.

## Project structure

| File | Purpose |
|---|---|
| [main.c](main.c) | Entry point; wires together file loading, strand creation, and gameplay. |
| [game.c](game.c) / [game.h](game.h) | File I/O for the data/dictionary files, instructions, and the main game loop. |
| [strand.c](strand.c) / [strand.h](strand.h) | `strand_t` struct and logic for building the puzzle, validating words against the grid, printing the grid, and freeing memory. |
| [makefile](makefile) / [defs.mk](defs.mk) | Build configuration. |
| [3x3_5.txt](3x3_5.txt) | Sample puzzle data file. |
