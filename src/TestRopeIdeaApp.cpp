#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Context.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace ci;
using namespace ci::app;
using namespace std;

class TestRopeIdeaApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    ifstream myfile;
    string line;
    std::vector<vector<float> > frames;
    int frameCount = 0;
};

void TestRopeIdeaApp::setup()
{
    fs::path pathToFile = getAssetPath("BeritTake1.csv");
    myfile.open(pathToFile.c_str(), ifstream::in);
    if (myfile.is_open())
    {
        int lineCount = 0;
        while ( myfile.good() )
        {
            getline(myfile,line);
            if (lineCount > 6) {
                string word;
                stringstream stream(line);
                std::vector<string> frameList;
                std::string token;
                while(std::getline(stream, token, ',')) {
                    frameList.push_back(token);
                }
                vector<float> newFrame;
                bool addIt = true;
                // first two frames meta data, then 49 joints * xyz positions (147 data points)
                if(frameList.size() > 2) {
                    for(int i=2; i<149; i++){
                        if(!frameList.at(i).empty()){
                            newFrame.push_back(stof(frameList.at(i)));
                        } else {
                            addIt = false;
                            break;
                        }
                    }
                }
                if(addIt) {
                    frames.push_back(newFrame);
                }
            }
            lineCount += 1;
        }
        cout << "done!" << endl;
        cout << "size: " << frames.size() << endl;
        myfile.close();
    } else {
        cout << "unable to open file" <<endl;
    }
}

void TestRopeIdeaApp::mouseDown( MouseEvent event )
{
}

void TestRopeIdeaApp::update()
{
}

void TestRopeIdeaApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    // reset the matrices
    gl::setMatricesWindow( getWindowSize() );
    // move to the window x center and the 'floor' of the screen
    gl::translate( getWindowCenter().x, getWindowHeight() );
    gl::rotate(M_PI);
//    gl::scale(100, 100, 100);
    gl::color(1.0, 0, 0);
    auto temp  = frames.at(frameCount);
    for(int i=0; i<temp.size(); i+=3){
        gl::drawSphere(vec3(temp.at(i)*150, temp.at(i+1)*150, temp.at(i+2)*15), 10, 10);
    }
    
    if(frameCount < frames.size()) {
        frameCount++;
    } else {
        cout << "DONE!" << std::endl;
    }
}

CINDER_APP( TestRopeIdeaApp, RendererGl )
