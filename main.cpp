#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include "pbPlots.hpp"
#include "supportLib.hpp"

#include <boost/random.hpp>
#include <boost/random/normal_distribution.hpp>


struct pose{
    std::vector<double>   timestamp;
    std::vector<double>   positionX;
    std::vector<double>   noisyData;
};

static std::string POSE_1_FILEPATH = "data\\cam_data1.txt";
static std::string FILE_DELIMITER = ",";

static pose CameraData1 {};

void preprocessFile(const std::string& filepath, pose _pose);
bool plotSignal(pose _pose, std::string title);


int main(int argc, char** argv){
    std::cout << "Start Project: Kalman Filter \n";

    // Retrieve data
    preprocessFile(POSE_1_FILEPATH, CameraData1);

    // Plot results
    plotSignal(CameraData1, "camera_data_1.png");

    std::cout << "Exiting.\n";\
    return 0;
}


void preprocessFile(const std::string& filepath, pose _pose){
    std::string line {};
    std::ifstream pose1File(filepath);

    if (pose1File.is_open()){
        while(std::getline(pose1File, line)){
            size_t del = line.find(FILE_DELIMITER);

            CameraData1.timestamp.push_back(stod(line.substr(0, del)));
            double position = stod(line.substr(del + 1, line.size()));
            CameraData1.positionX.push_back(position);

            // generating gaussian noise
            boost::mt19937 generator(42);
            boost::normal_distribution<double> normalDistribution(0.0, 1.0);
            boost::variate_generator<
                boost::mt19937&, 
                boost::normal_distribution<double>> randNormal(generator, normalDistribution);

            
            CameraData1.noisyData.push_back(position + randNormal());

        }
    }else{
        std::cout << "File not found \n";
    }   
}

bool plotSignal(pose _pose, std::string title){

    bool success;
    StringReference *errorMessage = new StringReference();
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = &(_pose.timestamp);
	series->ys = &(_pose.positionX);
	series->linearInterpolation = true;
	series->lineType = toVector(L"dashed");
	series->lineThickness = 2;
	series->color = GetGray(0.3);

    ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
	series2->xs = &(_pose.timestamp);
	series2->ys = &(_pose.noisyData);
	series2->linearInterpolation = true;
	series2->lineType = toVector(L"solid");
	series2->lineThickness = 2;
	series2->color = CreateRGBColor(0, 0, 1);

	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 600;
	settings->height = 400;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"Position X over time");
	settings->xLabel = toVector(L"X axis");
	settings->yLabel = toVector(L"Y axis");
	settings->scatterPlotSeries->push_back(series);
	settings->scatterPlotSeries->push_back(series2);

	success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

    if(success){
        std::vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, title);
        DeleteImage(imageReference->image);
	}else{
        std::cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            std::wcerr << c;
        }
        std::cerr << std::endl;
	}

	return success ? 0 : 1;
}

