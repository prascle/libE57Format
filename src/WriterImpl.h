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
#include "E57SimpleWriter.h"

namespace e57
{
   //! most of the functions follows Writer
   class WriterImpl
   {
   public:
      WriterImpl( const ustring &filePath, const WriterOptions &options );
      ~WriterImpl();

      // disallow copying a WriterImpl
      WriterImpl( const WriterImpl & ) = delete;
      WriterImpl &operator=( WriterImpl const & ) = delete;
      WriterImpl( const WriterImpl && ) = delete;
      WriterImpl &operator=( const WriterImpl && ) = delete;

      bool IsOpen() const;

      bool Close();

      int64_t NewImage2D( Image2D &image2DHeader );

      size_t WriteImage2DData( int64_t imageIndex, Image2DType imageType, Image2DProjection imageProjection,
                               uint8_t *pBuffer, int64_t start, size_t count );

      int64_t NewData3D( Data3D &data3DHeader );

      template <typename COORDTYPE>
      CompressedVectorWriter SetUpData3DPointsData( int64_t dataIndex, size_t pointCount,
                                                    const Data3DPointsData_t<COORDTYPE> &buffers );

      bool WriteData3DGroupsData( int64_t dataIndex, int64_t groupCount, int64_t *idElementValue,
                                  int64_t *startPointIndex, int64_t *pointCount );

      StructureNode GetRawE57Root();

      VectorNode GetRawData3D();

      VectorNode GetRawImages2D();

      ImageFile GetRawIMF();

   private:
      ImageFile imf_;
      StructureNode root_;

      VectorNode data3D_;

      VectorNode images2D_;
   }; // end Writer class
} // end namespace e57
