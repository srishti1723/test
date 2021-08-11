#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct
{
    int frame_number;
    string frame_data;
} Frame;

vector<Frame> ConvertToFrames(string msg)
{
    vector<Frame> frames;
    int frameNumber = 0, pos = 0;
    while (pos != msg.length())
    {
        Frame frame;
        frame.frame_number = frameNumber++;
        int random = rand() % 3 + 2;
        random = random > msg.length() - pos ? msg.length() - pos : random;
        frame.frame_data = msg.substr(pos, random);
        pos += random;
        frames.push_back(frame);
    }
    return frames;
}

void ShowFrames(vector<Frame> frames)
{
    for (Frame frame : frames)
    {
        cout << frame.frame_number << "\t" << frame.frame_data << endl;
    }
}

void Shuffle(vector<Frame> &frames)
{
    for (int i = frames.size() - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Frame temp = frames[i];
        frames[i] = frames[j];
        frames[j] = temp;
    }
}

bool CompareFrames(Frame frame1, Frame frame2)
{
    return frame1.frame_number < frame2.frame_number;
}

void SortFrames(vector<Frame> &frames)
{
    sort(frames.begin(), frames.end(), CompareFrames);
}

string GetMessage(vector<Frame> &frames)
{
    string msg;
    for (Frame frame : frames)
        msg += frame.frame_data;
    return msg;
}

int main()
{
    string msg;
    cout << "Enter the message: ";
    getline(cin, msg);
    cout << "Message: " << msg << endl;

    // Sender side
    vector<Frame> frames = ConvertToFrames(msg);
    cout << "Frames are:" << endl;
    ShowFrames(frames);
    Shuffle(frames);
    cout << "Shuffled frames are:" << endl;
    ShowFrames(frames);

    // Receiver side
    SortFrames(frames);
    cout << "Sorted frames are:" << endl;
    ShowFrames(frames);
    cout << "Message: " << GetMessage(frames) << endl;

    return 0;
}