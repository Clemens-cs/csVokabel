//
//  Dictionary.h
//  csVokabel
//
//  Created by Clemens Sageder on 10.02.21.
//

#ifndef Dictionary_h
#define Dictionary_h

#include <stdio.h>

struct vocable {
    char english[51];
    char german[51];
    struct vocable *next;
};

void trainingVokabeln(int);
void erneuteEingabe(int);
void vokabelTrainer(void);
int readDictionaryFromFile(void);
void safeDictionary(void);
void removeListItem(void);
void showDictionary(void);
void addListItem(void);
struct vocable * allocateMemory(void);
void evaluateUserChoice(char choice);
void showMenuEdit(void);
void clearBuffer(void);
void dictionaryBearbeiten(void);

#endif /* Dictionary_h */
