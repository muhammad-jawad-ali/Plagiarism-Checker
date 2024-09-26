// Muhammad Jawad Ali       23i-3024

#pragma once
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_WORDS = 1000;
const int MAX_LINE_LENGTH = 1000;
char** UniqueWords = NULL;
int UniqueCount = 0;
int** DocumentFrequency = NULL;
double** Similarities = NULL;

// Function Prototyping
void readInput(const char*);
int getNumberOfDocument();
char* getText(int);
char* getTextFormOrignalDocument(int);
void removePunctuationMarks();
void convertUpperToLowerCase();
void removeStopWords();
int getSizeOfCharArray(char*);
int getSizeOfFile(const char*);
int convertCharArrayToInt(char*);
void fillingStopWords();
void generateFrequencies(char**&, int&, int**&);
int getFrequency(char*, int);   // -1 if not found
void calculateAllCosineSimilarities(double**&, int**);
double similarityIn(int, int);
void printAllVariables();


//Helping Functions
int getSizeOfCharArray(char* arr) {
	int size = 0;
	while (arr[size++] != '\0') {}
	size--;
	return size;
}


int getSizeOfFile(const char* pathOfFile) {
	ifstream file(pathOfFile);
	if (!file.is_open()) {
		cout << "No file opened" << endl;
		return 0;
	}
	char line[MAX_LINE_LENGTH];
	int fileSize = 0;
	while (file.getline(line, MAX_LINE_LENGTH)) {
		fileSize += getSizeOfCharArray(line);
	}


	file.close();
	return fileSize;
}


int convertCharArrayToInt(char* array) {
	int num = 0;
	int i = 0;
	while (array[i] != '\0') {
		num = num * 10 + (array[i] - '0');
		i++;
	}
	return num;

}











// Global Classes and Variables
// Use of classes is must 

// Class to read input from a file
class readInputFileClass {
public:
	char stopWordsLine[MAX_LINE_LENGTH];
	char numberOfDocuments[MAX_LINE_LENGTH];
	int numberOfStopWords;
	char** stopWords;
	int numberOfDocumentsInt;
	char** pathofDocumentFiles;

	readInputFileClass() {
		stopWordsLine[0] = '\0'; // '\0' is same as 'NULL
		numberOfDocuments[0] = '\0';
		numberOfStopWords = 0;
		stopWords = NULL;
		numberOfDocumentsInt = 0;
		pathofDocumentFiles = NULL;
	}
	~readInputFileClass() {
		for (int i = 0; i < numberOfDocumentsInt; i++) {
			delete[] pathofDocumentFiles[i];
		}
		delete[] pathofDocumentFiles;
		for (int i = 0; i < numberOfStopWords; i++) {
			delete[] stopWords[i];
		}
		delete[] stopWords;
	}

};
readInputFileClass readInputFileObj;


class Document {
public:
	char** documents;
	char*** documentWords;
	int** sizeOfEachWord;
	int* numberofWordsInOneDocument;
	int* documentSize;
	int numberOfDocuments;
	Document() {
		sizeOfEachWord = NULL;
		numberofWordsInOneDocument = NULL;
		documentSize = NULL;
		documentWords = NULL;
		documents = NULL;
		numberOfDocuments = 0;
	}
	~Document() {
		for (int i = 0; i < numberOfDocuments; i++) {
			delete[] documents[i];
		}
		delete[] documents;
		for (int i = 0; i < numberOfDocuments; i++) {
			for (int j = 0; j < numberofWordsInOneDocument[i]; j++) {
				delete[] documentWords[i][j];
			}
			delete[] documentWords[i];
		}
		delete[] documentWords;
		for (int i = 0; i < numberOfDocuments; i++) {
			delete[] sizeOfEachWord[i];
		}
		delete[] sizeOfEachWord;
		delete[] numberofWordsInOneDocument;
		delete[] documentSize;

	}
};
Document documentObj;

