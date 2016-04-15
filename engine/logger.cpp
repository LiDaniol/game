#include "logger.h"

BaseLogger::BaseLogger(std::string prefix) : prefix(prefix) {}

#ifdef _WIN32
#warning Compiling under Windows; colored loggers not available yet
BaseLogger info("[i] ");
BaseLogger warn("[!] ");
BaseLogger err ("[X] ");
BaseLogger task("[*] ");
#else
BaseLogger info("\033[36m[i]\033[0m ");
BaseLogger warn("\033[33m[!]\033[0m ");
BaseLogger err ("\033[31m[X]\033[0m ");
BaseLogger task("\033[32m[*]\033[0m ");
#endif

char endl = '\n';