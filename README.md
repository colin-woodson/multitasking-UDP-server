# multitasking-UDP-server
This documentation is used to explain the feature of multitasking-UDP-server project.
# 多任务UDP服务器
本文档用于解释multitasking-UDP-server项目的功能。

# Project background
Nowadays, more and more devices need to be connected to the Internet, such as smart watches and smart water meters. These devices need to periodically upload their own failure status to the cloud for device managers to check at any time, especially in places that humans cannot easily reach, such as high-voltage power towers. At this time, they need to send thanks. Perceive equipment failures, and deliver relevant information to the UDP client program to upload to the UDP server.
# 项目背景
如今，越来越多的设备需要连接网络，比如，智能手表、智能水表等。这些设备需要把自身是否故障的状态周期性的上传到云端，以供设备管理人员随时查看，尤其是在一些人类不可以轻易所达的地方，比如，高压电力塔，这时就需要通过传感谢感知设备故障，并把相关信息交给UDP客户端程序上传到UDP服务端。

# Project purpose
A large amount of work in this project is used for server-side development, using a multitasking approach to exert CPU performance; a small amount of work is used for client-side development to communicate with the server.
# 项目目的
本项目大量工作用于服务端开发，使用了多任务的方式尽可能发挥CPU性能；少量工作用于客户端开发，用于跟服务端通信。

# Technology selection
The reasons for choosing UDP instead of TCP here are: in the state reporting scenario, the tolerance for occasional reported data loss is higher; UDP datagram communication has less system overhead than TCP stream communication.
# 技术选型
这里选用UDP而不是TCP的原因：状态上报场景下对偶尔的上报数据丢失容忍度较高；UDP数据报通信相对TCP流通信而言系统开销更小。
