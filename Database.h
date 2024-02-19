//Database.h

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
#include <fstream>
#include <algorithm>
#include <cmath>
#include "Song.h"

using namespace std;

class Database {
private: 		
	int cap;	
	Song* data;	
	int sz;

public:
	// Make a default constructor 
	Database() {
		cap = 10;
		data = new Song[cap];
		sz = 0;
	}

	// Make a destructor
	~Database() {
		delete[] data;
	}

  	// copy constructor taking in another database as input
 	Database(const Database& other) {
    		sz = other.sz;
    		cap = other.cap;
    		data = new Song[cap];
	  	for (int i = 0; i < other.sz; i++) {
		  	data[i] = other.data[i];
		} 
	}

	// Make a copy of this database
  	Database make_copy() {
    		Database copy;
    		copy.sz = sz;
    		copy.cap = cap;
    		copy.data = new Song[cap];

    		for (int i = 0; i < sz; i++) {
      		copy.data[i] = data[i];
    		}
    		return copy;
  	}

	// Returns the number of Songs
	int size() const { return sz;}

	// print all songs in Database
	void to_str() const {
		for (int i = 0; i < sz; i++) {
			cout << i + 1 << ": " << data[i].make_txt() << endl;
		}
	}

	// Set the song at the index location
	Song set(int i, Song s) {
		return data[i] = s;
	}

	// Add a song to the right of Database
	void append(Song s) {
	
		// Double cap if sz is greater than or equal to cap
		if (sz >= cap) {
			cap *= 2;	
			Song* new_vec = new Song[cap];

			for (int i = 0; i < sz; i++) {
				new_vec[i].set_song_title(data[i].song_title());
				new_vec[i].set_artist(data[i].artist());
				new_vec[i].set_year(data[i].year());
			}
			delete[] data;
			data = new_vec;
		}
		sz++;
		set(sz - 1, s);
	}

  	// Sorts data 
  	// third parameter accesses Song fields and passes bool to sort()
  	// utilize sort() for O(nlog n) runtime
  	// third parameter ensures case insensitivity 
  	// Used following source for help with third parameter (lambda function):
  	// https://stackoverflow.com/questions/33379846/case-insensitive-sorting-of-an-array-of-strings
  	void sort(const string& s) {
    		if (s == "songs") {
      		std::sort(data, data + sz, [](const Song a, const Song b) {
                                    		return lexicographical_compare(
                                      			begin(a.song_title()), end(a.song_title()),
                                      			begin(b.song_title()), end(b.song_title()),
                                        		[](const char& char1, const char& char2) {
                                          		   return tolower(char1) < tolower(char2); }); });
    		} else if (s == "artists") {
      		std::sort(data, data + sz, [](const Song a, const Song b) {
                                    		return lexicographical_compare(
                                      			begin(a.artist()), end(a.artist()),
                                      			begin(b.artist()), end(b.artist()),
                                        		[](const char& char1, const char& char2) {
                                          			return tolower(char1) < tolower(char2); }); });
    		} else if (s == "year") {
      		std::sort(data, data + sz, [](const Song a, const Song b) {
                                    		return a.year() < b.year(); });
    		}
  	}

  	// sorts data into reverse order
  	void reverse(const string& s) {
    		if (s == "songs") {
      		sort("songs");
      		std::reverse(data, data + sz);
    		} else if (s == "artists") {
      		sort("artists");
      		std::reverse(data, data + sz);
    		} else if (s == "year") {
      		sort("year");
      		std::reverse(data, data + sz);
    		}
  	}

  	// searches Database for the exact same record
  	bool search_exact_record(const string& song, const string& artist) {

    		// pointer will keep track of the start of the search range
    		Song* first = data;

    		// pointer points to the location in data where a match occurred
    		Song* index;

    		// data index where the match occured
    		int index_num = 0;

    		bool match = true;

    		// while a song title match was found
    		while (match == true) {
      		index = std::find_if(first, data + sz, [&s = song](const Song a) { 
                                              				return lexicographical_compare(
                                                					begin(a.song_title()), end(a.song_title()),
                                                					begin(s), end(s),
                                                  				[](const char& char1, const char& char2) {
                                                     					return tolower(char1) < tolower(char2); }); });
      		if (index != data + sz) {
        			// get the index in data[]
        			// this is for adding to the Song* index to continue the search
        			for (int i = 0; i < sz; i++) {
          			string record = data[i].song_title();
          			for (int j = 0; j < record.length(); j++) {
            				if (record.at(j) != song.at(j)) {
              					break;
            				} else if (j == record.length() - 1) {
              					index_num = i;
            				}
          			}		
        			}

        			// check if the artist matches too 
        			// assumption: unlikely that an artist releases a song of the same name
        			if (data[index_num].artist() == artist) {
          			return true;
        			} else {
          			first += index_num + 1;
        			}
      		} else {
        			return false;
      		}
    		}
     	return false;
  	}

