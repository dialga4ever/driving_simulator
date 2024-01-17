#include <SFML/Graphics.hpp>
#include "textureUtility.h"
#include "levelLoader.h"
#include <bits/stdc++.h>  
#include <fstream>
#define OFFSET 64


using namespace std;
using namespace sf;

Level::Level(){
    return;
}


Level::Level(string path){
    
    return;
}





void Level::load(string path){
    string line;
    ifstream myfile(path+"non_obstacle.txt");
    if (myfile.is_open())
    {
        int i=0;
        while (myfile.good())
        {
            printf("A\n");
            string str;
            getline(myfile,line);
            int j=0;
            stringstream ss(line); 
            while (getline(ss, str, ';')){
                printf("a\n");
                string elt;
                string tex;
                stringstream ssTwo(str); 
                int temp=1;
                while(getline(ssTwo, elt, ',')){
                    switch (temp)
                    {
                        case 1:
                            tex=elt;
                            printf("%s\n",elt.c_str());
                            temp=0;
                            break;
                        case 0:
                            printf("Texture :%s\n",tex.c_str());
                            printf("Rotate: %s\n",elt.c_str());
                            printf("Stoi :%d\n",stoi(elt));
                            printf("i%d j%d\n",i,j);
                            non_osbstacleMap[i][j]=pair<string,int>(tex,stoi(elt));
                            
                            break;
                        
                    }
                }
                j++;
            }
            i++;
        }
        myfile.close();
    }
    else 
    {  
        perror("ifstream\n");
        cout << "Unable to open file";
        return;
    }
    non_obstacles.clear();
    for(int i = 0; i < SIZE_MAP_Y; i++){
        for(int j = 0; j < SIZE_MAP_X; j++){
            non_obstacles.push_back(placeObject(non_osbstacleMap[i][j].first, j, i, non_osbstacleMap[i][j].second,OFFSET/64));
            
        }
    }
    loaded=true;

    
    myfile.open(path+"obstacle.txt");
    if (myfile.is_open())
    {
        while (myfile.good())
        {
            string str;
            getline(myfile,line);
            int j=0;
            stringstream ss(line);
            int temp=0;
            int x;
            int y;
            int rotation;
            string tex;
            while (getline(ss, str, ';')){
                printf("a\n");
                switch (temp)
                {
                    case 3:
                        y=stoi(str);
                        printf("y :%d\n",stoi(str));
                        break;
                    case 2:
                        x=stoi(str);
                        printf("x :%d\n",stoi(str));
                        break;
                    case 1:
                        rotation=stoi(str);
                        printf("rotation :%d\n",stoi(str));
                        break;
                    case 0:
                        printf("Texture :%s\n",str.c_str());
                        tex=str;
                        break;
                    
                }
                temp++;
            }
            obstacles.push_back(placeObject(tex,x,y,rotation,OFFSET/64));
        }
        myfile.close();
    }
    else 
    {  
        perror("ifstream\n");
        cout << "Unable to open file";
        return;
    }



    return;
}


