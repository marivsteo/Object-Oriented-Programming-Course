#pragma once
#ifndef CSV_REPO_H
#define CSV_REPO_H

#include <string>
#include <fstream>
#include <sstream>
#include <zconf.h>
#include "PersistentRepository.h"

template <class T>
class CSVRepository : virtual protected PersistentRepository<T> {
private:
	void load() {
		std::fstream fin(this->filename, std::ios::in);

		std::string line;
		T object;

		while (std::getline(fin, line)) {
			std::stringstream s(line);
			s >> object;
			this->objects.push_back(object);
		}

		fin.close();
	}

	void save() {
		std::fstream output(this->filename, std::ios::out | std::ios::trunc);
		for (auto& x : this->objects) {
			output << x << '\n';
		}
	}
public:
	explicit CSVRepository(const std::string& filename) {
		this->filename = filename;
		this->load();
	}

	~CSVRepository() {
		this->save();
	}

};
#endif