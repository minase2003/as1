#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

/// These constant variables are self-explanatory. Each is assigned
/// a default value to silence CodeGrade's silly error detection.
const int SUCCESS = 0;
const int FAILURE = 0;
const int MAX_STR_LEN = 1024;
const int MAX_ARGS = 64;
const string USAGE = R"(
usage: git <command> [<args>]

These are common Git commands used in various situations:

start a working area (a directory)
   clone    Clone a repository into a new directory
   init     Create an empty Git repository

work on the current change
   add      Add a file contents to the index
   mv       Move or rename a file or directory
   rm       Remove files from the working directory

examine the history and state
   diff     Show changes between commits
   grep     Print lines matching a pattern

grow, mark and tweak your common history
   commit   Record changes to the repository

collaborate (see also: git help workflows)
   push     Update remote refs along with associxated objects
)";

/// These declarations are generally necessary because of the
/// way C++ resolves and binds names to declarations.

/// A type that represents a file.
struct File
{
   string name;
   vector<string> lines;
};

/// A type that represents the changes made in a file.
struct Position
{
   int line;
   int column;
   int length;
   File file;
};

/// A type that represents a repository (i.e., a directory)
struct Directory
{
   string name;
   vector<File> files;
};

int parseCommand(const char* str, char** tokens);

bool makeDirectory(const char* name, vector<Directory>& directories);

int findDirectory(const char* name, vector<Directory>& directories);

int findFileInDirectory(const char* name, Directory& dir);

void printUsage();

bool stringCompare(const char* s1, const char* s2);

int strLength(const char* str);

bool addFileToDirectory(const char* name, Directory& dir);

void removeFileFromDirectory(vector<char*>& files, Directory& dir, bool& flag);

bool searchInFile(const char* str, Position& position, File& file);

bool replaceInFile(const char* str, Position& position, File& file);

///@fn int main(int, char**)
///@brief Entry point of our application.
///@param[in]argc the number of command-line argument passed to the program.
///@param[in]argv the vector of command-line arguments.
///@return SUCCESS if the program terminated successfully or FAILURE otherwise.
int main(int argc, char** argv) {
   // bailed out if we do not have enough arguments to process
   if (argc < 2) {
      cout << "ERROR: invalid number of command-line arguments." << endl;
      return FAILURE;
   }
   // Contains all repositories added via command-line. Don't forget
   // to close a previously opened directory!
   vector<Directory> directories;
   // Contains all changes made to files and before a commit command
   // is executed. Don't forget to move them to the commits vector
   // every time a commit command is executed
   vector<Position> stagingArea;
   // Contains all changes made to files which are ready to be pushed! (a.k.a supercommit)
   vector<Position> commits;
   // Contains the parsed command, that is, a sequence of tokens that
   // you should process and evaluate individually
   char* commands[MAX_ARGS];
   // working directory and current working file.
   // <-- add your variables here
   // TODO: use some variables to keep track of the current
   // -->
   // We begin at 1 because 0 contains the name of the program, which
   // is not a command!
   for (int i = 1; i < argc; i++) {
      // <--
      // 1. Make sure to validate each command before executing each command
      //    that is, check for syntax!!
      // 2. Here is the list of commands that you must implement and use:
      //    - git OR git help
      //    - git init <dir>
      //    - git add <file_1> <file_2> ... <file_N> to <dir>
      //    - git rm <file_1> <file_2> ... <file_N> from <dir>
      //    - git mv <file> to <dir> <file>
      //    - git grep <pattern> in <file> OR git grep <pattern>
      //    - git diff <file1> <file2>
      //    - git commit
      //    - git push

      int tokens = parseCommand(argv[i], commands);
      // TODO: Write your code here...
      // -->
   }
   return SUCCESS;
}

// TODO: write the implementation of each function here!

int parseCommand(const char* str, char** tokens){
   static char line[MAX_STR_LEN];
   int character;
   int tokenTotal = 0;

   for(int i = 0; str[i] != '\0'; i++){

         if(str[i] == character){
            i++;
            
            if(line[i] == str[i]){
               i++;
            }
            int newString = 0;
            for(int i = 0; line[i] != '\0'; i++){
                  if(line[i] == ' '){
                     line[i] = '\0';
                     tokens[tokenTotal] = &line[newString];
                     tokenTotal++;
                     newString = i + 1;
                  }
            }
            if(line[newString] != '\0'){
               tokens[tokenTotal] = &line[newString];
               tokenTotal++;
            }
         }

   }
   cout << tokenTotal;
   return tokenTotal;
};

bool makeDirectory(const char* name, vector<Directory>& directories);

int findDirectory(const char* name, vector<Directory>& directories);

int findFileInDirectory(const char* name, Directory& dir);

void printUsage(){
   cout << USAGE << endl;
};

bool stringCompare(const char* s1, const char* s2);

int strLength(const char* str){
   int L = 0;
   
   while(str[L] != '\0'){
      L++;
   }
   return L;
};

bool addFileToDirectory(const char* name, Directory& dir);

void removeFileFromDirectory(vector<char*>& files, Directory& dir, bool& flag);

bool searchInFile(const char* str, Position& position, File& file);

bool replaceInFile(const char* str, Position& position, File& file);