void fillingStopWords() {
	int n = getSizeOfCharArray(readInputFileObj.stopWordsLine);
	char ch;
	for (int i = 12; i < n; i++) { // Assuming the stop words will start from 12th index
		ch = readInputFileObj.stopWordsLine[i]; // This loop is to count the number of stop words
		while (ch != ' ') {
			i++;
			ch = readInputFileObj.stopWordsLine[i];
		}
		readInputFileObj.numberOfStopWords++;
	}
	readInputFileObj.stopWords = new char* [readInputFileObj.numberOfStopWords];
	int countWords = 0;
	for (int i = 12; i < n; i++) { // Assuming the stop words will start from 12th index
		ch = readInputFileObj.stopWordsLine[i];
		char* word = new char[30]; // Assuming the word will not be more than 30 characters
		int index = 0;
		while (ch != ' ' && i < n) {
			word[index] = ch;
			index++;
			i++;
			ch = readInputFileObj.stopWordsLine[i];
		}
		word[index] = '\0';
		readInputFileObj.stopWords[countWords] = word;
		countWords++;
	}
	readInputFileObj.numberOfStopWords = countWords;
}

void convertDocumentsToWords() {
	int n = getNumberOfDocument();
	documentObj.documentWords = new char** [n];
	documentObj.numberofWordsInOneDocument = new int[n];
	documentObj.sizeOfEachWord = new int* [n];
	for (int i = 0; i < n; i++) {
		int size = documentObj.documentSize[i];
		char* currentDocumentArray = documentObj.documents[i];
		int wordCount = 0;
		for (int j = 0; j < size; j++) {
			if (currentDocumentArray[j] == ' ' || j == (size - 1))
				wordCount++;
		}
		documentObj.documentWords[i] = new char* [wordCount];
		documentObj.sizeOfEachWord[i] = new int[wordCount];
		documentObj.numberofWordsInOneDocument[i] = wordCount;
		int wordIndex = 0;
		int wordSize = 0;
		for (int j = 0; j < size; j++) {
			wordSize = 0;
			while (currentDocumentArray[j] != ' ' && j < size) {
				wordSize++;
				j++;
			}
			char* word = new char[wordSize + 1];
			int index = 0;
			for (int k = j - wordSize; k < j; k++) {
				word[index] = currentDocumentArray[k];
				index++;
			}
			word[index] = '\0';
			documentObj.sizeOfEachWord[i][wordIndex] = wordSize;
			documentObj.documentWords[i][wordIndex] = word;
			wordIndex++;
		}
	}
}


// Function to read input from a file
void readInput(const char* pathofInputFile) {
	ifstream file(pathofInputFile);
	if (!file.is_open()) {
		cout << "No file opened" << endl;
		return;
	}

	file.getline(readInputFileObj.stopWordsLine, MAX_LINE_LENGTH);
	file.getline(readInputFileObj.numberOfDocuments, MAX_LINE_LENGTH);
	readInputFileObj.numberOfDocumentsInt = convertCharArrayToInt(readInputFileObj.numberOfDocuments);  //Using helping function for converting char* array to int

	readInputFileObj.pathofDocumentFiles = new char* [readInputFileObj.numberOfDocumentsInt];
	for (int i = 0; i < readInputFileObj.numberOfDocumentsInt; i++) {
		readInputFileObj.pathofDocumentFiles[i] = new char[MAX_LINE_LENGTH];
		file.getline(readInputFileObj.pathofDocumentFiles[i], MAX_LINE_LENGTH);
	}
	// Filling Object of Document with all documents
	documentObj.numberOfDocuments = readInputFileObj.numberOfDocumentsInt;
	documentObj.documents = new char* [readInputFileObj.numberOfDocumentsInt];
	documentObj.documentSize = new int[readInputFileObj.numberOfDocumentsInt];
	for (int i = 0; i < readInputFileObj.numberOfDocumentsInt; i++) {
		documentObj.documents[i] = getTextFormOrignalDocument(i + 1);
		documentObj.documentSize[i] = getSizeOfFile(readInputFileObj.pathofDocumentFiles[i]);
	}
	file.close();
	fillingStopWords();
	convertDocumentsToWords();
}

