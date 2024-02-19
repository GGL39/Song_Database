//Menu.h

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
#include <iostream>
#include <string>

using namespace std;

class Menu {
private:
	bool get_input = false;
  	string userinput;

public:
  	// default constructor
  	Menu() 
  	{ }

  	// Destructor
  	~Menu()
  	{ }

  	// Create the menu
  	string Create_Menu() {
    		cout << "----------------------------------\n"
    	   		<< "Welcome to the Song Database!\n"
    		 	<< "----------------------------------\n\n"
    		 	<< "1 - Add a song.\n"
    		 	<< "2 - Find a song.\n"
    		 	<< "3 - Delete songs.\n"
    		 	<< "4 - List songs.\n"
    		 	<< "5 - Quit.\n\n"
    		 	<< "Enter the number of your choice: ";
    	
    		get_input = false;

    		while (get_input == false) {	
    			getline(cin, userinput);
    		
    			if (userinput == "1" || userinput == "2" || userinput == "3" || 
    			    userinput == "4" || userinput == "5") {
    				get_input = true;
    			} else {
    				cout << "Invalid menu choice, enter again: ";
    				get_input = false;
    			}
    		}
    		get_input = false;
    		return userinput;
  	}	

  	// create sub-menu for finding songs
  	string create_findmenu() {
    		cout << "\nFind a song\n"
         		<< "----------------------------------\n\n"
         		<< "You can search by: \n"
         		<< "1 - Song title.\n"
         		<< "2 - Artist.\n"
         		<< "3 - Year released.\n\n"
         		<< "4 - Return to main menu.\n\n"
         		<< "Enter the number of your choice: ";
    
    		get_input = false;
    		bool song = false;

    		while (get_input == false) {
      		getline(cin, userinput);

      		if (userinput == "1" || userinput == "2") {
        			cout << "Search by: \n"
             			<< "1 - Exact match.\n"
             			<< "2 - Partial match.\n\n"
             			<< "Enter the number of your choice: ";

        			if (userinput == "1") {
          			song = true;
        			} else {
          			song = false;
        			}

        			bool is_string = true;
        			while (is_string == true) {
          			getline(cin, userinput);

          			if (userinput == "1" && song == true) {
            				// song, exact match
            				return "11";
          			} else if (userinput == "2" && song == true) {
            				// song, partial match
            				return "12";
          			} else if (userinput == "1" && song == false) {
            				// artist, exact match
            				return "21";
          			} else if (userinput == "2" && song == false) {
            				// artist, partial match
            				return "22";
          			} else {
            				cout << "Invalid menu choice, enter again: ";
          			}
        			}
      		} else if (userinput == "3") {
        			cout << "Search by: \n"
             			<< "1 - Exact year\n"
             			<< "2 - Range of years\n\n"
             			<< "Enter the number of your choice: ";
        
        			bool is_int = true;

        			while (is_int == true) {
          			getline(cin, userinput);
          			if (userinput == "1") {
            				// year, exact
            				return "31";
          			} else if (userinput == "2") {
            				// year, Range
            				return "32";
          			} else {
            				cout << "Invalid menu choice, enter again: ";
          			}
        			}
      		} else if (userinput == "4") {
        			return "0";
      		} else {
        			cout << "Invalid menu choice, enter again: ";
      		}
    		}
    		return userinput;
  	}

