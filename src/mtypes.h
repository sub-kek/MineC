#pragma once

#include <stdlib.h>
#include <stdint.h>

typedef unsigned char UUID[16];

char *uuid_to_string(UUID uuid);
