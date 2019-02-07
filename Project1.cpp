// SpellCheck <Project1.cpp>
// EE w312 Project 1 submission by
// <Amitesh Yeleswarapu>
// <avy89>
// Slip days used: <0>
// Spring 2019

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include <ctype.h>
/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

// counts the number of words in the article
// Makes everything in article lowercase
// and swaps out all non alphabetic characters in article with spaces
// returns number of words.
int numWords(char article[]){

    int iter =0;
    int wordCount =0;
    while(article[iter]!='\0'){
        //printf("iter = %d\n wordcount  = %d\n", iter,wordCount);
        if(isalpha(article[iter])){
            //printf("numwords if\n");
            article[iter] = tolower(article[iter]);
            wordCount++;
            iter++;
            while(article[iter]!=0 && isalpha(article[iter])){
                //printf("numwords if while\n");
                article[iter] = tolower(article[iter]);
                iter++;
            }
        }else{
            //printf("numwords else\n");
            iter++;
            while(article[iter]!=0 && !isalpha(article[iter])){
                //printf("numwords else while\n");
                article[iter] = ' ';
                iter++;
            }
        }

    }
    //printf("end of method\n");
    return wordCount;
}

//printed dictionary for testing
void printDictionary(char dictionary[]){

    int i =0;
    while(dictionary[i]!=0){
        if(dictionary[i]!='\\'){
            printf("%c", dictionary[i]);
        }
        else if(/*dictionary[i+1]!=0 && */dictionary[i+1]=='n'){
            printf("\n");
            i++;
        }
        i++;

    }

}

//printed the entire article for testing
int printArticle(char article[]){
    int i=0;
    char currentLetter = article[i];
    while(currentLetter!=0) {

        if (currentLetter >= 'A' && currentLetter <= 'Z') {
            currentLetter = tolower(currentLetter);
        }
        if (currentLetter >= 97 && currentLetter <= 122) {
            printf("%c", currentLetter);
        } else {
            printf("\n");
        }

        i++;
        currentLetter = article[i];
    }
    return i;
}
//this makes the word position array. wordPositionArray, is an array of integers which correspond
// to the position of the first character of each word in the article
void makeWordPositionArray(char article[], int wordPositions[]){
    //since numWords has already been called everything is lowercase and an alphabet or space
    int iter =0;//position in article
    int pos = 0;//position in wordPosition
    //printf("hello");
    while(article[iter]!=0){
        if(isalpha(article[iter])){
            //printf("iter %d is going in pos %d\n",iter, pos);
            wordPositions[pos]=iter;
            iter++;
            pos++;
            while(article[iter]!=0 && isalpha(article[iter])){
                iter++;
                //will leave loop when article[iter] is a space.
                //printf("if: %d\n", iter);
            }
        }else{
            iter++;
            while(article[iter]!=0 && !isalpha(article[iter])){
                iter++;
                //will leave this loop when article[iter] has some alphabet.
                //printf("el: %d\n", iter);
            }
            //printf("eL: %d\n", iter);
        }
    }
    wordPositions[pos]=iter;//this puts the length of the article in the final spot of the position array
    wordPositions[pos+1]=0;
    //printf("end of makewordpositionarray");
}

