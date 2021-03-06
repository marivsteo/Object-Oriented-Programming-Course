#include "UserUI.h"
#include <sstream>
#include <Windows.h>
#include <shellapi.h>


UserUI::UserUI(UserController& cntrl) : controller{ cntrl } {}


void UserUI::queryByGenre() {
	std::string query;
	std::cout << "Input query: ";
	std::getline(std::cin, query);
	this->controller.queryByGenre(query);

	int option;
	bool input_flag = true;

	system("clear");

	if (this->controller.getQuery().empty()) {
		std::cout << "No movie matching the query!\n";
		return;
	}

	while (input_flag) {
		try {
			this->seeDetails();
		}
		catch (std::exception & e) {
			std::cout << "No movies left!\n";
			input_flag = false;
			continue;
		}
		std::cout << "Menu:\n\
1. Play the trailer\n\
2. Next movie\n\
3. Add to watchlist\n\
4. Exit\n\
Your option: ";
		std::cin >> option;
		std::cin.ignore();
		switch (option) {
		case 1:
			system("clear");
			this->playTrailer();
			break;
		case 2:
			this->nextMovie();
			system("clear");
			break;
		case 3:
			this->addToWatchlist();
			system("clear");
			break;
		case 4:
			input_flag = false;
			break;
		default:
			break;
		}
	}
}


void UserUI::addToWatchlist() {
	this->controller.addToWatchList();
}


void UserUI::nextMovie() {
	this->controller.nextMovie();
}


void UserUI::seeDetails() {
	Movie m = this->controller.seeDetails();
	std::cout << m << "\n\n";
}


void UserUI::playTrailer() {
	Movie m = this->controller.seeDetails();
	std::stringstream ss;
	ShellExecuteA(NULL, NULL, "chrome.exe", m.getTrailer().c_str(), NULL, SW_SHOWMAXIMIZED);
	//ss << "google-chrome " << m.getTrailer();
	system(ss.str().c_str());
	system("clear");
}


void UserUI::getWatchlist() {
	std::vector<Movie> wl = this->controller.getWatchlist();

	if (wl.size()) {
		for (int i = 0; i < (int)wl.size(); i++) {
			std::cout << i << ". " << wl[i] << '\n';
		}
	}
	else {
		std::cout << "Watchlist is empty!\n";
	}
}


void UserUI::removeWatchlist() {
	if (this->controller.getWatchlist().empty()) {
		system("clear");
		std::cout << "Watchlist is empty!\n";
		return;
	}

	int idx;
	int liked;

	std::cout << "Index: ";
	std::cin >> idx;
	std::cout << "Did you like it (0/1) ? ";
	std::cin >> liked;

	this->controller.removeWatchlist(idx, liked);
}


void UserUI::input_loop() {
	bool input_flag = 1;
	int option;

	while (input_flag) {
		std::cout << "Menu:\n\
1. Query by genre\n\
2. See watchlist\n\
3. Remove movie from watchlist\n\
4. Exit\n\
Your option: ";
		std::cin >> option;
		std::cin.ignore();
		try {
			switch (option) {
			case 1:
				this->queryByGenre();
				break;
			case 2:
				system("clear");
				this->getWatchlist();
				break;
			case 3:
				this->removeWatchlist();
				break;
			case 4:
				input_flag = 0;
				system("clear");
				break;
			}
		}
		catch (std::exception e) {
			std::cout << e.what() << '\n';
		}
	}
}