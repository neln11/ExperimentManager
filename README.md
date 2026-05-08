# ExperimentManager

A simple C++ command-line experiment log manager

## Features

- Add experiment records
- View all experiment records
- Search experiment by model name
- Save records to CSV
- Load records from CSV
- Sort experiment by ASR
- Delete experiment records
- Modify experiment records

## Build with g++

```bash
g++ main.cpp Experiment.cpp -o experiment_manager
./experiment_manager
```

## Build with CMake

```bash
mkdir build
cd build
cmake ..
make
cd ..
./build/experiment_manager
```

## CSV Format

name,model,dataset,cleanSR,asr,targetSR,note

clean001,OpenVLA,libero_spatial,0.924,0,0.96,example clean baseline