cmake_minimum_required(VERSION 3.9)

project(ExperimentManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(experiment_manager
    main.cpp
    Experiment.cpp
)