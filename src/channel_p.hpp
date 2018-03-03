/*
 * channel_p.hpp
 *
 *  Created on: Jan 29, 2016
 *      Author: Nafis Zaman
 */

#ifndef _CHANNEL_P_HPP_
#define _CHANNEL_P_HPP_

#include "wallaby/camera.hpp"
#include <opencv2/core/core.hpp>


namespace Private
{
  namespace Camera
  {
    class HsvChannelImpl : public ::Camera::ChannelImpl
    {
    public:
      HsvChannelImpl();
      virtual void update(const cv::Mat &image);
      virtual ::Camera::ObjectVector findObjects(const Config &config);

    private:
      cv::Mat m_image;
    };

    class ArucoChannelImpl : public ::Camera::ChannelImpl
    {
    public:
      ArucoChannelImpl();
      virtual void update(const cv::Mat &image);
      virtual ::Camera::ObjectVector findObjects(const Config &config);

    private:
      cv::Mat m_image;
    };
  }
}

#endif
