#include <iostream>
#include <array>
#include "BigIntegerLibrary.hh" //third-party
#pragma once

#define NR_OF_ENTRIES 5
class Parser
{
public:
	Parser();
	virtual ~Parser();

	static std::string formatScore(BigInteger);
	std::string getPrintableLine() const;
	bool updateScore(BigInteger = 0);

	void read(); 
	
	
private: 
	const std::string highScoreFile;

	std::array<BigInteger, NR_OF_ENTRIES> highScores;
	std::array<std::string, NR_OF_ENTRIES> lines;

	void write();

};

