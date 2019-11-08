#include "lineanim.h"

Lineanim::Lineanim()
{
      gotvertices = false;
}



void Lineanim::setup(vector <vector<glm::vec3>> ivectorlist) {
    cout << "lineanim setup()" << endl;
    cout << "lineanim update()" << endl;
    cout << "lineanim vectorlist.size()" << ivectorlist.size() << endl;
    if(ivectorlist.size() > 0 ) {
        vectorslist = ivectorlist;
        gotvertices = true;
    } else {
        vectorslist.clear();
        gotvertices = false;
    }

    lines =false;

    if(gotvertices) {
        for (int i = 0; i < vectorslist.size(); i++){
            Pathinator(vectorslist[i], i, false);
            FatLineinator(vectorslist[i]);
        }
    }

    shader.load("data/shader/shader");
    ofMesh tessellation = path.getTessellation();

    //vbo.setVertexData(path, path.getOutline().back().getVertices().size(), GL_STATIC_DRAW);
    path.setMode(ofPath::Mode::POLYLINES);

    outline = true;

    pct = 0;

}

void Lineanim::update(){



}



void Lineanim::draw(){


     //ofPushMatrix();
     //ofRotateZ(ofGetElapsedTimef());
     //ofRotateRad(90, original_center.x, original_center.y, original_center.z);
     //path.draw();
     //ofPopMatrix();
     //path.draw();
     //matrix.rotate((ofGetElapsedTimef()*2), original_center.y,original_center.y,0);

     //matrix.scale(0.8,0.8,0.8);



    // draw
    //vbo.draw(GL_LINE_STRIP, path.getOutline().begin(), path.getOutline().size());

     //ofMultMatrix(matrix);


    //ofPushMatrix();
        //glm::vec3 original_center = path.getOutline().back().getBoundingBox().getCenter();
        //ofScale(0.8);
        //glm::vec3 new_center = path.getOutline().back().getBoundingBox().getCenter();
        //path.translate(original_center-new_center);
    //ofPopMatrix();
    //shader.begin();
     //path.draw();
    // tessellation.drawWireframe();
    //shader.end();

    //path.draw();

    //temppath.getOutline().back().ge



    //cout << "path stuff" << pathstack.size() << endl;
    if(linemode == 1) {
        for (int p = 0; p < pathstack.size() ; p++){

           ofPath temppath = pathstack[p];
           glm::vec3 original_center = pathstack[p].getOutline().back().getBoundingBox().getCenter();

           // draw fullscale path
           if(outline) temppath.draw();

           Scaleton(temppath, original_center);


       }
    }

    if(linemode == 2) {
        for (int p = 0; p < fatLinestack.size() ; p++){

           ofxFatLine temppath = fatLinestack[p];
           glm::vec3 original_center = temppath.getCentroid2D();

           // draw fullscale path
           //if(outline) temppath.draw();

           //Scaleton(temppath, original_center);
           //fatLinestack[p].drawDebug();
           if(outline) temppath.draw();
           ScaletonFatLines(temppath, original_center);
       }
    }

    if(linemode == 3) {
        for (int p = 0; p < pathstack.size() ; p++){

           ofPath temppath = pathstack[p];
           glm::vec3 original_center = pathstack[p].getOutline().back().getBoundingBox().getCenter();

           // draw fullscale path
           if(outline) temppath.draw();
           temppath.setFilled(true);
           ScaletonMesh(temppath, original_center);


       }
    }

    if(linemode == 4) {
        for (int p = 0; p < pathstack.size() ; p++){

           ofPath temppath = pathstack[p];
           glm::vec3 original_center = pathstack[p].getOutline().back().getBoundingBox().getCenter();

           // draw fullscale path
           if(outline) temppath.draw();
           temppath.setFilled(false);
           ofPolyline temppoly = temppath.getOutline().back();
           ConnectAnim(temppoly);
       }
    }

    if(linemode == 5) {
        for (int p = 0; p < pathstack.size() ; p++){

           ofPath temppath = pathstack[p];

           // draw fullscale path
           //if(outline) temppath.draw();
           temppath.setFilled(false);
           ofPolyline temppoly = temppath.getOutline().back().getResampledBySpacing(1);
           LineAnim(temppoly);
       }
    }



}