  	// searches Database for a range of years 
  	Database search_year_range(int range_start, int range_end) {
    		Database temp;
    		int i = 0;

    		while (i != sz) {
      		if (data[i].year() >= range_start && data[i].year() <= range_end) {
        			temp.append(data[i]);
      		}
    			i++; 
    		}
    		return temp;
  	}

  	// searches Database for user's exact input
  	Database search_exact(const string& field, const string& s) {

    		// temporary database stores found song records
    		Database temp;

    		Song* first = data;
    		Song* index;
    		int index_num = 0;
    		bool match = true;

    		// while loop checks for multiple occurences of the song
    		while (match == true) {
      		if (field == "Song") {
        			index = std::find_if(first, data + sz, [&cs = s](const Song a) { 
                                                			return a.song_title() == cs; });
      		} else if (field == "Artist") {
        			index = std::find_if(first, data + sz, [&cs = s](const Song a) { 
                                                			return a.artist() == cs; });
      		} else if (field == "Year") {
		    		int s_i = stoi(s);
		    		index = std::find_if(first, data + sz, [&cs = s_i](const Song a) { 
                                                			return a.year() == cs; });
	    		}
      
      		// if the song was found, add it to the temporary database
      		if (index != data + sz) {
        			Song song = *index;
        			temp.append(song);
        
        			// get the array index the song occurs in
        			string record_temp = (temp.data[(temp.sz) - 1]).make_txt();
        			for (int i = 0; i < sz; i++) {
          			string record = data[i].make_txt();
          			for (int j = 0; j < record.length(); j++) {
            				if (record.at(j) != record_temp.at(j)) {
              					break;
            				} else if (j == record.length() - 1) {
              					index_num = i;
            				}
          			}	
        			}
        			first += index_num + 1;
      		} else {
        			match = false;
      		}
    		}
    		return temp;
  	}
   
  	// searches Database for user's input substring
  	Database search_substring(const string& field, const string& s) {
    		Database temp;
    		if (field == "Song") {
      		int i = 0;
      		while (i != sz) {
        			bool match = data[i].check_str("Song", s);
        			if (match == true) {
          			temp.append(data[i]);
        			}
        			i++;
      		}
      		return temp;

    		} else if (field == "Artist") {
      		int i = 0;
      		while (i != sz) {
        			bool match = data[i].check_str("Artist", s);
        			if (match == true) {
          			temp.append(data[i]);
        			}
        			i++;
      		}
      		return temp;

    		} else if (field == "Year") {
		  int i = 0;
		  while (i != sz) {
			  bool match = data[i].check_str("Year", s);
			  if (match == true) {
				  temp.append(data[i]);
			  }
			  i++;
		  }
	  	}
  		return temp;
  	}
  
  	// remove one element from the database
  	void remove(int n) {
    		// make a copy database for reference
    		Database old = make_copy();
  
    		for (int i = n; i < old.sz - 1; i++) {
      		data[i] = old.data[i+1]; 
    		}
    		sz--;
  	}

  	// remove Songs contained in another database 
  	void remove_all(Database temp) {
    		for (int i = 0; i < temp.size(); i++) {
      		for (int j = 0; j < sz - i; j++) {
        			if (temp.data[i].make_txt() == data[j].make_txt()) {
          			remove(j);
        			}
      		}
    		}
  	}

	// Read in records from database.txt
	// https://www.geeksforgeeks.org/how-to-input-a-comma-separated-string-in-c/
	Database(const string& fname){
		ifstream fin;
		fin.open(fname);
		string record;
		cap = 10;
		data = new Song[cap];
		sz = 0;
		
		while (getline(fin, record)) {
			Song song(record);
			append(song);
		}
		fin.close();
	}

  	// makes a new Song
  	Song make_song(string song_name, string artist, string year) {
    		Song song;
    		song.set_artist(artist);
    		song.set_song_title(song_name);
    		int yr = song.make_int(year);
    		song.set_year(yr);

    		return song;
  	}
	
	// makes string all lowercase
  	string make_lower(string s) {
		string lower_s = s;
    		for_each(lower_s.begin(), lower_s.end(), [](char & c) {
	 		c = tolower(c);
	  	});
    		return lower_s;
  	}
  
  	// checks whether the user input an integer 
	bool check_int(string s) {
		int len = s.length();
			
		for (int i = 0; i < len; i++) {
			if (int(s.at(i)) < 48 || int(s.at(i)) > 57) {
				return 0;
			} 
		}
		return 1;
	}

  	// turns string containing only number characters to int
	int make_int(string s) { 
		int len = s.length();
		int myint = 0;
	 	for (int i = 0; i < len; i++) {
	 		myint += (int(s.at(i)) - 48 )* pow(10.0, len - i - 1);
	 	}
		return myint;
	}

  	// updates the .txt file when the user quits the database
	void update_file() {	
		ofstream myfile;
		string data_file = "";
		for (int i = 0; i < sz; i++) {
			data_file += data[i].make_txt() + "\n";
		}

		//From : http://www.cplusplus.com/reference/fstream/ofstream/open/
		myfile.open("database.txt", ios::out | ios::trunc);
		myfile << data_file;
		myfile.close();		
	}

};
