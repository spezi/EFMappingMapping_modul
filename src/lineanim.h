#pragma once

#include "ofMain.h"
#include "ofxFatLine.h"


class Lineanim
{
    private:
        vector <vector<glm::vec3>> vectorslist;
        bool    lines;
        ofPath path;
        vector <ofPath> pathstack;
        vector <ofxFatLine> fatLinestack;



        int linemode;

        ofMatrix4x4 matrix;


    private:
        void Pathinator(vector<glm::vec3> vertices, int index, bool draw);
        void PathinatorFine(vector<glm::vec3> vertices, int index);
        void Scaleton(ofPath temppath, glm::vec3 original_center);
        void ScaletonFatLines(ofxFatLine temppath, glm::vec3 original_center);
        void ScaletonMesh(ofPath temppath, glm::vec3 original_center);
        void ConnectAnim(ofPolyline temppoly);
        void LineAnim(ofPolyline temppoly);
        void RandomConnector(ofPolyline temppoly);


    public:
        Lineanim();
        void setup(vector <vector<glm::vec3>> ivectorlist);
        void update();
        void draw();

        void keyPressed(int key);

    public:
        bool gotvertices;
        bool outline;
        ofShader shader;
        ofMesh tessellation;
        ofVbo vbo;
        float pct;
        float pct2;



        void FatLineinator(vector<glm::vec3> vertices);
};


