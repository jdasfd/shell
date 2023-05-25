#!/usr/bin/env bash

echo "====> Install softwares via apt-get <===="

echo "==> Disabling the release upgrader"
sudo sed -i.bak 's/^Prompt=.*$/Prompt=never/' /etc/update-manager/release-upgrades

# Virtual machines needn't this and I want life easier.
# https://help.ubuntu.com/lts/serverguide/apparmor.html
if [ "$(whoami)" == 'vagrant' ]; then
    echo "==> Disable AppArmor"
    sudo service apparmor stop
    sudo update-rc.d -f apparmor remove
fi

echo "==> Disable whoopsie"
sudo sed -i 's/report_crashes=true/report_crashes=false/' /etc/default/whoopsie
sudo service whoopsie stop

echo "==> Install linuxbrew dependences"
sudo apt-get -y update
sudo apt-get -y upgrade
sudo apt-get -y install build-essential curl file git
sudo apt-get -y install pkg-config libbz2-dev zlib1g-dev libzstd-dev libexpat1-dev

echo "==> Install other software"
sudo apt-get -y install aptitude net-tools parallel vim screen xsltproc numactl

echo "==> Install develop libraries"
sudo apt-get -y install libdb-dev libxml2-dev libssl-dev libncurses5-dev libgd-dev

echo "==> Install R related libraries"
sudo apt-get -y install libharfbuzz-dev libfribidi-dev

echo "====> Basic software installation complete! <===="