void Level::createLevel(RenderWindow *window){
    if(Keyboard::isKeyPressed(Keyboard::R)){
        if(!rotate){
            creationRotation+=90;
            if(creationRotation>=360){
                creationRotation=0;
            }
            rotate=true;
        }
    }
    else{
        rotate=false;
    }
    if(Keyboard::isKeyPressed(Keyboard::Right)){
        if(!nextTexture){
            creationTex+=1;
            nextTexture=true;
            bool tooLate=true;
            std::multimap<string, Texture>::iterator it = textures.begin();
            int temp=0;
            for(;it!=textures.end();++it) {
                if(temp==creationTex){
                    tooLate=false;
                }
                temp+=1;
            }
            if(tooLate){
                creationTex=0;
            }
            
        }
    }
    else{
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            if(!nextTexture){
                creationTex-=1;
                nextTexture=true;
                if(creationTex<0){
                    creationTex=0;
                }
            }
        }
        else{
            nextTexture=false;
        }
    }
    

    int x=(Mouse::getPosition(*window).x+OFFSET/2)/OFFSET;
    int y=(Mouse::getPosition(*window).y+OFFSET/2)/OFFSET;

    String maTexture;
    std::multimap<string, Texture>::iterator it = textures.begin();
    int temp=0;
    for(;it!=textures.end();++it) {
        if(temp==creationTex){
            maTexture=it->first;
        }
        temp+=1;
    }

    creation=placeObject(maTexture, x, y, creationRotation,OFFSET/64);
    if(x>=SIZE_MAP_X||y>=SIZE_MAP_Y||x<0||y<0){
        return;
    }

    
    printf("%f %f\n",creation.getPosition().x,creation.getPosition().y);
    
    
    



    printf("x:%d y:%d\n",x,y);
    if(Mouse::isButtonPressed(Mouse::Left)){
        if(clicked==false){
            non_osbstacleMap[y][x].first=maTexture;

            non_osbstacleMap[y][x].second=creationRotation;
            non_obstacles[x+SIZE_MAP_X*y]=creation;
        }

        
    }
    else{
        clicked=false;
    }

    printf("x:%d y:%d\n",x,y);

    std::ofstream of("./level/test/non_obstacle.txt");
    if(of.is_open())
    {
        

        for(int i = 0; i < SIZE_MAP_Y; i++){
            for(int j = 0; j < SIZE_MAP_X; j++){
                of<<non_osbstacleMap[i][j].first<<","<<non_osbstacleMap[i][j].second<<";";
            }

            of<<std::endl;
        }


        of.flush();


        of.close();
    }
}


