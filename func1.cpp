//задание 1
#include <vector>
#include <string>
#include <iostream>
using namespace std;






struct Student
{
  string Name;
  string GroupId;
  vector<unsigned> Ratings;
  vector<string> Subjects;
};

void SortByName(vector<Student>& stud){
    
    for(int i=0;i<stud.size()-1;++i){
        for(int g=0;g<stud.size()-i-1;++g){
            if(stud[g].Name[0]>stud[g+1].Name[0]){
                swap(stud[g],stud[g+1]);
            }
        }
    }
    
};

int main()
{
    Student vlad = {"Vlad", "15", {4, 3, 5, 2}, {"aya", "AnalGem","MatAnal","Boobsovedenie"}};
    Student igor = {"Igor", "14", {5, 5, 5, 5}, {"aya", "AnalGem","MatAnal","Boobsovedenie"}};
    Student vova = {"Vova", "14", {2, 2, 2, 2}, {"aya", "AnalGem","MatAnal","Boobsovedenie"}};
    Student egor = {"Igor", "14", {2, 3, 5, 5}, {"aya", "AnalGem","MatAnal","Boobsovedenie"}};
    vector<Student> a={vlad, igor, vova, egor};
    SortByName(a);
    for(int i =0;i<4;++i){
        cout<<a[i].Name<<endl;
    }
    
}
