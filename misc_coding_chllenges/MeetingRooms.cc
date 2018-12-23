#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

int minMeetingRooms(vector<Interval>& intervals)
{
    if(intervals.empty()) return 0;

    vector<vector<Interval>> rooms = {};

    for(auto meeting : intervals) {
        if(rooms.empty()) {
            rooms.push_back({meeting});
        }  else {
            bool needslot = false;
            for(int i = 0; i < rooms.size() ; i++) {
                for(const Interval& iv : rooms[i]) {
                    if(meeting.end > iv.start and meeting.start < iv.end) {
                        needslot = true;
                        break;
                    }
                }
                if(not needslot) {
                    rooms[i].push_back(meeting); // no conflict detected.
                    break;
                } else { // conflicting times.
                    if( i == rooms.size() - 1) { // If we don't have any rooms left. We need to allocate a new one.
                        rooms.push_back({meeting});
                        break;
                    }
                }

                needslot = false;
            }
        }
    }

    return rooms.size();
}


int main()
{
    vector<Interval> iv = {Interval(0, 30), Interval(5, 10), Interval(15, 20)};

    std::cout << minMeetingRooms(iv) << "\n";
}