void Level::loadTextures(){
    Texture t;

    if (!t.loadFromFile("src/texture/cursor.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("cursor.png", t));
    if (!t.loadFromFile("src/texture/test.jpg")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("test.jpg", t));
    if (!t.loadFromFile("src/texture/voiture_orange.jpg")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("voiture_orange.jpg", t));
    if (!t.loadFromFile("src/texture/brique.jpg")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("brique.jpg", t));
    if (!t.loadFromFile("src/texture/route1.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route1.png", t));
    if (!t.loadFromFile("src/texture/route2.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route2.png", t));
    if (!t.loadFromFile("src/texture/route_slow1.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_slow1.png", t));
    if (!t.loadFromFile("src/texture/route_slow2.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_slow2.png", t));
    if (!t.loadFromFile("src/texture/route_egout.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_egout.png", t));
    if (!t.loadFromFile("src/texture/route_virage_exte.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_virage_exte.png", t));
    if (!t.loadFromFile("src/texture/route_virage_inte.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_virage_inte.png", t));
    if (!t.loadFromFile("src/texture/trotoire.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("trotoire.png", t));
    if (!t.loadFromFile("src/texture/route_parking_place.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_parking_place.png", t));
    if (!t.loadFromFile("src/texture/route_sans_bord.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_sans_bord.png", t));
    if (!t.loadFromFile("src/texture/route_bord1.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_bord1.png", t));
    if (!t.loadFromFile("src/texture/route_bord2.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_bord2.png", t));
    if (!t.loadFromFile("src/texture/route_bord3.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_bord3.png", t));
    if (!t.loadFromFile("src/texture/buisson_coin.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("buisson_coin.png", t));
    if (!t.loadFromFile("src/texture/buisson_cote.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("buisson_cote.png", t));
    if (!t.loadFromFile("src/texture/route_croisement1.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_croisement1.png", t));
    if (!t.loadFromFile("src/texture/route_croisement2.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("route_croisement2.png", t));
    if (!t.loadFromFile("src/texture/ventilo.bmp")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("ventilo.bmp", t));
    if (!t.loadFromFile("src/texture/phare.png")){ std::cout << "Error: Couldn't load texture\n";}
    textures.insert(pair<string, Texture>("phare.png", t));
}



void Level::loadObstacles(){
    printf("1\n");
    pair<string, int> map [SIZE_MAP_Y][SIZE_MAP_X] = 
    {{{"trotoire.png",0},   {"trotoire.png",90},            {"trotoire.png",180},           {"trotoire.png",0},     {"trotoire.png",270},           {"trotoire.png",90},            {"trotoire.png",180},       {"trotoire.png",0},             {"trotoire.png",180},           {"trotoire.png",270}},
    {{"trotoire.png",270},  {"route_virage_exte.png",0},    {"route1.png",90},              {"route_egout.png",90}, {"route1.png",90},              {"route1.png",90},              {"route1.png",90},          {"route_egout.png",90},         {"route1.png",90},              {"route_virage_exte.png",90}},
    {{"trotoire.png",0},    {"route1.png",0},               {"route_virage_inte.png",0},    {"route1.png",270},     {"route1.png",270},             {"route_croisement2.png",270},  {"route_sans_bord.png",90}, {"route_croisement1.png",270},  {"route_virage_inte.png",90},   {"route1.png",180}},
    {{"trotoire.png",90},   {"route1.png",0},               {"route1.png",180},             {"buisson_coin.png",0}, {"buisson_coin.png",90},        {"route_bord2.png",180},        {"route_bord3.png",180},    {"route_bord1.png",180},        {"route1.png",0},               {"route_egout.png",180}},
    {{"trotoire.png",0},    {"route_egout.png",0},          {"route1.png",180},             {"buisson_coin.png",270},{"buisson_coin.png",180},      {"trotoire.png",180},           {"trotoire.png",0},         {"trotoire.png",90},            {"route1.png",0},               {"route1.png",180}},
    {{"trotoire.png",270},  {"route1.png",0},               {"route1.png",180},             {"trotoire.png",0},     {"route_bord1.png",0},          {"route_bord3.png",0},          {"route_bord3.png",0},      {"route_bord2.png",0},          {"route1.png",0},               {"route1.png",180}},
    {{"trotoire.png",0},    {"route1.png",0},               {"route_virage_inte.png",270},  {"route1.png",90},      {"route_croisement1.png",90},   {"route_sans_bord.png",90},     {"route_sans_bord.png",90}, {"route_croisement2.png",90},   {"route_virage_inte.png",180},  {"route1.png",180}},
    {{"trotoire.png",180},  {"route1.png",0},               {"route_virage_inte.png",0},    {"route1.png",270},     {"route_croisement2.png",270},  {"route_sans_bord.png",90},     {"route_sans_bord.png",90}, {"route_croisement1.png",270},  {"route_egout.png",270},        {"route_virage_exte.png",180}},
    {{"trotoire.png",270},  {"route_egout.png",0},          {"route1.png",180},             {"trotoire.png",90},    {"route_bord2.png",180},        {"route_bord3.png",180},        {"route_bord3.png",180},    {"route_bord1.png",180},        {"trotoire.png",180},           {"trotoire.png",180}}
    };



    for(int i = 0; i < SIZE_MAP_Y; i++){
        for(int j = 0; j < SIZE_MAP_X; j++){
            printf("i %d, j %d\n\n", i, j);
            non_obstacles.push_back(placeObject(map[i][j].first, j, i, map[i][j].second,OFFSET/64));
        }
    }

    obstacles.push_back(placeObject("ventilo.bmp", 4, 4, 90,1));
    
}

Sprite Level::placeObject(string image, int x, int y){
    Sprite obs;
    obs.setTexture(textures.at(image));
    obs.setPosition(x*OFFSET, y*OFFSET);
    centerOrigin(&obs);
    return obs;
}

Sprite Level::placeObject(string image, int x, int y, int rotation,int scale){
    printf("ff\n");
    Sprite obs;
    obs.scale({float(scale),float(scale)});
    printf("ff %s\n",image.c_str());
    if(textures.count(image)){
        obs.setTexture(textures.at(image));
    }
    else{
        printf("mouai %s\n",image.c_str());
    }
    
    printf("ff\n");
    obs.setRotation(rotation);
    obs.setPosition(x*OFFSET, y*OFFSET);
    centerOrigin(&obs);
    return obs;
}