int getNumberOfDocument() {
	return documentObj.numberOfDocuments;
}


char* getTextFormOrignalDocument(int documentNumber) {
	ifstream file(readInputFileObj.pathofDocumentFiles[documentNumber - 1]);
	if (!file.is_open()) {
		cout << "No file opened" << endl;
		return NULL;
	}
	char line[MAX_LINE_LENGTH];
	char* text = new char[MAX_WORDS * 30]; // Assuming the word will not be more than 30 characters
	int textIndex = 0;
	while (file.getline(line, MAX_LINE_LENGTH)) {
		int i = 0;
		if (textIndex != 0)
			text[textIndex++] = ' ';
		while (line[i] != '\0') {
			text[textIndex++] = line[i];
			i++;
		}

	}
	text[textIndex] = '\0';
	file.close();
	return text;
}
char* getText(int documentNumber) {
	return documentObj.documents[documentNumber - 1];
}

// Function to remove punctuation marks from documents
void removePunctuationMarks() {
	for (int i = 0; i < documentObj.numberOfDocuments; i++) {
		int size = documentObj.documentSize[i];
		char* array = new char[size + 1];
		int newSize = 0;
		for (int j = 0; j < size; j++) {
			char ch = documentObj.documents[i][j];
			if (ch != '.' && ch != '~' && ch != '!' && ch != '@' && ch != '#' && ch != '$' && ch != '%' && ch != '^' && ch != '&' && ch != '*' && ch != '(' && ch != ')' && ch != '_' && ch != '+' && ch != '=' && ch != '"' && ch != ';' && ch != ':' && ch != '/' && ch != '?' && ch != '>' && ch != ',' && ch != '<' && ch != '\n' && ch != '-' && ch != '[' && ch != '{' && ch != '}' && ch != ']' && ch != '`') {
				if (ch == ' ' && newSize > 0 && array[newSize - 1] == ' ')
					continue;
				else
					if (newSize == 0 && ch == ' ')
						continue;
				array[newSize++] = ch;
			}
		}
		if (array[newSize - 1] == ' ')
			while (array[--newSize] != ' ');
		array[newSize] = '\0';
		delete[] documentObj.documents[i];
		documentObj.documents[i] = array;
		documentObj.documentSize[i] = newSize;

	}


}

// Function to convert all characters in documents to lowercase
void convertUpperToLowerCase() {
	for (int i = 0; i < documentObj.numberOfDocuments; i++) {
		int size = documentObj.documentSize[i];
		for (int j = 0; j < size; j++) {
			char ch = documentObj.documents[i][j];
			if (ch >= 'A' && ch <= 'Z') {
				documentObj.documents[i][j] = ch + 32;
			}
		}
	}
	convertDocumentsToWords();
}

