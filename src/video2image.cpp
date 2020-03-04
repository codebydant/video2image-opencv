#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
//----------------------------------------------

size_t frameNumber;
size_t reference_number;

int main(int argc, const char *argv[]) {

  if (argc < 2 or argc > 2) {
    std::cout << "Usage: <executable> <video file>" << std::endl;
    std::exit(-1);
  } else {
    std::cout << "\n*********************" << std::endl;
    std::cout << "*** VIDEO TO FRAME *** " << std::endl;
    std::cout << "*********************" << std::endl;

    std::vector<std::string> images_dir;
    std::cout << "-> Getting images sequence from video...please wait" << std::endl;

    ////////////////////input image sequences//////////////////////
    // std::vector<cv::Mat> video_input;
    cv::Mat referFrame;
    cv::Mat currentFrame;

    cv::VideoCapture capture(argv[1]);
    // Check if camera opened successfully

    if (!capture.isOpened()) {
      std::cout << "-> Error opening video stream or file" << std::endl;
      std::exit(-1);
    }

    // capture.set(cv::CAP_PROP_POS_AVI_RATIO, 1);

    frameNumber = capture.get(cv::CAP_PROP_FRAME_COUNT);
    reference_number = (frameNumber - 1) / 2;
    float fps = capture.get(cv::CAP_PROP_FPS);
    // float duration = frameNumber / fps;

    // std::cout << "fps: " << fps << std::endl;
    // std::cout << "Number of frames: " << frameNumber << std::endl;

    int multiplier = fps * 2;

    std::cout << "-------------------------------------" << std::endl;

    // cv::namedWindow("inputVideo", cv::WINDOW_AUTOSIZE);
    int cont = 0;
    for (size_t frame_i = 0; frame_i < frameNumber; frame_i++) {

      // while (capture.isOpened()) {
      int frameId = frame_i;
      float frameI_msc = capture.get(cv::CAP_PROP_POS_MSEC);
      // std::cout << "-> frame id: " << frameId << std::endl;
      // std::cout << "-> msc id: " << frameI_msc << std::endl;
      capture.set(cv::CAP_PROP_POS_FRAMES, frameId);
      if (((int)frameId % multiplier) == 0) {
        capture >> currentFrame;
        // if (frame_i == reference_number) {
        //   referFrame = currentFrame.clone();
        // }
        // std::cout << "-> frame id: " << frameId << std::endl;

        if (currentFrame.empty()) {
          std::cout << "-> frame empty: " << std::endl;
          break;
        }

        // video_input.push_back(currentFrame.clone());
        // std::string filename = "Image_" + std::to_string((int)frame_i) + ".png";
        std::string filename = "Image_" + std::to_string(cont) + ".png";
        cv::imwrite(filename.c_str(), currentFrame.clone());
        // cv::namedWindow("inputVideo", cv::WINDOW_NORMAL);
        // cv::resizeWindow("inputVideo", 640, 480);
        // cv::imshow("inputVideo", currentFrame);
        std::cout << "-> Saved: " << filename << std::endl;
        cont += 1;
        cv::waitKey(400);
        cv::destroyAllWindows();

      } else {
        continue;
      }
    }
    capture.release();
    std::cout << "-------------------------------------" << std::endl;
    cv::destroyAllWindows();
  }

  return 0;
}
