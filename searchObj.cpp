#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <sstream>
#define pi 3.14159265358979323846
#define earth_radius 6371.0
using namespace std;
class SearchObj
{   private:
    // Latitude of customer who needs a car.
    double lat1d;
    
    // Longitude of customer who needs a car.
    double lon1d;
    int printcount;
    
    ifstream car_list;
    ofstream out;
    /* i and j are used to access various
    elements of the char arrays. x is used
    to measure the size of the element of
    latitude_as_string array. y is used to
    measure the size of the element of
    longitude_as_string array. m is used
    to measure the size of the element
    of id_as_string array. n is used to
    measure the size of the element of
    name array. f keeps count of " " "
    symbol. fi keeps count of " : " symbol.
    */
    long long int length, i, j, x, y, m,
                n, f, fi, id[100000];
    
    char latitude_as_string[1000], 
        longitude_as_string[1000], 
        id_as_string[1000], name[1000];
    
    double lat2d, lon2d;
    
    // To get each line of car_list.json
    // file as string.
    string line;
    
    
    public:
    //getfunctions
    double getLat1d()
    {
        return lat1d;
    }
    double getLon1d()
    {
        return lon1d;
    }
    //setter functions
    void setLat1d(double a)
    {
        lat1d=a;
    }
    void setLon1d(double b)
    {
        lon1d=b;
    }
    void userlocation(double x,double y)
    {
        setLon1d(y);
        setLat1d(x);
    }
    double getLat2d()
    {
        return lat2d;
    }
    double getLon2d()
    {
        return lon2d;
    }
    //setter functions
    void setLat2d(double c)
    {
        lat2d=c;
    }
    void setLon2d(double d)
    {
        lon2d=d;
    }
    SearchObj()
    {   
        car_list.open("carList.json");
        out.open("nearBy.json");
        printcount=0;
    }
    ~SearchObj()
    {   
        // closing stream of customer's file.
        car_list.close();
        
        // closing stream of nearBy.json file.
        out.close();
    }
    
    
    // Function to convert degree to radian.
    double  static degtorad(double deg)
    {
        return ( deg * pi / 180);
    }
    
    // Function to calculate distance
    // between 2 given locations 
    // using Great Circle Distance Formula.
    double  distanceEarth()
    {   
        double lat1, lon1, lat2, lon2, 
            delta_lon, central_ang;
    
        lat1 = degtorad(getLat1d());
        lon1 = degtorad(getLon1d());
        lat2 = degtorad(getLat2d());
        lon2 = degtorad(getLon2d());
    
        delta_lon = lon2 - lon1;
        
        // great circle distance formula.
        central_ang = acos ( sin(lat1) *
                    sin(lat2) + cos(lat1) *
                    cos(lat2) * cos(delta_lon) ); 
                        
        return (earth_radius * central_ang);
    }
    
  
    
    // Function to check whether distance between
    // 2 points is less than 50km or not.
    void distance_calculator()
    {   
        //program set to return nodes under 50KM
        if (distanceEarth() <= 50.0000)
        {
            // Converting id to int format.
            id[i] = atoll(id_as_string);
            i++;

            out << "{\"car_id\": " << id[i - 1] << 
                ", \"company_Name\": " << name << ", \"Latitude\": " << latitude_as_string << 
                ", \"Longitude\": " << longitude_as_string << "}," << endl;
            if(++printcount < 5)
            {
                cout<<"\n\nCar ID:"<<id[i-1]<<"\nCompany Name:"<<name
                <<"\nLat: "<< latitude_as_string
                <<"\nLon: "<<longitude_as_string;
            }
        }
    }
    void printTop5()
    {

    }

    // Function to read various attributes
    // like latitude, longitude, name , id,
    // etc, from carList.json file. simplistic
    // approach is used to get JSON attributes.
    void json_parser()
    {                     
        if (car_list.is_open())
        {   f = 0; x = 0; y = 0; fi = 0; m = 0, n = 0;
            
            while (getline(car_list,line) )
            {//f = 0; x = 0; y = 0; fi = 0; m = 0, n = 0;
                
                
                length = line.size();
                 
                for (j = 0; j < length; j++)
                {
                    if (line[j] == '}')
                        {f = 0; x = 0; y = 0; fi = 0; m = 0, n = 0;

                        }
                    else if (line[j] == '"')
                        f++;

                    else if (line[j] == ':')
                        fi++;
                        
                    // To get latitude of the location.    
                    if (f == 3)
                    {
                        j++;

                        while (line[j] != '"')
                        {
                            latitude_as_string[x] = line[j];
                            x++; j++;
                        }

                        j--; latitude_as_string[x] = '\0';
                    }
                    
                    // To get longitude of the location.
                    else if (f == 13)
                    {
                        j++;

                        while (line[j] != '"')
                        {
                            longitude_as_string[y] = line[j];
                            y++; j++;
                        }

                        j--; longitude_as_string[y] = '\0';
                    }
                    
                    // To get id 
                    if (fi == 2)
                    {
                        j += 2;

                        while (line[j] != ',')
                        {
                            id_as_string[m] = line[j];
                            m++; j++;
                        }

                        j--; id_as_string[m] = '\0';
                        fi++;
                    }
                    
                    // To get name 
                    else if (fi == 4)
                    {
                        j += 2;

                        while (line[j] != ',')
                        {
                            name[n] = line[j];
                            n++; j++;
                        }

                        j--; name[n] = '\0';
                        fi++; f += 2;
                        //cout<<name<<endl;
                    }
                }

                // Converting latitude and longitude
                // in string to float.
                setLat2d(atof(latitude_as_string));
                setLon2d(atof(longitude_as_string));
                distance_calculator();
                
                
            }
        }
    
        
            
            
        
    }

};