// Function to remove stopwords from documents
void removeStopWords() {
	int n = documentObj.numberOfDocuments;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < documentObj.numberofWordsInOneDocument[i]; j++) {
			for (int k = 0; k < readInputFileObj.numberOfStopWords; k++) {
				if (documentObj.sizeOfEachWord[i][j] == getSizeOfCharArray(readInputFileObj.stopWords[k])) {
					int size = documentObj.sizeOfEachWord[i][j];
					char* word = documentObj.documentWords[i][j];
					char* stopWord = readInputFileObj.stopWords[k];
					int index = 0;
					while (index < size && word[index] == stopWord[index]) {
						index++;
					}
					if (index == size) {
						for (int l = j; l < documentObj.numberofWordsInOneDocument[i] - 1; l++) {
							documentObj.documentWords[i][l] = documentObj.documentWords[i][l + 1];
							documentObj.sizeOfEachWord[i][l] = documentObj.sizeOfEachWord[i][l + 1];
						}
						documentObj.numberofWordsInOneDocument[i]--;
						j--;
					}
				}
			}
		}
	}

	//create new documents
	for (int i = 0; i < n; i++) {
		int size = 0;
		for (int j = 0; j < documentObj.numberofWordsInOneDocument[i]; j++) {
			size += documentObj.sizeOfEachWord[i][j];
		}
		char* array = new char[size + documentObj.numberofWordsInOneDocument[i] + 1];
		int index = 0;
		for (int j = 0; j < documentObj.numberofWordsInOneDocument[i]; j++) {
			for (int k = 0; k < documentObj.sizeOfEachWord[i][j]; k++) {
				array[index++] = documentObj.documentWords[i][j][k];
			}
			if (j != documentObj.numberofWordsInOneDocument[i] - 1)
				array[index++] = ' ';
		}
		array[index] = '\0';
		delete[] documentObj.documents[i];
		documentObj.documents[i] = array;
		documentObj.documentSize[i] = size + documentObj.numberofWordsInOneDocument[i] - 1;
	}

}

