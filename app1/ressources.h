
typedef struct Head {
	int len;
	struct Node *first;
	struct Node *last;
} Head;

typedef struct Node {
	char data;
	struct Node *next;
	struct Node *prev;
} Node;

char* capitalize(char *string);
void deleteFirstChar(char* str);
void concatenateFromRight(char* str1, char* str2);
void concatenateFromLeft(char* str1, char* str2);
int lenString(char* str);
void copyLastChars(char* str1, char* str2, int n);
int indexPreviousChar(char* str, char c);
int indexNextChar(char* str, char c);
char popFirstChar(char* str);
void moveCharToEnd(char* str, char c);
int isCharInString(char* str, char c);
void appendChar(char* str, char c);
void clearString(char* str, int len);
char* deleteFirstLines(char* str, int n);
void cutString(char* str, int start, int end);

char cesarDecodeChar(char c, int shift);
void cesarDecodeString(char *string, int shift);
void encrypteMove(char* str);
void decrypteMove(char* str);
Head decrypteMoveLinkedList(Head * crypted);
void encrypteSeq(char* str);
void decrypteSeq(char* str);
void encrypteAssoc(char* str);
void decrypteAssoc(char* str);

Head initLinkedList(void);
void addNodeStart(Head * head, char data);
void addNodeEnd(Head * head, char data);
void removeNodeStart(Head * head);
void removeNodeEnd(Head * head);
void printLinkedList(Head * head);
