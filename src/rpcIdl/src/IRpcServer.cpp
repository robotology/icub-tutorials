/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.
// It could get re-generated if the ALLOW_IDL_GENERATION flag is on.

#include <IRpcServer.h>
#include <yarp/os/idl/WireTypes.h>



class IRpcServer_get_answer : public yarp::os::Portable {
public:
  std::int32_t _return;
  void init();
  bool write(yarp::os::ConnectionWriter& connection) const override;
  bool read(yarp::os::ConnectionReader& connection) override;
};

class IRpcServer_set_answer : public yarp::os::Portable {
public:
  std::int32_t rightAnswer;
  bool _return;
  void init(const std::int32_t rightAnswer);
  bool write(yarp::os::ConnectionWriter& connection) const override;
  bool read(yarp::os::ConnectionReader& connection) override;
};

class IRpcServer_add_int : public yarp::os::Portable {
public:
  std::int32_t x;
  std::int32_t _return;
  void init(const std::int32_t x);
  bool write(yarp::os::ConnectionWriter& connection) const override;
  bool read(yarp::os::ConnectionReader& connection) override;
};

class IRpcServer_start : public yarp::os::Portable {
public:
  bool _return;
  void init();
  bool write(yarp::os::ConnectionWriter& connection) const override;
  bool read(yarp::os::ConnectionReader& connection) override;
};

class IRpcServer_stop : public yarp::os::Portable {
public:
  bool _return;
  void init();
  bool write(yarp::os::ConnectionWriter& connection) const override;
  bool read(yarp::os::ConnectionReader& connection) override;
};

class IRpcServer_is_running : public yarp::os::Portable {
public:
  bool _return;
  void init();
  bool write(yarp::os::ConnectionWriter& connection) const override;
  bool read(yarp::os::ConnectionReader& connection) override;
};

bool IRpcServer_get_answer::write(yarp::os::ConnectionWriter& connection) const {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("get_answer",1,2)) return false;
  return true;
}

bool IRpcServer_get_answer::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI32(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void IRpcServer_get_answer::init() {
  _return = 0;
}

bool IRpcServer_set_answer::write(yarp::os::ConnectionWriter& connection) const {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("set_answer",1,2)) return false;
  if (!writer.writeI32(rightAnswer)) return false;
  return true;
}

bool IRpcServer_set_answer::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void IRpcServer_set_answer::init(const std::int32_t rightAnswer) {
  _return = false;
  this->rightAnswer = rightAnswer;
}

bool IRpcServer_add_int::write(yarp::os::ConnectionWriter& connection) const {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(3)) return false;
  if (!writer.writeTag("add_int",1,2)) return false;
  if (!writer.writeI32(x)) return false;
  return true;
}

bool IRpcServer_add_int::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readI32(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void IRpcServer_add_int::init(const std::int32_t x) {
  _return = 0;
  this->x = x;
}

bool IRpcServer_start::write(yarp::os::ConnectionWriter& connection) const {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("start",1,1)) return false;
  return true;
}

bool IRpcServer_start::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void IRpcServer_start::init() {
  _return = false;
}

bool IRpcServer_stop::write(yarp::os::ConnectionWriter& connection) const {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(1)) return false;
  if (!writer.writeTag("stop",1,1)) return false;
  return true;
}

bool IRpcServer_stop::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void IRpcServer_stop::init() {
  _return = false;
}

bool IRpcServer_is_running::write(yarp::os::ConnectionWriter& connection) const {
  yarp::os::idl::WireWriter writer(connection);
  if (!writer.writeListHeader(2)) return false;
  if (!writer.writeTag("is_running",1,2)) return false;
  return true;
}

bool IRpcServer_is_running::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  if (!reader.readListReturn()) return false;
  if (!reader.readBool(_return)) {
    reader.fail();
    return false;
  }
  return true;
}

void IRpcServer_is_running::init() {
  _return = false;
}

