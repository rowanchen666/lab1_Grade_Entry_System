#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Class.h"
#include "Student.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printScoreStats();
    void printGrade();
    void saveScore();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    Class *cl = nullptr;

    // Open a file as a input stream.
    ifstream stfile("./Students.txt");

    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each column in the line.
        bufv.clear();
        // Split the line into columns.
        //   pos1: beginning of the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.
        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);

        studentVec.push_back(st);
    }
    stfile.close();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    // Hint: how is student information read?

    // Open a file as a input stream.
    ifstream clfile("./Classes.txt");
    if (!clfile.is_open()) {
        cerr << "Error: Cannot open Classes.txt" << endl;
        exit(1);
    }

    // The lineBuf vector stores each line in the file, except empty lines and comment lines , to be processed later.
    vector<string> lines;
    while (getline(clfile, line)) {
        if (lines.empty() || line[0] == '#')
            continue;
        lines.push_back(line);
    }
    clfile.close();

    // Process each line in lineBuf to create Class objects and add them to classVec.
    size_t idx = 0;
    while (idx < lines.size()) {
        line = lines[idx];
        
        if (line.empty() || line[0] == '#') {
            idx ++;
            continue ;
        }

        //progress the line to get class name
        if (idx < lines.size() && line.find("Class") == 0) {
            idx ++;
            clsname = line.substr(line.find(":") + 1);

            //progress the line to get class point
            line = lines[idx];
            if (line.find("Point") == 0) {
                idx ++;
                point = stoi(line.substr(line.find(":") + 1));  // Convert string to int
                
                if (point <= 0) {
                    cerr << "Error: Invalid point value for class " << clsname << endl;
                    continue;
                }

                cl = new Class (clsname , point);

                idx ++;

                //progress the line to get student information
                while(idx < lines.size()) {
                    line = lines[idx];

                    // If the line is empty or next class, skip it.
                    if(line.empty() ){
                        idx ++;
                        continue;
                    }
                    if (line.find("Class") == 0) {
                        break;
                    }

                    string studentId = line;
                    bool found = false;
                    for (auto &s: studentVec) {
                        if (s->id == studentId) {
                            cl->addStudent(*s);
                            s->addClass(cl);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cerr << "Error: Student with ID " << studentId << " not found for class " << clsname << endl;
                    }
                    idx ++;
                }
                classVec.push_back(cl);
            } else {
                cerr << "Error: Point information missing for class " << clsname << endl;
            }
        } else {
            idx ++;
        }
    }
}

void AppX::inputScore()
{
    // TODO: implement inputScore.
    // Hint: Take a look at printScoreStats().
}

void AppX::printScoreStats()
{
    string sbuf;
    Class *cl;
    double highest, lowest, avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class*>::iterator it = classVec.begin();
                it != classVec.end();
                ++ it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cerr << "No Match Class!" << endl;
            continue;
        }

        try {
            highest = cl->getHighestScore();
            lowest = cl->getLowestScore();
            avg = cl->getAvgScore();

            cout << cl->toString() << endl;
            cout << setiosflags(ios::fixed) << setprecision(2)<< "Highest,Lowest,Avg = " << highest << "," << lowest << "," << avg << endl;
        } catch (string e) {
            cerr << e << endl;
        } catch (char const* e){
            cerr << e << endl;
        } catch (...) {
            cerr << "Unknown exception caught" << endl;
        }
    }
}

void AppX::printGrade()
{
    // TODO: implement printGrade.
    // Hint: Take a look at printScoreStats().
}

void AppX::saveScore() {
    // TODO: implement saveScore.
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute score statistics of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printScoreStats();
        } else if (cmd == 'g') {
            printGrade();
        } else if (cmd == 'q') {
            saveScore();
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
