#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // Path to video file
    std::string videoPath = "C:\\Users\\aaron\\Desktop\\Car.mp4";

    // Open video file
    cv::VideoCapture cap(videoPath);
    if (!cap.isOpened())
    {
        std::cout << "Error: Could not open video file" << std::endl;
        return -1;
    }

    // Create windows for displaying video
    cv::namedWindow("Original Video", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Segmented Video", cv::WINDOW_AUTOSIZE);

    // Read the first frame to initialize video properties
    cv::Mat frame, frameLab, segmentedFrame;
    cap >> frame;

    if (frame.empty())
    {
        std::cout << "Error: Could not read frame from video" << std::endl;
        return -1;
    }

    // Define parameters for Mean Shift segmentation
    int spatialWindowRadius = 20;
    int colorWindowRadius = 40;

    // Loop over each frame
    while (true)
    {
        // Capture next frame from video
        bool success = cap.read(frame);
        if (!success || frame.empty())
        {
            std::cout << "End of video or error in frame capture." << std::endl;
            break;
        }

        // Show original frame
        cv::imshow("Original Video", frame);

        // Convert frame to Lab color space for better segmentation
        cv::cvtColor(frame, frameLab, cv::COLOR_BGR2Lab);

        // Apply Mean Shift segmentation on the frame
        cv::pyrMeanShiftFiltering(frameLab, segmentedFrame, spatialWindowRadius, colorWindowRadius);

        // Convert segmented frame back to BGR color space
        cv::cvtColor(segmentedFrame, segmentedFrame, cv::COLOR_Lab2BGR);

        // Show segmented video
        cv::imshow("Segmented Video", segmentedFrame);

        // Wait for 30 ms between frames, exit on key press
        char key = (char)cv::waitKey(30);
        if (key == 27) // Exit if 'ESC' is pressed
        {
            std::cout << "ESC key pressed. Exiting..." << std::endl;
            break;
        }
    }

    // Release video capture object and close windows
    cap.release();
    cv::destroyAllWindows();
}