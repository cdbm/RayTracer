#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "material.h"
#include "hitable_list.h"
#include "float.h"
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

vec3 color (const ray& r, hitable *world){
    hit_record rec;
    if(world->hit(r, 0.0, MAXFLOAT, rec)){
        return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1
                 , rec.normal.z()+1) ;
    }else{
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y()+ 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0)+ t*vec3(0.5, 0.7,1.0);
    }
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
    map<string,vector<float>> materiais;
    vector <float> caractMaterial;
    hitable *list[10000];
    int qtdeEsferas = 0;
    int contEsferas = 0;
    int caractEsferas[4];
    int raioEsfera = 0;
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
            cam[contCam-1] = stof(rd);
            contCam++;
        }else if(rd.substr(0,8) == "material"){
            contMaterial = 1;
        }else if(contMaterial >= 1 && contMaterial <= 8){
            if(contMaterial == 1){
                nomeMaterial = rd;
                contMaterial++;
            }else{
                caractMaterial.push_back(stof(rd));
                if(contMaterial == 8){
                    materiais[nomeMaterial] = caractMaterial;
                }
                contMaterial++;
            }
        }else if(contMaterial == 9){
            for(float a : materiais[nomeMaterial]){
                cout << a << endl;
            }
            contMaterial = 0;
        }else if(rd == "sphere"){
            contEsferas = 1;
        }else if(contEsferas >= 1 && contEsferas <= 5){
            if(contEsferas <= 3){
                caractEsferas[contEsferas-1] = stoi(rd);
                contEsferas++;
            }else if(contEsferas == 4){
                raioEsfera = stof(rd);
                contEsferas++;
            }else if(contEsferas == 5){
                list[qtdeEsferas] = new sphere(vec3(caractEsferas[0],caractEsferas[1],caractEsferas[2]), raioEsfera);
            }
        }
	}
    
	inFile.close();
    int nx = 200;
    int ny = 100;
    cout << "P3\n"<< nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin (0.0, 0.0, 0.0); 
    list[0] = new sphere(vec3(0,0,-1), 0.5);
    list[1] = new sphere(vec3(0,-100.5,-1), 100);
    hitable *world = new hitable_list(list,2);

    for(int j=ny-1; j>=0;j--){
        for(int i=0; i<nx;i++){
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 p = r.point_at_parameter(2.0);
            vec3 col = color(r, world); 
            int ir= int(255.99*col[0]);
            int ig= int(255.99*col[1]);
            int ib= int(255.99*col[2]);
            cout << ir << " " << ig << " " << ib << "\n";

        }
    } 

}