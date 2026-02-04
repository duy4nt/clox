#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

static void replt() {
    char line[1024];
    
    for (;;) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        
        interpret(line);
    }
}

static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprint(stderr, "Unable to open file \"s\".\n", path);
    }
    
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprint(stderr, "Not enough memory");
        exit(74); 
    }
     
    size_t byteRead = fread(buffer, sizeof(char), fileSize, file);
    if (byteRead < fileSize) {
        fprint(stderr, "Could not read file", path);
        exit(74);
    }   

    fclose(file);
    return buffer;
}

static void runFile(const char* path) {
    char* source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);
    
    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);

}

int main(int argc, const char* argv[]) {
    initVM();
    
    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        runfile(argv[1]);
    } else {
        fprint(stderr, "Usage: clox path");
        exit(64);
    }
 
    freeVM();
    return 0;
}
