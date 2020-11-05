#include "./config.h"

extern const char *deviceIP;
extern int devicePort;
const char DEFAULT_IP[] = "127.0.0.1";

// loop through defaults
// loop through file
// loop through env
// loop through args

static struct option options[] = {{"ip", optional_argument, NULL, 'h'},
                                  {"port", optional_argument, NULL, 'p'},
                                  {NULL, 0, NULL, 0}};

int read_arg_config(int argc, char *argv[], struct config *conf) {
  int c;
  int i = 0;
  int tmp;

  while ((c = getopt_long(argc, argv, "hp", options, &i)) != -1) {
    switch (c) {
      case 'h':
        strcpy(conf->ip, optarg);
        break;

      case 'p':
        if ((tmp = atoi(optarg)) != 0) {
          conf->port = tmp;
        }
        break;

      case '?':
        /* getopt_long already printed an error message. */
        break;
    }
  }

  return 0;
}

int read_env_config(struct config *conf) {
  int iTmp;
  char *pTmp;

  if ((pTmp = getenv("DEVICE_IP")) != NULL) {
    strcpy(conf->ip, pTmp);
  }

  if (((pTmp = getenv("DEVICE_PORT")) != NULL) && (iTmp = atoi(pTmp)) > 0) {
    conf->port = iTmp;
  }

  return 0;
}

int read_file_config(const char *cfg_file, struct config *conf) {
  config_t cfg;

  config_init(&cfg);
  const char *tmp;

  if (config_read_file(&cfg, cfg_file) != CONFIG_TRUE) {
    fprintf(stderr, "unable to read config file \"%s\"\n", cfg_file);
    config_destroy(&cfg);
    return 1;
  }

  if (config_lookup_string(&cfg, "ip", &tmp) == CONFIG_TRUE) {
    strcpy(conf->ip, tmp);
  }
  config_lookup_int(&cfg, "port", &conf->port);

  config_destroy(&cfg);

  return 0;
}