void Lineanim::keyPressed(int key){
    cout << "lineanim draw()" << endl;
    cout << "lineanim verticies" << vectorslist.size() << endl;
    if(key == 'l') {
        lines = !lines;
    } else if(key == 'o') {
        outline = !outline;
    } else if(key == '1') {
        linemode = 1;
    } else if(key == '2') {
        linemode = 2;
    } else if(key == '3') {
        linemode = 3;
    } else if(key == '4') {
        linemode = 4;
    } else if(key == '5') {
        linemode = 5;
        cout << "pathstack.size: " <<  pathstack.size() << " " << endl;
    }

}

void Lineanim::Pathinator(vector<glm::vec3> vertices, int index, bool draw) {

    path.clear();
    //cout << "vertices size: " <<  vertices.size() << " " << endl;
    if (vertices.size() > 0 ) {

        for (int i = 0; i <= vertices.size(); i++){

            if ( i == 0 ) {
                path.moveTo(vertices[i].x,vertices[i].y);
                //mesh.addVertex(vertices[i]);
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

        //cout << "vertices size: " << " " << endl;
        //path.tessellate();

            path.setStrokeColor(ofColor(255, 255, 255));
            path.setStrokeWidth(1);
            path.setFilled(false);


        if(draw) path.draw();
        pathstack.push_back(path);


    }
}

void Lineanim::FatLineinator(vector<glm::vec3> vertices) {
    ofFloatColor c; c.setHsb(ofRandom(1), 1, 1 );
    vector<ofFloatColor> colors;
    vector<double> weights;
    vector<ofDefaultVec3> points;
    ofxFatLine fatLine;

    for (int i = 0; i <= vertices.size(); i++){

        colors.push_back(c);
        weights.push_back(3);

        if ( i == 0 ) {
            fatLine.addVertex(vertices[i]);
        } else if ( i == vertices.size()){
            fatLine.addVertex(vertices[0]);
            fatLine.close();
        }else {
            fatLine.addVertex(vertices[i]);
        }



    }

    //enum ofxFatLineJointType{
    //    OFX_FATLINE_JOINT_MITER,
    //    OFX_FATLINE_JOINT_BEVEL,
    //    OFX_FATLINE_JOINT_ROUND
    //};
    //enum ofxFatLineCapType{
    //    OFX_FATLINE_CAP_BUTT,
    //    OFX_FATLINE_CAP_ROUND,
    //    OFX_FATLINE_CAP_SQUARE,
    //    OFX_FATLINE_CAP_RECT
    //};


    //fatLine.setFeather(2);
    //fatLine.setCapType(OFX_FATLINE_CAP_ROUND);
    //fatLine.setJointType(OFX_FATLINE_JOINT_ROUND);
    fatLine.enableFeathering(true);
    fatLine.add(points, colors, weights);
    fatLine.close();

    fatLinestack.push_back(fatLine);
}


void Lineanim::Scaleton(ofPath temppath, glm::vec3 original_center) {
    for (int i = 0; i <= 10 ; i++){

            ofPushMatrix();

            //float scale =  ofMap(sin(ofGetElapsedTimef()), -1, 1, 0, 1);
            float scale =  fmod(ofGetElapsedTimef(),1);

            //if(scale > 0) {
                temppath.scale(scale, scale);

            //}

            temppath.scale(0.9,0.9);
            //temppath.translate()
            glm::vec3 temppath_center = temppath.getOutline().back().getBoundingBox().getCenter();
            temppath.translate(original_center-temppath_center);
            //temppath.setStrokeColor(ofColor(sin(ofGetElapsedTimef()), sin(ofGetElapsedTimef()), sin(ofGetElapsedTimef())));
            temppath.setStrokeWidth(ofMap(sin(ofGetElapsedTimef()), -1, 1, 0, 40));
            temppath.draw();
            ofPopMatrix();


    }
}

void Lineanim::ScaletonFatLines(ofxFatLine temppath, glm::vec3 original_center) {
    for (int i = 0; i <= 10 ; i++){

            ofPushMatrix();

            //float scale =  ofMap(sin(ofGetElapsedTimef()), -1, 1, 0, 1);
            float scale =  fmod(ofGetElapsedTimef(),1);




            //temppath.translate()
            //glm::vec3 temppath_center = temppath.getOutline().back().getBoundingBox().getCenter();
            glm::vec3 temppath_center = temppath.getCentroid2D();
            //temppath.translate(original_center-temppath_center);

            glm::vec3 scaleCenter;// set this to the point around which you want to scale.
            float scaleFactor = scale;

            //for( int i = 0; i < temppath.getVertices().size(); i++ ) {
            //    temppath.getVertices()[i] = temppath.getVertices()[i] - temppath_center;
            //}

            for( int i = 0; i < temppath.getVertices().size(); i++ ) {
                //temppath.getVertices()[i] = temppath.getVertices()[i]-scale;
                temppath[i] = temppath[i] - original_center;
            }


            //for(auto & v: temppath.getMesh()){
            //    v = (v - scaleCenter)*scaleFactor + scaleCenter;
            //}

            //temppath.set
            ofTranslate(original_center-temppath_center);
            ofScale(scale,scale);


            temppath.draw();
            ofPopMatrix();


    }
}

void Lineanim::ScaletonMesh(ofPath temppath, glm::vec3 original_center) {
    ofVboMesh vboMesh = temppath.getTessellation();
    vboMesh.setupIndicesAuto();
    vboMesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    for (int i = 0; i <= 10 ; i++){

        vboMesh.draw();

    }
}

void Lineanim::ConnectAnim(ofPolyline temppoly){
    for (float i = 0; i < temppoly.getVertices().size();){
            i = i + 0.05f;
            glm::vec3 temppoint_front = temppoly.getPointAtIndexInterpolated(i);
            glm::vec3 temppoint_back = temppoly.getPointAtIndexInterpolated(ofMap(ofGetElapsedTimef()/2, 0, 1, i-3, i*TWO_PI));
            //ofDrawCircle(temppoint, 10);
            ofPolyline partline;
            partline.addVertex(temppoint_back);
            partline.lineTo(temppoint_front);
            partline.draw();
    }
}

void Lineanim::LineAnim(ofPolyline temppoly){
    ofPolyline lineanimpoly;
     ofSetLineWidth(50);

    pct += 0.0002f;		// increase by a certain amount
    if (pct > 1) {
        pct = 0;	// just between 0 and 1 (0% and 100%)
    }

    int linesize = (temppoly.size()/8);
    //int linesize = 200;

    int pointer = ofMap(pct, 0, 1, 0, temppoly.size());

    //lineanimpoly.addVertex(temppoly.getVertices()[pointer]);

    int length;
    int overflow = 0;

    for (int i = 0; i <= linesize ;i++){

            length = pointer+i;

            if(length == 0) cout << "temppolysize : " << temppoly.size()  << endl;

            if( length < temppoly.size()) {
                lineanimpoly.addVertex(temppoly.getVertices()[length]);
            } else {
                //cout << "length: "  << length  << endl;
                //cout << "pointer: " << pointer  << endl;

                //lineanimpoly.addVertex(temppoly.getVertices()[pointer]);
                overflow = (length - temppoly.size());
            }



    }

    if(overflow > 0) {
        for (int i = 0; i <= overflow ;i++){
            //if( i== 0 )cout << "overflow:" << endl;
            lineanimpoly.addVertex(temppoly.getVertices()[i]);
        }
    }

    lineanimpoly.draw();

    //cout << "pointer: " << pointer << endl;


}

