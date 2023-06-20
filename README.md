# Messaging Application


# Build and Installation

- Dependencies: rust and cargo, MariaDB, Qt5, CMake and the g++ compiler.

For building the Qt5 QUI:
```bash
cd path/to/messasing_app
mkdir build && cd build
cmake ..
cmake --build .
```

For building the Rust main server: 
```bash
cd /messaging_app/app_server/
cargo build
```

# Run

In a terminal:
```bash
cd /messaging_app/app_server/
cargo run
```

In other terminals:
```bash
cd build
./messasing_application -c /path/to/messaging_app/config/your_config.yaml
```

# Notes

The .yaml files in the config directory are for creating GUI's with different user informations.
