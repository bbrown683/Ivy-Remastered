#ifndef IVY_FILE_H
#define IVY_FILE_H

#include <iostream>
#include <vector>

class File {
public:
    std::string Read(std::string filePath);

private:

    FILE* m_pFile;
};

#endif // IVY_FILE_H