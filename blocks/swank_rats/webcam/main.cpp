#include "diego/opencv/opencv2/objdetect/objdetect.hpp"
#include "diego/opencv/opencv2/highgui/highgui.hpp"
#include "diego/opencv/opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** @function main */
int main(int argc, const char **argv) {
    // Capture the Image from the webcam
    VideoCapture cap(0);

    // Get the frame
    Mat save_img;
    cap >> save_img;

    if (save_img.empty()) {
        std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
    }

    vector<uchar> in;
    vector<int> params;

    params.push_back(80);

    cv::imencode(".jpg", save_img, in, params);

    std::string t(in.begin(), in.end());

    vector<uchar> out(t.begin(), t.end());

    Mat img;
    cv::imdecode(out, CV_LOAD_IMAGE_ANYDEPTH, &img);

    imwrite("test.jpg", img); // A JPG FILE IS BEING SAVED

    return 0;
}