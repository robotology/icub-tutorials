/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#ifndef YARP_THRIFT_GENERATOR_IRpcServer
#define YARP_THRIFT_GENERATOR_IRpcServer

#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>

class IRpcServer;


/**
 * IRpcServer
 * Interface for an example module.
 */
class IRpcServer : public yarp::os::Wire {
public:
  IRpcServer();
  /**
   * Get answer from server
   * @return the answer
   */
  virtual std::int32_t get_answer();
  /**
   * Set value for future answers.
   * @param rightAnswer new answer
   * @return true if connection was successful
   */
  virtual bool set_answer(const std::int32_t rightAnswer);
  /**
   * Add one integer to future answers.
   * @param x value to add
   * @return new value
   */
  virtual std::int32_t add_int(const std::int32_t x);
  /**
   * Start service
   * @return true if service started correctly
   */
  virtual bool start();
  /**
   * Stop service
   * @return true if service stopped correctly
   */
  virtual bool stop();
  /**
   * Check is service is running
   * @return true/false if service is/is not running
   */
  virtual bool is_running();
  bool read(yarp::os::ConnectionReader& connection) override;
  virtual std::vector<std::string> help(const std::string& functionName="--all");
};

#endif
