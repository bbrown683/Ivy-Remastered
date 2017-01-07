#include <iostream>
#include <vector>

class File {
public:
    std::string Read(std::string filePath);

private:

    FILE* m_pFile;
};