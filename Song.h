//Song.h

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
#include <sstream>

using namespace std;

class Song {
private:
    string artist_name;
    string song_name;
    int year_released = 0;

public:
	// Make a default constructor 
	Song()
	{ }
	
	// Make a destructor
	~Song() 
	{ }
	
	// makes a new song from taking 1 string as input
	Song(const string& s) {
			
		// string that holds the current text
    		string current_field = "";

    		// this int indicates which Song field to assign the string to
		int field_num = 0;

    		bool comma = false;

    		for (int i = 0; i < s.length(); i++) {
      		// once comma is detected, skip the whitespace and assign the string to Song
      		if (s.at(i) == ',') {
        			comma = true;
        			continue;
      		} else if (comma == true) {
        			comma = false;
        			field_num++;

        			if (field_num == 1) {
          			song_name = current_field;
          			current_field = "";
        			} else if (field_num == 2) {
          			artist_name = current_field;
          			current_field = "";
        			}
        			continue;
      		} else {
        			current_field += s.at(i);
      		}

      		if (i == s.length() - 1) {
        			year_released = make_int(current_field);
      		}
    		} 
  	}

	// getters
	string artist() const { return artist_name; }
	string song_title() const { return song_name; }
	int year() const { return year_released; }
	
	// setters 
	string set_artist(string const& s) { return artist_name = s; }	
	string set_song_title(string const& s) { return song_name = s; }
	int set_year(int y) { return year_released = y; }
	
	// turns string containing only number characters to int
	int make_int(string s) { 
		int len = s.length();
		int myint = 0;
	 	for (int i = 0; i < len; i++) {
	 		myint += (int(s.at(i)) - 48 )* pow(10.0, len - i - 1);
	 	}
		return myint;
	}
	
	// turns song into string suitable for .txt format
	string make_txt() { 
		string mystring = song_name + ", " + artist_name + ", " + to_string(year_released);
		return mystring;
	}

  	// check if substring in Song matches another string
  	bool check_str(const string& field, const string& s) {
    		string record;
    		if (field == "Song") {
      		record = make_lower(song_name);
    		} else if (field == "Artist") {
      		record = make_lower(artist_name);
    		}
    		string l = make_lower(s);

    		if (record.find(l) == string::npos) {
      		return false;
    		} else {
      		return true;
    		}
  	}

  	// makes string all lowercase
  	string make_lower(string s) {
		string lower_s = s;
    		for_each(lower_s.begin(), lower_s.end(), [](char & c) {
	 		c = tolower(c);
	  	});
    		return lower_s;
  	}
  
};
