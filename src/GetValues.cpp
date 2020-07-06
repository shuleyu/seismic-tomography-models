#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>

#include<ShellExec.hpp>
#include<Tomography.hpp>

using namespace std;

int main(int argc, char * argv[]){

    if (argc != 2) {

        cout << "usage: ./GetValues.out [parameterFile]\n";
        cout << "\n";
        cout << "The first line in [parameterFile] is an absolute path of an .nc file.\n";
        cout << "The rest is 3-column locations separate by blanks: Depth(in km) Latitude (in degree, -90 ~ 90) Longitude(in degree, 0 ~ 360 or -180 ~ 180)\n";
        cout << "The output is stdout, namely, will print to the screen." << endl;
        return 1;
    }


    ifstream fpin;

    string inputFile(argv[1]);

    fpin.open(inputFile);

    if (!fpin.is_open()) {

        throw runtime_error("Can't open file: " + inputFile);
    }

    string ncFile = "";
    getline(fpin, ncFile);

    auto tomo = Tomography(ncFile);

    cout << "NcFile: " + ncFile << endl;
//     cout << "Depth range in the nc file: " << tomo.GetDepths()[0] << " " << tomo.GetDepths().back() << endl;
//     cout << "Latitude range in the nc file: " << tomo.GetLatitudes()[0] << " " << tomo.GetLatitudes().back() << endl;
//     cout << "Longitude range in the nc file: " << tomo.GetLongitudes()[0] << " " << tomo.GetLongitudes().back() << endl;

    string s;

    int lineCnt = 1;

    while (!fpin.eof() && getline(fpin, s)) {

        ++lineCnt;

        stringstream ss(s);
        double depth, lat, lon;

        if (ss >> depth >> lat >> lon) {

            cout << s << "    " << tomo.GetValueAt(depth, lon, lat) << "\n";
        }
        else {

            cerr << "Line: " + to_string(lineCnt) + ", File: " + inputFile + ", this line is not in a 3-column format" << endl;
            cout << s << "\n";
        }
    }

    
    return 0;
}
