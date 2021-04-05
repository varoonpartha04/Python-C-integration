#include<stdio.h>
#include<sys/stat.h>
#include<iostream>
#include<string.h>
#include<string>
#include<dirent.h>
#include<thread>
#include<istream>
#include<fstream>
#include<vector>
#include<exception>

using namespace std;
std::vector<std::string> listOfFiles ;

bool checkIfExists(char* file, char* searchString){

    string line;
    try{
        ifstream myfile(file);
        if (myfile.is_open())
        {
            while (! myfile.eof() )
            {
                getline (myfile,line);
	            if ( line.find( searchString) != std::string::npos )
                    return true;
                myfile.close();
            }
        }
        else
        std::cout << "Unable to open file"; 
        return false;
    } catch(exception& e){
        std::cout << "Exception " << e.what() << " occured" << std::endl;
    }
}

void find_files(char *dir_name, char *searchString){
    DIR *dir; // pointer to directory
    struct dirent *entry; // all stuff in the directory
    struct stat info; // info about each entry
    unsigned char isFile = 0x8;
    unsigned char isFolder = 0x4;
    try{
        dir = opendir(dir_name);
        if (!dir)
        {
            std::cout << "Directory not found" << dir_name << std::endl;
            return;
        }
        int i=0;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] != '.')
            {
                char *path = new char[5000];
                strcpy(path, dir_name);
                strcat(path,"/");
                strcat(path,entry->d_name);
        	    if ( entry->d_type == isFile)
        	    {
                    if(checkIfExists(path, searchString)){
                        listOfFiles.push_back(path);
                    }
        	    }
        	    else if ( entry->d_type == isFolder)
        	    {
                    std::thread threadObj(find_files,path,searchString);
                    threadObj.join();
        	    }
            }
        }
        closedir(dir);
    } catch(exception& e){
        std::cout << "Exception " << e.what() << " occured" << std::endl;
    }
}

int main(int argc, char *argv[]) 
{
    if(argc != 3){
        std::cout << "Error - sufficient number of inputs not provided" << std::endl ;
    }
    try{
        std::thread threadObj(find_files,argv[1],argv[2]);
        threadObj.join();
    } catch(exception& e){
        std::cout << "Exception " << e.what() << " occured" << std::endl;
    }
    if(listOfFiles.size()==0){
        std::cout << "File with givven Search String not found" << std::endl;
        return 0;
    }

    for (int i = 0; i < listOfFiles.size(); i++) {
		std::cout << listOfFiles.at(i) << ' ' << std::endl;
	}
    return 0;
}