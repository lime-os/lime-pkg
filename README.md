<picture>
  <source media="(prefers-color-scheme: dark)" srcset=".github/banner_white.png">
  <source media="(prefers-color-scheme: light)" srcset=".github/banner_black.png">
  <img alt="LimeOS Banner">
</picture>

###

The Lime Package Manager is a lightweight and intuitive package manager designed to give you access to the repositories of countless other package managers all in one place. Its goal is to provide a clean and clear overview of available packages, ranked from most reputable to least reputable, making it easy to discover and install software from a variety of sources.

> **NOTE:** This project is still in development and is not ready for use.

## Building & Running

To build this project locally, you will need the following dependencies:

```bash
# The following command is intended for Debian based systems.
sudo apt install \
    gcc \
    make \
    libcurl4-openssl-dev \
    libncurses5-dev \
    libcjson-dev
```

Once the dependencies are installed, you can build the project by running:

```bash
make
```

## Usage

The `pkg` executable provides a command-line interface. Below are some example commands:

```bash
./pkg install <package-name>
```