IRpcServer::IRpcServer() {
  yarp().setOwner(*this);
}
std::int32_t IRpcServer::get_answer() {
  std::int32_t _return = 0;
  IRpcServer_get_answer helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","std::int32_t IRpcServer::get_answer()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool IRpcServer::set_answer(const std::int32_t rightAnswer) {
  bool _return = false;
  IRpcServer_set_answer helper;
  helper.init(rightAnswer);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool IRpcServer::set_answer(const std::int32_t rightAnswer)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
std::int32_t IRpcServer::add_int(const std::int32_t x) {
  std::int32_t _return = 0;
  IRpcServer_add_int helper;
  helper.init(x);
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","std::int32_t IRpcServer::add_int(const std::int32_t x)");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool IRpcServer::start() {
  bool _return = false;
  IRpcServer_start helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool IRpcServer::start()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool IRpcServer::stop() {
  bool _return = false;
  IRpcServer_stop helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool IRpcServer::stop()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}
bool IRpcServer::is_running() {
  bool _return = false;
  IRpcServer_is_running helper;
  helper.init();
  if (!yarp().canWrite()) {
    yError("Missing server method '%s'?","bool IRpcServer::is_running()");
  }
  bool ok = yarp().write(helper,helper);
  return ok?helper._return:_return;
}

bool IRpcServer::read(yarp::os::ConnectionReader& connection) {
  yarp::os::idl::WireReader reader(connection);
  reader.expectAccept();
  if (!reader.readListHeader()) { reader.fail(); return false; }
  std::string tag = reader.readTag();
  bool direct = (tag=="__direct__");
  if (direct) tag = reader.readTag();
  while (!reader.isError()) {
    // TODO: use quick lookup, this is just a test
    if (tag == "get_answer") {
      std::int32_t _return;
      _return = get_answer();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI32(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "set_answer") {
      std::int32_t rightAnswer;
      if (!reader.readI32(rightAnswer)) {
        reader.fail();
        return false;
      }
      bool _return;
      _return = set_answer(rightAnswer);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "add_int") {
      std::int32_t x;
      if (!reader.readI32(x)) {
        reader.fail();
        return false;
      }
      std::int32_t _return;
      _return = add_int(x);
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeI32(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "start") {
      bool _return;
      _return = start();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "stop") {
      bool _return;
      _return = stop();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "is_running") {
      bool _return;
      _return = is_running();
      yarp::os::idl::WireWriter writer(reader);
      if (!writer.isNull()) {
        if (!writer.writeListHeader(1)) return false;
        if (!writer.writeBool(_return)) return false;
      }
      reader.accept();
      return true;
    }
    if (tag == "help") {
      std::string functionName;
      if (!reader.readString(functionName)) {
        functionName = "--all";
      }
      std::vector<std::string> _return=help(functionName);
      yarp::os::idl::WireWriter writer(reader);
        if (!writer.isNull()) {
          if (!writer.writeListHeader(2)) return false;
          if (!writer.writeTag("many",1, 0)) return false;
          if (!writer.writeListBegin(BOTTLE_TAG_INT32, static_cast<uint32_t>(_return.size()))) return false;
          std::vector<std::string> ::iterator _iterHelp;
          for (_iterHelp = _return.begin(); _iterHelp != _return.end(); ++_iterHelp)
          {
            if (!writer.writeString(*_iterHelp)) return false;
           }
          if (!writer.writeListEnd()) return false;
        }
      reader.accept();
      return true;
    }
    if (reader.noMore()) { reader.fail(); return false; }
    std::string next_tag = reader.readTag();
    if (next_tag=="") break;
    tag.append("_").append(next_tag);
  }
  return false;
}

std::vector<std::string> IRpcServer::help(const std::string& functionName) {
  bool showAll=(functionName=="--all");
  std::vector<std::string> helpString;
  if(showAll) {
    helpString.emplace_back("*** Available commands:");
    helpString.emplace_back("get_answer");
    helpString.emplace_back("set_answer");
    helpString.emplace_back("add_int");
    helpString.emplace_back("start");
    helpString.emplace_back("stop");
    helpString.emplace_back("is_running");
    helpString.emplace_back("help");
  }
  else {
    if (functionName=="get_answer") {
      helpString.emplace_back("std::int32_t get_answer() ");
      helpString.emplace_back("Get answer from server ");
      helpString.emplace_back("@return the answer ");
    }
    if (functionName=="set_answer") {
      helpString.emplace_back("bool set_answer(const std::int32_t rightAnswer) ");
      helpString.emplace_back("Set value for future answers. ");
      helpString.emplace_back("@param rightAnswer new answer ");
      helpString.emplace_back("@return true if connection was successful ");
    }
    if (functionName=="add_int") {
      helpString.emplace_back("std::int32_t add_int(const std::int32_t x) ");
      helpString.emplace_back("Add one integer to future answers. ");
      helpString.emplace_back("@param x value to add ");
      helpString.emplace_back("@return new value ");
    }
    if (functionName=="start") {
      helpString.emplace_back("bool start() ");
      helpString.emplace_back("Start service ");
      helpString.emplace_back("@return true if service started correctly ");
    }
    if (functionName=="stop") {
      helpString.emplace_back("bool stop() ");
      helpString.emplace_back("Stop service ");
      helpString.emplace_back("@return true if service stopped correctly ");
    }
    if (functionName=="is_running") {
      helpString.emplace_back("bool is_running() ");
      helpString.emplace_back("Check is service is running ");
      helpString.emplace_back("@return true/false if service is/is not running ");
    }
    if (functionName=="help") {
      helpString.emplace_back("std::vector<std::string> help(const std::string& functionName=\"--all\")");
      helpString.emplace_back("Return list of available commands, or help message for a specific function");
      helpString.emplace_back("@param functionName name of command for which to get a detailed description. If none or '--all' is provided, print list of available commands");
      helpString.emplace_back("@return list of strings (one string per line)");
    }
  }
  if ( helpString.empty()) helpString.emplace_back("Command not found");
  return helpString;
}


