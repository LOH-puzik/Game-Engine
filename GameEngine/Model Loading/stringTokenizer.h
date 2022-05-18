#pragma once
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//helper functions
float _stringToFloat(const std::string &source) {
	std::stringstream ss(source.c_str());
	float result;
	ss >> result;
	return result;
}

unsigned int _stringToUint(const std::string &source) {
	std::stringstream ss(source.c_str());
	unsigned int result;
	ss >> result;
	return result;
}

int _stringToInt(const std::string &source) {
	std::stringstream ss(source.c_str());
	int result;
	ss >> result;
	return result;
}

void _stringTokenize(const std::string &source, std::vector<std::string> &tokens) {
	tokens.clear();
	std::string aux = source;
	for (unsigned int i = 0; i<aux.size(); i++) if (aux[i] == '\t' || aux[i] == '\n') aux[i] = ' ';
	std::stringstream ss(aux, std::ios::in);
	while (ss.good()) {
		std::string s;
		ss >> s;
		if (s.size()>0) tokens.push_back(s);
	}
}

void _faceTokenize(const std::string &source, std::vector<std::string> &tokens) {
	std::string aux = source;
	for (unsigned int i = 0; i<aux.size(); i++) if (aux[i] == '\\' || aux[i] == '/') aux[i] = ' ';
	_stringTokenize(aux, tokens);
}
