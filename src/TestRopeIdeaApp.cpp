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
//            if(lineCount % 1000 == 0) {
//                cout << lineCount << endl;
//            }
            
                getline(myfile,line);
            if (lineCount > 6) {
    //            cout << line << endl;
    //             index 2,3,5,6,14,15
                string word;
                stringstream stream(line);
                std::vector<string> frameList;
                std::string token;
                while(std::getline(stream, token, ',')) {
                    frameList.push_back(token);
                }
                vector<float> newFrame;
                if( frameList.size() > 2 && !frameList.at(2).empty() && !frameList.at(5).empty() && !frameList.at(14).empty()) {
                    // hip 1 x
                    newFrame.push_back(stof(frameList.at(2)));
                    // hip 1 y
                    newFrame.push_back(stof(frameList.at(3)));
//                    cout << frameList.at(3) << endl;
                    // hip 2 x
                    newFrame.push_back(stof(frameList.at(5)));
    //                cout << frameList.at(5) << endl;
                    // hip 2 y
                    newFrame.push_back(stof(frameList.at(6)));
    //                cout << frameList.at(6) << endl;
                    // chest x
                    newFrame.push_back(stof(frameList.at(14)));
    //                cout << frameList.at(14) << endl;
                    // chest y
                    newFrame.push_back(stof(frameList.at(15)));
    //                cout << frameList.at(15) << endl;
    //                break;
                    frames.push_back(newFrame);
                } else {
//                    cout << "empty" << endl;
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
    // move to the window center
    gl::translate( getWindowCenter().x, getWindowCenter().y );
    gl::rotate(M_PI);
    gl::color(1.0, 0, 0);
    auto temp  = frames.at(frameCount);
    for(int i=0; i<6; i+=2){
        gl::drawSolidEllipse(vec2(temp.at(i)*100, temp.at(i+1)*100), 10, 10);
    }
    
    if(frameCount < frames.size()) {
        frameCount++;
    } else {
        cout << "DONE!" << std::endl;
    }
}

CINDER_APP( TestRopeIdeaApp, RendererGl )
