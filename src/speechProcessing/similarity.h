#ifndef SIMILARITY_HEAD__
#define SIMILARITY_HEAD__

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>

class Similarity{
	private:
	public:
		Similarity();
		~Similarity();
		
		int loadData(string& dirs);
		int amr2wavOp(string& filename);
		int readAmr2int16(string& filename, string& speechLine);
		int readint16toWav(string filename, string& line);
		int CalSimilarity(string& file1, std::string& emotion);
		int JudgeEmotion(string& sequence, string& emotion);
	public:
		vector<vector<vector<float> > > dataFloatSmile;
		vector<vector<vector<float> > > dataFloatCry;
		vector<vector<vector<float> > > dataFloatSilent;
		queue<string> emotionQueue;
		int cry;
		int smile;
		int silent;
};



#endif
