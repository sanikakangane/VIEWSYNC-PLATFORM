// ViewSync Platform - Streaming Video Network Syndication Mesh

#include <algorithm>
#include <cctype>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>  
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// Standard width for aligning prompt labels horizontally
const int PROMPT_WIDTH = 32;

// Struct definitions
struct Video {
    int id;
    string title;
    string genre;
    string category;
    string tag;
    string licenseCode;
};

struct ViewingStateChange {
    int subscriberId;
    int videoId;
    string previousState;
    string newState;
};

struct PipelineTask {
    int taskId;
    string taskType;
    string details;
};

struct License {
    string code;
    string publisher;
    string region;
};

struct Clip {
    int clipId;
    string title;
    double retentionMinutes;
};

struct Edge {
    int destination;
    int cost;
};

struct Platform {
    int id;
    string name;
};

struct FrameTask {
    int frameId;
    int encodingTime;
};

struct ProcessorLoad {
    int processorId;
    int currentLoad;
};

struct CompareProcessorLoad {
    bool operator()(ProcessorLoad first, ProcessorLoad second) {
        if (first.currentLoad != second.currentLoad) {
            return first.currentLoad > second.currentLoad;
        }
        return first.processorId > second.processorId;
    }
};

// Global variables
vector<Video> videos;
unordered_map<int, int> videoIndexById;
unordered_map<string, vector<int>> catalogIndex;

map<pair<int, int>, string> viewingStates;
stack<ViewingStateChange> correctionLog;
queue<PipelineTask> algorithmPipeline;
unordered_map<string, License> licenseDirectory;

vector<Clip> clips;
vector<Platform> platforms;
vector<vector<Edge>> syndicationGrid;

// Function declarations
string toLowerText(string text);
string shortText(string text, int width);
void ignoreLine();
void printLine(int width = 60);
void printTitle();
void printMainMenu();
void printMessageBox(string title, string message);
void printVideoTable(string title, vector<Video> tableVideos);
void printExitScreen();
void rebuildCatalogIndex();
void loadSampleData();
int findPlatformIndexById(int id);

void catalogMenu();
void correctionLogMenu();
void algorithmPipelineMenu();
void registrationCodeMenu();
void clipSorterMenu();
void syndicationGridMenu();
void deliveryTransportMenu();
void frameSplitterMenu();

void addVideo();
void searchVideosByMetadata();
void displayCatalog();
void updateViewingState();
void undoLastViewingState();
void displayViewingStates();
void addPipelineTask();
void processNextPipelineTask();
void displayPipelineTasks();
void addLicense();
void verifyLicense();
void displayLicenses();
void addClip();
void displaySortedClips();
void addPlatform();
void addLicensingConnection();
void displaySyndicationGrid();
void findLowestCostRoute();
void splitFramesAcrossProcessors();

// Utility functions
string toLowerText(string text) {
    for (int i = 0; i < (int)text.length(); i++) {
        text[i] = (char)tolower((unsigned char)text[i]);
    }
    return text;
}

string shortText(string text, int width) {
    if ((int)text.length() <= width) {
        return text;
    }
    if (width <= 3) {
        return text.substr(0, width);
    }
    return text.substr(0, width - 3) + "...";
}

