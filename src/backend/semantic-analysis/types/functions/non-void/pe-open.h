#ifndef PEOPEN_H
#define PEOPEN_H

typedef enum {
	PE_OPEN_PATH,
	PE_OPEN_ID
} PEOpenType;

typedef struct {
	PEOpenType type;
	char* path;
	char* id;
} PEOpen;

#endif