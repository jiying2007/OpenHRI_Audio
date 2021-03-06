// -*- C++ -*-
/*!
 * @file  BeamForming.h
 * @author Isao Hara(isao-hara@aist.go.jp)
 *
 * Copyright (C) 
 *     All rights reserved.
 *
 */

#ifndef _BeamForming_H_
#define _BeamForming_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <math.h>

/*
 insert include files for 3rd party libs
*/

/*
  Data Types
*/
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

/*
  for RTC
*/
#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/SystemLogger.h>
#include <coil/Mutex.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

typedef struct mic_info {
  double x,y,z;
  double xy_rad,yz_rad;
  int dt;
  bool used;
}mic_info;

struct delay_rank {
  int mic_num,trigger_cnt;
};

using namespace RTC;

#ifndef M_PI
#define M_PI 3.14159265358979
#endif
#define SONIC 340.29
#define SEND_LENGTH 1024

/*!
 * @class BeamForming
 * @brief Periodic Console Out Component
 *
 */
class BeamForming
  : public RTC::DataFlowComponentBase
{
 public:
  void RcvBuffer(RTC::TimedOctetSeq data);
  void RcvAngle(RTC::TimedOctetSeq data);
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  BeamForming(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~BeamForming();

  // <rtc-template block="public_attribute">

  // </rtc-template>

  // <rtc-template block="public_operation">

  // </rtc-template>

   /**
     Actions
  */
   
   virtual RTC::ReturnCode_t onInitialize();

   virtual RTC::ReturnCode_t onFinalize();

   /* virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id); */

   /* virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id); */

   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

   /* virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id); */

   /* virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id); */

   /* virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id); */

   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

   /* virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id); */

   /* virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id); */

   /* virtual RTC::ReturnCode_t onAction(RTC::UniqueId ec_id); */

   /* virtual RTC::ReturnCode_t onModeChanged(RTC::UniqueId ec_id); */



 protected:
  // <rtc-template block="protected_attribute">

  // </rtc-template>

  // <rtc-template block="protected_operation">

  // </rtc-template>

  // DataPort declaration
  // <rtc-template block="dataport_declare">

  RTC::TimedOctetSeq m_mic;
  InPort<RTC::TimedOctetSeq> m_micIn;

  RTC::TimedDouble m_angle;
  InPort<RTC::TimedDouble> m_angleIn;

  RTC::TimedOctetSeq m_result;
  OutPort<RTC::TimedOctetSeq> m_resultOut;



  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">

  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">

  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">

  // </rtc-template>

 private:
  void BufferClr(void);
  void DelayFunc(void);
  mic_info *m_micinfo;
  bool is_active;
  bool m_horizon;

  // <rtc-template block="private_attribute">
  coil::Mutex m_mutex;
  
  int m_SampleRate;
  double m_ConstAngle;
  std::string m_Mode;
  int m_ChannelNumbers;


  // </rtc-template>

  // <rtc-template block="private_operation">

  // </rtc-template>

};


/*!
 * @class DataListener
 * @brief
 */
class MicDataListener
  : public ConnectorDataListenerT<RTC::TimedOctetSeq>
{
  USE_CONNLISTENER_STATUS;
public:
  /*!
   * @brief constructor
   */
  MicDataListener(const char* name, BeamForming *data) : m_name(name), m_obj(data){};

  /*!
   * @brief destructor
   */
  virtual ~MicDataListener(){};

  virtual ReturnCode operator()( ConnectorInfo& info,
                                 RTC::TimedOctetSeq& data){
    if ( m_name == "ON_BUFFER_WRITE" ) {
     /* onBufferWrite */
     m_obj->RcvBuffer(data);
    }
    return NO_CHANGE;
  };

  BeamForming *m_obj;
  std::string m_name;
};



extern "C"
{
  /*!
   * @brief BeamForming initialize
   *
   * @param manager Maneger Object
   */
  DLL_EXPORT void BeamFormingInit(RTC::Manager* manager);
};


#endif // _BeamForming_H_
