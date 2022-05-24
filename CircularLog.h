#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;


int countFiles(){         //This function counts files that in the logs folder.
    int counter = 0;
        std::string path = "./logs";
        for (const auto & entry : fs::directory_iterator(path))
        counter++;
        return counter;
}


bool isEmpty()           //That function checks folder if it is empty.
{
        int counter = countFiles();
        if(counter == 0){
            return true;
        }else {
            return false;
        }
}

    void file_exit(const char* filePath){
        fopen(filePath, "w");

}

void removeLog(int logNumber, int maxLog){             //This function delete oldest log files to keep maximum log file number for the logs folder.
      std::string path = "./logs";
      std::string last_Index;
      int Index = 0;
      int test = countFiles();
      for(int i = 0; i < test + logNumber - maxLog; i++){
        int sayac = 0;
        for (const auto & entry : fs::directory_iterator(path)){      //This part enables to reach every file from logs folder and keep their log numbers.
        while(sayac == 0){
          last_Index = entry.path().filename().string().substr(3);       
          Index = std::atoi(last_Index.c_str());
          sayac++;
          }
      }
         for (const auto & entry : fs::directory_iterator(path)){         
          last_Index = entry.path().filename().string().substr(3);    // With this part, we can obtain the Index of the log file name. We can remove files with using this Index.
          if(Index > std::atoi(last_Index.c_str())){                     
          Index = std::atoi(last_Index.c_str());
          } 
        }
        std::string a = "./logs/log";              
        std::stringstream ss;
        ss << Index;
        a += ss.str();
        remove(a.c_str());      
      }
}

void logWrite(FILE* file, int type){          

 //This part enables to write the current time, log type and log text in the log file when the log file is taken.

    std::time_t current_time = std::time(0);
    std::tm* timestamp = std::localtime(&current_time);
    char buffer[80];
    strftime(buffer, 80, "%c", timestamp);
    std::string str;
    

    switch (type)
    {
    case 1:
    str = "\t [Trace] Lorem ipsum.\n";
        break;
    case 2:
    str = "\t [Debug] Example debug message.\n";
        break;
    case 3:
    str = "\t [Info] This message reports an event.\n";
        break;
    case 4:
    str = "\t [Warn] Careful for that.\n";
        break;
    case 5:
    str = "\t [Error] Error occurred.\n";
        break;
    case 6:
    str = "\t [Critical] Something bad happened.\n";
        break;
    default:
    str = "\t Wrong log type.\n";
        break;
    }

fprintf(file, buffer);
fprintf(file, str.c_str());
    
}


void addLog(int logNumber, int maxLog, int type){     

/* This function creates log files, writes the log type messages that received from user into the created log files, 
and keep as many as log files that user wishes in the logs folder. */
    
    if(isEmpty()){

    std::string path = "./logs";
    std::string last_name;
    int Index = 0;
    for (const auto & entry : fs::directory_iterator(path)){
    last_name = entry.path().filename().string().substr(3);
    if(Index < std::atoi(last_name.c_str())){
        Index = std::atoi(last_name.c_str());
        }    
      }
    std:: string filename_base = "./logs/log";    
    for(int i = Index; i < Index + (logNumber); i++){
    std::string fileIndex;   
    std::stringstream ss;  
    ss << i;
    ss >> fileIndex;
    std::string filename  = filename_base + fileIndex;
    const char* name = filename.c_str();    
    file_exit(filename.c_str());
    FILE* file = fopen(filename.c_str(),"w");
    logWrite(file, type);
    fclose(file);
    }
}
  
  else{
      if(countFiles() + logNumber > maxLog){
      removeLog(logNumber, maxLog);
      std::string path = "./logs";
      std::string last_name;
      int Index = 0;
      for (const auto & entry : fs::directory_iterator(path)){
      last_name = entry.path().filename().string().substr(3);
      if(Index < std::atoi(last_name.c_str())){
        Index = std::atoi(last_name.c_str());
        }    
      }
      std:: string filename_base = "./logs/log";    
      for(int i = Index + 1; i < Index + (logNumber + 1); i++){
      std::string fileIndex;   
      std::stringstream ss;  
      ss << i;
      ss >> fileIndex;
      std::string filename  = filename_base + fileIndex;
      const char* name = filename.c_str();    
      file_exit(filename.c_str());
      FILE* file = fopen(filename.c_str(),"w");
      logWrite(file, type);
      fclose(file);
      }
      
    }
    else{
    std::string path = "./logs";
    std::string last_name;
    int Index = 0;
    for (const auto & entry : fs::directory_iterator(path)){
    last_name = entry.path().filename().string().substr(3);
    if(Index < std::atoi(last_name.c_str())){
        Index = std::atoi(last_name.c_str());
        }    
      }
    std:: string filename_base = "./logs/log";    
    for(int i = Index + 1; i < Index + (logNumber + 1); i++){
    std::string fileIndex;   
    std::stringstream ss;  
    ss << i;
    ss >> fileIndex;
    std::string filename  = filename_base + fileIndex;
    const char* name = filename.c_str();    
    file_exit(filename.c_str());
    FILE* file = fopen(filename.c_str(),"w");
    logWrite(file, type);
    fclose(file);
    }
        
    }
    
  }
}



    

