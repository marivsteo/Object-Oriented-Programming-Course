#pragma once
#include<string>
#include<iostream>

class Movie {
private:
	std::string name;
	std::string genre;
	std::string trailer;
	int year;
	int likes;
public:
	Movie();

	Movie(const std::string& n, const std::string& g, const std::string& t, int y);

	Movie(const Movie& movie);

	Movie& operator = (const Movie&);

	void setName(std::string name);

	std::string getName() const;

	void setGenre(std::string genre);

	std::string getGenre() const;

	void setTrailer(std::string trailer);

	std::string getTrailer() const;

	void setYear(int year);

	int getYear() const;

	bool operator == (const Movie movie) const;

	Movie& operator ++ ();

	Movie& operator ++ (int);

	friend std::ostream& operator << (std::ostream& os, const Movie& movie);

	void setLikes(int likes);

	int getLikes() const;
};