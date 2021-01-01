//
// Taken and modified from opencv v4.0 to support cap_v4l.cpp
//
/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#ifndef __VIDEOIO_H_
#define __VIDEOIO_H_

//#include "opencv2/videoio.hpp"
//#include "opencv2/videoio/legacy/constants_c.h"

//#include "opencv2/core/utility.hpp"
//#include "opencv2/core/private.hpp"

//#include <opencv2/core/utils/configuration.private.hpp>
//#include <opencv2/core/utils/logger.hpp>

//#include "opencv2/imgcodecs.hpp"

//#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui.hpp"

//#include "opencv2/videoio/videoio_c.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <assert.h>  // FIXIT remove this

#if defined _WIN32 || defined WINCE
    #if !defined _WIN32_WINNT
        #ifdef HAVE_MSMF
            #define _WIN32_WINNT 0x0600 // Windows Vista
        #else
            #define _WIN32_WINNT 0x0501 // Windows XP
        #endif
    #endif

    #include <windows.h>
    #undef small
    #undef min
    #undef max
    #undef abs
#endif

#define __BEGIN__ __CV_BEGIN__
#define __END__  __CV_END__
#define EXIT __CV_EXIT__

/***************************** CvCapture structure ******************************/

struct CvCapture
{
    virtual ~CvCapture() {}
    virtual double getProperty(int) const { return 0; }
    virtual bool setProperty(int, double) { return 0; }
    virtual bool grabFrame() { return true; }
    virtual IplImage* retrieveFrame(int) { return 0; }
    virtual int getCaptureDomain() { return 0; } // Return the type of the capture object: CAP_DSHOW, etc...
};

/*************************** CvVideoWriter structure ****************************/

struct CvVideoWriter
{
    virtual ~CvVideoWriter() {}
    virtual bool writeFrame(const IplImage*) { return false; }
    virtual int getCaptureDomain() const { return 0; } // Return the type of the capture object: CAP_FFMPEG, etc...
};

CvCapture * cvCreateCameraCapture_V4L( int index );
CvCapture * cvCreateCameraCapture_V4L( const char* deviceName );
CvCapture * cvCreateCameraCapture_DC1394_2( int index );
CvCapture* cvCreateCameraCapture_MIL( int index );
CvCapture* cvCreateCameraCapture_Giganetix( int index );
CvCapture* cvCreateFileCapture_Win32( const char* filename );
CvVideoWriter* cvCreateVideoWriter_Win32( const char* filename, int fourcc,
                                          double fps, CvSize frameSize, int is_color );
CvCapture* cvCreateCameraCapture_DShow( int index );
CvCapture* cvCreateCameraCapture_OpenNI( int index );
CvCapture* cvCreateCameraCapture_OpenNI2( int index );
CvCapture* cvCreateFileCapture_OpenNI( const char* filename );
CvCapture* cvCreateFileCapture_OpenNI2( const char* filename );
CvCapture* cvCreateCameraCapture_Android( int index );
CvCapture* cvCreateCameraCapture_XIMEA( int index );
CvCapture* cvCreateCameraCapture_XIMEA( const char* serialNumber );
CvCapture* cvCreateCameraCapture_AVFoundation(int index);
CvCapture* cvCreateCameraCapture_Aravis( int index );

CvVideoWriter* cvCreateVideoWriter_Images(const char* filename);


#define CV_CAP_GSTREAMER_1394		0
#define CV_CAP_GSTREAMER_V4L		1
#define CV_CAP_GSTREAMER_V4L2		2
#define CV_CAP_GSTREAMER_FILE		3

CvCapture * cvCreateFileCapture_QT (const char  * filename);
CvCapture * cvCreateCameraCapture_QT  (const int     index);

CvVideoWriter* cvCreateVideoWriter_QT ( const char* filename, int fourcc,
                                        double fps, CvSize frameSize, int is_color );

CvCapture* cvCreateFileCapture_AVFoundation (const char * filename);
CvVideoWriter* cvCreateVideoWriter_AVFoundation( const char* filename, int fourcc,
                                                double fps, CvSize frameSize, int is_color );


CvCapture * cvCreateCameraCapture_PvAPI  (const int     index);
CvVideoWriter* cvCreateVideoWriter_GStreamer( const char* filename, int fourcc,
                                            double fps, CvSize frameSize, int is_color );


namespace cv
{

//#`fdef CVCAPANY
/// from videoio.hpp

/** @brief %VideoCapture API backends identifier.
 *
 * Select preferred API for a capture object.
 *e used in the VideoCapture::VideoCapture() constructor or VideoCapture::open()
 *
 * @note Backends are available only if they have been built with your OpenCV binaries.
 * See @ref videoio_overview for more information.
 * */
//#ifdef DELETETHIS	
    
    class IVideoCapture
    {
    public:
        virtual ~IVideoCapture() {}
        virtual double getProperty(int) const { return 0; }
        virtual bool setProperty(int, double) { return false; }
        virtual bool grabFrame() = 0;
        virtual bool retrieveFrame(int, OutputArray) = 0;
        virtual bool isOpened() const = 0;
        virtual int getCaptureDomain() { return 0; } // Return the type of the capture object: CAP_DSHOW, etc...
    };

    class IVideoWriter
    {
    public:
        virtual ~IVideoWriter() {}
        virtual double getProperty(int) const { return 0; }
        virtual bool setProperty(int, double) { return false; }

        virtual bool isOpened() const = 0;
        virtual void write(InputArray) = 0;

        virtual int getCaptureDomain() const { return cv::CAP_ANY; } // Return the type of the capture object: CAP_FFMPEG, etc...
    };

    Ptr<IVideoCapture> createFileCapture_Images(const String& filename);

    Ptr<IVideoCapture> createMotionJpegCapture(const String& filename);
    Ptr<IVideoWriter> createMotionJpegWriter(const String& filename, int fourcc, double fps, Size frameSize, bool iscolor);

    Ptr<IVideoCapture> createGPhoto2Capture(int index);
    Ptr<IVideoCapture> createGPhoto2Capture(const String& deviceName);


    Ptr<IVideoCapture> createXINECapture(const char* filename);

    Ptr<IVideoCapture> createGStreamerCapture(const String& filename);
    Ptr<IVideoCapture> createGStreamerCapture(int index);

    Ptr<cv::IVideoCapture> cvCreateFileCapture_FFMPEG_proxy(const String& filename);
    Ptr<IVideoWriter> cvCreateVideoWriter_FFMPEG_proxy(const String& filename, int fourcc, double fps, Size frameSize, int isColor);

    Ptr<IVideoCapture> cvCreateCapture_MSMF(int index);
    Ptr<IVideoCapture> cvCreateCapture_MSMF(const String& filename);
    Ptr<IVideoWriter> cvCreateVideoWriter_MSMF(const String& filename, int fourcc, double fps, Size frameSize, int is_color);
}

#endif /* __VIDEOIO_H_ */
