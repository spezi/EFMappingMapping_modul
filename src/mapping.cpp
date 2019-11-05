#include "mapping.h"

Mapping::Mapping()
{

}

//--------------------------------------------------------------
void Mapping::setup(){
    bpaining = false;
    painted = false;
    edit = false;

    lines = false;
    snapping = true;
    catchpath = 0;

    crosshair =  false;



    nearest_distance = 99999;
    selected = 99999999;
}

//--------------------------------------------------------------
void Mapping::update(){
    if(!bpaining && painted) {
        cout << "trigger : !bpaining && painted" << " " << endl;
        vectorslist.push_back(vertices_global);
        vertices_global.clear();
        painted = false;
    }

    dragging = false;

   // if (line.size() > 200){
   //     line.getVertices().erase(
   //                              line.getVertices().begin()
   //                              );
   // }
    bool del = false;
    bool wiggle = false;

    if (vectorslist_fine.size() > 0) {
            for(vector<glm::vec3> & vector : vectorslist_fine) {
                if(vector.size() > 8 && del) {
                     std::vector<glm::vec3> vector_temp;
                    //vector.pop_back();

                    vector.erase(vector.begin(), vector.begin()+4);
                    vector.erase(vector.end()-4, vector.end());
                }
                if(wiggle) {
                    for(glm::vec3 & vert : vector) {
                        vert.x += ofRandom(-1,1);
                        vert.y += ofRandom(-1,1);
                    }
                }

               // vector.erase(vector.end());
            }

    }
}

//--------------------------------------------------------------
void Mapping::draw(){
    if(crosshair){
        ofSetColor(255);
        ofSetLineWidth(1);
        ofDrawLine(0, mouse.y, ofGetWidth(), mouse.y);
        ofDrawLine(mouse.x, 0, mouse.x, ofGetHeight());
    }

    //debug output
    ofSetColor(ofColor::white);
    if(edit) ofDrawBitmapString("edit",20,20);
    if(bpaining) ofDrawBitmapString("painting",20,20);
    if(painted) ofDrawBitmapString("painted",20,40);

    if(bpaining) {
       draw_vertices_global();
    }



    if(vectorslist.size() > 0 ) {
        paintPathVectorlist();

    }

    if(vectorslist.size() > 0 ) {
        paintPathVectorlistFine();
    }
}

void Mapping::draw_vertices_global() {
    //cout << "draw vertices: " <<  vertices_global[nearestIndex] << " " << endl;
    Pathinator(vertices_global, 0, true);
    drawHandles(vertices_global);
}

void Mapping::paintPathVectorlist() {
    for (int i = 0; i < vectorslist.size(); i++){
        Pathinator(vectorslist[i], i, true);
        //PathinatorFine(vectorslist[i], i);
        if(edit && i == selected)drawHandles(vectorslist[i]);
    }
}

void Mapping::paintPathVectorlistFine() {
    if(catchpath) {
        catchpath = false;
        vectorslist_fine.clear();
        for (int i = 0; i < vectorslist.size(); i++){
            //Pathinator(vectorslist[i], i, true);
            PathinatorFine(vectorslist[i], i, false);
            if(edit && i == selected)drawHandles(vectorslist[i]);
        }
    }

    //for (int i = 0; i < vectorslist_fine.size(); i++){
    //    Pathinator(vectorslist_fine[i], i, true);
    //    if(edit && i == selected)drawHandles(vectorslist_fine[i]);
    //}
}


void Mapping::drawHandles(vector<glm::vec3> vertices) {

    ofNoFill();

    for (int i = 0; i < vertices.size(); i++){
        if(i != nearestIndex) {
            ofSetColor(ofColor::white);
            ofDrawCircle(vertices[i], 10);
        } else {
            ofSetColor(ofColor::blueSteel);
            ofDrawCircle(vertices[i], 10);
        }
    }
}

