#pragma once

#undef uuid_t
typedef unsigned char uuid_t[16];

char *uuid_to_string(uuid_t uuid);
