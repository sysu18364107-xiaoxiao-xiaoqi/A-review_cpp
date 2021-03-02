
# coding: utf-8

# In[72]:


import socket
import time
#from matplotlib.pyplot import imshow


# In[73]:


tello_ip = '192.168.10.1'
tello_port = 8889
tello_address = (tello_ip , tello_port)

#udpソケット作成
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#コマンドモードを使うため'command'というテキストを投げる
udp_socket.sendto('command'.encode('utf-8'),tello_address)


# In[74]:


def init_cmd(udp_socket):
    udp_socket.sendto('command'.encode('utf-8'),tello_address)


# In[75]:


def cmd(command_str, udp_socket=udp_socket):
    udp_socket.sendto(command_str.encode('utf-8'),tello_address)
    print(command_str)


# In[76]:


def STOP(socket=udp_socket):
    socket.sendto("stop".encode('utf-8'),tello_address)


# In[69]:


#udp_socket.sendto('emrgency'.encode('utf-8'),tello_address)


# In[77]:


init_cmd(udp_socket)
time.sleep(5)



# In[87]:


cmd("land", udp_socket)
time.sleep(3)





