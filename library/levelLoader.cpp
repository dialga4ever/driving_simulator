#include <SFML/Graphics.hpp>
#include "textureUtility.h"
#include "levelLoader.h"
#include <bits/stdc++.h>  
#include <fstream>
#include <iostream>
#include <filesystem>
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
    //two dimensional array for scaleX and scaleY
    int scaleX[SIZE_MAP_Y][SIZE_MAP_X];
    int scaleY[SIZE_MAP_Y][SIZE_MAP_X];


    obstacles.clear();
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
                printf("%s\n",str.c_str());
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
                            temp=-1;
                            break;
                        case -1:
                            scaleX[i][j]=stoi(elt);
                            temp=-2;
                            break;
                        case -2:
                            scaleY[i][j]=stoi(elt);
                            temp=-3;
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

    obstacles.clear();
    obstaclesTexture.clear();
    for(int i = 0; i < SIZE_MAP_Y; i++){
        for(int j = 0; j < SIZE_MAP_X; j++){
            printf("maybe\n");
            non_obstacles.push_back(placeObjectReal(non_osbstacleMap[i][j].first, j*OFFSET+OFFSET/2, i*OFFSET+OFFSET/2, non_osbstacleMap[i][j].second,scaleX[i][j],scaleY[i][j]));
            
            printf("maybe\n");
        }
    }
    
    myfile.open(path+"obstacle.txt");
    if (myfile.is_open())
    {
        while (myfile.good())
        {
            string str;
            getline(myfile,line);
            //check if the string is empty
            if(line.empty()){
                continue;
            }
            if(line=="\n"){
                continue;
            }
            int j=0;
            stringstream ss(line);
            int temp=0;
            int x;
            int y;
            int rotation;
            float ScaleTempX;
            float ScaleTempY;
            string tex;
            while (getline(ss, str, ';')){
                //check if the string is empty
                if(str.empty()){
                    continue;
                }
                if(str=="\n"){
                    continue;
                }

                printf("a\n");
                switch (temp)
                {
                    case 5:
                        ScaleTempY=stof(str);
                        printf("Scale :%d\n",stoi(str));
                        break;
                    case 4:
                        ScaleTempX=stof(str);
                        printf("Scale :%d\n",stoi(str));
                        break;
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
            printf("???\n");
            obstacles.push_back(placeObjectReal(tex,x,y,rotation,ScaleTempX,ScaleTempY));
            obstaclesTexture.push_back(tex);
        }
        myfile.close();
    }
    else 
    {  
        perror("ifstream\n");
        cout << "Unable to open file";
        return;
    }
    decos.clear();
    decoTexture.clear();
    myfile.open(path+"deco.txt");
    if (myfile.is_open())
    {
        while (myfile.good())
        {
            string str;
            getline(myfile,line);
            if(line.empty()){
                continue;
            }
            if(line=="\n"){
                continue;
            }
            int j=0;
            stringstream ss(line);
            int temp=0;
            int x;
            int y;
            int rotation;
            float ScaleTempX;
            float ScaleTempY;
            string tex;
            while (getline(ss, str, ';')){
                if(str.empty()){
                    continue;
                }
                if(str=="\n"){
                    continue;
                }

                switch (temp)
                {
                    case 5:
                        ScaleTempY=stof(str);
                        break;
                    case 4:
                        ScaleTempX=stof(str);
                        break;
                    case 3:
                        y=stoi(str);
                        break;
                    case 2:
                        x=stoi(str);
                        break;
                    case 1:
                        rotation=stoi(str);
                        break;
                    case 0:
                        tex=str;
                        break;
                }
                temp++;
            }
            decos.push_back(placeObjectReal(tex,x,y,rotation,ScaleTempX,ScaleTempY));
            decoTexture.push_back(tex);
        }
        myfile.close();
    }
    else 
    {  
        perror("ifstream\n");
        cout << "Unable to open file";
        return;
    }


    places_parking.clear();
    place_park_Text.clear();
    myfile.open(path+"place_parking.txt");
    if (myfile.is_open())
    {
        while (myfile.good())
        {
            string str;
            getline(myfile,line);
            if(line.empty()){
                continue;
            }
            if(line=="\n"){
                continue;
            }
            int j=0;
            stringstream ss(line);
            int temp=0;
            int x;
            int y;
            int rotation;
            float ScaleTempX;
            float ScaleTempY;
            string tex;
            while (getline(ss, str, ';')){
                if(str.empty()){
                    continue;
                }
                if(str=="\n"){
                    continue;
                }

                switch (temp)
                {
                    case 5:
                        ScaleTempY=stof(str);
                        break;
                    case 4:
                        ScaleTempX=stof(str);
                        break;
                    case 3:
                        y=stoi(str);
                        break;
                    case 2:
                        x=stoi(str);
                        break;
                    case 1:
                        rotation=stoi(str);
                        break;
                    case 0:
                        tex=str;
                        break;
                }
                temp++;
            }
            places_parking.push_back(placeObjectReal(tex,x,y,rotation,ScaleTempX,ScaleTempY));
            place_park_Text.push_back(tex);
        }
        myfile.close();
    }
    else 
    {  
        perror("ifstream\n");
        cout << "Unable to open file";
        return;
    }


    loaded=true;

    return;
}


void Level::createLevel(RenderWindow *window,String path){
    if(Keyboard::isKeyPressed(Keyboard::Tab)){
        tabMode=true;
    }
    if(tabMode){
        if(Mouse::isButtonPressed(Mouse::Left)){
            int j=0;
            for(auto i:selectTile){
                if(i.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)){
                    creationTex=j;
                    tabMode=false;
                    clicked=true;
                    printf("%d\n",j);
                }
                j++;
            }
        }
        return;
    }
    if(Keyboard::isKeyPressed(Keyboard::Space)){
        printf("Space\n");
        if(!ChangingMode){
            Mode+=1;
            if(Mode>3){
                Mode=0;
            }
            if(Mode==0){
                creationRotation=90*(creationRotation/90);
            }
            ChangingMode=true;
            printf("Mode :%d\n",Mode);
        }
        
    }
    else{
        ChangingMode=false;
    }



    if(Mode==0){ //mode fond
        printf("Mode :%d\n",Mode);
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
            if(!scaleSwitch){
                scaleXCreate=-scaleXCreate;
                scaleSwitch=true;
                
            }
        }
        else{
            if(Keyboard::isKeyPressed(Keyboard::Left)){
                if(!scaleSwitch){
                    scaleYCreate=-scaleYCreate;
                    scaleSwitch=true;
                }
            }
            else{
                scaleSwitch=false;
            }
        }


        
        

        int x=(Mouse::getPosition(*window).x)/OFFSET;
        int y=(Mouse::getPosition(*window).y)/OFFSET;

        String maTexture;
        std::multimap<string, Texture>::iterator it = textures.begin();
        int temp=0;
        for(;it!=textures.end();++it) {
            if(temp==creationTex){
                maTexture=it->first;
            }
            temp+=1;
        }
        int xPos=x*OFFSET+OFFSET/2;
        int yPos=y*OFFSET+OFFSET/2;

        creation=placeObjectReal(maTexture, xPos, yPos, creationRotation,scaleXCreate,scaleYCreate);
        if(x>=SIZE_MAP_X||y>=SIZE_MAP_Y||x<0||y<0){
            return;
        }
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
        std::ofstream of(path+"non_obstacle.txt");
        if(of.is_open())
        {
            for(int i = 0; i < SIZE_MAP_Y; i++){
                for(int j = 0; j < SIZE_MAP_X; j++){
                    int scaleX=non_obstacles[i*SIZE_MAP_X+j].getScale().x;
                    int scaleY=non_obstacles[i*SIZE_MAP_X+j].getScale().y;
                    if(scaleX>0){
                        scaleX=1;
                    }
                    else{
                        scaleX=-1;
                    }
                    if(scaleY>0){
                        scaleY=1;
                    }
                    else{
                        scaleY=-1;
                    }
                    of<<non_osbstacleMap[i][j].first<<","<<non_osbstacleMap[i][j].second<<","<<scaleX<<","<<scaleY<<";";
                }
                of<<std::endl;
            }
            of.flush();
            of.close();
        }
    }
    if(Mode==1){ //mode obstacle
        if(Keyboard::isKeyPressed(Keyboard::R)){
            if(!rotate){
                creationRotation+=10;
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
            if(!scaleSwitch){
                scaleXCreate=-scaleXCreate;
                scaleSwitch=true;
                
            }
        }
        else{
            if(Keyboard::isKeyPressed(Keyboard::Left)){
                if(!scaleSwitch){
                    scaleYCreate=-scaleYCreate;
                    scaleSwitch=true;
                }
            }
            else{
                if(Keyboard::isKeyPressed(Keyboard::Up)){
                    if(!nextTexture){
                        scale+=0.1;
                        nextTexture=true;
                        
                    }
                }
                else{
                    if(Keyboard::isKeyPressed(Keyboard::Down)){
                        if(!nextTexture){
                            scale-=0.1;
                            nextTexture=true;
                            if(scale<0.1){
                                scale=0.1;
                            }
                        }
                    }
                    else{
                        nextTexture=false;
                    }
                }
            }
            
        }
        
        if(Keyboard::isKeyPressed(Keyboard::BackSpace)){
            for(int i = 0; i < obstacles.size(); i++){
                if(obstacles.at(i).getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)){
                    obstacles.erase(obstacles.begin()+i);
                    obstaclesTexture.erase(obstaclesTexture.begin()+i);
                }
            }
        }

        int x=(Mouse::getPosition(*window).x);
        int y=(Mouse::getPosition(*window).y);

        string   maTexture;
        std::multimap<string, Texture>::iterator it = textures.begin();
        int temp=0;
        for(;it!=textures.end();++it) {
            if(temp==creationTex){
                maTexture=it->first;
            }
            temp+=1;
        }
        creation=placeObjectReal(maTexture, x, y, creationRotation,scale*scaleXCreate,scale*scaleYCreate);

        if(x<0||y<0){
            return;
        }

        if(Mouse::isButtonPressed(Mouse::Left)){
            if(clicked==false){
                printf("x :%d y :%d\n",x,y);
                obstacles.push_back(creation);
                obstaclesTexture.push_back(maTexture);
                clicked=true;
            }
        }
        else{
            clicked=false;
        }

        std::ofstream of(path+"obstacle.txt");
        if(of.is_open())
        {
            printf("obstacle :%d\n",obstacles.size());
            for(int i = 0; i < obstacles.size(); i++){
                string textureReal=obstaclesTexture[i];
                of<<textureReal<<";"<<obstacles[i].getRotation()<<";"<<obstacles[i].getPosition().x<<";"<<obstacles[i].getPosition().y<<";"<<(obstacles[i].getScale().x)<<";"<<(obstacles[i].getScale().y);
                of<<std::endl;
            }
            of.flush();
            of.close();
        }
    }
    if(Mode==2){//mode deco (comme mode obstacle)
        if(Keyboard::isKeyPressed(Keyboard::R)){
            if(!rotate){
                creationRotation+=10;
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
            if(!scaleSwitch){
                scaleXCreate=-scaleXCreate;
                scaleSwitch=true;
                
            }
        }
        else{
            if(Keyboard::isKeyPressed(Keyboard::Left)){
                if(!scaleSwitch){
                    scaleYCreate=-scaleYCreate;
                    scaleSwitch=true;
                }
            }
            else{
                if(Keyboard::isKeyPressed(Keyboard::Up)){
                    if(!nextTexture){
                        scale+=0.1;
                        nextTexture=true;
                        
                    }
                }
                else{
                    if(Keyboard::isKeyPressed(Keyboard::Down)){
                        if(!nextTexture){
                            scale-=0.1;
                            nextTexture=true;
                            if(scale<0.1){
                                scale=0.1;
                            }
                        }
                    }
                    else{
                        nextTexture=false;
                    }
                }
            }
            
        }
        
        if(Keyboard::isKeyPressed(Keyboard::BackSpace)){
            for(int i = 0; i < decos.size(); i++){
                if(decos.at(i).getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)){
                    decos.erase(decos.begin()+i);
                    decoTexture.erase(decoTexture.begin()+i);
                }
            }
        }

        int x=(Mouse::getPosition(*window).x);
        int y=(Mouse::getPosition(*window).y);

        string   maTexture;
        std::multimap<string, Texture>::iterator it = textures.begin();
        int temp=0;
        for(;it!=textures.end();++it) {
            if(temp==creationTex){
                maTexture=it->first;
            }
            temp+=1;
        }
        creation=placeObjectReal(maTexture, x, y, creationRotation,scale*scaleXCreate,scale*scaleYCreate);

        if(x<0||y<0){
            return;
        }
        
        if(Mouse::isButtonPressed(Mouse::Left)){
            if(clicked==false){
                printf("x :%d y :%d\n",x,y);
                decos.push_back(creation);
                decoTexture.push_back(maTexture);
                clicked=true;
            }
        }
        else{
            clicked=false;
        }

        std::ofstream of(path+"deco.txt");
        if(of.is_open())
        {
            printf("obstacle :%d\n",decos.size());
            for(int i = 0; i < decos.size(); i++){
                string textureReal=decoTexture[i];
                of<<textureReal<<";"<<decos[i].getRotation()<<";"<<decos[i].getPosition().x<<";"<<decos[i].getPosition().y<<";"<<(decos[i].getScale().x)<<";"<<(decos[i].getScale().y);
                of<<std::endl;
            }
            of.flush();
            of.close();
        }
    }

    if(Mode==3){//mode place de parking (comme mode obstacle)
        if(Keyboard::isKeyPressed(Keyboard::R)){
            if(!rotate){
                creationRotation+=10;
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
            if(!scaleSwitch){
                scaleXCreate=-scaleXCreate;
                scaleSwitch=true;
                
            }
        }
        else{
            if(Keyboard::isKeyPressed(Keyboard::Left)){
                if(!scaleSwitch){
                    scaleYCreate=-scaleYCreate;
                    scaleSwitch=true;
                }
            }
            else{
                if(Keyboard::isKeyPressed(Keyboard::Up)){
                    if(!nextTexture){
                        scale+=0.1;
                        nextTexture=true;
                        
                    }
                }
                else{
                    if(Keyboard::isKeyPressed(Keyboard::Down)){
                        if(!nextTexture){
                            scale-=0.1;
                            nextTexture=true;
                            if(scale<0.1){
                                scale=0.1;
                            }
                        }
                    }
                    else{
                        nextTexture=false;
                    }
                }
            }
            
        }
        
        if(Keyboard::isKeyPressed(Keyboard::BackSpace)){
            for(int i = 0; i < places_parking.size(); i++){
                if(places_parking.at(i).getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)){
                    places_parking.erase(places_parking.begin()+i);
                    place_park_Text.erase(place_park_Text.begin()+i);
                }
            }
        }

        int x=(Mouse::getPosition(*window).x);
        int y=(Mouse::getPosition(*window).y);

        string   maTexture;
        std::multimap<string, Texture>::iterator it = textures.begin();
        int temp=0;
        for(;it!=textures.end();++it) {
            if(temp==creationTex){
                maTexture=it->first;
            }
            temp+=1;
        }
        creation=placeObjectReal(maTexture, x, y, creationRotation,scale*scaleXCreate,scale*scaleYCreate);

        if(x<0||y<0){
            return;
        }
        
        if(Mouse::isButtonPressed(Mouse::Left)){
            if(clicked==false){
                printf("x :%d y :%d\n",x,y);
                places_parking.push_back(creation);
                place_park_Text.push_back(maTexture);
                clicked=true;
            }
        }
        else{
            clicked=false;
        }

        std::ofstream of(path+"place_parking.txt");
        if(of.is_open())
        {
            printf("place de parking :%d\n",places_parking.size());
            for(int i = 0; i < places_parking.size(); i++){
                string textureReal=place_park_Text[i];
                of<<textureReal<<";"<<places_parking[i].getRotation()<<";"<<places_parking[i].getPosition().x<<";"<<places_parking[i].getPosition().y<<";"<<(places_parking[i].getScale().x)<<";"<<(places_parking[i].getScale().y);
                of<<std::endl;
            }
            of.flush();
            of.close();
        }
    }

}


