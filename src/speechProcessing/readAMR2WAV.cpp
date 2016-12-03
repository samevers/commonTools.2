/* ------------------------------------------------------------------
 * Copyright (C) 2009 Martin Storsjo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */

#include "decodeAmr.h"
#include <sstream>
#include <vector>
#include "../include/gary_common/gary_string.h"
extern "C" {
//#include <interf_dec.h>
#include "opencore-amr/amrnb/interf_dec.h"
}
using namespace std;


/* From WmfDecBytesPerFrame in dec_input_format_tab.cpp */
const int sizes[] = { 12, 13, 15, 17, 19, 20, 26, 31, 5, 6, 5, 5, 0, 0, 0, 0 };

int readAmr2int16(string& filename, string& speechLine) {

	FILE* in = fopen(filename.c_str(), "rb");
	if (!in) {
		_ERROR("Fail to open file < %s >" ,filename.c_str());
		return -1;
	}
	char header[6];
	int n = fread(header, 1, 6, in);
	if (n != 6 || memcmp(header, "#!AMR\n", 6)) {
		_ERROR("Bad header, amr2wav FAILS.");
		return 1;
	}
	//cout << "header : " << header << endl;

	
	void* amr = Decoder_Interface_init();
	string content = "";
	stringstream os;
	os.str("");
	while (true) {
		uint8_t buffer[500];
		/* Read the mode byte */
		n = fread(buffer, 1, 1, in);
		if (n <= 0)
			break;
		//cout << "buffer : " << buffer << endl;
		/* Find the packet size */
		int size = sizes[(buffer[0] >> 3) & 0x0f];
		if (size <= 0)
			break;
		n = fread(buffer + 1, 1, size, in);
		//cout << "buffer + 1 : " << buffer + 1 << endl;

		if (n != size)
			break;

		/* Decode the packet */
		int16_t outbuffer[160];
		Decoder_Interface_Decode(amr, buffer, outbuffer, 0);
		//cout << "outbuffer: " << endl;
		for (int i = 0; i < 160; i++) 
		{
			os << outbuffer[i] << "\t";
			//cout << outbuffer[i];
		}
		os << "##_##";
	}
	speechLine = os.str();
	cout << speechLine << endl; 
	fclose(in);
	Decoder_Interface_exit(amr);
	return 0;
}

int readint16toWav(string filename, string& line) {
	string outfilename = filename + ".wav";
	WavWriter wav(outfilename.c_str(), 8000, 16, 1);

	/* Convert to little endian and write to wav */
	vector<string> vec;
	spaceGary::StringSplit(line, vec, "##_##");
	for (int i = 0; i < vec.size() - 1; i++)
	{
		vector<string> vv;
		spaceGary::StringSplit(vec[i], vv, "\t");
		uint8_t littleendian[320];
		uint8_t* ptr = littleendian;
		if(vv.size() != 160)
		{
			cerr << "ERROR. vv size != 160" << endl;
			return -1;
		}
		for (int j = 0; j < 160; j++) {
			stringstream os;
			os.str("");
			os << vv[j];
			int16_t v;
			os >> v;
			*ptr++ = (v >> 0) & 0xff;
			*ptr++ = (v >> 8) & 0xff;
		}
		wav.writeData(littleendian, 320);
	}
	return 0;
}
int main()
{
	string filename = "data/amr.amr";
	string speechLine;
	readAmr2int16(filename, speechLine);
	readint16toWav(filename, speechLine);

	//readAmr(filename);
	return 0;
}