  	// create sub-menu for deleting songs
  	string create_deletemenu() {
    		cout << "\nDelete songs\n"
         		<< "----------------------------------\n\n"
         		<< "Search for songs to delete by: \n"
         		<< "1 - Song title.\n"
         		<< "2 - Artist.\n"
         		<< "3 - Year released.\n\n"
         		<< "Enter the number of your choice: ";

    		get_input = false;
    		bool song = false;

    		while (get_input == false) {
      		getline(cin, userinput);

      		if (userinput == "1" || userinput == "2") {
        			cout << "\n1 - Exact match\n"
             			<< "2 - Partial match\n\n"
             			<< "Enter the number of your choice: ";
        
        			if (userinput == "1") {
          			song = true;
        			} else {
          			song = false;
        			}

        			bool is_string = true;
        			while (is_string == true) {
          			getline(cin, userinput);

          			if (userinput == "1" && song == true) {
            				// song, exact match
            				return "11";
          			} else if (userinput == "1" && song == false) {
            				// artist, exact match
            				return "21";
          			} else if (userinput == "2" && song == true) {
            				// song, partial match
            				return "12";
          			} else if (userinput == "2" && song == false) {
            				// artist, partial match
            				return "22";
          			} else {
            				cout << "Invalid menu choice, enter again: ";
          			}
        			}
      		} else if (userinput == "3") {
        			cout << "\n1 - Exact year.\n"
             			<< "2 - Range of years.\n\n"
             			<< "Enter the number of your choice: ";

        			bool is_year = true;
        			while (is_year == true) {
          			getline(cin, userinput);

          			if (userinput == "1") {
            				// year, exact match
            				return "31";
          			} else if (userinput == "2") {
            				// year, Range
            				return "32";
          			} else {
            				cout << "Invalid menu choice, enter again: ";
          			}
        			}
      		} else {
        			cout << "Invalid menu choice, enter again: ";
      		}
    		}
    		return userinput;
  	}

  	// create sub-menu for song deletion confirmation
  	string create_confirm_menu() {
    		cout << "\nDo you want to delete the listed songs?\n"
         		<< "Y - Yes\n"
         		<< "N - No\n\n"
         		<< "Enter the letter of your choice: ";
      
    		get_input = false;

    		while (get_input == false) {
      		getline(cin, userinput);

      		if (userinput == "Y" || userinput == "y") {
        			return "Y";
      		} else if (userinput == "N" || userinput == "n") {
        			return "N";
      		} else {
        			cout << "Invalid menu choice, enter again: ";
      		}
    		}
    		return userinput;
  	}

  	// create sub-menu for listing songs
  	string create_listmenu() {
    		cout << "\nList songs\n"
         		<< "----------------------------------\n\n"
         		<< "Sort songs by: \n"
         		<< "1 - Song title.\n"
         		<< "2 - Artist.\n"
         		<< "3 - Year released.\n\n"
         		<< "Enter the number of your choice: ";
      
    		get_input = false;
    		bool song = false;

    		while (get_input == false) {
      		getline(cin, userinput);

      		if (userinput == "1" || userinput == "2") {
        			cout << "\n1 - Alphabetical order.\n"
             			<< "2 - Reverse alphabetical order.\n\n"
             			<< "Enter the number of your choice: ";
          
        			if (userinput == "1") {
          			song = true;
        			} else {
          			song = false;
        			}

        			bool is_string = true;
        			while (is_string == true) {
          			getline(cin, userinput);

          			if (userinput == "1" && song == true) {
            				// song, alphabetical order
            				return "11";
          			} else if (userinput == "1" && song == false) {
            				// artist, alphabetical order
            				return "21";
          			} else if (userinput == "2" && song == true) {
            				// song, reverse
            				return "12";
          			} else if (userinput == "2" && song == false) {
            				// artist, reverse
            				return "22";
          			} else {
            				cout << "Invalid menu choice, enter again: ";
          			}
        			}
      		} else if (userinput == "3") {
        			cout << "\n1 - Ascending order.\n"
             			<< "2 - Descending order.\n\n"
             			<< "Enter the number of your choice: ";

        			bool is_int = true;
        			while (is_int == true) {
          			getline(cin, userinput);

          			if (userinput == "1") {
            				// year, ascending
            				return "31";
          			} else if (userinput == "2") {
            				// year, descending
            				return "32";
          			} else {
            				cout << "Invalid menu choice, enter again: ";
          			}
        			}
      		} else {
        			cout << "Invalid menu choice, enter again: ";
      		}
    		}
  		return userinput;
  	}

};
