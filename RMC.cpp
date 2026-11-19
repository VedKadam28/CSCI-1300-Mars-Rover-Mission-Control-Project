#include <iostream>
#include <string>
using namespace std;

//functions

//Direcion Math Function
void directionMath(int h, int &dx, int &dy){
    switch(h){
        case 1:
            dy = 1;
            break;
        case 2:
            dx = 1;
            break;
        case 3:
            dy = -1;
            break;
        case 4:
            dx = -1;
            break;
        default: 
            dx = dx;
            dy = dy;
            break;
    }
}

//Heading Function
string headingToString(int h){
    switch(h){
        case 1:
            return "North ";
        case 2:
            return "East ";
        case 3:
            return "South ";
        case 4:
            return "West ";
        default: 
            return "Unknown ";
    }
}

//Battery Check Function
void batteryCheck(int &batteryValue, int batterySubtract, int &successfulMissions){
    batteryValue += batterySubtract;
    if ((batteryValue + batterySubtract) >= 0){
        successfulMissions += 1;
        cout << "succeeded. ";
        cout << "Battery: " << batteryValue << " ";
    }
    else{
        cout << "rejected: insufficient battery ";
    }
}

//Movement function
void movement(string inputMission, int &heading, int &battery, int &x, int &y, int &dx, int &dy, int &successfulMissions) {
    int batteryChange;
    for (size_t i = 0; i < inputMission.length(); i++) {
        switch (inputMission[i]) {
            case 'F':
                cout << "Command F ";
                batteryChange = -2;
                
                directionMath(heading, dx, dy);
                if((x + dx) > 9 || (x + dx) < 0 || (y + dy) > 9 || (y + dy) < 0){
                    cout << "rejected: out of bounds ";
                }
                else{
                    x += dx;
                    y += dy;
                }
                dx = 0;
                dy = 0;

                break;
            case 'L':
                cout << "Command L ";
                batteryChange = -1;
                if (heading == 1) {
                    heading = 4;
                } else {
                    heading = heading - 1;
                }
                break;
            case 'R':
                cout << "Command R ";
                batteryChange = -1;
                if (heading == 4) {
                    heading = 1;
                } else {
                    heading = heading + 1;
                }
                break;
            case 'S':
                cout << "Command S ";
                batteryChange = -3;
                break;
            case 'C':
                cout << "Command C ";
                break;
            default:
                cout << "what u is? ";
                continue;   // skip the heading print for invalid commands
        }
        
        

        batteryCheck(battery, batteryChange, successfulMissions);
        cout << "Current coordinate: (" << x << ", " << y << ") ";
        if (battery > 0){
            cout << "Heading: " << headingToString(heading) << endl;
        }
        else{
            cout << endl;
        }
    }
}



int main(){
    //variables
    string inputMission;
    int x = 0;
    int y = 0;
    int dx = 0;
    int dy = 0;
    int heading = 2;
    int battery = 40;
    int goalX;
    int goalY;
    int successfulMissions = 0;

    cout << "Input Mission: " << endl;
    cin >> inputMission;
    cout << endl;
    cout << "Input goal x coordinate: ";
    cin >> goalX;
    cout << endl;
    cout << "Input goal y coordinate: ";
    cin >> goalY;
    cout << endl;

    movement(inputMission, heading, battery, x, y, dx, dy, successfulMissions);
    cout << endl << "Mission Complete!";
    cout << endl << "Rover ended at coordinates (" << x << ", " << y << ") with heading " << headingToString(heading) << " and battery " << battery << ".";
    
    return 0;
}