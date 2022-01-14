# Golang Crash Course

## Installation

* curl or wget the tar.gz file\ 
``curl -O https://storage.googleapis.com/golang/go1.12.9.linux-amd64.tar.gz``

* Extract\
``tar -xvf go1.12.9.linux-amd64.tar.gz``

* Adjust the permissions and move the go directory to /usr/local:
```bash
sudo chown -R root:root ./go
sudo mv go /usr/local
```

* Open ~/.profile file and add the following two lines to the bottom of the file to adjust Path and Root:

```bash
nano ~/.profile
export GOPATH=$HOME/go
export PATH=$PATH:/usr/local/go/bin:$GOPATH/bin
```
* Save the file,and execute\
``source ~/.profile``

* To verify installation is successfull run\
``go version``

## Updating existing version

* To update to the latest vesion of golang, use this beautiful script by [@udhos](https://github.com/udhos)
```bash
git clone https://github.com/udhos/update-golang
cd update-golang
sudo ./update-golang.sh
```

## Project structure

* Run the following commands(replace ``ahampriyanshu`` with whatever you like)
```bash
mkdir go && cd go
mkdir bin src && cd src
mkdir github.com && cd github.com
mkdir ahampriyanshu && cd ahampriyanshu 
mkdir me-learning-go && cd me-learning-go
```
* Your project's structure should like
```go
.
├── bin
│   └── 
└── src
    └── github.com
        └── ahampriyanshu
            └── me-learning-go
```

* At the end , the project's folder structures should like:
```go
.
├── bin
│   └── 03_packages
└── src
    └── github.com
        └── ahampriyanshu
            └── me-learning-go
                ├── 01_hello_world
                │   └── main.go
                ├── 02_var
                │   └── main.go
                ├── 03_packages
                │   ├── main.go
                │   └── strutil
                │       └── reverse.go
                ├── 04_functions
                │   └── main.go
                ├── 05_arrays_slices
                │   └── main.go
                ├── 06_conditionals
                │   └── main.go
                ├── 07_loops
                │   └── main.go
                ├── 08_maps
                │   └── main.go
                ├── 09-range
                │   └── main.go
                ├── 10_pointers
                │   └── main.go
                ├── 11_closures
                │   └── main.go
                ├── 12_structs
                │   └── main.go
                ├── 13_interfaces
                │   └── main.go
                └── 14_web
                    └── main.go
```