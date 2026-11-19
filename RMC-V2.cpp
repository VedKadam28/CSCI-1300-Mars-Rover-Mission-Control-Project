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
            return "North";
        case 2:
            return "East";
        case 3:
            return "South";
        case 4:
            return "West";
        default:
            return "Unknown";
    }
}

//Battery Check Function (true if there is enough battery to pay the whole cost)
bool batteryCheck(int batteryValue, int batterySubtract){
    if ((batteryValue + batterySubtract) >= 0){
        return true;
    }
    else{
        return false;
    }
}

//Movement function
void movement(string inputMission, int &heading, int &battery, int &x, int &y, int &dx, int &dy, int &successfulMissions, int goalX, int goalY, bool &goalReached) {
    int batteryChange = 0;
    bool success;
    string reason;
    int missionLength = inputMission.length();
    for (int i = 0; i < missionLength; i++) {
        success = true;
        batteryChange = 0;
        switch (inputMission[i]) {
            case 'F':
                batteryChange = -2;
                if (!batteryCheck(battery, batteryChange)){
                    success = false;
                    reason = "insufficient battery";
                }
                else{
                    directionMath(heading, dx, dy);
                    if((x + dx) > 9 || (x + dx) < 0 || (y + dy) > 9 || (y + dy) < 0){
                        success = false;
                        reason = "out of bounds";
                    }
                    else{
                        x += dx;
                        y += dy;
                    }
                    dx = 0;
                    dy = 0;
                }
                break;
            case 'L':
                batteryChange = -1;
                if (!batteryCheck(battery, batteryChange)){
                    success = false;
                    reason = "insufficient battery";
                }
                else if (heading == 1) {
                    heading = 4;
                } else {
                    heading = heading - 1;
                }
                break;
            case 'R':
                batteryChange = -1;
                if (!batteryCheck(battery, batteryChange)){
                    success = false;
                    reason = "insufficient battery";
                }
                else if (heading == 4) {
                    heading = 1;
                } else {
                    heading = heading + 1;
                }
                break;
            case 'S':
                batteryChange = -3;
                if (!batteryCheck(battery, batteryChange)){
                    success = false;
                    reason = "insufficient battery";
                }
                break;
            case 'C':
                if (x == 0 && y == 0){
                    battery = 40;
                }
                else{
                    success = false;
                    reason = "not at charging station";
                }
                break;
            default:
                success = false;
                reason = "unknown command";
                break;
        }

        if (success){
            battery += batteryChange;
            successfulMissions += 1;
            if (x == goalX && y == goalY){
                goalReached = true;
            }
            cout << "Command " << inputMission[i] << " succeeded. ";
            cout << "Current coordinates: (" << x << "," << y << ") ";
            cout << "Heading: " << headingToString(heading) << " ";
            cout << "Battery: " << battery << endl;
        }
        else{
            cout << "command " << inputMission[i] << " rejected: " << reason << endl;
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
    int successfulMissions;
    bool goalReached;
    bool roverReset;

    cout << "Input mission: ";
    cin >> inputMission;

    while (inputMission != "quit"){
        cout << "Input goal x coordinate: ";
        cin >> goalX;
        cout << "Input goal y coordinate: ";
        cin >> goalY;

        successfulMissions = 0;
        goalReached = (x == goalX && y == goalY);

        movement(inputMission, heading, battery, x, y, dx, dy, successfulMissions, goalX, goalY, goalReached);

        roverReset = (x == 0 && y == 0 && battery == 40);

        cout << "Mission Complete!" << endl;
        cout << "Rover ended at coordinates (" << x << "," << y << ") with heading " << headingToString(heading) << " and battery " << battery << "." << endl;
        cout << "Number of Successful Commands: " << successfulMissions << endl;

        if (goalReached && roverReset){
            cout << "Goal reached and rover reset." << endl;
        }
        else if (goalReached){
            cout << "Goal reached but rover not reset." << endl;
        }
        else if (roverReset){
            cout << "Goal not reached but rover reset." << endl;
        }
        else{
            cout << "Goal not reached and rover not reset." << endl;
        }

        cout << "Input mission: ";
        cin >> inputMission;
    }

    return 0;
}
