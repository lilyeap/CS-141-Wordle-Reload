//Lily Eap - UIN: 676977984 - netID: leap2
//Program 3 - Wordle Reload
#include <iostream>  
#include <fstream>   
#include <vector>     
#include <cassert>    
#include <cctype>     
#include <ctime>
#include <algorithm>

using namespace std;

/////////////////////////////////////////////////////////////////////
//////////////////////time functions/////////////////////////////////
/////////////////////////////////////////////////////////////////////
void timeOut(int overTime, int maxTime, int& guess){
  guess--;
  cout << "Your time has expired.  Try again." << endl
    << "  - You are " << overTime << " seconds over the " << maxTime
    << " second time limit." << endl;
}

int checkTime(int startTime, int maxTime){
  int elapsedTime = difftime(time( NULL), startTime);
  if (elapsedTime > maxTime){
    int overTime = elapsedTime - maxTime;
    return overTime;
  } else {
    return 0;
  }
}

/////////////////////////////////////////////////////////////////////
//////////displays the guessed words/////////////////////////////////
/////////////////////////////////////////////////////////////////////
void winGame(int seconds, int userAttempt, int totalAttempt){
  cout << "Nice Work!  You guessed the correct word" << endl
    << "  - You completed the board in: " << seconds << " seconds." << endl
    << "  - It took you " << userAttempt << "/" << totalAttempt << " attempts." << endl << endl;
  
}

void endGame(int guess, int streak, int wordCount, int totaltime){
  int avg = 0;
  
  cout << "Overall Stats:" << endl
    << "  - You guessed: " << guess << endl
    << "  - Your longest streak is: " << streak << endl;
  if (guess != 0){
    avg = totaltime / wordCount;
    cout << "  - Average word completion time: " << avg << endl;
  } else {
    cout << "  - Average word completion time: N/A" << endl;
  }
    cout << "Exiting program" << endl;
}

/////////////////////////////////////////////////////////////////////
//////////displays the guessed words/////////////////////////////////
/////////////////////////////////////////////////////////////////////

void displayBoardThree(char board [3]){
   for(int row = 0; row < 3; row++){
    cout << " [ " << board[row]<< " ] ";
   }
  cout << endl;
}

void displayBoardFive(char board [5]){
   for(int row = 0; row < 5; row++){
    cout << " [ " << board[row]<< " ] ";
   }
  cout << endl;
}

/////////////////////////////////////////////////////////////////////
//////////changes string to all upper/lowercase//////////////////////
/////////////////////////////////////////////////////////////////////

string stringLower(string upTxt){
	for (int i = 0; i < upTxt.length(); i++)
  	{
  		if(upTxt[i] >= 'A' && upTxt[i] <= 'Z')
  		{
  			upTxt[i] = upTxt[i] + 32;
		}
  	}
  	return upTxt;
}

string stringUpper (string lowTxt){
	for (int i = 0; i < lowTxt.length(); i++)
  	{
  		if(lowTxt[i] >= 'A' && lowTxt[i] <= 'Z')
  		{
  			lowTxt[i] = lowTxt[i] - 32;
		}
  	}
  	return lowTxt;
}

/////////////////////////////////////////////////////////////////////
//////////determines what board to output////////////////////////////
/////////////////////////////////////////////////////////////////////

void ans3cout(bool wordFound, bool wordFound2,bool wordFound3,bool wordFound4, char board1[3], char board2[3], char board3[3], char board4[3] ){
  if (wordFound == true){
    displayBoardThree(board1);
  }
  if (wordFound2 == true){
    displayBoardThree(board2);
  }
  if (wordFound3 == true){
    displayBoardThree(board3);
  }
  if (wordFound4 == true){
    displayBoardThree(board4);
  }

}

void ans5cout(bool wordFound, bool wordFound2,bool wordFound3,bool wordFound4,bool wordFound5,bool wordFound6, char board1[5], char board2[5], char board3[5], char board4[5], char board5[5], char board6[5] ){
  if (wordFound == true){
    displayBoardFive(board1);
  }
  if (wordFound2 == true){
    displayBoardFive(board2);
  }
  if (wordFound3 == true){
    displayBoardFive(board3);
  }
  if (wordFound4 == true){
    displayBoardFive(board4);
  }
  if (wordFound5 == true){
    displayBoardFive(board5);
  }
  if (wordFound6 == true){
    displayBoardFive(board6);
  }

}