//longestWord returns the length of the longest word in the article
int longestWord(int wordPositions[], int numwords){

    int max = 0;
    int iter = 0;
    //printf("longest word\n");
    while(iter<numwords-1){
        if(wordPositions[iter+1]-wordPositions[iter]>max){
            max = wordPositions[iter+1]-wordPositions[iter];
        }

        //printf("%d ", wordPositions[iter]);
        iter++;

    }
    //printf("%d ", wordPositions[iter]);
    //printf("%d ", wordPositions[iter+1]);
    //wordPositions[iter+1]=0;
    //printf("%d, %d", wordPositions[iter+1], max);
    return max;
}
//printMispelledWords uses the wordPositionArray and longestWord to create an array called word containing a single word from the article.
//this word is is then compared to dictionary entries and if it does not exist it is printed out.
//the method keeps looping and refilling word[] with the next word in the article until every word is checked.
void printMispelledWords(char article[], char dictionary[], int wordpositions[], int longestWord, int numWordsInArticle) {

    char word[longestWord];
    int wordIter;
    int wordPosIter;
    //int articleIter = wordpositions[wordPosIter];
    int currentWordLength = 0;
    wordPosIter = 0;
    int dictionaryIter;
    int inDictionary;
    //printf("start of printMispelledWords");

    while (wordPosIter < numWordsInArticle) {
        currentWordLength=0;
        wordIter = 0;
        //FIll in word with each word in the loop
        for (int i = wordpositions[wordPosIter]; i < wordpositions[wordPosIter + 1]; i++) {
            char c = article[i];
            if (isalpha(c)) {
                word[wordIter] = c;
                currentWordLength++;
                //printf("%c\n", word[wordIter]);
            } else {
                word[wordIter] = '\0';
                //printf("%c\n", word[wordIter]);

            }
            //printf("%c", word[wordIter]);
            wordIter++;
        }

        wordPosIter++;
        while (wordIter < longestWord) {
            word[wordIter] = '\0';
            wordIter++;
        }
    //}
        /*int a =0;
        while(word[a]!='\0'){
            printf("\n%c", word[a]);
            a++;
        }
        printf("\n");
        setbuf(stdout, 0);
        */
        //this is the part where you compare word to each entry in the dictionary and see if it is in it. remember the dictionary is in alphabetical order.
        dictionaryIter = 0;//dictionary entries end in \n. to get to the next entry loop until seeing \ then add 2.
        wordIter = 0;// stop iterating when you see a \0 value in word
        inDictionary = 0; //False is 0; true is 1
        if(currentWordLength!=1) {
            while (dictionary[dictionaryIter] != 0 && inDictionary == 0) {
                //printf("%c\n%d\n", dictionary[dictionaryIter], word[wordIter]);
                if (word[wordIter] == '\0' && dictionary[dictionaryIter] == '\n') {
                    inDictionary = 1;
                } else if (word[wordIter] != tolower(dictionary[dictionaryIter]) ||
                           (word[wordIter] == '\0') != (dictionary[dictionaryIter] == '\n')) {
                    while (dictionary[dictionaryIter] != '\n') {
                        dictionaryIter++;
                    }
                    dictionaryIter += 1;// this should put the dictionary iterator on the next word
                    wordIter = 0;
                } else {
                    dictionaryIter++;
                    wordIter++;
                }
            }
            if (word[wordIter] == '\0' && dictionary[dictionaryIter] == '\n') {
                inDictionary = 1;}

            if (inDictionary == 0) {
                //printf("\n");
                wordIter = 0;
                while (word[wordIter] != '\0') {
                    printf("%c", word[wordIter]);
                    wordIter++;
                }
                printf("\n");
            }
        }

    }
//it is printing but it is a null value so it does not show up. it is a null because in the loop when you fill in the word array you are
//going until it is less than the next wordpos value and the last one is currently a 0 so it does not get filled with any characters, but rather all nulls.


}

//this is the main method which calls on other helper methods.
void spellCheck(char article[], char dictionary[]) {

    //printArticle(article);
    int numWordsInArticle = numWords(article);
    //printf("this is the number of words in the article %d\n", numWordsInArticle);
    numWordsInArticle+=1;
    int wordPositions[numWordsInArticle];//want one more spot to figure out the length of the last word.
    numWordsInArticle-=1;
    makeWordPositionArray(article, wordPositions);

    int longWord = longestWord(wordPositions, numWordsInArticle);
    printMispelledWords(article, dictionary, wordPositions, longWord, numWordsInArticle);

    /*printf("this is the article\n");
    printArticle(article);
    printf("this is the dictionary\n");
    printDictionary(dictionary);*/
    //printf("this is the longest word length: %d", longWord);
    /*
    int i =0;
    printf("printing the word positions array\n[");
    while(i<=numWordsInArticle)
    {
        printf("%d ", wordPositions[i]);
        i++;
    }
    printf("]");

*/
    //printf("\narticle word count = %d\n", numWordsInArticle);

    //printf("\ndictionary starts here\n");
    //printDictionary(dictionary);
    //printf("longest word = %d", Longest);
}








