#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

size_t readFileToVector(std::istream& file, std::vector<char>& buf)
{
     file.seekg(0, std::ios_base::end);
     size_t size = file.tellg();
     file.seekg(0, std::ios_base::beg);

     buf.resize(size);
     file.read(&buf[0], size);

     return size;
}

int main(int argc, char** argv)
{
     std::vector<std::string> arguments(argv, argv + argc);
     if (arguments.size() != 5)
     {
         std::cout << "usage: breplace <file_container> <file_to_be_replaced>";
         std::cout << "<file_to_replace> <dest_file_container>" << std::endl;
         return 1;
     }

     std::vector<char> container;
     std::ifstream containerFile;
     containerFile.open(arguments[1], std::ios_base::binary | std::ios_base::in);
     size_t containerSize = readFileToVector(containerFile, container);

     std::vector<char> toBeReplaced;
     std::ifstream toBeReplacedFile;
     toBeReplacedFile.open(arguments[2], std::ios_base::binary | std::ios_base::in);
     size_t fileSize = readFileToVector(toBeReplacedFile, toBeReplaced);

     std::vector<char> toReplace;
     std::ifstream toReplaceFile;
     toReplaceFile.open(arguments[3], std::ios_base::binary | std::ios_base::in);
     readFileToVector(toReplaceFile, toReplace);

     std::vector<char> destination;
     std::ofstream destinationFile;
     destinationFile.open(arguments[4], std::ios_base::binary | std::ios_base::out);

     std::vector<char>::iterator itpos = std::search(
         container.begin(), container.end(), toBeReplaced.begin(), toBeReplaced.end());

     if (itpos == container.end())
     {
         std::cout << "File's content " << arguments[2] << " was not found" << std::endl;
         return 1;
     }

     size_t beforeFileSize = std::distance(container.begin(), itpos);
     std::cout << "File's content " << arguments[2] << " found at position: ";
     std::cout << beforeFileSize << std::endl;

     destination.resize(containerSize);
     std::copy(container.begin(), container.begin() + beforeFileSize, destination.begin());
     std::copy(toReplace.begin(), toReplace.end(), destination.begin() + beforeFileSize);
     std::copy(container.begin() + beforeFileSize + fileSize, container.end(),
               destination.begin() + beforeFileSize + fileSize);

     destinationFile.write(&destination[0], containerSize);

     return 0;
}
