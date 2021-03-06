/*
The MIT License (MIT)

This file is part of the Phoenard Arduino library
Copyright (c) 2014 Phoenard

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/**
 * @file
 * @brief Contains the DataBuffer class for safely storing dynamic memory on the heap
 */

#include <Arduino.h>
#include "PHNTextContainer.h"

#ifndef _DATA_BUFFER_H_
#define _DATA_BUFFER_H_

/**
 * @brief Maintains data stored on the heap and frees it when the class is destructed
 *
 * The problem of storing arrays as containers is that they are fixed-size, and with heap
 * memory the size and freeing all has to be maintained. That is what this class solves.
 * Memory can be easily allocated/resized and destroyed as the class is used.
 */
class DataBuffer : public PHN_TextContainer {
public:
  /// Creates a new buffer without any data
  DataBuffer() : data(NULL), dataSize(0) {}
  /// Creates a new buffer, copying the initial data into the buffer
  DataBuffer(const void* data, int dataSize);
  /// Destructor frees the memory
  ~DataBuffer();
  /// Resizes the buffer preserving contents to newDataSize, shrinking if needed
  void resize(int newDataSize);
  /// Resizes the buffer preserving contents to fit newDataSize
  void growToFit(int newDataSize);
  /// Sets new data to be stored, the data is copied into this buffer
  void set(const void* data, int dataSize);
  /// Assigns data from one buffer to another
  DataBuffer& operator=( const DataBuffer& other );

  // Implementation for PHN_TextContainer
  virtual const char* text() { return (char*) data; }
  virtual void setTextRaw(const char* text, int textLen);
  
  void* data;
  int dataSize;
};

#endif