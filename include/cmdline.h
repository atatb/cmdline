//
// Created by Kenji Nomura on 12/7/16.
//

#include <string>
#include <map>
#include <sstream>

class CmdLineParser {
 private:
  int argc;
  char **argv;
  mutable std::map<std::string, std::string> param_map;

 public:
  CmdLineParser(int _argc, char **_argv);

  bool operator[](const std::string &param) const;

  /** Throw exception if param is not found. */
  std::string operator()(const std::string &param) const;

  std::string operator()(const std::string &param, const char *def_value) const;
  std::string operator()(const std::string &param, const std::string &def_value) const;
  int operator()(const std::string &param, const int def_value) const;
  float operator()(const std::string &param, const float def_value) const;
  double operator()(const std::string &param, const double def_value) const;
  bool operator()(const std::string &param, const bool def_value) const;
  virtual std::string dump() const;
};

inline CmdLineParser::CmdLineParser(int _argc, char **_argv)
    : argc(_argc), argv(_argv) {}

inline bool CmdLineParser::operator[](const std::string &param) const {
  bool ret;
  int idx = -1;
  for (int i = 0; i < argc; i++)
    if (std::string(argv[i]) == param) {
      idx = i;
      break;
    }
  ret = (idx != -1);
  param_map.insert({param, ret ? "true" : "false"});
  return ret;
}

inline std::string CmdLineParser::operator()(const std::string &param) const {
  std::string ret;
  int idx = -1;
  for (int i = 0; i < argc; i++)
    if (std::string(argv[i]) == param) {
      idx = i;
      break;
    }
  if (idx == -1) {
    throw std::invalid_argument("parameter " + param + " is required.");
  } else {
    ret = (argv[idx + 1]);
  }
  param_map.insert({param, ret});
  return ret;
}

inline std::string CmdLineParser::operator()(const std::string &param, const char *def_value) const {
  std::string ret;
  int idx = -1;
  for (int i = 0; i < argc; i++)
    if (std::string(argv[i]) == param) {
      idx = i;
      break;
    }
  if (idx == -1) {
    ret = def_value;
  } else {
    ret = (argv[idx + 1]);
  }
  param_map.insert({param, ret});
  return ret;
}

/**
 * NOTE: https://stackoverflow.com/a/14770297
 */
inline std::string CmdLineParser::operator()(const std::string &param, const std::string &def_value) const {
  return operator()(param, def_value.c_str());
}

inline int CmdLineParser::operator()(const std::string &param, const int def_value) const {
  int ret;
  int idx = -1;
  for (int i = 0; i < argc; i++)
    if (std::string(argv[i]) == param) {
      idx = i;
      break;
    }
  if (idx == -1) {
    ret = def_value;
  } else {
    const std::string arg(argv[idx + 1]);
    ret = std::stoi(arg);
  }
  param_map.insert({param, std::to_string(ret)});
  return ret;
}

inline float CmdLineParser::operator()(const std::string &param, const float def_value) const {
  float ret;
  int idx = -1;
  for (int i = 0; i < argc; i++)
    if (std::string(argv[i]) == param) {
      idx = i;
      break;
    }
  if (idx == -1) {
    ret = def_value;
  } else {
    const std::string arg(argv[idx + 1]);
    ret = std::stof(arg);
  }
  param_map.insert({param, std::to_string(ret)});
  return ret;
}

inline double CmdLineParser::operator()(const std::string &param, const double def_value) const {
  double ret;
  int idx = -1;
  for (int i = 0; i < argc; i++)
    if (std::string(argv[i]) == param) {
      idx = i;
      break;
    }
  if (idx == -1) {
    ret = def_value;
  } else {
    const std::string arg(argv[idx + 1]);
    ret = std::stod(arg);
  }
  param_map.insert({param, std::to_string(ret)});
  return ret;
}

inline bool CmdLineParser::operator()(const std::string &param, const bool def_value) const {
  bool ret;
  int idx = -1;
  for (int i = 0; i < argc; i++)
    if (std::string(argv[i]) == param) {
      idx = i;
      break;
    }
  if (idx == -1) {
    ret = def_value;
  } else {
    const std::string arg(argv[idx + 1]);
    ret = arg == "true" || arg == "on";
  }
  param_map.insert({param, ret ? "true" : "false"});
  return ret;
}

inline std::string CmdLineParser::dump() const {
  std::stringstream ss;
  ss << std::endl;
  for (const auto &entity : param_map) {
    const auto param = entity.first;
    const auto value = entity.second;
    ss << param << " : " << value << std::endl;
  }
  return ss.str();
}
