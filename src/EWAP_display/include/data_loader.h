#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const float PI = 3.14159265359F;

struct Point{
	float x;
	float y;
	float z;
};

class Color{
public:
    Color(float red, float green, float blue)
    {
        r = red; g = green; b = blue;
    }
	float r;
	float g;
	float b;
};

struct data_line{
	double frame_time;
	double ped_id;
	double pos_x;
	double pos_z;
	double pos_y;
	double v_x;
	double v_z;
	double v_y;
	
};

class Data_loader{
private:
	int total_num_;
	vector<data_line> dataset_;
	int num_trajectory_;
	
public:
	Data_loader();
	~Data_loader();
	
	bool openFile(string path);
	int getNum() { return total_num_; }
	vector<data_line> getDataset() { return dataset_; }
	
};

Data_loader::Data_loader()
{
	total_num_ = 0;
	num_trajectory_ = 0;
}

bool Data_loader::openFile(string path)
{
	fstream d;
	d.open(path);
	if (!d)
	{
	    cout << "open data file: " << path << " failed!" << endl;
	    return false;
	}

	string line;
	data_line a;
	
	while(d.good())
	{
		getline(d, line);
		if (line.length() == 0)
			break;
		
		stringstream ss(line);
		ss >> a.frame_time >> a.ped_id >> a.pos_x >> a.pos_z >> a.pos_y
									   >> a.v_x   >> a.v_z   >> a.v_y;
		if (a.ped_id > num_trajectory_)
		    num_trajectory_ = a.ped_id;
		dataset_.push_back(a);
		++total_num_;
	}
	
	d.close();
	cout << "dataset loaded! \n total num = " << total_num_ 
	     << "\n total trajectory = " << num_trajectory_ << endl;
	return true;
}

Data_loader::~Data_loader()
{
	dataset_.clear();
}

#endif
