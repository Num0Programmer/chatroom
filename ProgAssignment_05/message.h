#include <stdlib.h>


#ifndef MESSAGE_H
#define MESSAGE_H


/* structures */
struct note
{
	char usernamen[16];
	char sentence[64];
	uint8_t length;
};


/* function prototypes */
void note_init(struct note* n);


/* preprocessor definitions */


#endif /* MESSAGE_H */

