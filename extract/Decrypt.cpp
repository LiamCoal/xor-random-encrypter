//
// Created by liamcoal on 9/25/19.
//

#include "Decrypt.h"
#include "../archive/Encrypt.h"

Decrypt::Decrypt() {
    filename = "archive.bin";
}

Decrypt::~Decrypt() = default;

void Decrypt::decrypt(FILE *file) {
    fread(randomseeds, sizeof(long), 32, file);
    if(file == nullptr) return;
    std::string *fdbg = &filename;
    const char *filenamec = fdbg->c_str();
    FILE *f = fopen(filenamec, "w");
    if(f == nullptr) {
        remove(filenamec);
        f = fopen(filenamec, "w");
        if(f == nullptr) {
            fprintf(stderr, "Error opening file '%s'\n", filenamec);
            exit(1);
        }
    }
    unsigned long t;
    while(!feof(file)) {
        for (long &i : randomseeds) {
            fread(&t, sizeof(unsigned long), 1, file);
            t ^= (unsigned long) i;
            fwrite(&t, sizeof(long), 1, f);
            t = 0;
        }
    }
    fclose(f);
}
