#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>

#include "../base/defs.h"
#include "../base/Types.h"
#include "../headers/fontcli.h"
#include "../base/Base.h"
#include "../base/General.h"

class FuzzFile: public File {
    public: 
        FuzzFile(char* a) : File(a) {

        }
        
        void setData(const uint8_t *Data, size_t Size) {
            if (this->EP) {
                free(this->EP);
            }
            this->data = (char*) malloc(Size);
            memcpy(this->data, Data, Size);
            this->EP = this->data;
            this->LP = this->data + (Size - 1);
            this->size = Size;
        }
};

FuzzFile file("dummy_file");

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // std::ofstream binFile("tmp.bin", std::ios::out | std::ios::binary);
    // binFile.write((char*)Data, Size);
    // binFile.close();

    file.setData(Data, Size);

    // File file("tmp.bin");
	Syntax syntax(&file);
	syntax.scan();

    return 0;
}