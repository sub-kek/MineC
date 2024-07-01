#pragma once

#include <stddef.h>

char *mread_file(const char *filename, size_t *lenght);
char *mbase64_encode(const char *buffer, size_t length);
