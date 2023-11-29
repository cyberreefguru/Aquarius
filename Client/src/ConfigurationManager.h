/*
 * ConfigurationManager.h
 *
 *  Created on: Nov 17, 2023
 *      Author: cyberreefguru
 */
#pragma once

class ConfigurationManager {
public:
	FileSystemWrapper();
	boolean initialize();
	FatFileSystem* getFileSystem();

private:
	boolean config = false;

};
