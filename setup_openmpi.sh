#for quick setting up of master/worker nodes on Debian live usb (requires root)


#the user provides this script with a hostname which will be used to set up this node
read -r given_hostname


#install necessary Open MPI runtime
sudo apt update
sudo apt install -y openssh-server openmpi-bin libopenmpi-dev

#change hostname so that nodes can recognise eachother
sudo hostnamectl set-hostname master


#set up SSH (necessary for Open MPI to communicate to other nodes)
sudo systemctl enable ssh
sudo systemctl start ssh
