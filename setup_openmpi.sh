#for quick setting up of master/worker nodes on Debian live usb (requires root)

#install necessary Open MPI runtime
sudo apt update
sudo apt install -y openssh-server openmpi-bin libopenmpi-dev

#allow unprotected SSH (dangerous cybersecurity-wise, but there are probably no hackers on our network)
sudo sed -i 's/PermitEmptyPasswords no/PermitEmptyPasswords yes/' /etc/ssh/sshd_config
sudo sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/' /etc/ssh/sshd_config
sudo sed -i 's/PermitRootLogin no/PermitRootLogin yes/' /etc/ssh/sshd_config

#set up SSH (necessary for Open MPI to communicate to other nodes)
sudo systemctl enable ssh
sudo systemctl start ssh
