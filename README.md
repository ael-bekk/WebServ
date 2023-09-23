# WebServ


<div align="center">
  <img src="https://github.com/ael-bekk/WebServ/blob/main/logo.gif" alt="WebServ Logo">
</div>

*`WebServ`* is a high-performance, lightweight web server built from scratch in `C++98`, inspired by the likes of ``Nginx``. It utilizes `websockets` and `I/O multiplexing` using the `select` mechanism to efficiently handle `HTTP methods like POST, GET, and DELETE`. This project adheres to `SOLID principles` and implements the `Singleton design pattern`, making it both robust and scalable.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Configuration](#configuration)
- [Architecture](#architecture)
- [License](#license)

## Features

- **WebSockets:** WebServ supports WebSockets, enabling real-time, bidirectional communication between clients and the server.

- **I/O Multiplexing:** Utilizing the select mechanism, WebServ efficiently manages multiple connections, making it suitable for handling high loads.

- **HTTP Methods:** WebServ handles common HTTP methods such as POST, GET, and DELETE, allowing you to build dynamic web applications.

- **Design Patterns:** The project follows SOLID principles and employs the Singleton design pattern, ensuring clean, maintainable code.

- **Data Mapping:** The entire project is mapped, simplifying data manipulation and enhancing code readability and efficiency.

## Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:

- C++98 compatible compiler

### Installation

- To install WebServ, follow these steps:

   ```sh
     git clone https://github.com/yourusername/WebServ.git
     cd WebServ
     make
   ```
- run the webserver
  ```
    ./serv /path/to/config.conf
  ```

### Configuration

WebServ is highly configurable, allowing you to use a custom configuration file. To specify a custom configuration file, create a .conf configuration file (e.g., `my_config.conf`) with the desired settings:

```conf
server {
    port 8080
    host 127.0.0.1
    server_name example.com
    error_page 404 ./www/pages_error/404.html
    error_page ... ...
    client_max_body_size 2454545454545

    location /page {
        root ./www
        allow_methods POST DELETE GET
        return 301 /
    }
    location / {
        root ./www
        index index.html
        cgi .py /usr/bin/python3
        cgi .php  /usr/bin/php-cgi
        autoindex ON
        upload Upload
        allow_methods POST DELETE GET
        return 200 file.html
    }

    location ...
    ...
    ...
}
server ...
  ...
  ...
}
```

## Architecture

WebServ is designed with a modular and efficient architecture, aimed at delivering high-performance web server capabilities. The architecture consists of several key components:

- **WebServer:**
  The core of the server responsible for handling incoming connections and HTTP requests. It manages the overall server flow and delegates specific requests to appropriate handlers.

- **RequestHandler:**
  This component processes HTTP requests, including parsing request data, routing requests to the correct endpoints, and handling various HTTP methods (e.g., GET, POST, DELETE).

- **WebSocketHandler:**
  Responsible for managing WebSocket connections and facilitating real-time, bidirectional communication between the server and clients. It enables efficient handling of WebSocket-specific protocols and events.

- **Configuration:**
  Reads and manages server settings and configurations, allowing users to customize server behavior, including port numbers, document roots, and other relevant parameters. It uses a .conf configuration file.

- **Design Patterns:**
  The project follows SOLID principles, emphasizing the importance of robust, maintainable, and scalable code. Additionally, the Singleton design pattern is employed where appropriate to ensure single instances of critical components, enhancing efficiency and resource utilization.

  - ***SOLID Principles:***

    `SOLID` is an acronym representing five design principles crucial for creating robust and maintainable software:

    - `S` => Single Responsibility Principle: Each class should have a single responsibility and reason to change.<br><br>
    - `O` => Open/Closed Principle: Software entities should be open for extension but closed for modification.<br><br>
    - `L` => Liskov Substitution Principle: Subtypes should be substitutable for their base types without altering the correctness of the program.<br><br>
    - `I` => Interface Segregation Principle: Clients should not be forced to depend on interfaces they do not use.<br><br>
    - `D` => Dependency Inversion Principle: High-level modules should not depend on low-level modules, but both should depend on abstractions.<br><br>

  - ***Singleton Design Pattern:***

    - `Singleton` ensures a class has only one instance and provides a global point of access to that instance. This is useful when exactly one object is needed to coordinate actions across the system, such as a shared resource.

  In WebServ, adhering to SOLID principles ensures clean, maintainable code, while implementing Singleton guarantees a single, globally accessible instance of critical components, enhancing efficiency and resource usage.

The interaction between these components allows WebServ to efficiently process incoming HTTP requests, handle WebSocket communications, and provide a flexible and customizable server experience.

## License
This project is licensed under the MIT 📝 - see the [LICENSE](LICENSE) file for details.
