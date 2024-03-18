docker run --privileged -d -p 26122:22 --name go-ubuntu20 ubuntu-ssh-go /usr/sbin/sshd -D
f9cfc2ef2a7079d9087a5bfe005ed5c63e8b6eb83a1c93ba391624bebba551c6
docker start go-ubuntu20
ssh -p 26122 root@localhost
root:root