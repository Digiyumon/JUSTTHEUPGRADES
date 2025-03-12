//TODO: so right now this is just going to take in file names, but maybe later we can make a gui and have the user select the files and then have the text output,
//THEN MAYBE LATER we can have it to where we fetch data from a json and show a visualization of replacing them???

//TODO: be able to deal with more than 1 leftover basic land (because right now we have just 1 basic land leftover, but that won't always be the case
//TODO: make a gui to be able to pick the files in our explorer
//TODO: get a way to show the price of each upgrade? then have a sum total of the cost of upgrades

//this program will be called JUST THE UPGRADES
//you take in a deck that you have, and you put in a deck that you want, and it will show you just the cards you have with no duplicates

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <unordered_map>

//this function trims the whitespace from the beginning and end of the string
std::string trim(const std::string& s) {
	size_t start = s.find_first_not_of(" \n");
	if (start == std::string::npos) {
		return "";
	}

	size_t end = s.find_last_not_of(" \n");

	return s.substr(start, end - start + 1);
}

//this creates the unordered_map for each of the files provided
std::unordered_map<std::string, size_t> createTheListOfCardsForDeck(std::string& fileName) {
	//temporary variable to hold the current line of text
	std::string currentLine = "";
	std::string currentCardName = "";

	int numberOfCopies = 1;

	//We will be using a unordered map to show what card has how many copies,
	// most are gonna be 1 but if its an island or a card that says we can have more than 1 copy then we can put the amount there
	//Fun fact: to my knowledge, there are only 8 cards in magic that allow you to have any amount of copies of them in your deck
	std::unordered_map<std::string, size_t> listOfCards;

	//opening the main deck file
	std::ifstream file(fileName);
	if (!file) {// if we fail to open the file then we will send an error
		std::cerr << "Error opening up the file!" << std::endl;
		//returning with a 1 in order to indicated a failure
		return listOfCards;
	}

	while (std::getline(file, currentLine)) {
		size_t x_pos = currentLine.find('x');
		if (x_pos != std::string::npos)
		{
			numberOfCopies = std::stoi(currentLine.substr(0, x_pos));
			currentCardName = trim(currentLine.substr(x_pos + 1));
			listOfCards.insert({ currentCardName, numberOfCopies });
		}
	}
	return listOfCards;
}

void createFile(std::unordered_map<std::string, size_t> MainDeck) {
	std::ofstream outFile("../CardsToPrint.txt");

	if (outFile.is_open()) {
		for (const auto& cardName : MainDeck) {
			outFile << cardName.first << "\n";
		}
		outFile.close();
		std::cout << "Successfully changed the file" << std::endl;
	}
	else {
		std::cout << "Failed to open the file" << std::endl;
	}
}

void compareTheDecks(std::unordered_map<std::string, size_t> MainDeck, std::unordered_map<std::string, size_t> CurrentDeck) {
	//we make this copy because we are changing the MainDeck while we are iterating through it, which the program doesn't like, so instead we are changing this copy
	std::vector<std::string> keysToRemove;

	for (const auto& card : MainDeck) {
		if (CurrentDeck.find(card.first) != CurrentDeck.end()) {
			while (MainDeck[card.first] != 0) {
				MainDeck[card.first]--;
				CurrentDeck[card.first]--;
				if (CurrentDeck[card.first] == 0) {
					CurrentDeck.erase(card.first);
				}
				if (MainDeck[card.first] == 0) {
					keysToRemove.push_back(card.first);
				}
			}
		}
	}
	for (const auto& key : keysToRemove) {
		MainDeck.erase(key);
	}
	std::cout << "\nThis is for maindeck: " << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------" << std::endl;
	for (const auto& pair : MainDeck) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
	std::cout << "\nThis is for currentDeck: " << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------" << std::endl;
	for (const auto& pair : CurrentDeck) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
	createFile(MainDeck);
}

int main()
{
	//filenames
	std::string MainDeckFileName = "../DeckWeWant.txt";
	std::string CurrentDeckFileName = "../DeckWeHave.txt";

	//creating the lists for the decks
	std::unordered_map<std::string, size_t> listOfCardNamesMainDeck = {};
	std::unordered_map<std::string, size_t> listOfCardNamesCurrentDeck = {};

	listOfCardNamesMainDeck = createTheListOfCardsForDeck(MainDeckFileName);
	listOfCardNamesCurrentDeck = createTheListOfCardsForDeck(CurrentDeckFileName);

	compareTheDecks(listOfCardNamesMainDeck, listOfCardNamesCurrentDeck);
}