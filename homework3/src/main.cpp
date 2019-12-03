#include"terminal.h"
#include<iostream>
#include<fstream>
using namespace std;

int main(int argc, char *argv[])
{
  ifstream readFile;
  readFile.open( argv[1],ios::in);
  char sline[100];
  if (readFile.is_open()) {
    while (!readFile.eof())
    {
      readFile.getline(sline,sizeof(readFile),'\0');
    }
  }
  else
  {
    cout<<"檔案無法讀取"<<endl;
  }
  readFile.close();
  string sTer(sline);
  sTer=sTer+" "+argv[3]+" "+argv[4];
  Terminal ter(sTer);
  // call showResult() to get result
  string result = ter.showResult();
  // write the result to output.txt
  // std::cout << result << '\n';
  char c_result[100];
  strcpy(c_result, result.c_str());
  FILE * oFile;
  oFile=fopen("./output.txt","w");
  if(oFile!=NULL)
  {
    fputs(c_result,oFile);
    fclose(oFile);
  }
  return 0;
}
