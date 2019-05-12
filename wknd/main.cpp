#include <iostream>
#include "vec3.h"
#include "ray.h"
#include <fstream>
#include <bits/stdc++.h>
using namespace std;


vec3 color (const ray& r){
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y()+ 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0)+ t*vec3(0.5, 0.7,1.0);
}

int main(){
	ifstream inFile;
	inFile.open("desc.txt");
	if (!inFile) {
    	cerr << "Unable to open file datafile.txt";
    	exit(1);   // call system to stop
 	}
 	string rd;
 	int width = 0;
 	int length = 0;
    int contRes = 0;
    int contCam = 0;
    int contMaterial = 0;
    float cam[11];
    string nomeMaterial = "";
    map<string,material> materiais;
    float caractMaterial[7];
 	while (inFile >> rd) {
  		if(rd.substr(0,3) == "res"){
           contRes = 1;
  		}else if(contRes == 1){
            width = stoi(rd);
            contRes++;
        }else if(contRes == 2){
            length = stoi(rd);
            contRes = 0;
        }else if(rd.substr(0,6) == "camera"){
            contCam = 1;
  		}else if(contCam >= 1 && contCam <= 11){
            //cout << rd << endl;
            cam[contCam-1] = stof(rd);
            contCam++;
        }else if(rd.substr(0,8) == "material"){
            contMaterial = 1;
        }else if(contMaterial >= 1 && contMaterial <= 9){
            if(contMaterial == 1){
                nomeMaterial = rd;
            }else{
                caractMaterial[contMaterial-2] = stof(rd);
                contMaterial++;
            }
        }else if(contMaterial == 10){
            Material material(caractMaterial[0],caractMaterial[1],caractMaterial[2],caractMaterial[3],caractMaterial[4],caractMaterial[5],caractMaterial[6]);
            materiais[nomeMaterial] = material;
            contMaterial = 0;
        }
	}
    
    cout << cam[10] << " " << cam[0];
	inFile.close();
    int nx = 200;
    int ny = 100;
    cout << "P3\n"<< nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin (0.0, 0.0, 0.0); 

    for(int j=ny-1; j>=0;j--){
        for(int i=0; i<nx;i++){
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r); 
            int ir= int(255.99*col[0]);
            int ig= int(255.99*col[1]);
            int ib= int(255.99*col[2]);
            cout << ir << " " << ig << " " << ib << "\n";

        }
    } 

}