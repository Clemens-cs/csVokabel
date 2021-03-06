//
//  Dictionary.c
//  csVokabel
//
//  Created by Clemens Sageder on 10.02.21.
//

#include "Dictionary.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

struct vocable * first = NULL;
struct vocable * current = NULL;

void trainingVokabeln(int count) {
    printf("Das Wörterbuch enthält %d %s\n", count, (count == 1) ? "Eintrag":"Einträge");
    
    if (!first) {
        return;
    }
    
    int randomNumber;
    int training = 1;
    int i;
    char answer[51];
    int trainingIndex = 0;
    
    srand((unsigned int)time(NULL));
    
    while (training) {
        
        current = first;
        randomNumber = rand() % count + 1;
        
        for (i = 1; i < randomNumber; i++) {
            current = current->next;
        }
        
        printf("Gib die englische Übersetzung ein:\n");
        printf("[No.%d]: %s ", ++trainingIndex, current->german);
        scanf("%s", answer);
        clearBuffer();
        
        if (strcmp(current->english, answer) == 0) {
            puts("Richtig!");
        }
        else{
            puts("Die Antwort war leider falsch, versuche es erneut!");
            erneuteEingabe(trainingIndex);
        }
        
        if (trainingIndex >= 10) {
            trainingIndex = 0;
            printf("Möchtest du weiter machen? (0 = Abbruch) ");
            scanf("%d", &training);
            clearBuffer();
        }
    }
}

void erneuteEingabe(int trainingIndex){
    
    char answer[51];
    
    printf("Gib die englische Übersetzung ein:\n");
    printf("[No.%d]: %s ", trainingIndex, current->german);
    scanf("%s", answer);
    clearBuffer();
    
    if (strcmp(current->english, answer) == 0) {
        puts("Richtig!");
    }
    else{
        puts("Die Antwort war leider falsch, versuche es erneut!");
        erneuteEingabe(trainingIndex);
    }
}

void vokabelTrainer(void){
    int auswahl = -1;
    int count = readDictionaryFromFile();
    
    for (; auswahl != 0; ) {
        puts("___________________________________________");
        puts("Wähle aus, was du machen willst:");
        puts("(0) Vokabeltrainer schließen");
        puts("(1) Vokabeln trainieren");
        puts("(2) Wörterbuch anlegen oder bearbeiten");
        puts("___________________________________________");
        
        scanf("%d", &auswahl);
        clearBuffer();
        
        switch (auswahl) {
            case 1:
                puts("Vokabeln trainieren");
                trainingVokabeln(count);
                break;
            case 2:
                puts("Wörterbuch bearbeiten");
                dictionaryBearbeiten();
                break;
            case 0:
                puts("Der Vokabeltrainer wird geschlossen...");
            default:
                puts("Deine Eingabe ist ungültig!");
                break;
        }
    }
}

int readDictionaryFromFile(void){
    
    FILE *fp = NULL;
    char temp[51];
    int vocableCount = 0;
    
    fp = fopen("dictionary.txt", "r");
    
    if (!fp) {
        return -1;
    }
    
    if (fscanf(fp, "%s", temp) != EOF) {
        
        vocableCount++;
        first = allocateMemory();
        current = first;
        strcpy(current->english, temp);
        fscanf(fp, "%s", temp);
        strcpy(current->german, temp);
        current->next = NULL;
        
        while (fscanf(fp, "%s", temp) != EOF) {
            vocableCount++;
            current->next = allocateMemory();
            current = current->next;
            strcpy(current->english, temp);
            fscanf(fp, "%s", temp);
            strcpy(current->german, temp);
            current->next = NULL;
        }
    }
    
    fclose(fp);
    
    return vocableCount;
}

