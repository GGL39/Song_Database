# C++ Song Database

### Description 
A custom C++ program designed to organize a collection of song records. The user can add, find, delete, and list songs in the database. This program was created for a school project to showcase proficiency in C++ and simple database systems. 

The code includes a dynamic array class to hold and manipulate data, without using pre-made container classes from STL.

### Features
- Add new songs to the database
- Delete songs from the database
- Search for songs by title, artist, release year, either by exact match or partial match
- List songs by alphabetical order, reverse alphabetical order, ascending and descending order by year
- Prevents the user from inputting nonsensical data (e.g. release year 3000) 
- Save and load the database from a file 

### Installation
1. Clone the repository to your local machine:
```
git clone https://github.com/GGL39/Song_Database.git
```
2. Compile the program using a C++ compiler:
```
g++ final_project.cpp -o song_database
```

Alternatively, you can import this repository into a new project on [replit.com](https://replit.com/~) to easily run the code without installing a compiler. 

### Usage
1. Run the compiled executable:
```
./song_database
```
2. Follow the on-screen prompts to navigate the database. 

### Example
Here's an example of searching for a song in the database.

1. Upon running the program, the main menu will pop up:
```
----------------------------------
Welcome to the Song Database!
----------------------------------

1 - Add a song.
2 - Find a song.
3 - Delete songs.
4 - List songs.
5 - Quit.

Enter the number of your choice:
```
2. Entering '2' will direct the user to this screen:
```
Find a song
----------------------------------

You can search by:
1 - Song title.
2 - Artist.
3 - Year released.

4 - Return to main menu.

Enter the number of your choice:
```
3. Entering '2' again:
```
Search by:
1 - Exact match.
2 - Partial match.

Enter the number of your choice:
```
4. Entering '2':
```
Enter part of the artist's name that you want to find:
```
5. Entering 'ari':
```
----------------------------------
5 matches found.
1: breathin, Ariana Grande, 2018
2: Emotions, Mariah Carey, 1991
3: Greedy, Ariana Grande, 2016
4: positions, Ariana Grande, 2020
5: goodnight n go, Ariana Grande, 2018
```