void Level::loadTextures(){
    Texture t;
    filesystem::path path{"./src/texture/"};
    
    for (auto const& dir_entry : std::filesystem::directory_iterator{ path }){
        auto path=dir_entry.path();
        if (!t.loadFromFile(path)){ std::cout << "Error: Couldn't load texture\n";}{
            textures.insert(pair<string, Texture>(path.filename(), t));
            
        }
    }
    
    int i=0;
    for(auto t:textures){
        selectTile.push_back(placeObject(t.first,i%16,int((i-i%16)/16),0,1));
        i++;
    }
}



void Level::loadObstacles(){
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

Sprite Level::placeObject(string image, int x, int y, int rotation,float scale){
    Sprite obs;
    if(!textures.count(image)){
        return obs;
    }
    Vector2u s=textures.at(image).getSize();
    float xRatio=(64.0/float(s.x))*scale;
    float yRatio=(64.0/float(s.y))*scale;



    obs.scale({xRatio,yRatio});
    if(textures.count(image)){
        obs.setTexture(textures.at(image));
    }
    else{
        
    }
    
    
    obs.setRotation(rotation);
    obs.setPosition(x*OFFSET+OFFSET/2, y*OFFSET+OFFSET/2);
    centerOrigin(&obs);
    return obs;
}

Sprite Level::placeObjectFix(string image, int x, int y, int rotation,float scale){
    Sprite obs;
    if(!textures.count(image)){
        return obs;
    }
    Vector2u s=textures.at(image).getSize();
    float xRatio=(64.0/float(s.x))*scale;
    float yRatio=(64.0/float(s.y))*scale;
    obs.scale({xRatio,yRatio});
    printf("ffF %s\n",image.c_str());
    if(textures.count(image)){
        obs.setTexture(textures.at(image));
    }
    obs.setRotation(rotation);
    obs.setPosition(x, y);
    centerOrigin(&obs);
    return obs;
}


Sprite Level::placeObjectReal(string image, int x, int y, int rotation,float scaleX,float scaleY){
    Sprite obs;
    if(!textures.count(image)){
        return obs;
    }
    Vector2u s=textures.at(image).getSize();
    obs.scale({scaleX,scaleY});
    printf("ffF %s\n",image.c_str());
    if(textures.count(image)){
        obs.setTexture(textures.at(image));
    }
    obs.setRotation(rotation);
    obs.setPosition(x, y);
    centerOrigin(&obs);
    return obs;
}