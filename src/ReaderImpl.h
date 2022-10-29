/*
 * Copyright (c) 2010 Stan Coleby (scoleby@intelisum.com)
 * Copyright (c) 2020 PTC Inc.
 * Copyright (c) 2022 Andy Maloney <asmaloney@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "E57SimpleData.h"
#include "E57SimpleReader.h"

namespace e57
{
   //! most of the functions follows Reader
   class ReaderImpl
   {
   public:
      explicit ReaderImpl( const ustring &filePath, const ReaderOptions &options );
      ~ReaderImpl();

      // disallow copying a ReaderImpl
      ReaderImpl( const ReaderImpl & ) = delete;
      ReaderImpl &operator=( ReaderImpl const & ) = delete;
      ReaderImpl( const ReaderImpl && ) = delete;
      ReaderImpl &operator=( const ReaderImpl && ) = delete;

      bool IsOpen() const;

      bool Close();

      bool GetE57Root( E57Root &fileHeader ) const;

      int64_t GetImage2DCount() const;

      bool ReadImage2D( int64_t imageIndex, Image2D &Image2DHeader ) const;

      bool GetImage2DSizes( int64_t imageIndex, Image2DProjection &imageProjection, Image2DType &imageType,
                            int64_t &imageWidth, int64_t &imageHeight, int64_t &imageSize, Image2DType &imageMaskType,
                            Image2DType &imageVisualType ) const;

      size_t ReadImage2DData( int64_t imageIndex, Image2DProjection imageProjection, Image2DType imageType,
                              uint8_t *pBuffer, int64_t start, size_t count ) const;

      int64_t GetData3DCount() const;

      bool ReadData3D( int64_t dataIndex, Data3D &data3DHeader ) const;

      bool GetData3DSizes( int64_t dataIndex, int64_t &rowMax, int64_t &columnMax, int64_t &pointsSize,
                           int64_t &groupsSize, int64_t &countSize, bool &bColumnIndex ) const;

      bool ReadData3DGroupsData( int64_t dataIndex, int64_t groupCount, int64_t *idElementValue,
                                 int64_t *startPointIndex, int64_t *pointCount ) const;

      template <typename COORDTYPE>
      CompressedVectorReader SetUpData3DPointsData( int64_t dataIndex, size_t pointCount,
                                                    const Data3DPointsData_t<COORDTYPE> &buffers ) const;

      StructureNode GetRawE57Root() const;

      VectorNode GetRawData3D() const;

      VectorNode GetRawImages2D() const;

      ImageFile GetRawIMF() const;

   private:
      ImageFile imf_;
      StructureNode root_;

      VectorNode data3D_;

      VectorNode images2D_;
   }; // end Reader class
} // end namespace e57
