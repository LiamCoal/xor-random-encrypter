//
// Created by liamcoal on 9/24/19.
//

#include <random>
#include "Archiver.h"

Archiver::Archiver() {
    srandom(time(nullptr));
    for (long & i : randomseeds) {
        i = random();
    }
    filename = "archive.aiz";
}
Archiver::~Archiver() = default;

void Archiver::compress(FILE *file) {
    if(file == nullptr) return;
    std::string *fdbg = &filename;
    const char *filenamec = fdbg->c_str();
    FILE *f = fopen(filenamec, "w");
    if(f == NULL) {
        remove(filenamec);
        f = fopen(filenamec, "w");
        if(f == NULL) {
            fprintf(stderr, "Error opening file '%s'\n", filenamec);
            exit(1);
        }
    }
    for (long & i : randomseeds) {
        fwrite(&i, sizeof(long), 1, f);
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