/////////////////////////////////////////////////////////////////////
//////////checks if the word exists in the wordle list///////////////
/////////////////////////////////////////////////////////////////////

int binarySearchString(string searchWord, vector< string> dictionary){
   int mid;
   int low;
   int high;
   
   low = 0;
   high = dictionary.size() - 1;
   
   while (high >= low) {
      mid = (high + low) / 2;
      int searchResult = searchWord.compare(dictionary[mid]);
      if (searchResult == 0) {
         return mid;
      }
      else if (searchResult < 0) {
         high = mid - 1;
      }
      else {
         low = mid + 1;
      }
   }
   return -1; // not found
}

int checkExists(string word, vector <string> dictionary){
  int result = binarySearchString(word, dictionary);
  if (result == -1){
    return 0;
  }
  else{
    return 1;  
  }
}

/////////////////////////////////////////////////////////////////////
//checks the current game streak and compares it to the best game streak///////////////
/////////////////////////////////////////////////////////////////////

void checkStrk(int& streak, int tempstreak){
  if (streak < tempstreak){
    streak = tempstreak;
  } 
}

/////////////////////////////////////////////////////////////////////
////compares and sets character board according to user input////////
/////////////////////////////////////////////////////////////////////

void compareWord(string wordleWord, string input, char wordAttempt[3]){
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      if (wordleWord[j] == tolower(input[i])){
        wordAttempt[i] = tolower(wordleWord[j]);
      }      
    }
    if (wordleWord[i] == tolower(input[i])){
        wordAttempt[i] = toupper(wordleWord[i]);
      }
}
}

