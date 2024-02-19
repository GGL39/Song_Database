//final_project.cpp

/////////////////////////////////////////////////////////////////////////  
// 
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough detail
// so that someone can see the exact source and extent of the borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
// 
/////////////////////////////////////////////////////////////////////////

#include "Database.h"
#include "Menu.h"
#include <iostream>
#include <string> 

using namespace std;

// helper function that prints result text of a search
void print_result_msg(int n) {
    if (n == 0) {
        cout << "0 matches found.\n";
    } else {
        cout << "----------------------------------\n" 
             << n << " matches found.\n";
    } 
}

int main() {
    // load the .txt file into memory
    Database songs("database.txt");
    
    Menu menu;
    string userinput = "";
    while (userinput != "5") {
        //display the menu to the user
        userinput = menu.Create_Menu();

        // add song
        if (userinput == "1") {
        
            string song_title;
            string artist_name;
            string year_released_str;

            //ask user for the record to be added
            cout << "Add a song\n"
                 << "----------------------------------\n\n";
            cout << "Enter the name of the song: ";
            getline(cin, song_title);
            cout << "Enter the artist's name: ";
            getline(cin, artist_name);
            cout << "Enter the year the song was released: ";
            getline(cin, year_released_str);
       
            // validate input
            bool year_valid = 0;
            if (songs.check_int(year_released_str) == 1) {
                int year_released = songs.make_int(year_released_str);

                //if year is out of range loop to ask user to re-enter      
                if (year_released <= 0 || year_released > 2021) {
                    year_valid = 0;
                } else {
                    year_valid = 1;
                }
            } else {
                year_valid = 0;
            } 

            //loop to keep asking user for year until it's within range   
            while (year_valid == 0) {
                cout << "Enter a valid year\n";
                cout << "Enter the year the song was released: ";
                getline(cin, year_released_str);
            
                if (songs.check_int(year_released_str) == 1) { 
                    int year_released = songs.make_int(year_released_str);
            
                    if (year_released <= 0 || year_released > 2021) {
                        year_valid = 0;
                    } else {
                        year_valid = 1;
                    }
                } else {
                    year_valid = 0;
                }   
            }

            // check if record is in database
            bool found = songs.search_exact_record(song_title, artist_name);

            if (found == true) {
                cout << "Record already exists in the database.\n"            
                     << "Returning to the main menu.\n\n";
            } else {
                // add record
                Song new_song = songs.make_song(song_title, artist_name, year_released_str);
                songs.append(new_song);
                cout << "The record has been added to the database\n"
                     << "Returning to the main menu\n\n";
            }      

        // find songs     
        } else if (userinput == "2") {
            //display the find sub-menu
            userinput = menu.create_findmenu(); 

            //user wants to find by name of song
            if (userinput == "11") {
                cout << "Enter the name of the song you want to find: ";
                string song_name;
                getline(cin, song_name);

                //user wants to find exact song
                Database temp = songs.search_exact("Song", song_name); 
                print_result_msg(temp.size());

                if (temp.size() != 0) {
                    temp.to_str();
                }
            } else if (userinput == "12") {
                //user wants to find with partial match
                cout << "Enter part of the song name you want to find: ";
                string song_name;
                getline(cin, song_name);
        
                Database temp = songs.search_substring("Song", song_name);
                print_result_msg(temp.size());

                if (temp.size() != 0) {
                    temp.to_str();
                }
            } else if (userinput == "21") {
                //user wants to find by name of artist
                cout << "Enter the artist you want to find: ";
                string artist_name;
                getline(cin, artist_name);

                //user wants to find exact artist
                Database temp = songs.search_exact("Artist", artist_name);
                print_result_msg(temp.size());

                if (temp.size() != 0) {
                    temp.to_str();
                }
            } else if (userinput == "22") {
                //user wants to find with partial match
                cout << "Enter part of the artist's name that you want to find: ";
                string artist_name;
                getline(cin, artist_name);

                Database temp = songs.search_substring("Artist", artist_name);
                print_result_msg(temp.size());

                if (temp.size() != 0) {
                    temp.to_str();
                }
            } else if (userinput == "31") {
                //user wants to find by year
                cout << "Enter the year you want to find: ";
                string year_name;
                getline(cin, year_name);

                //user wants find with exact year
                Database temp = songs.search_exact("Year", year_name);
                print_result_msg(temp.size());

                if (temp.size() != 0) {
                    temp.to_str();
                }
            } else if (userinput == "32") {
                //user wants find within a range of years
                cout << "Enter the start year of the range: ";
                string range_start;
                getline(cin, range_start);

                int i = 0;
                int start;
                while (i == 0) {
                    bool start_is_int = songs.check_int(range_start);

                    // check that the user entered only numbers
                    if (start_is_int == false) {
                        cout << "Input is not a year, enter again: ";
                        getline(cin, range_start);
                    } else {
                        start = songs.make_int(range_start);

                        // check that the year is valid
                        if (start < 0 || start > 2021) {
                            cout << "Invalid year, enter again: ";
                            getline(cin, range_start);
                        } else {
                            i = 1;
                        }
                    } 
                }   

                cout << "Enter the end year of the range: ";
                string range_end;
                getline(cin, range_end);

                i = 0;
                int end;
                //loop to ask user to re-enter year until it's valid
                while (i == 0) {
                    bool end_is_int = songs.check_int(range_end);

                    if (end_is_int == false) {
                        cout << "Input is not a valid year, enter again: ";
                        getline(cin, range_end); 
                    } else {
                        end = songs.make_int(range_end);

                        if (end < 0 || end > 2021) {
                            cout << "Invalid year, enter again: ";
                            getline(cin, range_end);
                        } else if (end < start) {
                            cout << "End year cannot be less than start year, enter again: ";
                            getline(cin, range_end);
                        } else {
                            i = 1;
                        }
                    } 
                }

                //search for songs within user's range of years
                Database temp = songs.search_year_range(start, end);
                print_result_msg(temp.size());

                if (temp.size() != 0) {
                    temp.to_str();
                }
            } else if (userinput == "0") {
                cout << "\n";
            }
        } else if (userinput == "3") {
            //display the delete sub-menu
            userinput = menu.create_deletemenu();

            //user wants to delete by song's name
            if (userinput == "11") {
                cout << "Enter the name of the song you want to find: ";
                string song_name;
                getline(cin, song_name);

                //user wants to delete exact song's name
                Database temp = songs.search_exact("Song", song_name); 
                print_result_msg(temp.size());

                if (temp.size() == 0) {
                    cout << "\n";
                } else { 
                    //display records and confirm with user if they want to delete them
                    temp.to_str();
                    userinput = menu.create_confirm_menu();

                    //remove the records if user chooses to, else leave records unchanged
                    if (userinput == "Y") {
                        Database temp2(temp);
                        songs.remove_all(temp2);
                        cout << "Listed songs have been deleted.\n";
                    } else {
                        cout << "Listed songs will not be deleted.\n";
                    }
                }
            } else if (userinput == "12") {
                //user wants to delete with a partial match of the song's name
                cout << "Enter part of the song name you want to find: ";
                string song_name;
                getline(cin, song_name);

                Database temp = songs.search_substring("Song", song_name);
                print_result_msg(temp.size());

                if (temp.size() == 0) {
                    cout << "\n";
                } else { 
                    //display records and confirm with user if they want to delete them
                    temp.to_str();
                    userinput = menu.create_confirm_menu();

                    //remove the records if user chooses to, else leave records unchanged
                    if (userinput == "Y") {
                        Database temp2(temp);
                        songs.remove_all(temp2);
                        cout << "Listed songs have been deleted.\n";
                    } else {
                        cout << "Listed songs will not be deleted.\n";
                    }
                }
            } else if (userinput == "21") {
                //user wants to delete by artist's name
                cout << "Enter the artist you want to find: ";
                string artist_name;
                getline(cin, artist_name);

                //user wants to delete with exact artist's name
                Database temp = songs.search_exact("Artist", artist_name);
                print_result_msg(temp.size());

                if (temp.size() == 0) {
                    cout << "\n";
                } else { 
                    //display records and confirm with user if they want to delete them
                    temp.to_str();
                    userinput = menu.create_confirm_menu();

                    //remove the records if user chooses to, else leave records unchanged
                    if (userinput == "Y") {
                        Database temp2(temp);
                        songs.remove_all(temp2);
                        cout << "Listed songs have been deleted.\n";
                    } else {
                        cout << "Listed songs will not be deleted.\n";
                    }
                }
            } else if (userinput == "22") {
                //user wants to delete with a partial match of artist's name
                cout << "Enter part of the artist's name that you want to find: ";
                string artist_name;
                getline(cin, artist_name);

                Database temp = songs.search_substring("Artist", artist_name);
                print_result_msg(temp.size());

                if (temp.size() == 0) {
                    cout << "\n";
                } else { 
                    //display records and confirm with user if they want to delete them
                    temp.to_str();
                    userinput = menu.create_confirm_menu();

                    //remove the records if user chooses to, else leave records unchanged
                    if (userinput == "Y") {
                        Database temp2(temp);
                        songs.remove_all(temp2);
                        cout << "Listed songs have been deleted.\n";
                    } else {
                        cout << "Listed songs will not be deleted.\n";
                    }
                }
            } else if (userinput == "31") {
                //user wants to delete by the year of the record
                cout << "Enter the year you want to find: ";
                string year_name;
                getline(cin, year_name);

                //user wants to delete records from the exact year
                Database temp = songs.search_exact("Year", year_name);
                print_result_msg(temp.size());

                if (temp.size() == 0) {
                    cout << "\n";
                } else { 
                    //display records and confirm with user if they want to delete them
                    temp.to_str();
                    userinput = menu.create_confirm_menu();

                    //remove the records if user chooses to, else leave records unchanged
                    if (userinput == "Y") {
                        Database temp2(temp);
                        songs.remove_all(temp2);
                        cout << "Listed songs have been deleted.\n";
                    } else {
                        cout << "Listed songs will not be deleted.\n";
                    }
                }
            } else if (userinput == "32") {
                //user wants to delete within a range of years
                cout << "Enter the start year of the range: ";
                string range_start;
                getline(cin, range_start);

                int i = 0;
                int start;
        
                //loop that asks user to enter a year until it's valid
                while (i == 0) {
                    bool start_is_int = songs.check_int(range_start);
                    if (start_is_int == false) {
                        cout << "Input is not a year, enter again: ";
                        getline(cin, range_start);
                    } else {
                        start = songs.make_int(range_start);
                        if (start < 0 || start > 2021) {
                            cout << "Invalid year, enter again: ";
                            getline(cin, range_start);
                        } else {
                            i = 1;
                        }
                    } 
                }

                cout << "Enter the end year of the range: ";
                string range_end;
                getline(cin, range_end);

                i = 0;
                int end;

                //loop that asks user to enter a year until it's valid
                while (i == 0) {
                    bool end_is_int = songs.check_int(range_end);
                    if (end_is_int == false) {
                        cout << "Input is not a valid year, enter again: ";
                        getline(cin, range_end);
                    } else {
                        end = songs.make_int(range_end);
                        if (end < 0 || end > 2021) {
                            cout << "Invalid year, enter again: ";
                            getline(cin, range_end);
                        } else if (end < start) {
                            cout << "End year cannot be less than start year, enter again: ";
                            getline(cin, range_end);
                        } else {
                            i = 1;
                        }
                    } 
                }

                //search for the range of years within the database
                Database temp = songs.search_year_range(start, end);
                print_result_msg(temp.size());

                if (temp.size() == 0) {
                    cout << "\n";
                } else { 
                    //display records and confirm with user if they want to delete them
                    temp.to_str();
                    userinput = menu.create_confirm_menu();

                    //remove the records if user chooses to, else leave records unchanged
                    if (userinput == "Y") {
                        Database temp2(temp);
                        songs.remove_all(temp2);
                        cout << "Listed songs have been deleted.\n";
                    } else {
                        cout << "Listed songs will not be deleted.\n";
                    }
                }
            }
        } else if (userinput == "4") {
            //display the list sub-menu
            userinput = menu.create_listmenu();

            //user wants to list songs by song names in alphabetical order
            if (userinput == "11") {
                songs.sort("songs");   
                cout << "\n----------------------------------\n";
                cout << "List of songs sorted in alphabetical order:\n";
                songs.to_str();

            //user wants to list songs by song names in reverse alphabetical order
            } else if (userinput == "12") {
                songs.reverse("songs");
                cout << "\n----------------------------------\n";
                cout << "List of songs sorted in reverse alphabetical order:\n"; 
                songs.to_str();

            //user wants to list songs by artist names in alphabetical order
            } else if (userinput == "21") {
                songs.sort("artists");
                cout << "\n----------------------------------\n";
                cout << "List of songs sorted in alphabetical order of artists:\n";
                songs.to_str();

            //user wants to list songs with artist names in reverse alphabetical order
            } else if (userinput == "22") {
                songs.reverse("artists");
                cout << "\n----------------------------------\n";
                cout << "List of songs sorted in reverse alphabetical order of artists:\n";
                songs.to_str();

            //user wants to list songs with years in ascending order
            } else if (userinput == "31") {
                songs.sort("year");
                cout << "\n----------------------------------\n";
                cout << "List of songs sorted in ascending order of release year:\n";
                songs.to_str();

            //user wants to list songs with years in descending order
            } else if (userinput == "32") {
                songs.reverse("year");
                cout << "\n----------------------------------\n";
                cout << "List of songs sorted in descending order of release year:\n";
                songs.to_str();
            }   
        } else if (userinput == "5") {
            cout << "You have selected to quit. Bye\n";

            //add the array of songs that user may have made updates to, to the txt file
            songs.update_file();    
        } 
    }        
}
