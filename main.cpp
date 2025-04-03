#include <opencv2/opencv.hpp>
#include <iostream>

bool isImageOnScreen(const std::string& screenPath, const std::string& templatePath, double threshold = 0.9) {
    try {
        // Load screenshot (replace this with real screen capture later)
        cv::Mat screenshot = cv::imread(screenPath);
        if (screenshot.empty()) {
            std::cerr << "Failed to load screenshot image: " << screenPath << "\n";
            return false;
        }

        // Load template image
        cv::Mat templ = cv::imread(templatePath);
        if (templ.empty()) {
            std::cerr << "Failed to load template image: " << templatePath << "\n";
            return false;
        }

        // Match template
        cv::Mat result;
        cv::matchTemplate(screenshot, templ, result, cv::TM_CCOEFF_NORMED);

        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

        std::cout << "Match confidence: " << maxVal << "\n";
        if (maxVal >= threshold) {
            std::cout << "Image found on screen at: " << maxLoc << "\n";
            return true;
        } else {
            std::cout << "Image not found.\n";
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "⚠Exception: " << e.what() << "\n";
        return false;
    }
}

int main() {
    std::string screenImage = "screenshot.png";     // Replace with your actual screenshot
    std::string targetImage = "template.png";       // Replace with your actual image to find

    bool found = isImageOnScreen(screenImage, targetImage, 0.9);
    return found ? 0 : 1;
}
