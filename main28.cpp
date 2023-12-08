#include <iostream>
#include "PlaylistNode.h"

using namespace std;

void PrintMenu(const string playlistTitle) {
    cout << playlistTitle << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
}

PlaylistNode* ExecuteMenu(char option, string playlistTitle, PlaylistNode* headNode) {
switch (option) {
        case 'a':
            {
        string uniqueID, songName, artistName;
        int songLength;

        cout << "ADD SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        cin >> uniqueID;
        cin.ignore(); 
        
        cout << "Enter song's name:" << endl;
        getline(cin, songName);

        cout << "Enter artist's name:" << endl;
        getline(cin, artistName);

        cout << "Enter song's length (in seconds):" << endl;
        cout << endl;
        cin >> songLength;

        PlaylistNode* newNode = new PlaylistNode(uniqueID, songName, artistName, songLength);

        if (headNode == nullptr) {
            headNode = newNode; 
        } else {
            PlaylistNode* temp = headNode;
            while (temp->GetNext() != nullptr) {
                temp = temp->GetNext();
            }
            temp->SetNext(newNode); 
        }

        
        break;
    }
        case 'c':
            {
        if (headNode == nullptr) {
            cout << "Playlist is empty. No songs to change position." << endl;
            break;
        }

       
        cout << "CHANGE POSITION OF SONG" << endl;
        cout << "Enter song's current position:" << endl;
        int currentPosition, newPosition;
        cin >> currentPosition;
        cin.ignore(); 

        int nodeCount = 0;
        PlaylistNode* tempCount = headNode;
        while (tempCount != nullptr) {
            nodeCount++;
            tempCount = tempCount->GetNext();
        }

        if (currentPosition < 1 || currentPosition > nodeCount) {
            cout << "Invalid current position." << endl;
            break;
        }

        cout << "Enter new position for song:" << endl;
        cin >> newPosition;
        cin.ignore(); 

        if (newPosition < 1) {
            newPosition = 1; 
        } else if (newPosition > nodeCount) {
            newPosition = nodeCount; 
        }

        PlaylistNode* prevNode = nullptr;
        PlaylistNode* currentNode = headNode;
        for (int i = 1; i < currentPosition; ++i) {
            prevNode = currentNode;
            currentNode = currentNode->GetNext();
        }

        if (currentPosition == newPosition) {
            cout << "The song is already at the desired position." << endl;
            break;
        }

        if (prevNode != nullptr) {
            prevNode->SetNext(currentNode->GetNext());
        } else {
            headNode = currentNode->GetNext();
        }

        PlaylistNode* tempNode = headNode;
        for (int i = 1; i < newPosition - 1; ++i) {
            tempNode = tempNode->GetNext();
        }

        if (tempNode != nullptr) {
            currentNode->SetNext(tempNode->GetNext());
            tempNode->SetNext(currentNode);
        } else {
            currentNode->SetNext(headNode);
            headNode = currentNode;
        }

        cout << "\"" << currentNode->GetSongName() << "\"" << " moved to position " << newPosition << endl;
        cout << endl;
        break;
    }
        case 's':
            {
        if (headNode == nullptr) {
            cout << "Playlist is empty." << endl;
            break;
        }

        string artistName;
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        cout << "Enter artist's name:" << endl;
        cout << endl;
        getline(cin, artistName);

        PlaylistNode* temp = headNode;
        int position = 1;
        bool found = false;

        while (temp != nullptr) {
            if (temp->GetArtistName() == artistName) {
                found = true;
                cout << position << "." << endl;
                temp->PrintPlaylistNode();
                cout << endl;
            }

            temp = temp->GetNext();
            position++;
        }

        if (!found) {
            cout << "No songs found by artist:" << artistName << endl;
        }
        break;
    }
        case 't':
             if(headNode == nullptr){
                cout << "Playlist is empty" << endl;
            }
            else{
                int total = 0;
                PlaylistNode* temp = headNode;

                cout << playlistTitle << " OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
                while(temp != nullptr){
                    total += temp->GetSongLength();
                    temp = temp->GetNext();
                }
                cout << "Total time: " << total << " seconds" << endl;
                cout << endl;  
                break;
            }
        break;
        case 'd':
            {
        if (headNode == nullptr) {
            cout << "Playlist is empty. No songs to remove." << endl;
            break;
        }

        string uniqueID;
        
        cout << "REMOVE SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        cin >> uniqueID;
        cin.ignore(); 

        PlaylistNode* current = headNode;
        PlaylistNode* previous = nullptr;
        bool found = false;

        while (current != nullptr) {
            if (current->GetID() == uniqueID) {
                found = true;
                if (previous != nullptr) {
                    previous->SetNext(current->GetNext());
                } else {
                    headNode = current->GetNext();
                }
                delete current; 
                cout << "\"" << current->GetSongName() << "\" removed." << endl;
                cout << endl;
                break;
            }
            previous = current;
            current = current->GetNext();
        }

        if (!found) {
            cout << "Song with unique ID \"" << uniqueID << "\" not found in the playlist." << endl;
            cout << endl;
        }
        break;
     }
        case 'o':
            {               
        if (headNode == nullptr) {
            cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
            cout << "Playlist is empty" << endl;
            cout << endl;
            break;
        }

        int position = 1;
        PlaylistNode* temp = headNode;

        cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
        while (temp != nullptr) {
            cout << position << "." << endl;
            temp->PrintPlaylistNode();
            cout << endl;

            temp = temp->GetNext();
            position++;
        }
        break;
    }
     
        case 'q':
       
       exit(0);
       break;
        default:
            cout << "Invalid option. Please choose a valid option from the menu." << endl;
            break;
    }
     return headNode; 
}


int main(){
    string playlistTitle;
    
    cout << "Enter playlist's title:" << endl;
    cout << endl;
    getline(cin, playlistTitle);
    
    PlaylistNode* headNode = nullptr; 
    
    char choice;
    do {
        PrintMenu(playlistTitle);
        cout << endl;
        cout << "Choose an option:" << endl;
        cin >> choice;
        cin.ignore(); 
        
        headNode = ExecuteMenu(choice, playlistTitle, headNode);
        
    } while (choice != 'q');

    return 0;
}