void Mapping::Pathinator(vector<glm::vec3> vertices, int index, bool draw) {

    ofPath path;
    //cout << "vertices size: " <<  vertices.size() << " " << endl;
    if (vertices.size() > 0 ) {

        for (int i = 0; i <= vertices.size(); i++){

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
        if(lines) {
            path.setStrokeColor(ofColor(255, 255, 255));
            path.setStrokeWidth(1);
            path.setFilled(false);
        } else {
            path.setFilled(true);
        }

        if(draw) path.draw();

    }
}

void Mapping::PathinatorFine(vector<glm::vec3> vertices, int index, bool draw) {

    ofPath path;
    path.setMode(ofPath::POLYLINES);

    //cout << "vertices size: " <<  vertices.size() << " " << endl;
    if (vertices.size() > 0) {

        for (int i = 0; i <= vertices.size(); i++){

            if ( i == 0 ) {
                path.moveTo(vertices[i].x,vertices[i].y);
                //cout << "poli: " <<  line.getVertices()[i].x << " " << endl;
            } else if ( i == vertices.size()){
                path.lineTo(vertices[0].x,vertices[0].y);
                path.close();
                //cout << "poli: " <<  vertices.size() << " " << endl;
            }else {
                path.lineTo(vertices[i].x,vertices[i].y);
            }

        }




        //ofPolyline countPoly = path.getResampledByCount( 100 );
        //ofPolyline spacePoly = path.getResampledBySpacing( 10 );

         //cout << "origPoly.size(): " << origPoly.size() << " countPoly.size(): " << countPoly.size() << " spacePoly.size(): " << spacePoly.size() << endl;

           // Feine Linien malen
           //ofPolyline newline;
           auto & lines = path.getOutline();


           for(auto & element : lines) {
                cout << element.size() << endl;
                ofPolyline new_element = element.getVertices();
                ofPolyline new_new_element = new_element.getResampledBySpacing( 1 );

                //new_element.draw();
                cout << new_new_element.size() << endl;
                vectorslist_fine_polyl.push_back(new_new_element);
                vectorslist_fine.push_back(new_new_element.getVertices());
                //new_element.draw();
           }

           //for (int i = 0; i <= lines.size(); i++){
           //    ofPolyline newline = lines[i];
               //ofPolyline newlinefine = newline.getResampledBySpacing( 10 );
               //vectorslist_fine.push_back(newline.getVertices());
               //std::cout << i << std::endl;
           //    //newline.draw();
           //}
           //ofPolyline newline = line.getResampledBySpacing( 1 );
           //std::cout << lines[0].getVertices().size() << std::endl;
           //std::cout << newline.getVertices().size() << std::endl;
           //for(auto & v : line.getVertices()) {
           //for(auto & element : line) {
           //
           //}



        //newline.draw();
        if(draw) path.draw();

    }
}
void Mapping::nearest_detection(int x, int y) {

    //glm::vec3   MousePosition(ofGetMouseX(), ofGetMouseY(), 0);
    glm::vec3   MousePosition(x, y, 0);
    glm::vec3   cur;
    if(selected <= vectorslist.size()) {
        for (int i = 0; i < vectorslist[selected].size(); i++){
            glm::vec3 cur = vectorslist[selected][i];
            float distance = glm::distance(MousePosition, cur);
            if( distance < 30) {
                nearest_distance = distance;
                nearestIndex = i;
                //cout << "distance < 30 : " <<  nearestIndex << " " << endl;
            }
        }
    }
}

void Mapping::select_detection(int x, int y) {
    // select detection

    ofPath checkpath;

    selected = 99999999;

    for (int i = 0; i < vectorslist.size(); i++){
        for (int j = 0; j < vectorslist[i].size(); j++){
            if ( j == 0 ) {
                checkpath.moveTo(vectorslist[i][j].x,vectorslist[i][j].y);
                //cout << "poli: " <<  line.getVertices()[i].x << " " << endl;
            } else if ( j == vectorslist[i].size()){
                checkpath.close();
            }else {
                checkpath.lineTo(vectorslist[i][j].x,vectorslist[i][j].y);
                //cout << "poli2: " <<  line.getVertices()[i].x << " " << endl;
            }

            // select detection
            bool select = checkpath.getOutline().back().inside(x, y);
            if(select) {
                selected = i;
                //cout << "hit: " <<  i << " " << endl;
            }
        }
    }

    //cout << "checkpath: " <<  checkpath.getCommands().size() << " " << endl;
    //cout << "checkclickpoint: " <<  x << " " << endl;
}

void Mapping::snapTo() {

    //vectorslist[selected][nearestIndex].x = x;
    //vectorslist[selected][nearestIndex].y = y;

    for (int i = 0; i < vectorslist.size(); i++){
        for (int j = 0; j < vectorslist[i].size(); j++){
            glm::vec3 current = vectorslist[i][j];
            float distance = glm::distance(vectorslist[selected][nearestIndex], current);
            if( distance < 30) {
                vectorslist[selected][nearestIndex] = vectorslist[i][j];
                cout << "snap to : " <<  i << j << " " << endl;
            }
        }
    }

}

void Mapping::SaveSvg(){
    ofBeginSaveScreenAsSVG("data/test.svg");
        paintPathVectorlist();
    ofEndSaveScreenAsSVG();
}

vector <vector <glm::vec3>> Mapping::getVectorsList(){
    cout << "getVectorsList()" << endl;
    cout << "vectorslist size : getVectorsList()" <<  vectorslist.size() << " " << endl;
    return vectorslist;
}

//--------------------------------------------------------------
void Mapping::keyPressed(int key){
    cout << key << endl;

    if(key == 'p'){
        edit = false;
        bpaining = !bpaining;
    } else if (key == 'e') {
        bpaining = false;
        edit = !edit;
    } else if (key == 'l') {
        lines = !lines;
    } else if (key == 'x'){
        crosshair =  !crosshair;
    } else if (key == 's'){
        SaveSvg();
    }

}

//--------------------------------------------------------------
void Mapping::keyReleased(int key){

}

//--------------------------------------------------------------
void Mapping::mouseMoved(int x, int y ){
    if(!dragging && edit) nearest_detection(x, y);
     mouse = glm::vec3(x, y, 0);

    //cout << "MOUSE: " <<  x << ":" << y << " " << endl;
}

//--------------------------------------------------------------
void Mapping::mouseDragged(int x, int y, int button){
    if (edit && nearest_distance < 15 && selected <= vectorslist.size()) {
        //vertices_global[nearestIndex].x = x;
        //vertices_global[nearestIndex].y = y;
        vectorslist[selected][nearestIndex].x = x;
        vectorslist[selected][nearestIndex].y = y;

        if(snapping) snapTo();

        //cout << "MOUSE: " <<  vertices_global[nearestIndex] << " " << endl;
    }

    dragging = true;

}

//--------------------------------------------------------------
void Mapping::mousePressed(int x, int y, int button){
    if(bpaining){
        clickpoint.x = x;
        clickpoint.y = y;
        clickpoint.z = 0;
        vertices_global.push_back(clickpoint);
        painted = true;
    } else {
        //clickpoint.x = 0;
        //clickpoint.y = 0;
        //clickpoint.z = 0;
    }


    if(!dragging) select_detection(x, y);


    //debug
    cout << "MOUSE: " <<  clickpoint << " " << endl;
    cout << "vertices: " <<  vertices_global.size() << " " << endl;
    cout << "vectorslist: " <<  vectorslist.size() << " " << endl;
    cout << "vectorslistfine: " <<  vectorslist_fine.size() << " " << endl;
    if ( vectorslist_fine.size() > 0 ) cout << "vectorslistfine 0 : " <<  vectorslist_fine[0].size() << " " << endl;
    cout << "nearest: " <<  nearestIndex << " " << endl;
    cout << "nearest_distance: " <<  nearest_distance << " " << endl;
    cout << "selected: " <<  selected << " " << endl;
    cout << "dragging: " <<  dragging << " " << endl;
    cout << "crosshair: " <<  crosshair << " " << endl;
}

//--------------------------------------------------------------
void Mapping::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Mapping::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void Mapping::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void Mapping::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Mapping::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Mapping::dragEvent(ofDragInfo dragInfo){

}

