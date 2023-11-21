#ifndef ASSERT_H
#define ASSERT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void AssertNotNull(void* parameter);
void AssertTypeIs(int type, int expected);
void AssertNotNullCallback(void* parameter, void (*f)());
#endif