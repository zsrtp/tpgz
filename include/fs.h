#pragma once
typedef void (*FileReadCallback)(void* buffer, int bytesRead);
void loadFile(const char* filePath);
void loadFile(const char* filePath, FileReadCallback);