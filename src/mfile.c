#include "mfile.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

char *mread_file(const char *filename, size_t *length) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *buffer = malloc(file_size);
    fread(buffer, 1, file_size, file);
    fclose(file);
    
    *length = file_size;
    return buffer;
}

char *mbase64_encode(const char *buffer, size_t length) {
    BIO *bio, *b64;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, buffer, length);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bptr);

    char *base64_encoded = malloc(bptr->length + 1);
    memcpy(base64_encoded, bptr->data, bptr->length);
    base64_encoded[bptr->length] = '\0';

    BIO_free_all(bio);

    return base64_encoded;
}
