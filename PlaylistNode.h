#ifndef PLAYLISTNODE_H
#define PLAYLISTNODE_H

#include <string>
using namespace std;

class PlaylistNode {

public:
    PlaylistNode();
    PlaylistNode(string initID, string initSongName, string initArtistName, int initSongLength, PlaylistNode* nextLoc = 0);
    string GetID() const;
    string GetSongName() const;
    string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const;
    void InsertAfter(PlaylistNode* nodePtr);
    void SetNext(PlaylistNode* nodePtr);
    void PrintPlaylistNode() const;


private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
};

#endif
