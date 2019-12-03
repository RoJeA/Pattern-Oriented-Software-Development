#ifndef TERMINAL_H
#define TERMINAL_H
#include"shape.h"
#include"circular_sector.h"
#include"ellipse.h"
#include"triangle.h"
#include"sort.h"

#include <iostream>
#include <regex>
#include<sstream>
#include<functional>
#include <iomanip>

class Terminal
{
public:
  // you can use regular expression to get useful token from "Input string"
  Terminal(std::string InputString):_InputString(InputString)
  {
    _verify->clear();
    // std::string aaa=showResult();
    _inputVec=cutString(_InputString);
    // showVector(_inputVec);
    _inputVec=check(_inputVec);
    for(string str : _inputVec)
    {
      compStr(str);
    }
    // showVector(_inputVec);
    // showResult();
  }
std::vector<string> check(std::vector<std::string> vec){
  std::vector<std::string> newVec;
  bool run=true;
  char c[]={'!','@','#','$','%','^','&','*','>','<'};
  char c3[]={'T','C','E'};
  for(std::vector<std::string>::iterator it =vec.begin();it!=vec.end();){
    run=true;
    for(char c6:c3){
      int i1=(*it).find(c6);
      if(i1==-1) continue;
      int i2=(*it).find(')');
      for(int k=i1;(k<i2+1)&&run;k++){
        for(char c1:c){
            if((*it)[k]==c1){
              it=vec.erase(it);
              run=false;
              break;
            }
        }
      }
    }
      if(run) it++;
  }
    return vec;
}

  // void showVector(std::vector<std::string> vec){
  //   for(std::vector<std::string>::iterator it =vec.begin();it!=vec.end();it++)
  //     cout<<"SHOW: "<<*it<<endl;
  // }
    // Input string like this => "Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc"
  std::vector<std::string> cutString(std::string inputS)
  {
    std::vector<std::string> _v;
    _v.clear();
    std::string delimiter = ")";
    size_t pos = 0;
    std::string token;
    while ((pos = inputS.find(delimiter)) != std::string::npos) {
      token = inputS.substr(0, pos+1);
      _v.push_back(token);
      inputS.erase(0, pos + delimiter.length());
    }
    // std::string delimiter_S = " ";
    // size_t pos_S = 0;
    // std::string token_S;
    // int count_S = 0;
    // while ((pos_S = inputS.find(delimiter_S)) != std::string::npos) {
    //   inputS.erase(0, pos_S + delimiter_S.length());
    //   _Suffix[count_S] = inputS.substr(0, inputS.find(delimiter_S));
    //   count_S++;
    // }
    // _Suffix[count_S]=inputS;
    _Suffix=inputS;
    return _v;
  }
  void compStr(std::string v)
  {
    std::string shapeInfo=v;
    std::smatch m;
    //Ellipse/CircularSector
    std::regex e ("\\bEllipse\\b|\\bCircularSector\\b");
    std::regex en ("\\s*[(]\\s*(.?\\d+)\\s*[,]\\s*(.?\\d+)\\s*[)]\\s*");
    shapeInfo = regex_Searching(shapeInfo, m, e, en);
    //Triangle
    std::regex et ("\\bTriangle\\b");
    std::regex ent ("\\s*[(]\\s*(.?\\d+)\\s*[,]\\s*(.?\\d+)\\s*[,]\\s*(.?\\d+)\\s*[,]\\s*(.?\\d+)\\s*[,]\\s*(.?\\d+)\\s*[,]\\s*(.?\\d+)\\s*[)]\\s*");
    shapeInfo = regex_Searching(shapeInfo, m, et, ent);
  }
  string regex_Searching(string shapeInfo,std::smatch m,std::regex e, std::regex en)
  {
    while (std::regex_search (shapeInfo,m,e))
    {
      string stemp;
      for (auto x:m){
        stemp=x;
      }
      shapeInfo = m.suffix().str();
      int count=0;
      while (std::regex_search (shapeInfo,m,en))
      {
        for (auto x:m)
        {
           if(count>0) //count0 :  (9, 35) count1 : 9 count2 : 35
           {
             _inputNum.push_back(x);
           }
           count++;
         }
        shapeInfo = m.suffix().str();
      }
      if(stemp=="CircularSector" && count==3)
        _verify->push_back(new CircularSector(std::stoi(_inputNum[0]),std::stoi(_inputNum[1])));
      else if(stemp=="Ellipse" && count==3)
        _verify->push_back(new Ellipse(std::stoi(_inputNum[0]),std::stoi(_inputNum[1])));
      else if(stemp=="Triangle" && count==7)
        _verify->push_back(new Triangle(std::stoi(_inputNum[0]),std::stoi(_inputNum[1]),std::stoi(_inputNum[2]),std::stoi(_inputNum[3]),std::stoi(_inputNum[4]),std::stoi(_inputNum[5])));
      _inputNum.clear();
    }
    return shapeInfo;
  }


  std::string showResult()
  {
    string result="[";
    regex model("\\barea\\b|\\bperimeter\\b|\\bsumOfSquares\\b");
    regex incdec("\\binc\\b|\\bdec\\b");
    string _model;
    string _incdec;
    bool _model_tof = false;
    bool _incdec_tof = false;
    std::smatch hello;
    while (std::regex_search (_Suffix,hello,model))
    {
      for(auto x:hello)
      {
        _model = x;
        _model_tof = true;
      }
      break;
    }
    std::smatch hello2;
    while (std::regex_search (_Suffix,hello2,incdec))
    {
      for(auto x:hello2)
      {
        _incdec = x;
        _incdec_tof = true;
      }
      break;
    }
    if(_incdec_tof == true && _model_tof == true)
    {
      if(_incdec=="inc")
      {
        Sort Q(_verify);
        AscendingComparison qaq(_model); //Object
        Q.quickSort(qaq);
      }
      else if(_incdec=="dec")
      {
        Sort Q(_verify);
        DescendingComparison qaq(_model); //Object
        Q.quickSort(qaq);
      }
      for(vector <Shape*> :: iterator j = _verify->begin() ; j != _verify->end(); j++)
      {
        std::string str;
        if(_model=="area")
        {
          str = to_string((*j)->area());
        }
        else if(_model=="perimeter")
        {
          str = to_string((*j)->perimeter());
        }
        else if(_model=="sumOfSquares")
        {
          str = to_string((*j)->sumOfSquares());
        }

        result+=str;
        if(j != _verify->end()-1)
        result=result+", ";
      }
      result+="]";
      return result;
    }
    else
    {
      throw string("Unuseful User Input!");
    }
  }
private:
  std::string _InputString;
  std::string _Suffix;//[2];
  std::vector<Shape *> _v;
  std::vector<Shape *>* _verify=new std::vector<Shape *>;
  std::vector<string> _inputVec;//Ellipse (9,8)
  std::vector<string> _inputShape;//Ellipse
  std::vector<string> _inputNum;//(9,8)
};
#endif
