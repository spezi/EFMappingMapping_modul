#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mapping.setup();
    //lineanim.setup(vectorslist);

    svg.load("test.svg");
    cout << "svg size" << svg.getPaths().size() << endl;

    if(svg.getPaths().size() > 0) {
        for (ofPath p: svg.getPaths()){
            // svg defaults to non zero winding which doesn't look so good as contours
            p.setPolyWindingMode(OF_POLY_WINDING_ODD);
            const vector<ofPolyline>& lines = p.getOutline();

            for(const ofPolyline & line: lines){
                vectorslist.push_back(line.getVertices());
                cout << "vectorslist svg size" << vectorslist.size() << endl;
            }
            vectorslist.pop_back();
            lineanim.setup(vectorslist);
        }
    }

    ofSetVerticalSync(false);
    ofBackground(0);

    ofEnableSmoothing();
    glEnable(GL_DEPTH_TEST);

    mesh.addColor(ofFloatColor(255,255,255));

    mod_mapping = false;
    bFullscreen = false;

}

//--------------------------------------------------------------
void ofApp::update(){
    if(mod_mapping) mapping.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofDrawBitmapString(ofGetFrameRate(),500,20);

    if(mod_mapping) {
        mapping.draw();
        ofDrawBitmapString("mod mapping",100,20);
    } else {
        //if(lineanim.gotvertices)lineanim.draw();
    }

    lineanim.draw();

    //if(outline.getOutline().size() >= 0 ) {
    //    for (int i = 0; i < vectorslist .size(); i++){
    //        Pathinator(vectorslist [i], i, false);
    //    }
    //}

    //outline.setStrokeColor(ofColor(255, 255, 0));
    //outline.setStrokeWidth(1);
    //outline.setFilled(false);
    //outline.draw();

      //vbo.setMesh(mesh, GL_STATIC_DRAW);

      //camera.begin();
      //ofScale(100,100,100);

      //vbo.draw(GL_TRIANGLE_STRIP,0,24);
}

void ofApp::Pathinator(vector<glm::vec3> vertices, int index, bool draw) {

    ofPath path;
    //cout << "vertices size: " <<  vertices.size() << " " << endl;
    if (vertices.size() > 0 ) {

        for (int i = 0; i <= vertices.size(); i++){
            mesh.addVertex(glm::vec3(vertices[i].x,vertices[i].y,vertices[i].z));
            if ( i == 0 ) {
                path.moveTo(vertices[i].x,vertices[i].y);

                //cout << "poli: " <<  line.getVertices()[i].x << " " << endl;
            } else if ( i == vertices.size()){
                //path.lineTo(vertices[0].x,vertices[0].y);
                path.close();
                //cout << "poli: " <<  vertices.size() << " " << endl;
            }else {
                path.lineTo(vertices[i].x,vertices[i].y);
            }

        }

        path.setFillColor(ofColor(255, 255, 255));

            path.setStrokeColor(ofColor(255, 255, 255));
            path.setStrokeWidth(1);
            path.setFilled(false);

        if(draw) path.draw();
        outline = path;
        vbo.setMesh(mesh, GL_STATIC_DRAW);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(mod_mapping) mapping.keyPressed(key);
    lineanim.keyPressed(key);

    switch (key){
            case 'm':
                mod_mapping = !mod_mapping;
                if(!mod_mapping) {
                    lineanim.setup(vectorslist);
                    vectorslist = mapping.getVectorsList();
                    cout << "vectorslist size: " <<  vectorslist.size() << " " << endl;
                }
            default:
                break;
    }

    if ( key == 'f' ){
        bFullscreen = !bFullscreen;
        if(!bFullscreen){
            ofToggleFullscreen();
        } else if(bFullscreen == 1){
            ofToggleFullscreen();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    if(mod_mapping) mapping.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(mod_mapping) mapping.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(mod_mapping) mapping.mousePressed(x,y, button);

    //cout << "vectorslist size: " <<  vectorslist.size() << " " << endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(mod_mapping) cout << "mapping vectorlist: " <<  vectorslist.size() << " " << endl;
    if(mod_mapping) cout << "outline size: " <<  outline.getOutline().size() << " " << endl;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
