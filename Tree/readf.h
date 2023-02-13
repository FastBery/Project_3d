#include "vec3.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include "ray.h"

// struct vec2 
// {
//         float x, y;
// };

// struct triangle
// {
//         vec3 a, b, c;
//         vec3 n1, n2, n3;
//         vec2 d1, d2, d3;
// };
// str = "cube.obj" так задавать строку через название файла
std::vector<triangle> maketrigon(std::string str )
{       
        setlocale(LC_ALL, "ru");
        std::ifstream fin;
        fin.open(str);
        //Массив из точек в пространстве  
        vec3 V; 
        std::vector <vec3> Vmass;
        //Массив из нормалей          
        vec3 VN;
        std::vector <vec3> VNmass;
        //Массив из точек на плоскости
        vec2 VT;
        std::vector <vec2> VTmass;
        //Основной нужный нам массив
        std::vector <triangle> TRmass;
        if (!fin.is_open()) // если файл не открыт
        {
                std::cout << "Nezaebis\n";
        }
        else
        {
                std::cout << "Zaebis\n";
                std::string kok;
               
                while(getline(fin, kok))
                {      
                        if(kok[0] == 'v' && kok[1] == ' ') //точки в пространстве
                        {
                                float vx, vy, vz;
                                std::string mysor;
                                const char *ckok = kok.c_str();
                                sscanf(ckok, "%s%f%f%f", &mysor, &vx, &vy, &vz);
                                V.x = vx;
                                V.y = vy;
                                V.z = vz;
                                Vmass.push_back(V);
                                
                        }

                        if(kok[0] == 'v' && kok[1] == 'n') //нормали
                        {
                                float vnx, vny, vnz;
                                std::string mysor;
                                const char *ckok = kok.c_str();
                                sscanf(ckok, "%s%f%f%f", &mysor, &vnx, &vny, &vnz);
                                VN.x = vnx;
                                VN.y = vny;
                                VN.z = vnz;
                                VNmass.push_back(VN);
                                
                        }

                        if(kok[0] == 'v' && kok[1] == 't') //точки на поскости
                        {
                                float vtx, vty;
                                std::string mysor;
                                const char *ckok = kok.c_str();
                                sscanf(ckok, "%s%f%f", &mysor, &vtx, &vty);
                                VT.x = vtx;
                                VT.y = vty;
                                VTmass.push_back(VT);
                                
                        }

                }
                while(getline(fin, kok))
                {  
                        if(kok[0] == 'f' && kok[1] == ' ') // ебаное распределение точек в треугольники, ебись оно конем, блять
                        {
                                
                                //f 1/1/1 2/2/2 4/4/3 3/3/4
                                int v1, vt1 ,vn1,   v2, vt2 ,vn2,  v3, vt3 ,vn3,   v4, vt4, vn4;
                                std::string mysor;
                                const char *ckok = kok.c_str();
                                sscanf(ckok, "%s %d%c%d%c%d %d%c%d%c%d %d%c%d%c%d %d%c%d%c%d", &mysor, &v1, &mysor, &vt1, &mysor, &vn1,       &v2, &mysor, &vt2, &mysor, &vn2,       &v3, &mysor, &vt3, &mysor, &vn3,    &v4, &mysor, &vt4, &mysor, &vn4 );

                                triangle trigon1, trigon2;
                                //1ый треугольник
                                        {trigon1.a = Vmass[(v1-1)];
                                        trigon1.b = Vmass[(v2-1)];
                                        trigon1.c = Vmass[(v4-1)];

                                        trigon1.n1 = VNmass[(vn1-1)];
                                        trigon1.n2 = VNmass[(vn2-1)];
                                        trigon1.n3 = VNmass[(vn4-1)];
                                        
                                        trigon1.d1 = VTmass[(vt1-1)];
                                        trigon1.d2 = VTmass[(vt2-1)];
                                        trigon1.d3 = VTmass[(vt4-1)];}

                                //2ой треугольник
                                        {trigon2.a = Vmass[(v2-1)];
                                        trigon2.b = Vmass[(v3-1)];
                                        trigon2.c = Vmass[(v4-1)];

                                        trigon2.n1 = VNmass[(vn2-1)];
                                        trigon2.n2 = VNmass[(vn3-1)];
                                        trigon2.n3 = VNmass[(vn4-1)];
                                        
                                        trigon2.d1 = VTmass[(vt2-1)];
                                        trigon2.d2 = VTmass[(vt3-1)];
                                        trigon2.d3 = VTmass[(vt4-1)];}
                                

                                TRmass.push_back(trigon1);
                                TRmass.push_back(trigon2);

                        }
                }
                        
        }
        fin.close();
        return TRmass;
}

