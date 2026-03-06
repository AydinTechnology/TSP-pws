#for quick setting up of master/worker nodes on Debian live usb (requires root)

#the user provides this script with a hostname which will be used to set up this node
read -r given_hostname

#install necessary Open MPI runtime
sudo apt update
sudo apt install -y openssh-server openmpi-bin libopenmpi-dev

#set up SSH (necessary for Open MPI to communicate to other nodes)
sudo systemctl enable ssh
sudo systemctl start ssh

#change hostname so that nodes can recognise eachother by name instead of hardcoded local IP adresses (no, i'm not willing to disable DHCP on my home network!)
sudo hostnamectl set-hostname $given_hostname

echo
echo Log out and in again to have the hostname change take effect
echo Todo edit "/etc/hosts" and add in the format ip hostname on each system
echo Also create a hostfile for openmpi on the master node in the format hostname slots=x in which x is amount of CPU cores available
echo Remember to run "ssh-keygen -t ed25519" on the master node
echo And on the master node "ssh-copy-id user@hostname" to each node other than the master