void ignoreLine() {
    if (cin.fail()) {
        cin.clear();
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printLine(int width) {
    cout << string(width, '-') << "\n";
}

void printMessageBox(string title, string message) {
    string lowerTitle = toLowerText(title);
    string lowerMessage = toLowerText(message);

    if (lowerTitle.find("invalid") != string::npos ||
        lowerMessage.find("not") != string::npos ||
        lowerMessage.find("no ") != string::npos ||
        lowerMessage.find("already") != string::npos ||
        lowerMessage.find("must") != string::npos) {
        cout << "\n\033[1;31mERROR : " << message << "\033[0m\n"; // Bold Red
    } else {
        cout << "\n\033[1;32mSUCCESS : " << message << "\033[0m\n"; // Bold Green
    }
}

void printVideoTable(string title, vector<Video> tableVideos) {
    cout << "\n" << title << "\n";
    printLine(100);
    cout << left << setw(8) << "ID"
        << setw(24) << "TITLE"
        << setw(16) << "GENRE"
        << setw(16) << "CATEGORY"
        << setw(20) << "TAGS"
        << setw(16) << "LICENSE CODE" << "\n";
    printLine(100);

    for (int i = 0; i < (int)tableVideos.size(); i++) {
        cout << left << setw(8) << tableVideos[i].id
            << setw(24) << shortText(tableVideos[i].title, 22)
            << setw(16) << shortText(tableVideos[i].genre, 14)
            << setw(16) << shortText(tableVideos[i].category, 14)
            << setw(20) << shortText(tableVideos[i].tag, 18)
            << setw(16) << shortText(tableVideos[i].licenseCode, 14) << "\n";
    }

    printLine(100);
    cout << "Total Videos : " << tableVideos.size() << "\n";
}

void printExitScreen() {
    cout << "\033[1;32m============================================================\n"; // Bold Green
    cout << "                    THANK YOU\n";
    cout << "              ViewSync Platform Closed\n";
    cout << "============================================================\033[0m\n";
}

void rebuildCatalogIndex() {
    catalogIndex.clear();
    videoIndexById.clear();

    for (int i = 0; i < (int)videos.size(); i++) {
        videoIndexById[videos[i].id] = i;
        
        string genre = toLowerText(videos[i].genre);
        string category = toLowerText(videos[i].category);
        string tag = toLowerText(videos[i].tag);

        catalogIndex[genre].push_back(i);
        if (category != genre) {
            catalogIndex[category].push_back(i);
        }
        if (tag != category && tag != genre) {
            catalogIndex[tag].push_back(i);
        }
    }
}

void loadSampleData() {
    videos.push_back({101, "Ocean Crimes", "Thriller", "Series", "mystery", "LIC-NET-IND"});
    videos.push_back({102, "Galaxy Kids", "Animation", "Movie", "kids", "LIC-DIS-USA"});
    videos.push_back({103, "Chef World", "Reality", "Show", "food", "LIC-AMZ-GLB"});

    licenseDirectory["LIC-NET-IND"] = {"LIC-NET-IND", "Netflix Studios", "India"};
    licenseDirectory["LIC-DIS-USA"] = {"LIC-DIS-USA", "Disney Content Group", "USA"};
    licenseDirectory["LIC-AMZ-GLB"] = {"LIC-AMZ-GLB", "Amazon Media", "UK"};

    clips.push_back({201, "Ocean Crimes Opening", 8.70});
    clips.push_back({202, "Galaxy Kids Trailer", 6.20});
    clips.push_back({203, "Chef World Finale", 9.50});

    platforms.push_back({1, "Rights Holder"});
    platforms.push_back({2, "India CDN"});
    platforms.push_back({3, "Global CDN"});
    platforms.push_back({4, "User Device"});

    syndicationGrid.resize(4);
    syndicationGrid[0].push_back({1, 10});
    syndicationGrid[0].push_back({2, 25});
    syndicationGrid[1].push_back({3, 15});
    syndicationGrid[2].push_back({3, 5});

    rebuildCatalogIndex();
}

int findPlatformIndexById(int id) {
    for (int i = 0; i < (int)platforms.size(); i++) {
        if (platforms[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Menu functions
void printTitle() {
    cout << "\033[1;31m============================================================\n"; // Bold Red
    cout << "                    VIEWSYNC PLATFORM\n";
    cout << "         Streaming Video Network Syndication Mesh\n";
    cout << "============================================================\033[0m\n";
}

void printMainMenu() {
    cout << "\nMAIN MENU\n";
    printLine();
    cout << "1. Catalog Directory\n";
    cout << "2. Correction Log\n";
    cout << "3. Algorithm Pipeline\n";
    cout << "4. Registration Code\n";
    cout << "5. Clip Sorter\n";
    cout << "6. Syndication Grid\n";
    cout << "7. Delivery Transport\n";
    cout << "8. Frame Splitter\n";
    cout << "0. Exit\n";
    printLine();
    cout << "\nEnter Choice : ";
}

void catalogMenu() {
    int choice;
    do {
        cout << "\nCATALOG DIRECTORY MENU\n";
        printLine();
        cout << "1. Add Video Metadata\n";
        cout << "2. Search by Genre Category or Tag\n";
        cout << "3. Display Catalog\n";
        cout << "0. Back\n";
        printLine();
        cout << "\nEnter Choice : ";
        cin >> choice;
        ignoreLine();

        if (choice == 1) addVideo();
        else if (choice == 2) searchVideosByMetadata();
        else if (choice == 3) displayCatalog();
        else if (choice != 0) printMessageBox("INVALID CHOICE", "Please select a valid catalog option.");
    } while (choice != 0);
}

void correctionLogMenu() {
    int choice;
    do {
        cout << "\nCORRECTION LOG MENU\n";
        printLine();
        cout << "1. Record Viewing State Change\n";
        cout << "2. Undo Last State Change\n";
        cout << "3. Display Viewing States\n";
        cout << "0. Back\n";
        printLine();
        cout << "\nEnter Choice : ";
        cin >> choice;
        ignoreLine();

        if (choice == 1) updateViewingState();
        else if (choice == 2) undoLastViewingState();
        else if (choice == 3) displayViewingStates();
        else if (choice != 0) printMessageBox("INVALID CHOICE", "Please select a valid correction option.");
    } while (choice != 0);
}

void algorithmPipelineMenu() {
    int choice;
    do {
        cout << "\nALGORITHM PIPELINE MENU\n";
        printLine();
        cout << "1. Add Profile Processing Task\n";
        cout << "2. Process Next Task\n";
        cout << "3. Display Pending Tasks\n";
        cout << "0. Back\n";
        printLine();
        cout << "\nEnter Choice : ";
        cin >> choice;
        ignoreLine();

        if (choice == 1) addPipelineTask();
        else if (choice == 2) processNextPipelineTask();
        else if (choice == 3) displayPipelineTasks();
        else if (choice != 0) printMessageBox("INVALID CHOICE", "Please select a valid pipeline option.");
    } while (choice != 0);
}

void registrationCodeMenu() {
    int choice;
    do {
        cout << "\nREGISTRATION CODE MENU\n";
        printLine();
        cout << "1. Add License Code\n";
        cout << "2. Verify License for Region\n";
        cout << "3. Display License Codes\n";
        cout << "0. Back\n";
        printLine();
        cout << "\nEnter Choice : ";
        cin >> choice;
        ignoreLine();

        if (choice == 1) addLicense();
        else if (choice == 2) verifyLicense();
        else if (choice == 3) displayLicenses();
        else if (choice != 0) printMessageBox("INVALID CHOICE", "Please select a valid license option.");
    } while (choice != 0);
}

void clipSorterMenu() {
    int choice;
    do {
        cout << "\nCLIP SORTER MENU\n";
        printLine();
        cout << "1. Add Clip Retention Data\n";
        cout << "2. Display Clips by Highest Retention\n";
        cout << "0. Back\n";
        printLine();
        cout << "\nEnter Choice : ";
        cin >> choice;
        ignoreLine();

        if (choice == 1) addClip();
        else if (choice == 2) displaySortedClips();
        else if (choice != 0) printMessageBox("INVALID CHOICE", "Please select a valid clip sorter option.");
    } while (choice != 0);
}

void syndicationGridMenu() {
    int choice;
    do {
        cout << "\nSYNDICATION GRID MENU\n";
        printLine();
        cout << "1. Add Licensing Platform\n";
        cout << "2. Add Licensing Connection\n";
        cout << "3. Display Syndication Grid\n";
        cout << "0. Back\n";
        printLine();
        cout << "\nEnter Choice : ";
        cin >> choice;
        ignoreLine();

        if (choice == 1) addPlatform();
        else if (choice == 2) addLicensingConnection();
        else if (choice == 3) displaySyndicationGrid();
        else if (choice != 0) printMessageBox("INVALID CHOICE", "Please select a valid grid option.");
    } while (choice != 0);
}

void deliveryTransportMenu() {
    int choice;
    do {
        cout << "\nDELIVERY TRANSPORT MENU\n";
        printLine();
        cout << "1. Find Lowest Cost Delivery Route\n";
        cout << "0. Back\n";
        printLine();
        cout << "\nEnter Choice : ";
        cin >> choice;
        ignoreLine();

        if (choice == 1) findLowestCostRoute();
        else if (choice != 0) printMessageBox("INVALID CHOICE", "Please select a valid delivery option.");
    } while (choice != 0);
}

void frameSplitterMenu() {
    int choice;
    do {
        cout << "\nFRAME SPLITTER MENU\n";
        printLine();
        cout << "1. Distribute Encoding Frames\n";
        cout << "0. Back\n";
        printLine();
        cout << "\nEnter Choice : ";
        cin >> choice;
        ignoreLine();

        if (choice == 1) splitFramesAcrossProcessors();
        else if (choice != 0) printMessageBox("INVALID CHOICE", "Please select a valid frame splitter option.");
    } while (choice != 0);
}

// Feature functions
void addVideo() {
    Video video;

    cout << "\nADD VIDEO\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "Video ID" << ": ";
    cin >> video.id;
    ignoreLine();

    if (videoIndexById.find(video.id) != videoIndexById.end()) {
        printMessageBox("CATALOG RESULT", "Video ID Already Exists.");
        return;
    }

    cout << left << setw(PROMPT_WIDTH) << "Title" << ": ";
    getline(cin, video.title);
    cout << left << setw(PROMPT_WIDTH) << "Genre" << ": ";
    getline(cin, video.genre);
    cout << left << setw(PROMPT_WIDTH) << "Category" << ": ";
    getline(cin, video.category);
    cout << left << setw(PROMPT_WIDTH) << "Tag" << ": ";
    getline(cin, video.tag);
    cout << left << setw(PROMPT_WIDTH) << "License Code" << ": ";
    getline(cin, video.licenseCode);
    printLine();

    videos.push_back(video);
    rebuildCatalogIndex();
    printMessageBox("CATALOG RESULT", "Video Added Successfully.");
}

void searchVideosByMetadata() {
    string key;

    cout << "\nSEARCH VIDEO\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "Genre Category or Tag" << ": ";
    getline(cin, key);
    printLine();
    key = toLowerText(key);

    if (catalogIndex.find(key) == catalogIndex.end()) {
        printMessageBox("SEARCH RESULT", "No Videos Found For The Entered Metadata.");
        return;
    }

    vector<Video> resultVideos;
    vector<int> indexes = catalogIndex[key];
    for (int i = 0; i < (int)indexes.size(); i++) {
        resultVideos.push_back(videos[indexes[i]]);
    }

    printVideoTable("SEARCH RESULT", resultVideos);
}

void displayCatalog() {
    if (videos.empty()) {
        printMessageBox("CATALOG REPORT", "No Videos Are Available In The Catalog.");
        return;
    }
    printVideoTable("VIDEO CATALOG", videos);
}

void updateViewingState() {
    int subscriberId, videoId;
    string newState;

    cout << "\nRECORD VIEWING STATE\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "Subscriber ID" << ": ";
    cin >> subscriberId;
    cout << left << setw(PROMPT_WIDTH) << "Video ID" << ": ";
    cin >> videoId;
    ignoreLine();
    cout << left << setw(PROMPT_WIDTH) << "New State" << ": ";
    getline(cin, newState);
    printLine();

    pair<int, int> key = make_pair(subscriberId, videoId);
    string previousState = "none";
    if (viewingStates.find(key) != viewingStates.end()) {
        previousState = viewingStates[key];
    }

    viewingStates[key] = newState;
    correctionLog.push({subscriberId, videoId, previousState, newState});
    printMessageBox("CORRECTION LOG", "Viewing State Recorded Successfully.");
}

void undoLastViewingState() {
    if (correctionLog.empty()) {
        printMessageBox("UNDO RESULT", "No Viewing State Change Is Available To Undo.");
        return;
    }

    ViewingStateChange change = correctionLog.top();
    correctionLog.pop();

    pair<int, int> key = make_pair(change.subscriberId, change.videoId);
    if (change.previousState == "none") {
        viewingStates.erase(key);
    } else {
        viewingStates[key] = change.previousState;
    }

    printMessageBox("UNDO RESULT", "Last Viewing State Change Reversed Successfully.");
}

void displayViewingStates() {
    if (viewingStates.empty()) {
        printMessageBox("VIEWING STATES", "No Subscriber Viewing States Are Recorded.");
        return;
    }

    cout << "\nVIEWING STATES REPORT\n";
    printLine(80);
    cout << left << setw(20) << "SUBSCRIBER ID"
        << setw(20) << "VIDEO ID"
        << setw(40) << "CURRENT STATE" << "\n";
    printLine(80);

    for (map<pair<int, int>, string>::iterator it = viewingStates.begin(); it != viewingStates.end(); it++) {
        cout << left << setw(20) << it->first.first
            << setw(20) << it->first.second
            << setw(40) << shortText(it->second, 38) << "\n";
    }

    printLine(80);
    cout << "Total States : " << viewingStates.size() << "\n";
}

void addPipelineTask() {
    PipelineTask task;

    cout << "\nADD PIPELINE TASK\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "Task ID" << ": ";
    cin >> task.taskId;
    ignoreLine();
    cout << left << setw(PROMPT_WIDTH) << "Task Type" << ": ";
    getline(cin, task.taskType);
    cout << left << setw(PROMPT_WIDTH) << "Details" << ": ";
    getline(cin, task.details);
    printLine();

    algorithmPipeline.push(task);
    printMessageBox("PIPELINE RESULT", "Task Added To FIFO Algorithm Pipeline.");
}

void processNextPipelineTask() {
    if (algorithmPipeline.empty()) {
        printMessageBox("PIPELINE RESULT", "No Pending Task Is Available For Processing.");
        return;
    }

    PipelineTask task = algorithmPipeline.front();
    algorithmPipeline.pop();

    cout << "\nPROCESSED TASK\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "Task ID" << ": " << task.taskId << "\n";
    cout << left << setw(PROMPT_WIDTH) << "Task Type" << ": " << task.taskType << "\n";
    cout << left << setw(PROMPT_WIDTH) << "Details" << ": " << task.details << "\n";
    printLine();
}

void displayPipelineTasks() {
    if (algorithmPipeline.empty()) {
        printMessageBox("PIPELINE REPORT", "No Pending Tasks Are Available.");
        return;
    }

    cout << "\nPENDING PIPELINE TASKS\n";
    printLine(90);
    cout << left << setw(15) << "TASK ID"
        << setw(25) << "TASK TYPE"
        << setw(50) << "DETAILS" << "\n";
    printLine(90);

    queue<PipelineTask> copyQueue = algorithmPipeline;
    int totalTasks = 0;
    while (!copyQueue.empty()) {
        PipelineTask task = copyQueue.front();
        copyQueue.pop();
        totalTasks++;

        cout << left << setw(15) << task.taskId
            << setw(25) << shortText(task.taskType, 23)
            << setw(50) << shortText(task.details, 48) << "\n";
    }

    printLine(90);
    cout << "Total Pending Tasks : " << totalTasks << "\n";
}

void addLicense() {
    License license;

    cout << "\nADD LICENSE CODE\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "License Code" << ": ";
    getline(cin, license.code);
    cout << left << setw(PROMPT_WIDTH) << "Publisher Name" << ": ";
    getline(cin, license.publisher);
    cout << left << setw(PROMPT_WIDTH) << "Region" << ": ";
    getline(cin, license.region);
    printLine();

    licenseDirectory[license.code] = license;
    printMessageBox("LICENSE RESULT", "License Code Stored Successfully.");
}

void verifyLicense() {
    string code, region;

    cout << "\nVERIFY LICENSE\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "License Code" << ": ";
    getline(cin, code);
    cout << left << setw(PROMPT_WIDTH) << "Region" << ": ";
    getline(cin, region);
    printLine();

    if (licenseDirectory.find(code) == licenseDirectory.end()) {
        printMessageBox("LICENSE RESULT", "License Code Is Not Registered.");
        return;
    }

    if (toLowerText(licenseDirectory[code].region) == toLowerText(region)) {
        printMessageBox("LICENSE RESULT", "Content Is Licensed For This Region.");
    } else {
        printMessageBox("LICENSE RESULT", "Content Is Not Licensed For This Region.");
    }
}

void displayLicenses() {
    if (licenseDirectory.empty()) {
        printMessageBox("LICENSE REPORT", "No License Codes Are Registered.");
        return;
    }

    cout << "\nLICENSE CODE REPORT\n";
    printLine(90);
    cout << left << setw(25) << "LICENSE CODE"
        << setw(35) << "PUBLISHER"
        << setw(30) << "REGION" << "\n";
    printLine(90);

    for (unordered_map<string, License>::iterator it = licenseDirectory.begin(); it != licenseDirectory.end(); it++) {
        cout << left << setw(25) << shortText(it->second.code, 23)
            << setw(35) << shortText(it->second.publisher, 33)
            << setw(30) << shortText(it->second.region, 28) << "\n";
    }

    printLine(90);
    cout << "Total Licenses : " << licenseDirectory.size() << "\n";
}

void addClip() {
    Clip clip;

    cout << "\nADD CLIP RETENTION DATA\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "Clip ID" << ": ";
    cin >> clip.clipId;
    ignoreLine();
    cout << left << setw(PROMPT_WIDTH) << "Clip Title" << ": ";
    getline(cin, clip.title);
    cout << left << setw(PROMPT_WIDTH) << "User Retention Minutes" << ": ";
    cin >> clip.retentionMinutes;
    ignoreLine();
    printLine();

    clips.push_back(clip);
    printMessageBox("CLIP RESULT", "Clip Retention Data Added Successfully.");
}

void displaySortedClips() {
    if (clips.empty()) {
        printMessageBox("CLIP REPORT", "No Clip Retention Data Is Available.");
        return;
    }

    vector<Clip> sortedClips = clips;
    sort(sortedClips.begin(), sortedClips.end(), [](Clip first, Clip second) {
        return first.retentionMinutes > second.retentionMinutes;
    });

    cout << "\nCLIP RETENTION REPORT\n";
    printLine(85);
    cout << left << setw(10) << "RANK"
        << setw(15) << "CLIP ID"
        << setw(40) << "TITLE"
        << setw(20) << "RETENTION" << "\n";
    printLine(85);

    for (int i = 0; i < (int)sortedClips.size(); i++) {
        cout << left << setw(10) << i + 1
            << setw(15) << sortedClips[i].clipId
            << setw(40) << shortText(sortedClips[i].title, 38)
            << fixed << setprecision(2) << setw(20) << sortedClips[i].retentionMinutes << "\n";
    }

    printLine(85);
    cout << "Total Clips : " << sortedClips.size() << "\n";
}

void addPlatform() {
    Platform platform;

    cout << "\nADD LICENSING PLATFORM\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "Platform ID" << ": ";
    cin >> platform.id;
    ignoreLine();

    if (findPlatformIndexById(platform.id) != -1) {
        printMessageBox("GRID RESULT", "Platform ID Already Exists.");
        return;
    }

    cout << left << setw(PROMPT_WIDTH) << "Platform Name" << ": ";
    getline(cin, platform.name);
    printLine();

    platforms.push_back(platform);
    syndicationGrid.push_back(vector<Edge>());
    printMessageBox("GRID RESULT", "Licensing Platform Added Successfully.");
}

void addLicensingConnection() {
    int fromId, toId, cost;

    cout << "\nADD LICENSING CONNECTION\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "Source Platform ID" << ": ";
    cin >> fromId;
    cout << left << setw(PROMPT_WIDTH) << "Destination Platform ID" << ": ";
    cin >> toId;
    cout << left << setw(PROMPT_WIDTH) << "Delivery Cost" << ": ";
    cin >> cost;
    ignoreLine();
    printLine();

    int fromIndex = findPlatformIndexById(fromId);
    int toIndex = findPlatformIndexById(toId);

    if (fromIndex == -1 || toIndex == -1) {
        printMessageBox("GRID RESULT", "Source Or Destination Platform Was Not Found.");
        return;
    }

    syndicationGrid[fromIndex].push_back({toIndex, cost});
    printMessageBox("GRID RESULT", "Licensing Connection Added Successfully.");
}

void displaySyndicationGrid() {
    if (platforms.empty()) {
        printMessageBox("GRID REPORT", "No Platforms Are Available In The Grid.");
        return;
    }

    cout << "\nSYNDICATION GRID REPORT\n";
    printLine(95);
    cout << left << setw(15) << "ID"
        << setw(30) << "PLATFORM"
        << setw(35) << "CONNECTION"
        << setw(15) << "COST" << "\n";
    printLine(95);

    for (int i = 0; i < (int)platforms.size(); i++) {
        if (syndicationGrid[i].empty()) {
            cout << left << setw(15) << platforms[i].id
                << setw(30) << shortText(platforms[i].name, 28)
                << setw(35) << "No outgoing connection"
                << setw(15) << "-" << "\n";
        } else {
            for (int j = 0; j < (int)syndicationGrid[i].size(); j++) {
                int destination = syndicationGrid[i][j].destination;
                cout << left << setw(15) << platforms[i].id
                    << setw(30) << shortText(platforms[i].name, 28)
                    << setw(35) << shortText(platforms[destination].name, 33)
                    << setw(15) << syndicationGrid[i][j].cost << "\n";
            }
        }
    }

    printLine(95);
}

void findLowestCostRoute() {
    int sourceId, targetId;

    cout << "\nFIND LOWEST COST DELIVERY ROUTE\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "Rights Holder Platform ID" << ": ";
    cin >> sourceId;
    cout << left << setw(PROMPT_WIDTH) << "User Device Platform ID" << ": ";
    cin >> targetId;
    ignoreLine();
    printLine();

    int source = findPlatformIndexById(sourceId);
    int target = findPlatformIndexById(targetId);

    if (source == -1 || target == -1) {
        printMessageBox("DELIVERY RESULT", "Source Or Target Platform Was Not Found.");
        return;
    }

    int n = platforms.size();
    vector<int> distance(n, numeric_limits<int>::max());
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    distance[source] = 0;
    minHeap.push(make_pair(0, source));

    while (!minHeap.empty()) {
        int currentCost = minHeap.top().first;
        int current = minHeap.top().second;
        minHeap.pop();

        if (currentCost != distance[current]) {
            continue;
        }

        for (int i = 0; i < (int)syndicationGrid[current].size(); i++) {
            Edge edge = syndicationGrid[current][i];
            if (distance[current] + edge.cost < distance[edge.destination]) {
                distance[edge.destination] = distance[current] + edge.cost;
                parent[edge.destination] = current;
                minHeap.push(make_pair(distance[edge.destination], edge.destination));
            }
        }
    }

    if (distance[target] == numeric_limits<int>::max()) {
        printMessageBox("DELIVERY RESULT", "No Delivery Route Exists Between Selected Platforms.");
        return;
    }

    vector<int> path;
    int current = target;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());

    string route = "";
    for (int i = 0; i < (int)path.size(); i++) {
        route += platforms[path[i]].name;
        if (i != (int)path.size() - 1) {
            route += " -> ";
        }
    }

    cout << "\nDELIVERY ROUTE REPORT\n";
    printLine();
    cout << left << setw(15) << "Source" << ": " << platforms[source].name << "\n";
    cout << left << setw(15) << "Destination" << ": " << platforms[target].name << "\n";
    cout << left << setw(15) << "Total Cost" << ": " << distance[target] << "\n";
    cout << left << setw(15) << "Route" << ": " << route << "\n";
    printLine();
}

void splitFramesAcrossProcessors() {
    int processorCount, frameCount;
    vector<FrameTask> frames;

    cout << "\nDISTRIBUTE ENCODING FRAMES\n";
    printLine();
    cout << left << setw(PROMPT_WIDTH) << "Number of Processors" << ": ";
    cin >> processorCount;
    cout << left << setw(PROMPT_WIDTH) << "Number of Heavy Frames" << ": ";
    cin >> frameCount;

    if (processorCount <= 0 || frameCount <= 0) {
        ignoreLine();
        printMessageBox("FRAME RESULT", "Processor Count And Frame Count Must Be Positive.");
        return;
    }

    for (int i = 0; i < frameCount; i++) {
        FrameTask frame;
        frame.frameId = i + 1;
        cout << left << setw(PROMPT_WIDTH) << ("Encoding Time Frame " + to_string(i + 1)) << ": ";
        cin >> frame.encodingTime;
        frames.push_back(frame);
    }
    ignoreLine();
    printLine();

    sort(frames.begin(), frames.end(), [](FrameTask first, FrameTask second) {
        return first.encodingTime > second.encodingTime;
    });

    priority_queue<ProcessorLoad, vector<ProcessorLoad>, CompareProcessorLoad> minHeap;
    vector<vector<FrameTask>> assignedFrames(processorCount);

    for (int i = 0; i < processorCount; i++) {
        minHeap.push({i + 1, 0});
    }

    for (int i = 0; i < (int)frames.size(); i++) {
        ProcessorLoad processor = minHeap.top();
        minHeap.pop();

        assignedFrames[processor.processorId - 1].push_back(frames[i]);
        processor.currentLoad += frames[i].encodingTime;
        minHeap.push(processor);
    }

    int totalEncodingTime = 0;

    cout << "\nFRAME SPLITTER REPORT\n";
    printLine(80);
    cout << left << setw(20) << "PROCESSOR"
        << setw(40) << "FRAMES"
        << setw(20) << "LOAD" << "\n";
    printLine(80);

    for (int i = 0; i < processorCount; i++) {
        int load = 0;
        string frameList = "";

        for (int j = 0; j < (int)assignedFrames[i].size(); j++) {
            load += assignedFrames[i][j].encodingTime;
            frameList += "F" + to_string(assignedFrames[i][j].frameId) + " ";
        }

        totalEncodingTime = max(totalEncodingTime, load);

        cout << left << setw(20) << i + 1
            << setw(40) << shortText(frameList, 38)
            << setw(20) << load << "\n";
    }

    printLine(80);
    cout << left << setw(20) << "Total Encoding Time" << ": " << totalEncodingTime << "\n";
}

// Main function
int main() {
    loadSampleData();
    int choice;

    do {
        printTitle();
        printMainMenu();
        cin >> choice;
        ignoreLine();

        if (choice == 1) catalogMenu();
        else if (choice == 2) correctionLogMenu();
        else if (choice == 3) algorithmPipelineMenu();
        else if (choice == 4) registrationCodeMenu();
        else if (choice == 5) clipSorterMenu();
        else if (choice == 6) syndicationGridMenu();
        else if (choice == 7) deliveryTransportMenu();
        else if (choice == 8) frameSplitterMenu();
        else if (choice == 0) printExitScreen();
        else printMessageBox("INVALID CHOICE", "Please select a valid main menu option.");
    } while (choice != 0);

    return 0;
}