void printAllVariables() {
	cout << readInputFileObj.stopWordsLine << endl;
	cout << "Number of Documents: " << readInputFileObj.numberOfDocuments << endl;
	cout << "Number of Stop Words: " << readInputFileObj.numberOfStopWords << endl;
	cout << "Number of Documents Int: " << readInputFileObj.numberOfDocumentsInt << endl;
	cout << "Path of Document Files: " << endl;
	for (int i = 0; i < readInputFileObj.numberOfDocumentsInt; i++) {
		cout << readInputFileObj.pathofDocumentFiles[i] << endl;
	}
	cout << "Documents: " << endl;
	for (int i = 0; i < documentObj.numberOfDocuments; i++) {
		cout << documentObj.documents[i] << endl;
	}
	cout << "Document Size: " << endl;
	for (int i = 0; i < documentObj.numberOfDocuments; i++) {
		cout << documentObj.documentSize[i] << endl;
	}
	cout << "Document Words: " << endl;
	for (int i = 0; i < documentObj.numberOfDocuments; i++) {
		for (int j = 0; j < documentObj.numberofWordsInOneDocument[i]; j++) {
			cout << documentObj.documentWords[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Size of Each Word: " << endl;
	for (int i = 0; i < documentObj.numberOfDocuments; i++) {
		for (int j = 0; j < documentObj.numberofWordsInOneDocument[i]; j++) {
			cout << documentObj.sizeOfEachWord[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Number of Words in One Document: " << endl;
	for (int i = 0; i < documentObj.numberOfDocuments; i++) {
		cout << documentObj.numberofWordsInOneDocument[i] << endl;
	}
	cout << "Number of Documents: " << documentObj.numberOfDocuments << endl;
}

// Function to generate frequencies of each unique word in each document
void generateFrequencies(char**& uniqueWords, int& uniqueCount, int**& documentFrequency) {
	int totalWords = 0;
	for (int i = 0; i < documentObj.numberOfDocuments; i++) {
		totalWords += documentObj.numberofWordsInOneDocument[i];
	}
	uniqueWords = new char* [totalWords];
	documentFrequency = new int* [documentObj.numberOfDocuments];

	for (int i = 0; i < documentObj.numberOfDocuments; i++) {
		documentFrequency[i] = new int[totalWords];
		for (int j = 0; j < totalWords; j++) {
			documentFrequency[i][j] = 0;
		}
	}
	uniqueCount = 0;
	bool isUnique = true;
	for (int i = 0; i < documentObj.numberOfDocuments; i++) {
		for (int j = 0; j < documentObj.numberofWordsInOneDocument[i]; j++) {
			isUnique = true;
			for (int k = 0; k < uniqueCount; k++) {
				bool miniIsUnique = false;
				if (documentObj.sizeOfEachWord[i][j] == getSizeOfCharArray(uniqueWords[k])) {
					for (int l = 0; l < documentObj.sizeOfEachWord[i][j]; l++) {

						if (documentObj.documentWords[i][j][l] != uniqueWords[k][l]) {
							miniIsUnique = true;
							break;
						}
					}

					if (miniIsUnique == false) {
						documentFrequency[i][k]++;
						isUnique = false;
						break;
					}
				}
			}
			if (isUnique == true) {
				uniqueWords[uniqueCount] = documentObj.documentWords[i][j];
				documentFrequency[i][uniqueCount] = 1;
				uniqueCount++;
			}
		}
	}
	UniqueCount = uniqueCount;
	UniqueWords = new char* [uniqueCount];
	for (int i = 0; i < uniqueCount; i++) {
		UniqueWords[i] = new char[30];
		for (int j = 0; j < 30; j++) {
			UniqueWords[i][j] = uniqueWords[i][j];
		}
	}
	DocumentFrequency = new int* [documentObj.numberOfDocuments];

	for (int i = 0; i < documentObj.numberOfDocuments; i++) {
		DocumentFrequency[i] = new int[totalWords];
		for (int j = 0; j < totalWords; j++) {
			DocumentFrequency[i][j] = documentFrequency[i][j];
		}
	}



}

int getFrequency(char* word, int documentNum) { // -1 if not found
	documentNum--;
	int wordSize = getSizeOfCharArray(word);
	for (int i = 0; i < UniqueCount; i++) {
		if (getSizeOfCharArray(UniqueWords[i]) == wordSize) {
			for (int j = 0; j < wordSize; j++) {
				if (word[j] != UniqueWords[i][j]) {
					break;
				}
				if (j == wordSize - 1)
					return DocumentFrequency[documentNum][i];
			}
		}
	}
	return -1;
}

void calculateAllCosineSimilarities(double**& similarities, int** documentFrequency) {
	int n = getNumberOfDocument();
	similarities = new double* [n];
	for (int i = 0; i < n; i++) {
		similarities[i] = new double[n];
	}
	Similarities = new double* [n];
	for (int i = 0; i < n; i++) {
		Similarities[i] = new double[n];
	}
	double ans = 0;
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			if (r > c) {
				int sum = 0;
				double mag1 = 0;
				double mag2 = 0;

				for (int i = 0; i < UniqueCount; i++) {
					sum += DocumentFrequency[r][i] * DocumentFrequency[c][i];
					mag1 += DocumentFrequency[r][i] * DocumentFrequency[r][i];
					mag2 += DocumentFrequency[c][i] * DocumentFrequency[c][i];
				}

				mag1 = sqrt(mag1);
				mag2 = sqrt(mag2);

				ans = round((sum * 10000) / (mag1 * mag2));
				ans /= 100;
				similarities[r][c] = ans;
				similarities[c][r] = ans;

				Similarities[r][c] = ans;
				Similarities[c][r] = ans;
			}
			if (r == c) {
				similarities[r][c] = 100.00;
				Similarities[r][c] = 100.00;
			}
		}
	}

}

double similarityIn(int doucmentNum1, int documentNum2) {
	return Similarities[doucmentNum1 - 1][documentNum2 - 1];
}


//int main() {
//	char** uniqueWords = NULL;
//	int uniqueCount = 0;
//	int** documentFrequency = NULL;
//	readInput("input16.txt");
//	removePunctuationMarks();
//	convertUpperToLowerCase();
//	removeStopWords();
//	generateFrequencies(uniqueWords, uniqueCount, documentFrequency);
//	calculateAllCosineSimilarities(Similarities, DocumentFrequency);
//	printAllVariables();
//
//	//print all similarities
//	cout << "Similarities: " << endl;
//	for (int i = 0; i < getNumberOfDocument(); i++) {
//		for (int j = 0; j < getNumberOfDocument(); j++) {
//			cout << similarityIn(i + 1, j + 1) << "\t";
//		}
//		cout << endl;
//	}
//
//
//
//	return 0;
//}