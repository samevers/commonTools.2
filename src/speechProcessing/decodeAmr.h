#ifndef AMR2WAV_HEAD_H__
#define AMR2WAV_HEAD_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "wav.h"
#include <string>
#include <iostream>
#include <vector>
#include "../include/service_log.hpp"

class DecodeAmr{
	public:
		DecodeAmr();
		~DecodeAmr();
	public:
		int amr2wav(std::string& filename);
};

#endif
