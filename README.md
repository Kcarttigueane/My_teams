
# My Teams - Collaborative Communication Application

My Teams is a server and CLI client application designed to manage collaborative communication similar to Microsoft Teams. It follows a simple request-response model and uses TCP sockets for communication. The protocol supports a set of commands that facilitate various actions, such as logging in, sending messages, and creating teams, channels, threads, and comments.

Table of contents
=================

<!--ts-->
   * [Features](#features)
   * [Getting Started](#Getting_Started)
      * [Prerequisites](#Prerequisites)
      * [Installation](#Installation)
   * [Protocol Specification](#Protocol_Specification)
      * [Commands](#Commands)
      * [Responses](#Responses)
      * [Error Handling](#Error_Handling)
   * [Usage](#Usage)
   * [Server](#Server)
   * [Client](#Client)
   * [Security Considerations](#Security_Considerations)
   * [Built With](#Built_With)
   * [Contributions](#contributions)
<!--te-->

Features
============

* Creating, joining, and leaving a team
* Creating a user
* Creating a channel within a team
* Creating a thread in a channel
* Creating a comment in a thread
* Saving and restoring users, teams, channels, threads, and associated comments
* Personal discussions between users
* Saving and restoring personal discussions

Getting Started
===============

Follow these instructions to get a copy of the project up and running on your local machine for development and testing purposes.


Prerequisites
-------------

* A modern C compiler
* Make utility
* A Unix-based operating system (Linux, macOS)


Installation
------------

* Clone the repository:

```shell
git clone https://github.com/yourusername/myteams.git
```

* Change to the project directory:
```shell
cd myteams
```

* Compile the project:
```shell 
make
```

Usage
=====

Server
------

To start the server, run the following command in the terminal:

```shell
./myteams_server <port>
```
- `<port>`: The port number on which the server socket listens.


Client
------

To start the client, run the following command in the terminal:
```shell
./myteams_client <ip_address> <port>
```
- `<ip_address>`: The IP address of the server.
- `<port>`: The port number on which the server socket listens.


Protocol Specification
======================

Commands
--------

The MyTeams protocol supports the following commands:


|   Endpoints   |      Parameter      |   Type   | Description                       |
| :----------   | :------------------ | :------- | :-------------------------------- |
| `/help`       |                     |          | List all available command or specific command details if command_name is provided |
| `/login`      | `user_name`         | `string` | **Required**. Set the user_name used by the client |
| `/logout`     |                     |          | Disconnect the client from the server|
| `/users`      |                     |          | Get the list of all users that exist on the domain|
| `/user`       | `user_uuid`         | `string` | **Required**. Get details about the requested user |
| `/send`       | `user_uuid`         | `string` | **Required**. Send a message to a specific user |
| `/messages`   | `user_uuid`         | `string` | **Required**. List all messages exchanged with the specified use |
| `/subscribe`  | `team_uuid`         | `string` | **Required**. Subscribe to the events of a team and its subdirectories (enable reception of all events from a team) |
| `/subscribed` | `?team_uuid`        | `string` | **Optionnal**. List all subscribed teams or list all users subscribed to a team |
| `/unsubscribe`| `team_uuid`         | `string` | **Required**. Unsubscribe from a team |
| `/use`        | `?team_uuid` `?channel_uuid` `?thread_uuid`     | `string` | **Required**. Sets the command context to a team/channel/thread |


The following commands are only available in a context: (team, channel, thread) or (team, channel) or (team) or (user) or (none):


|   Endpoints   | Description                       |
| :----------   | :-----------------------------    |
| `/create` |  Based on the context, create the sub resource | 
| `/list`   |  Based on the context, list all the sub resources | 
| `/info`   |  Based on the context, display details of the current resource |



Responses
---------

```json
{
    "status": "{StatusCode}",
    "message": "List of users",
    ...specific data
}
```


Error Handling
--------------

In case of an error, the response data will contain the error message, like:

```json
{
    "status": "{StatusCode}",
    "message": "Invalid command"
}
```


Security Considerations
======================

- No password authentication is required for this project.
- A user that is not logged in should NOT be able to see connected users.
- Someone that is NOT subscribed to a team should not be able to create a thread.
- Someone that is NOT subscribed in a team should not receive events related to that team (new threads, etc.).

Built With
==========

- C programming language
- TCP sockets for network communication
- Select system call for handling multiple clients

Credits
=======

* Kevin CARTTIGUEANE: 

<a href="https://www.linkedin.com/in/kevin-carttigueane-4798a9227/"><img src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"></a>
<a href="https://github.com/Kcarttigueane"><img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white"></a>


* Jules DUTEL: 

<a href="https://www.linkedin.com/in/jules-dutel/"><img src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"></a>
<a href="https://github.com/jvlxz"><img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white"></a>

* Dylan WINTER

<a href="https://www.linkedin.com/in/dylan-winter-a28765201/"><img src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"></a>
<a href="https://github.com/DylanWTR"><img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white"></a>

