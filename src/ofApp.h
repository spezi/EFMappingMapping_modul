#pragma once

#include "ofMain.h"
#include "mapping.h"
#include "lineanim.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void Pathinator(vector<glm::vec3> vertices, int index, bool draw);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    vector <vector <glm::vec3>> vectorslist;

    bool mod_mapping;

    bool    bFullscreen;

    Mapping mapping;
    Lineanim lineanim;

    ofPath outline;
    ofMesh mesh;


    ofVbo vbo;
    ofEasyCam camera;

};
