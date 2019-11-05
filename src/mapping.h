#pragma once

#include "ofMain.h"

class Mapping {

    public:
        Mapping();
        void setup();
        void update();
        void draw();
        vector <vector <glm::vec3>> getVectorsList();
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

    private:
        void draw_vertices_global();
        void nearest_detection(int x, int y);
        void select_detection(int x, int y);
        void paintPathVectorlist();
        void paintPathVectorlistFine();
        void drawHandles(vector<glm::vec3> vertices);
        void Pathinator(vector<glm::vec3> vertices, int index, bool draw);
        void PathinatorFine(vector<glm::vec3> vertices, int index, bool draw);
        void animPathVectorlistFine();
        void snapTo();
        void SaveSvg();

        bool    bpaining;
        bool    painted;
        bool    edit;
        bool    lines;
        bool    snapping;
        bool    dragging;
        bool    catchpath;

        bool    crosshair;

        float   nearest_distance;
        int     selected;
        int     nearestIndex;

        glm::vec3 clickpoint;
        glm::vec3 mouse;

        vector<glm::vec3> vertices_global;
        vector < vector<glm::vec3> > vectorslist;
        vector < vector<glm::vec3> > vectorslist_fine;
        vector <ofPolyline> vectorslist_fine_polyl;
};

