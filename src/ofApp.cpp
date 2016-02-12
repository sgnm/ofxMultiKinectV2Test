#include "ofApp.h"

#define STRINGIFY(x) #x
#define W 640
#define H 480

static string depthFragmentShader =
STRINGIFY(
      uniform sampler2DRect tex;
      uniform float near;
      uniform float far;
          
      void main()
      {
          vec4 col = texture2DRect(tex, gl_TexCoord[0].xy);
          float value = col.r;
          float low1 = near;
          float high1 = far;
          float low2 = 1.0;
          float high2 = 0.0;
          float d = clamp(low2 + (value - low1) * (high2 - low2) / (high1 - low1), 0.0, 1.0); //d is between 0.0~1.0
          if (d == 1.0) {
              d = 0.0;
          }
          gl_FragColor = vec4(vec3(d), 1.0);
      }
//          const float R_LUMINANCE = 0.298912;
//          const float G_LUMINANCE = 0.586611;
//          const float B_LUMINANCE = 0.114478;
//          uniform sampler2DRect tex;
//          uniform float threshold;
//          void main(){
//              vec4 color = texture2DRect(tex, gl_TexCoord[0].xy);
//              float thres = threshold / 255.0;
//              float val = color.x * R_LUMINANCE + color.y * G_LUMINANCE + color.z * B_LUMINANCE;
//              if (val <= thres) {
//                  val = 1.0;
//              } else {
//                  val = 0.0;
//              }
//              gl_FragColor = vec4(vec3(val), 1.0);
//          }
  );


//--------------------------------------------------------------
void ofApp::setup(){
    depthShader.setupShaderFromSource(GL_FRAGMENT_SHADER, depthFragmentShader);
    depthShader.linkProgram();
    
    kinect.open();
    kinect.start();
    
    gui.setup();
    gui.add(near.set("near", 500, 0, 1000));
    gui.add(far.set("far", 5000, 500, 10000));
    gui.add(threshold.set("threshold", 100, 0, 255));
    
    depthFbo.allocate(W, H);
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    if (kinect.isFrameNew()){
        colorTex.loadData(kinect.getColorPixelsRef());
        depthTex.loadData(kinect.getDepthPixelsRef());

        //TODO: shaderでやる
        depthFbo.begin();
            depthShader.begin();
                depthShader.setUniform1f("near", near);
                depthShader.setUniform1f("far", far);
                depthShader.setUniform1f("threshold", threshold);
                depthTex.draw(0, 0, W, H);
            depthShader.end();
        depthFbo.end();
        
        depthFbo.draw(0, 0, W, H);
        
        ofPixels p;
        depthFbo.readToPixels(p);
        grayImg.setFromPixels(p);
        contour.findContours(grayImg, 100, W*H, 5, true);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (colorTex.isAllocated()){
        colorTex.draw(W, 0, W, H);
        depthFbo.draw(0, 0, W, H);
        contour.draw();
    }
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case 'f':
            ofToggleFullscreen();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
