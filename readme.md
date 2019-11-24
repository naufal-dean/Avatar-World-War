# TUGAS BESAR IF2120 - ALGORITMA DAN STRUKTUR DATA 2019

## AVATAR : WORLD WAR

Kelompok 4 / K03 :
1. Panawar Hasibuan     13517129
2. Daffa Pratama Putra  13518033
3. Dhafin Rayhan Ahmad  13518063
4. Morgen Sudyanto      13518093
5. Naufal Dean Anugrah  13518123

## How to compile?
1. Clone this repository
2. Compile all non-driver files ending with ".c" extension. An example would be like this (assuming you are in the repository folder)

    ```
    gcc -o main src/*.c src/ADT/array/array.c src/ADT/bangunan/bangunan.c src/ADT/graph/graph.c src/ADT/kata/kata.c src/ADT/listlinier/listlinier.c src/ADT/matriks/matriks.c src/ADT/mesinkar/mesinkar.c src/ADT/mesinkata/mesinkata.c src/ADT/point/point.c src/ADT/queue/queue.c src/ADT/stack/stack.c src/ADT/status/status.c
    ```
    This will create an executable file named "main.exe" (windows) or an ELF file named "main" (linux).
3. Move the main file into the bin folder.
    
## How to run?
1. Change the current directory to bin.
2. Run the main file.

## File Structure
```
.
├── bin
│   ├── main.exe          # Our main.exe if you are too lazy to compile
│   └── sample_savedata   # Just an example save data
├── data
│   ├── 5x5.txt
│   ├── 10x10.txt
│   ├── savedataformat.txt
│   └── config.txt        # Configuration file
├── docs                  # For the formalities. FYI we are not providing any form of documentation.
│   │                     # All the codes are self explanatory.
│   ├── Spesifikasi...2019).pdf
│   ├── IF2110_Form..._03.xlsx
│   └── IF2110_TB..._03.pdf  <-- Our report.
├── src
│   ├── boolean.h
│   ├── console.c         # Implementation of all commands
│   ├── console.h
│   ├── main.c            # Simply calls the AppExecute function
│   ├── pcolor.c          # Colour module
│   ├── pcolor.h
│   ├── ADT               # Location of all the data structures used by this game. 
│   │                     # Every subfolder will have a header, a c implementation and a driver.
│   │   ├── array         # Contains all building information
│   │   ├── bangunan     
│   │   ├── graph         # Basically an adjacency list of all buildings
│   │   ├── kata
│   │   ├── listlinier    # Honestly, we have no idea where to use this data structure.
│   │   ├── matriks       # Displays the map.
│   │   ├── mesinkar      
│   │   ├── mesinkata     # How to input string like a boss?
│   │   ├── point
│   │   ├── queue         # For skill purposes.
│   │   ├── stack         # For undo purposes.
└── └── └── status
```

## FAQ
### Why are some characters in the game is not displayed properly?
Make sure your terminal supports unicode (UTF-8).
### Can I change the game's initial configuration?
Sure! Just change the config.txt file inside the data folder. We also provide you with another 2 sample config files, just copy the data into config.txt.
### I want to write my own save file. Where should I put it?
All saved files are inside the bin folder. Try to save the game once and see its format.
### Your game sucks! How can I make this better?
We are not planning develop this game anytime in the near future. But, we will gladly accept contributions! Simply make a pull request :)
