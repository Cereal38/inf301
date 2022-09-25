
#include "asserts.h"
#include "ressources.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void testAll() {

	char str1[100];
	char str2[100];
	char* str3 = (char*) malloc(100 * sizeof(char));
	char c;


	printf("TEST [");


	// capitalize
	strcpy(str1, "abc");
	assert(strcmp(capitalize(str1), "ABC") == 0);
	printf("#");

	
	// deleteFirstChar
	strcpy(str1, "abc");
	deleteFirstChar(str1);
	assert(strcmp(str1, "bc") == 0);
	printf("#");
	

	// concatenateFromRight
	strcpy(str1, "abc");
	strcpy(str2, "defg");
	concatenateFromRight(str1, str2);
	assert(strcmp(str1, "abcdefg") == 0);
	printf("#");


	// concatenateFromLeft
	strcpy(str1, "abc");
	strcpy(str2, "defg");
	concatenateFromLeft(str1, str2);
	assert(strcmp(str1, "defgabc") == 0);
	strcpy(str1, "abc");
	strcpy(str2, "d");
	concatenateFromLeft(str1, str2);
	assert(strcmp(str1, "dabc") == 0);
	printf("#");


	// lenString
	strcpy(str1, "abc");
	assert(lenString(str1) == 3);
	printf("#");


	// copyLastChars
	strcpy(str1, "abc");
	strcpy(str2, "defg");
	copyLastChars(str1, str2, 2);
	assert(strcmp(str1, "fg") == 0);
	printf("#");


	// indexPreviousChar
	strcpy(str1, "abc");
	assert(indexPreviousChar(str1, 'a') == 2);
	assert(indexPreviousChar(str1, 'b') == 0);
	assert(indexPreviousChar(str1, 'z') == -1);
	printf("#");


	// indexNextChar
	strcpy(str1, "abc");
	assert(indexNextChar(str1, 'a') == 1);
	assert(indexNextChar(str1, 'c') == 0);
	assert(indexNextChar(str1, 'z') == -1);
	printf("#");


	// popFirstChar
	strcpy(str1, "abc");
	c = popFirstChar(str1);
	assert(c == 'a');
	assert(strcmp(str1, "bc") == 0);
	printf("#");


	// moveCharToEnd
	strcpy(str1, "abcdefg");
	c = 'd';
	moveCharToEnd(str1, c);
	assert(strcmp(str1, "abcefgd") == 0);
	strcpy(str1, "abcdefg");
	c = 'g';
	moveCharToEnd(str1, c);
	assert(strcmp(str1, "abcdefg") == 0);
	strcpy(str1, "abcdefg");
	c = 'h';
	moveCharToEnd(str1, c);
	assert(strcmp(str1, "abcdefg") == 0);
	printf("#");


	// isCharInString
	strcpy(str1, "abc");
	assert(isCharInString(str1, 'a') == 1);
	assert(isCharInString(str1, 'b') == 1);
	assert(isCharInString(str1, 'c') == 1);
	assert(isCharInString(str1, 'd') == 0);
	printf("#");


	// appendChar
	strcpy(str1, "abc");
	appendChar(str1, 'd');
	assert(strcmp(str1, "abcd") == 0);
	strcpy(str1, "");
	appendChar(str1, 'a');
	assert(strcmp(str1, "a") == 0);
	printf("#");


	// clearString
	strcpy(str1, "abc");
	clearString(str1, 3);
	assert(strcmp(str1, "") == 0);
	printf("#");


	// deleteFirstLines
	strcpy(str1, "abc\ndef\nghi\njkl");
	str3 = deleteFirstLines(str1, 2);
	assert(strcmp(str3, "ghi\njkl") == 0);
	strcpy(str1, "abc\ndef\nghi\njkl");
	str3 = deleteFirstLines(str3, 0);
	assert(strcmp(str1, "abc\ndef\nghi\njkl") == 0);
	strcpy(str1, "abc\ndef\nghi\njkl");
	printf("#");


	// cutString
	strcpy(str1, "abcdef");
	cutString(str1, 2, 4);
	assert(strcmp(str1, "cde") == 0);
	strcpy(str1, "abcdef");
	cutString(str1, 0, 0);
	assert(strcmp(str1, "a") == 0);
	strcpy(str1, "abcdef");
	cutString(str1, 3, 5);
	assert(strcmp(str1, "def") == 0);
	printf("#");


	// cesarDecodeChar
	c = 'g';
	assert(cesarDecodeChar(c, 5) == 'b');
	c = 'G';
	assert(cesarDecodeChar(c, 1) == 'F');
	c = 'B';
	assert(cesarDecodeChar(c, 5) == 'W');
	c = 'b';
	assert(cesarDecodeChar(c, -3) == 'e');
	c = 'b';
	assert(cesarDecodeChar(c, -26) == 'b');
	printf("#");


	// cesarDecodeString
	strcpy(str1, "Gtg");
	cesarDecodeString(str1, 5);
	assert(strcmp(str1, "Bob") == 0);
	strcpy(str1, "Gtg");
	cesarDecodeString(str1, -1);
	assert(strcmp(str1, "Huh") == 0);
	strcpy(str1, "Gtg");
	cesarDecodeString(str1, 26);
	assert(strcmp(str1, "Gtg") == 0);
	printf("#");


	// encrypteMove
	strcpy(str1, "Petit message court.");
	encrypteMove(str1);
	assert(strcmp(str1, "Pee ct mosusriae.ttg") == 0);
	printf("#");


	// decrypteMove
	strcpy(str1, "Pee ct mosusriae.ttg");
	decrypteMove(str1);
	assert(strcmp(str1, "Petit message court.") == 0);
	printf("#");


	// encrypteSeq
	strcpy(str1, "abcbcca");
	encrypteSeq(str1);
	assert(strcmp(str1, "abcaabc") == 0);
	printf("#");
	

	// decrypteSeq
	strcpy(str1, "abcaabc");
	decrypteSeq(str1);
	assert(strcmp(str1, "abcbcca") == 0);
	printf("#");
	

	printf("]\n\n");
	printf("#######################\n");
	printf("### ALL TEST PASSED ###\n");
	printf("#######################\n\n");

}
