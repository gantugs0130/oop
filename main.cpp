#include <fstream>
#include<iostream>
#include "Universe.h"
using namespace std;
Universe aa;
static double g = 0;
void File_Read(){
        ifstream file;
        file.open("./nbodys.txt");
        if(file.is_open()){
            file >> g;
            char a;
            for(int i=0; i<7; i++){
            file >> a;
            file >> aa.planet[i].posision_x;
            file >> aa.planet[i].posision_y;
            file >> aa.planet[i].acc_x;
            file >> aa.planet[i].acc_y;
            file >> aa.planet[i].mass;
        }
        
        }
        
    }
int main(){
    File_Read();
    return 0;
}