void safeDictionary(void){
    
    FILE *fp = NULL;
    
    fp = fopen("dictionary.txt", "w");
    
    if (!fp) {
        puts("Die Datei konnte nicht geöffnet werden!\n Das Speichern der Vokabeln ist fehlgeschlagen");
        exit(1);
    }
    
    current = first;
    
    while (current) {
        fprintf(fp, "%s %s\n", current->english, current->german);
        current = current->next;
    }
    
    fclose(fp);
    puts("Das Wörterbuch wurde erfolgreich gespeichert!");
}

void removeListItem(void){
    
    if (!first) {
        puts("Das Wörterbuch hat keine Vokabeln, füge welche mit B hinzu!");
        return;
    }
    
    struct vocable * prev = NULL;
    int removeItem;
    int count = 1;

eingabe:
    
    puts("Welche Vokabel möchtest du entfernen?");
    showDictionary();
    scanf("%d", &removeItem);
    clearBuffer();
    
    if(removeItem < count)
    {
        goto eingabe;
    }
    current = first;
    
    while (count++ < removeItem) {
        prev = current;
        current = current->next;

        
        if (current == NULL){
            puts("Diese Vokabel gibt es nicht!");
            return;
        }
    }
    
    if (prev == NULL) {
        first = current->next;
    }
    else {
        prev->next = current->next;
    }
    
    free(current);
    puts("Die Vokabel wurde aus dem Wörterbuch entfernt.");
    safeDictionary();
}

void showDictionary(void){
    
    if (!first) {
        puts("Das Wörterbuch hat keine Vokabeln, füge welche mit B hinzu!");
        return;
    }
    
    int index = 1;
    current = first;
    
    puts("Hier ist dein Wörterbuch!");
    while (current) {
        printf("No.%d: [%s - %s]\n", index++, current->english, current->german);
        current = current->next;
    }
}

void addListItem(void){
    
    if (!first) {
        first = allocateMemory();
        current = first;
    }
    else {
        current = first;
        
        while (current->next) {
            current = current->next;
        }
        
        current->next = allocateMemory();
        current = current->next;
    }
    
    printf("englisch: ");
    scanf("%s", current->english);
    clearBuffer();
    printf("german: ");
    scanf("%s", current->german);
    clearBuffer();

    current-> next = NULL;
    
    puts("Die Vokabel wurde deinem Wörterbuch erfolgreich hinzugefügt!");
    safeDictionary();
}

struct vocable * allocateMemory(void){
    struct vocable * pVocable = (struct vocable *) malloc(sizeof(struct vocable));
    
    if (!pVocable) {
        puts("Malloc  in ALLOCATEMEMORY hat einen Fehler!");
        exit(1);
    }
    
    return pVocable;
}

void evaluateUserChoice(char choice){
    switch (choice) {
        case 'A':
            puts("Wörterbuch ansehen");
            showDictionary();
            break;
        case 'B':
            puts("Vokabel dem Wörterbuch hinzufügen");
            addListItem();
            break;
        case 'C':
            puts("Vokabel aus dem Wörterbuch entfernen");
            removeListItem();
            break;
        case 'D':
            puts("Wörterbuch speichern");
            safeDictionary();
            break;
        case 'E':
            puts("Bearbeiten beenden");
            break;
        default:
            puts("Die Eingabe ist inkorrekt!");
            break; }
}
    
void showMenuEdit(void){
    puts("___________________________________________");
    puts("Wähle aus, was du machen willst:");
    puts("(A) Wörterbuch ansehen");
    puts("(B) Vokabel dem Wörterbuch hinzufügen");
    puts("(C) Vokabel aus dem Wörterbuch entfernen");
    puts("(D) Wörterbuch speichern");
    puts("(E) Bearbeiten beenden");
    puts("___________________________________________");
}

void clearBuffer(void){
    while (getchar() != '\n'){
        ;
    }
}

void dictionaryBearbeiten(void){
    char choice;
    
    do {
        showMenuEdit();
        choice = getchar();
        clearBuffer();
        choice = toupper(choice);
        evaluateUserChoice(choice);
        
    } while (choice != 'E');
}