void compare5ltrWord(string wordleWord, string input, char wordAttempt[5]){
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 5; j++){
      if (wordleWord[j] == tolower(input[i])){
        wordAttempt[i] = tolower(wordleWord[j]);
      }      
    }
    if (wordleWord[i] == tolower(input[i])){
        wordAttempt[i] = toupper(wordleWord[i]);
      }
}
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void inputThree(char array[3], int& guess, int& tempstreak, int& streak, int& wordCount, int& totalTime){
  string word, word2, word3, word4;
  vector<string> wordleWords;
  bool gameOn = true;
  char wordAttempt1 [3] = {'*','*','*'};
  char wordAttempt2 [3] = {'*','*','*'};
  char wordAttempt3 [3] = {'*','*','*'};
  char wordAttempt4 [3] = {'*','*','*'};

  int elapsedSeconds = 0;
  time_t startTime = time(NULL);
  
  
  ifstream ifs;
  bool wordFound, wordFound2, wordFound3, wordFound4;
  bool attempt1, attempt2, attempt3;
  wordFound = false;
  wordFound2 = false;
  wordFound3 = false;
  wordFound4 = false;
  attempt1 = false;
  attempt2 = false;
  attempt3 = false;

  cout << "To get started, enter your first 3 letter word." << endl
    << "You have 4 attempts to guess the random word." << endl
    << "The timer will start after your first word entry." << endl
    << "Try to guess the word within 20 seconds." << endl << endl;

////////////////////////////////////////
 // Read in dictionary into dictionary vector
  ifstream inStream;                     
  inStream.open("wordlewords.txt");       
  assert( inStream.fail() == false );    
  wordleWords.clear();

  string newWord;                         
  while( inStream >> newWord) {          
    if (newWord.size() == 3){
      wordleWords.push_back(newWord);
    }  
  }
  inStream.close();
////////////////////////////////////////
  vector<string> wordle3ltrWords;                  
  inStream.open("wordlewords.txt");       
  assert( inStream.fail() == false );    
  wordle3ltrWords.clear();

  string ltr3wrd;                         
  while( inStream >> ltr3wrd) {      
    wordle3ltrWords.push_back(ltr3wrd);
  }
  inStream.close();

 // Randomizes the word
  int wordIDX = 0;
  wordIDX = rand() % 1065;
  string wordleWord = wordle3ltrWords.at(wordIDX);

////////////////////////////////////////////
  int attempts = 0;
  while (gameOn == true){
    /////////////////
    ////ATTEMPT 1////
    /////////////////
    guess++;
    do{
      cout << "Please enter word -->  " << endl;
      cin >> word;
      if (checkTime(startTime, 20) != 0){
        int overT = checkTime(startTime, 20);
        timeOut(overT, 20, guess);
        return;
      }
      if (wordleWord == stringLower(word)){
        attempts++;
        wordAttempt1[0] = toupper(word[0]);
        wordAttempt1[1] = toupper(word[1]);
        wordAttempt1[2] = toupper(word[2]);
        displayBoardThree(wordAttempt1);
        elapsedSeconds = difftime(time( NULL), startTime);
        winGame(elapsedSeconds, attempts, 4);
        tempstreak++;
        checkStrk(streak, tempstreak);
        wordCount++;
        return;
      }
      if (word.size() == 3){
        ////check if the word is playable///
        if ((checkExists(stringLower(word), wordleWords)) == 1){
            wordFound = true;
          }
        /////////
        if (wordFound == true){
          attempts++;
          compareWord(wordleWord, word, wordAttempt1);
          ans3cout(wordFound, wordFound2, wordFound3, wordFound4, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4);
          attempt1 = true;
        } else {
          cout << "Not a playable word, please select another word." << endl;
          continue;
        }
      
      } else {
        cout << "Invalid word entry - please enter a word that is 3 characters long." <<     endl;
        continue;
      }
    } while (attempt1 == false);
    /////////////////
    ////ATTEMPT 2////
    /////////////////
    do{
      cout << "Please enter word -->  " << endl;
      cin >> word2;
      if (checkTime(startTime, 20) != 0){
        int overT = checkTime(startTime, 20);
        timeOut(overT, 20, guess);
        return;
      }
      if (word2.size() == 3){
        ////check if the word is playable///
        if ((checkExists(stringLower(word2), wordleWords)) == 1){
            wordFound2 = true;
          }
        /////////
        if (wordFound2 == true){
          attempts++;
          compareWord(wordleWord, word2, wordAttempt2);
          if (wordleWord == stringLower(word2)){
            wordAttempt2[0] = toupper(word2[0]);
            wordAttempt2[1] = toupper(word2[1]);
            wordAttempt2[2] = toupper(word2[2]);
            ans3cout(wordFound, wordFound2, wordFound3, wordFound4, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4);
            elapsedSeconds = difftime(time( NULL), startTime);
            winGame(elapsedSeconds, attempts, 4);
            tempstreak++;
            checkStrk(streak, tempstreak);
            wordCount++;
            totalTime = totalTime + elapsedSeconds;
            return;
          } else {
            ans3cout(wordFound, wordFound2, wordFound3, wordFound4, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4);
            attempt2 = true;
          }
        } else {
          cout << "Not a playable word, please select another word." << endl;
          continue;
        }
        
      } else {
        cout << "Invalid word entry - please enter a word that is 3 characters long." <<     endl;
        continue;
      }
    } while (attempt2 == false);
  ///////////////////////////////////////////////////////////
    do{
      cout << "Please enter word -->  " << endl;
      cin >> word3;
      if (checkTime(startTime, 20) != 0){
        int overT = checkTime(startTime, 20);
        timeOut(overT, 20, guess);
        return;
      }
      if (word3.size() == 3){
        ////check if the word is playable///
        if ((checkExists(stringLower(word3), wordleWords)) == 1){
            wordFound3 = true;
          }
        /////////
        if (wordFound3 == true){
          attempts++;
          compareWord(wordleWord, word3, wordAttempt3);
          if (wordleWord == stringLower(word3)){
            wordAttempt3[0] = toupper(word3[0]);
            wordAttempt3[1] = toupper(word3[1]);
            wordAttempt3[2] = toupper(word3[2]);
            ans3cout(wordFound, wordFound2, wordFound3, wordFound4, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4);
            elapsedSeconds = difftime(time( NULL), startTime);
            winGame(elapsedSeconds, attempts, 4);
            tempstreak++;
            checkStrk(streak, tempstreak);
            wordCount++;
            totalTime = totalTime + elapsedSeconds;
            return;
          } else {
            ans3cout(wordFound, wordFound2, wordFound3, wordFound4, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4);
            attempt3 = true;
          }
        } else {
          cout << "Not a playable word, please select another word." << endl;
          continue;
        }
      } else {
        cout << "Invalid word entry - please enter a word that is 3 characters long." <<     endl;
        continue;
      }
    } while (attempt3 == false);
  /////////////////////////////////////////////
    cout << "Please enter word -->  " << endl;
    cin >> word4;
    if (checkTime(startTime, 20) != 0){
        int overT = checkTime(startTime, 20);
        timeOut(overT, 20, guess);
        return;
      }
    if (word4.size() == 3){
      ////check if the word is playable///
      if ((checkExists(stringLower(word4), wordleWords)) == 1){
          wordFound4 = true;
        }
      /////////
      if (wordFound4 == true){
        attempts++;
        if (word4.size() == 3){
        compareWord(wordleWord, word4, wordAttempt4);
        if (wordleWord == stringLower(word4)){
          wordAttempt4[0] = toupper(word4[0]);
          wordAttempt4[1] = toupper(word4[1]);
          wordAttempt4[2] = toupper(word4[2]);
          ans3cout(wordFound, wordFound2, wordFound3, wordFound4, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4);
          elapsedSeconds = difftime(time( NULL), startTime);
          winGame(elapsedSeconds, attempts, 4);
          tempstreak++;
          checkStrk(streak, tempstreak);
          wordCount++;
          totalTime = totalTime + elapsedSeconds;
          break;
        } else {
          ans3cout(wordFound, wordFound2, wordFound3, wordFound4, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4);
          cout << "Maximum amount of attempts have been reached. Try again." << endl;
          guess--;
          tempstreak = 0;
          break;
        }
      } else {
        cout << "Not a playable word, please select another word." << endl;
      }  
    } else {
      cout << "Invalid word entry - please enter a word that is 3 characters long." <<     endl;
    }
    ////tabbed////
  }

}
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

void inputFive(char array[5], int& guess, int& tempstreak, int& streak, int& wordCount, int& totalTime){
  string word, word2, word3, word4, word5, word6;
  vector<string> wordleWords;
  bool gameOn = true;
  // time_t startTime = time( NULL);
  char wordAttempt1 [5] = {'*','*','*','*','*'};
  char wordAttempt2 [5] = {'*','*','*','*','*'};
  char wordAttempt3 [5] = {'*','*','*','*','*'};
  char wordAttempt4 [5] = {'*','*','*','*','*'};
  char wordAttempt5 [5] = {'*','*','*','*','*'};
  char wordAttempt6 [5] = {'*','*','*','*','*'};

  int elapsedSeconds = 0;
  time_t startTime = time(NULL);
  
  ifstream ifs;
  bool wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6;
  bool attempt1, attempt2, attempt3, attempt4, attempt5;
  wordFound = false;
  wordFound2 = false;
  wordFound3 = false;
  wordFound4 = false;
  wordFound5 = false;
  wordFound6 = false;
  attempt1 = false;
  attempt2 = false;
  attempt3 = false;
  attempt4 = false;
  attempt5 = false;



  cout << "To get started, enter your first 5 letter word." << endl
    << "You have 6 attempts to guess the random word." << endl
    << "The timer will start after your first word entry." << endl
    << "Try to guess the word within 40 seconds." << endl << endl;
  
  // elapsedSeconds = difftime(time(NULL), startTime);
  // if (elapsedSeconds == 0){
  //   timeOut(elapsedSeconds);
  //   break;
  // }

////////////////////////////////////////

 // Read in dictionary into dictionary vector
  ifstream inStream;                     
  inStream.open("wordlewords.txt");       
  assert( inStream.fail() == false );    
  wordleWords.clear();

  string newWord;                         
  while( inStream >> newWord) {      
    if (newWord.size() == 5){
      wordleWords.push_back(newWord);
    }
  }
  inStream.close();
////////////////////////////////////////
  vector<string> wordle5ltrWords;                  
  inStream.open("wordlewords.txt");       
  assert( inStream.fail() == false );    
  wordle5ltrWords.clear();

  string ltr5wrd;                         
  while( inStream >> ltr5wrd) {      
    wordle5ltrWords.push_back(ltr5wrd);
  }
  inStream.close();
  
  
 // Randomizes the word
  int wordIDX = 0;
  wordIDX = rand() % 2499 + 1065 ;  
  string wordleWord = wordle5ltrWords.at(wordIDX);

////////////////////////////////////////////
  
  int attempts =0;
  while (gameOn == true){
    /////////////////
    ////ATTEMPT 1////
    /////////////////
    guess++;

    do{
      cout << "Please enter word -->  " << endl;
      cin >> word;
      if (checkTime(startTime, 40) != 0){
        int overT = checkTime(startTime, 40);
        timeOut(overT, 40, guess);
        return;
      }
      if (wordleWord == stringLower(word)){
        attempts++;
        wordAttempt1[0] = toupper(word[0]);
        wordAttempt1[1] = toupper(word[1]);
        wordAttempt1[2] = toupper(word[2]);
        wordAttempt1[3] = toupper(word[3]);
        wordAttempt1[4] = toupper(word[4]);
        displayBoardFive(wordAttempt1);
        elapsedSeconds = difftime(time( NULL), startTime);
        winGame(elapsedSeconds, attempts, 6);
        tempstreak++;
        checkStrk(streak, tempstreak);
        wordCount++;
        totalTime = totalTime + elapsedSeconds;
        return;
      }
      if (word.size() == 5){
        ////check if the word is playable///
        if ((checkExists(stringLower(word), wordleWords)) == 1){
          wordFound = true;
        }
        /////////
        if (wordFound == true){
          attempts++;
          compare5ltrWord(wordleWord, word, wordAttempt1);
          ans5cout(wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4, wordAttempt5, wordAttempt6);
          attempt1 = true;
        } else {
          cout << "Not a playable word, please select another word." << endl;
          continue;
        }
      
      } else {
        cout << "Invalid word entry - please enter a word that is 5 characters long." <<     endl;
        continue;
      }
    } while (attempt1 == false);
  ///////////////////////////////////////////////
    /////////////////
    ////ATTEMPT 2////
    /////////////////
    do{
      cout << "Please enter word -->  " << endl;
      cin >> word2;
      if (checkTime(startTime, 40) != 0){
        int overT = checkTime(startTime, 40);
        timeOut(overT, 40, guess);
        return;
      }
      if (word2.size() == 5){
        ////check if the word is playable///
        if ((checkExists(stringLower(word2), wordleWords)) == 1){
          wordFound2 = true;
        }
        /////////
        if (wordFound2 == true){
          attempts++;
          compare5ltrWord(wordleWord, word2, wordAttempt2);
          if (wordleWord == stringLower(word2)){
            wordAttempt2[0] = toupper(word2[0]);
            wordAttempt2[1] = toupper(word2[1]);
            wordAttempt2[2] = toupper(word2[2]);
            wordAttempt5[3] = toupper(word5[3]);
            wordAttempt5[4] = toupper(word5[4]);
            ans5cout(wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4, wordAttempt5, wordAttempt6);
            elapsedSeconds = difftime(time( NULL), startTime);
            winGame(elapsedSeconds, attempts, 6);
            tempstreak++;
            checkStrk(streak, tempstreak);
            wordCount++;
            totalTime = totalTime + elapsedSeconds;
            return;
          } else {
            ans5cout(wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4, wordAttempt5, wordAttempt6);
            attempt2 = true;
          }
        } else {
          cout << "Not a playable word, please select another word." << endl;
          continue;
        }
        
      } else {
        cout << "Invalid word entry - please enter a word that is 5 characters long." <<     endl;
        continue;
      }
    } while (attempt2 == false);
  ///////////////////////////////////////////////////////////
    do{
      cout << "Please enter word -->  " << endl;
      cin >> word3;
      if (checkTime(startTime, 40) != 0){
        int overT = checkTime(startTime, 40);
        timeOut(overT, 40, guess);
        return;
      }
      if (word3.size() == 5){
        ////check if the word is playable///
        if ((checkExists(stringLower(word3), wordleWords)) == 1){
          wordFound3 = true;
        }
        /////////
        if (wordFound3 == true){
          if (word3.size() == 5){
            attempts++;
            compare5ltrWord(wordleWord, word3, wordAttempt3);
          }
          if (wordleWord == stringLower(word3)){
            wordAttempt3[0] = toupper(word3[0]);
            wordAttempt3[1] = toupper(word3[1]);
            wordAttempt3[2] = toupper(word3[2]);
            wordAttempt5[3] = toupper(word5[3]);
            wordAttempt5[4] = toupper(word5[4]);
            ans5cout(wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4, wordAttempt5, wordAttempt6);
            elapsedSeconds = difftime(time( NULL), startTime);
            winGame(elapsedSeconds, attempts, 6);
            tempstreak++;
            checkStrk(streak, tempstreak);
            wordCount++;
            totalTime = totalTime + elapsedSeconds;
            return;
          } else {
            ans5cout(wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4, wordAttempt5, wordAttempt6);            
            attempt3 = true;
            
          }
        } else {
          cout << "Not a playable word, please select another word." << endl;
          continue;
        }
      } else {
        cout << "Invalid word entry - please enter a word that is 5 characters long." <<     endl;
        continue;
      }
    } while (attempt3 == false);
  /////////////////////////////////////////////
    do{
      cout << "Please enter word -->  " << endl;
      cin >> word4;
      if (checkTime(startTime, 40) != 0){
        int overT = checkTime(startTime, 40);
        timeOut(overT, 40, guess);
        return;
      }
      if (word4.size() == 5){
        ////check if the word is playable///
        if ((checkExists(stringLower(word4), wordleWords)) == 1){
          wordFound4 = true;
        }
        /////////
        if (wordFound4 == true){
          if (word4.size() == 5){
            attempts++;
            compare5ltrWord(wordleWord, word4, wordAttempt4);
          }
          if (wordleWord == stringLower(word4)){
            wordAttempt4[0] = toupper(word4[0]);
            wordAttempt4[1] = toupper(word4[1]);
            wordAttempt4[2] = toupper(word4[2]);
            wordAttempt5[3] = toupper(word5[3]);
            wordAttempt5[4] = toupper(word5[4]);
            ans5cout(wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4, wordAttempt5, wordAttempt6);\
            elapsedSeconds = difftime(time( NULL), startTime);
            winGame(elapsedSeconds, attempts, 6);
            tempstreak++;
            checkStrk(streak, tempstreak);
            wordCount++;
            totalTime = totalTime + elapsedSeconds;
            return;
          } else {
            ans5cout(wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4, wordAttempt5, wordAttempt6);
            attempt4 = true;
          }
        } else {
          cout << "Not a playable word, please select another word." << endl;
          continue;
        }  
      } else {
        cout << "Invalid word entry - please enter a word that is 5 characters long." <<     endl;
        continue;
      }
    } while (attempt4 == false);
  ///////////////////////////////////////////////////////////
    do{
      cout << "Please enter word -->  " << endl;
      cin >> word5;
      if (checkTime(startTime, 40) != 0){
        int overT = checkTime(startTime, 40);
        timeOut(overT, 40, guess);
        return;
      }
      if (word5.size() == 5){
        ////check if the word is playable///
        if ((checkExists(stringLower(word5), wordleWords)) == 1){
          wordFound5 = true;
        }
        /////////
        if (wordFound5 == true){
          compare5ltrWord(wordleWord, word5, wordAttempt5);
          if (wordleWord == stringLower(word5)){
            wordAttempt5[0] = toupper(word5[0]);
            wordAttempt5[1] = toupper(word5[1]);
            wordAttempt5[2] = toupper(word5[2]);
            wordAttempt5[3] = toupper(word5[3]);
            wordAttempt5[4] = toupper(word5[4]);
            ans5cout(wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4, wordAttempt5, wordAttempt6);
            elapsedSeconds = difftime(time( NULL), startTime);
            winGame(elapsedSeconds, attempts, 6);
            tempstreak++;
            checkStrk(streak, tempstreak);
            wordCount++;
            totalTime = totalTime + elapsedSeconds;
            return;
          } else {
            ans5cout(wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4, wordAttempt5, wordAttempt6);
            attempt5 = true;
          }
        } else {
          cout << "Not a playable word, please select another word." << endl;
          continue;
        }
      } else {
        cout << "Invalid word entry - please enter a word that is 5 characters long." <<     endl;
        continue;
      }
    } while (attempt5 == false);
  ///////////////////////////////////////////////////////////
    cout << "Please enter word -->  " << endl;
    cin >> word6;
    if (checkTime(startTime, 40) != 0){
        int overT = checkTime(startTime, 40);
        timeOut(overT, 40, guess);
        return;
      }
    if (word6.size() == 5){
      ////check if the word is playable///
      if ((checkExists(stringLower(word6), wordleWords)) == 1){
        wordFound6 = true;
      }
      /////////
      if (wordFound6 == true){
        attempts++;
        compare5ltrWord(wordleWord, word6, wordAttempt6);
        if (wordleWord == stringLower(word6)){
          wordAttempt6[0] = toupper(word6[0]);
          wordAttempt6[1] = toupper(word6[1]);
          wordAttempt6[2] = toupper(word6[2]);
          wordAttempt6[3] = toupper(word6[3]);
          wordAttempt6[4] = toupper(word6[4]);
          ans5cout(wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4, wordAttempt5, wordAttempt6);
          elapsedSeconds = difftime(time( NULL), startTime);
          winGame(elapsedSeconds, attempts, 6);
          tempstreak++;
          checkStrk(streak, tempstreak);
          wordCount++;
          totalTime = totalTime + elapsedSeconds;
          return;
        } else {
          ans5cout(wordFound, wordFound2, wordFound3, wordFound4, wordFound5, wordFound6, wordAttempt1, wordAttempt2, wordAttempt3, wordAttempt4, wordAttempt5, wordAttempt6);
          cout << "Maximum amount of attempts have been reached. Try again." << endl;
          guess--;
          tempstreak = 0;
          break;
        }
      } else {
        cout << "Maximum amount of attempts have been reached. Try again." << endl;
        guess--;
        tempstreak = 0;
        break;
      }
    } else {
      cout << "Maximum amount of attempts have been reached. Try again." << endl;
      guess--;
      tempstreak = 0;
      break;
    }
  /////////////////////////////////////////////
    ////tabbed////
  }
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

int main()
{
	char boardThree [3]=
    {' ', ' ', ' '};
  char boardFive [5] =
    {' ', ' ', ' ', ' ', ' '};
   
	vector<string> dictionary = {"enter", "hello", "mixed", "shift","world"};
	
	int task;
	
	cout << "Program 3: Wordle Reload" << endl
	    << "CS 141, Spring 2022, UIC" << endl << endl
	    << "The objective of this game is to guess the randomly selected word within a given number of attempts. You can select either a three or five word board." << endl
	    << "At the conlusion of the game, stats will be displayed. Indicators will be given if characters of the user entered word are reflected in the guessed word." << endl
      << "  - If the character is in the correct position, the character will display as an uppercase value." << endl
      << "  - If the character is within the random word, the character will display as a lowercase value." << endl
      << "  - If you enter a character that is not in the word, an asterisk '*' will display." << endl << endl;

  bool play;
  int guess = 0;
  int tempstrk = 0;
  int strk = 0;
  int wordComplete = 0;
  int totaltime = 0;
  srand(1);

  play = true;
  do {
    cout << "Select a menu option:" << endl
    << "   1. To play Wordle Reload 3 letter play" << endl
    << "   2. To play Wordle Reload 5 letter play" << endl
    << "   3. Exit the program" << endl
    << "Your choice --> ";

  	cin >> task;
  	if (task == 1){
  	  inputThree(boardThree, guess, tempstrk, strk, wordComplete, totaltime);
      continue;
  	}
  	else if (task == 2){
  	  inputFive(boardFive, guess, tempstrk, strk, wordComplete, totaltime);
      continue;
  	}
  	else if (task == 3){
      endGame(guess, strk, wordComplete, totaltime);
      // cout << " false";
  	  play = false;
    }
  } while(play);	
}


