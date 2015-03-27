#include "Parser.h"
#include <fstream>
#include <d3dx9.h>
#include <array>

#pragma once

Parser::Parser() : highScoreFile("highscores.txt")
{
	read();
}


Parser::~Parser()
{

}

void Parser::read(){
	std::ifstream file (highScoreFile);

	if (file.is_open()){
		for (int i = 0; file.good() && i < NR_OF_ENTRIES; i++){
			std::getline(file, lines[i]);
			highScores[i] = stringToBigInteger(lines[i]);
		}
		file.close(); 
	}

	else 
		MessageBox(NULL,
		(LPCWSTR)L"Failed to open file 'highscores.txt' in parser function read()",
		(LPCWSTR)L"Error",
		MB_ICONERROR | MB_OK);
}

void Parser::write(){

	std::ofstream file(highScoreFile);
	if (file.is_open()){
		for (int i = 0; i < NR_OF_ENTRIES; i++){
			file << lines[i] << "\n";
		}

		if (file.is_open())
			file.close();
	}
	else 
		MessageBox(NULL,
		(LPCWSTR)L"Failed to open file 'highscores.txt' in parser function write()",
		(LPCWSTR)L"Error",
		MB_ICONERROR | MB_OK);
}

bool Parser::updateScore(BigInteger argScore){
	bool change = false;
	BigInteger temp; //to remember replaced scores

	//update high-score list if argScore is a high-score
	for (int i = 0; i < NR_OF_ENTRIES; i++){
		if (highScores[i].compareTo(argScore) == BigInteger::CmpRes::less && !change){
            
			//remember replaced score
			if (i < NR_OF_ENTRIES - 1) temp = highScores[i];
			
			highScores[i] = argScore;
			lines[i] = bigIntegerToString(highScores[i]);
			change = true;
		}
		/*Should the player set a new high score, then we must alter all
		elements below (further to the right in the array) the new high score. */
		else if (change){
			highScores[i] = temp;
			if (i < NR_OF_ENTRIES - 1) temp = highScores[i + 1];
            lines[i] = bigIntegerToString(highScores[i]);
		}
	}

	if (change) write();

	return change;
}


//Groups the numerical value of the param into triplets
//e.g. 10000000 will be formated to "10,000,000"
std::string Parser::formatScore(BigInteger score){
	std::string formated = bigIntegerToString(score);

	for (unsigned int i = 3; i < formated.length(); i += 4){
		formated.insert(formated.end() - i, ',');
	}
	return formated;
}

//Format a table of current high scores into a single string. 
std::string Parser::getPrintableLine() const{
	std::string tmp ("");
	std::array<std::string, 5> pos{ { "1: \t", "2: ", "3: ", "4: " , "5: " } };
	BigInteger score;
	for (int i = 0; i < NR_OF_ENTRIES; i++){
		score = highScores[i];
		tmp = tmp + pos[i] + formatScore(score) + '\n';
	}
	return tmp;
}