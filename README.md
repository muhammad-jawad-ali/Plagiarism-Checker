# Plagiarism Checker

## Overview
This C++ tool detects plagiarism by calculating textual similarity between documents using **Cosine Similarity**. It preprocesses the text by removing irrelevant content (like stop words and punctuation), generates word frequency vectors, and computes a similarity score between the documents.

## Features
- Text preprocessing: removes punctuation, converts text to lowercase, and eliminates stop words.
- Word frequency analysis: generates frequency vectors for each document.
- Cosine Similarity: calculates similarity between documents, returning a score in percentage.

## Input Files
- **input.txt**: Contains stop words, number of documents, and document paths.
  Example:
- **Documents**: Files listed in `input.txt` are processed and compared.

## Process
1. **Read Input**: Load stop words and documents.
2. **Preprocess**: Remove punctuation, convert to lowercase, and remove stop words.
3. **Frequency Analysis**: Generate word frequency vectors.
4. **Cosine Similarity**: Calculate the similarity score between documents.

## Functions
- `readInput(const char* pathofInputFile)`
- `getNumberOfDocument()`
- `getText(int documentNumber)`
- `removePunctuationMarks()`
- `convertUpperToLowerCase()`
- `removeStopWords()`
- `generateFrequencies(char**& uniqueWords, int& uniqueCount, int**& documentFrequency)`
- `calculateAllCosineSimilarities(double**& similarities, int** documentFrequency)`
- `similarityIn(int documentNum1, int documentNum2)`

## Example
With the input:
- **document1.txt**: "John likes to watch movies. Mary likes movies too."
- **document2.txt**: "Mary also likes to watch football games."
- Output: Cosine Similarity between document 1 and document 2: 53.94%


## How to Run
1. Place `input.txt` and document files in the project folder.
2. Compile and run the program.
3. View similarity scores in the console.

## License
This project is part of a university assignment for **FAST NUCES** (Fall 2024) and is intended for academic purposes.
