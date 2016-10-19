# Ubuntu Desktop (GUI) ssh manager
GUI ssh manager for Ubuntu 16.04 (not tested on below versions)

![travis-ci](https://api.travis-ci.org/Doka-NT/cpp-ssh-manager.svg?branch=master)

![alt tag](https://raw.githubusercontent.com/Doka-NT/cpp-ssh-manager/master/screenshot.png)
# Requirements
- qt 5.7

# Install
```bash
# Install qt57
sudo add-apt-repository ppa:beineri/opt-qt57-xenial
sudo apt-get update
sudo apt-get install qt57base

# cd in project root directory

# Make
source /opt/qt57/bin/qt57-env.sh
qmake -r
make
make check
```

# Run
```bash
./SshManager-3
```

# Config
config.json file will be created after first run.
Edit it as you need.
