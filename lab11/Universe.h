#include <string.h>
#include "Body.h"
#include <fstream>
#include <math.h>

class Universe{
    public:
       Body planet[7];
       float g;
       void file_read(std::string path);
       float find_x_force(const Body & );
       float find_y_force(const Body & );
       void update(float t);
};
void Universe:: file_read(std::string path){
        std::ifstream file;
        file.open(path);
        if(file.is_open()){
            file >> g;
            char a;
            for(int i=0; i<7; i++){
            file >> a;
            file >> this->planet[i].posision_x;
            file >> this->planet[i].posision_y;
            file >> this->planet[i].v_x;
            file >> this->planet[i].v_y;
            file >> this->planet[i].mass;
            }
        }
    }
float Universe:: find_x_force(const Body &a){
    float fx = 0;
    for(int i = 0; i < 7; i++){
        float dx = -a.posision_x + this->planet[i].posision_x, dy = -a.posision_y + this->planet[i].posision_y;
        if(dx != 0 && dy != 0 ){
            float d = dx*dx + dy*dy;
            float f = a.mass*this->planet[i].mass*this->g/d;
            fx += dx/sqrt(d)*f;
        }
    }
    return fx;
} 
float Universe:: find_y_force(const Body &a){
    float fy = 0;
    for(int i = 0; i < 7; i++){
        float dx = -a.posision_x + this->planet[i].posision_x, dy = -a.posision_y + this->planet[i].posision_y;
        if(dx != 0 && dy != 0 ){
            float d = dx*dx + dy*dy;
            float f = a.mass*this->planet[i].mass*this->g/d;
            fy += dy/sqrt(d)*f;
        }
    }
    return fy;       
}   

void Universe:: update(float t){
    for(int i=0; i<7; i++){
        float a_x = find_x_force(this->planet[i])/this->planet[i].mass;
        float a_y = find_y_force(this->planet[i])/this->planet[i].mass;
        this->planet[i].v_x+=a_x*t;
        this->planet[i].v_y+=a_y*t;
        this->planet[i].posision_x +=this->planet[i].v_x * t + (0.5 * a_x * pow(t,2));
        this->planet[i].posision_y +=this->planet[i].v_y * t + (0.5 * a_y * pow(t,2));
    }
}
